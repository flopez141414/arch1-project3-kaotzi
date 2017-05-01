//main.c

#include <msp430.h>
//Character file for the start up screen
#include "msp430pong_screen.ci"
#include "ponggame.h"
#include "scoreboard.h"

unsigned char videomem[24*4];   //32x24 pixels => 32/8*24 bytes

volatile unsigned int state; 
unsigned int freq;
volatile unsigned int play;
unsigned int sde;
unsigned int line;



int main (void) 
{
    int i;
    WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer
    
    //Setup ports P1 & P2  
    //Define output registers of port P1 
    P1OUT  = BIT0|BIT6;        // Init Output data of port1  -- leds         
    
    //Define the direction of pins on port P1 & P2      
    P1DIR &= ~SWITCHLOW;		/* set switch5's bits for input */
    P2DIR &= ~SWITCHES;	    	/* set switches' bits for input */
    
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
                drawboard(&videomem);		/**< send data */
	    if( (~P2IN & FIRE) != 0 || (~P2IN & FIRE) != 0 ) break;
	}
        
        //Prolong startup screen after 1st game is played
        for( y = 50;y ; y-- )
	{
                drawboard(&videomem);		/**< send data */
	}
       
       ponggame();
    }
}
