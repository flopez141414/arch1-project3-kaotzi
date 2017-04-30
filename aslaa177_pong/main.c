//main.c

//#include <msp430x11x1.h>
#include <msp430.h>
//Character file for the start up screen
#include "msp430pong_screen.ci"

void pong_game( void );

unsigned char videomem[24*4];   //32x24 pixels => 32/8*24 bytes

volatile unsigned int state; 
unsigned short freq;
unsigned short play;
unsigned short sde;
unsigned short line;

//Controler setup to associated port pins 
//Controler 1
//#define FIRE1		0x20      //P2.5
#define UP1	        BIT0      //P2.0
#define DOWN1		BIT1      //P2.1

//Controler 2 
//#define FIRE2		0x10      //P2.4
#define UP2	        BIT3      //P2.3
#define DOWN2		BIT2      //P2.2

int main (void) 
{
    int i;
    WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer
    
    //Setup ports P1 & P2  
    //Define output registers of port P1 
    P1OUT  = BIT0|BIT1;        // Init Output data of port1           
    
    //Define the direction of pins on port P1 & P2      
    P1DIR  = 0XFF;             // All pins on port P1 are in output direction       
    P2DIR  = 0xC0;             // Set Pins Port2 Data-Direction (Out=1 / Inp=0)       
    
    //Selection of pins of port P1 to be used by TimerA    
    P1SEL = BIT1|BIT2;                     
    
    P1IE = 0;
    P2IE = 0;
    
    //Clock setup
    BCSCTL1 |= XTS;                         // select 8MHz Crystal
    
    do{
          IFG1 &= ~OFIFG;
          BCSCTL2 = SELM0+SELM1+DIVS1;      // select XT2CLK, smclk div 4
          BCSCTL2 |= SELS;  
                          // select XT2CLK
      }while ((IFG1 & OFIFG) != 0);
    
    TACTL  = TASSEL0+TACLR;                 // Timer init ACLK
    CCR0   = 512;                           // 64us using a 8MHz crystal 
    CCTL0  = CCIE|OUT;                      // Enables CCR0 interupt or video line interrupt
    CCTL1  = 0;
    CCTL2  = 0;
    TACTL  |= MC0;                          // Start timer up mode
    _EINT();                                // enable interrupts
    state = 0;
    
    //blackout screen
    for( i = 24*4-1; i>=0; i--) 
      {
            videomem[i] = 0;
      }
    
    while(1) 
    {
        int y;
        
        //Set startup screen
        for( y = 0; y<24*4; y++) 
	{
		videomem[y] = msp430pong_screen[y];
	}
	
	//Prolong startup screen 
	for( y = 5000;y ; y-- )
	{
	    //LPM0 places MSP430 standby until the vertical pulse intrupts
	    LPM0;                           
	    if( (~P2IN & FIRE1) != 0 || (~P2IN & FIRE2) != 0 ) break;
	}
        
        //Prolong startup screen after 1st game is played
        for( y = 50;y ; y-- )
	{
	    LPM0;
	}
       
       pong_game();
    }
}
