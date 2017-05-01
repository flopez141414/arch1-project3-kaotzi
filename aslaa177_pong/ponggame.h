#ifndef ponggame_included
#define ponggame_included

//Passed variables to Assembler File
extern unsigned char videomem[24*4];
extern unsigned int freq;
extern unsigned int sde;
extern unsigned int play;

//Controler setup to associated port pins 

//Controler 1
#define UP1	        BIT0      //P2.0
#define DOWN1		BIT1      //P2.1

//Controler 2 
#define UP2	        BIT3      //P2.3
#define DOWN2		BIT2      //P2.2

#define SWITCHES    (UP1 | DOWN1 | UP2 | DOWN2)

#define FIRE		BIT3      //P1.3
#define SWITCHLOW FIRE

#define PADDLEHEIGHT 5

void ponggame( void );

//Function to set score frame
void scoreboard( int player );
//function to play tone at collision
void bing( unsigned int fr );
