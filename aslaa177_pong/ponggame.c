//pong game.c

#include <msp430.h>
#include "ponggame.h"

void ponggame( void ) 
{
	int x=1, y=16, dx=0, dy=0;
	int s,py;
	int bounce = 0;
	int speed = 5;
	int leaveout = 0;
	int winner = -1;
	int lastdir = 1;
       	int p1 = y-PADDLEHEIGHT/2;
	int p2 = 14;

	//blackout screen
	for( s = 24*4-1; s>=0; s--) {
		videomem[s] = 0;
	}
	videomem[0] = videomem[1] = videomem[2] = videomem[3] = 0xff;
	videomem[92] = videomem[93] = videomem[94] = videomem[95] = 0xff;

	do {
		LPM0;		//vsync

		//scan joystick 1
		s = ~P2IN;
		if( s & UP1   ) {p1--; lastdir = -1; }
		if( s & DOWN1 ) {p1++; lastdir = 1; }

		//scan joystick 2
		s = ~P2IN;
		if( s & UP2   ) p2--;
		if( s & DOWN2 ) p2++;

		//limit paddles
		if( p1 < 1 ) p1 = 1;
		if( p1 > (22-PADDLEHEIGHT) ) p1 = (22-PADDLEHEIGHT);

		if( p2 < 1 ) p2 = 1;
		if( p2 > (22-PADDLEHEIGHT) ) p2 = (22-PADDLEHEIGHT);

                //LED
		P1OUT = 0xff;
		videomem[y*4+(3-(x>>3))] &= ~(0x80>>(x&7));	//clear dot
		
		//draw paddles
		for( py = 22; py > 0; py-- ) {
			if( py >= p1 && py <= p1+PADDLEHEIGHT ) videomem[py*4+3] |= 0x80; else videomem[py*4+3] &= ~0x80;
			if( py >= p2 && py <= p2+PADDLEHEIGHT ) videomem[py*4  ] |= 0x01; else videomem[py*4  ] &= ~0x01;
		}
		
		//first let player one position the ball
		if( dx == 0 && dy == 0 ) {
			y = p1+PADDLEHEIGHT/2;
			if( ~P1IN & FIRE ) {
				dx = 1;
				dy = lastdir;
				bing(2);
			}
		} else if( ++leaveout >= speed ) { 
		        //move the ball otherwise
			x += dx;
			y += dy;
			leaveout = 0;
                
                //Slows down the speed of ball increase to slow down further    
                LPM0;
                LPM0;
                LPM0;
                    	//upper and lower boundaries
			if( y >= 22 || y <= 1 ) {
				dy = -dy;
				bing(4);
			}
              
			//p1 collision
			if( x <= 1 && y >= p1 && y <= (p1+PADDLEHEIGHT) ) {
				dx = -dx;
				bounce++;
				bing(2);
			}
			if( x <= 0 ) winner = 1;
			//p2 collision
			if( x >= 30 && y >= p2 && y <= (p2+PADDLEHEIGHT) ) {
				dx = -dx;
				bounce++;
				bing(3);
			}
			if( x >= 31 ) winner = 0;
                    
                        //increment speed every n bounces to get some action
			if( speed && (bounce == 2) ) { speed--; bounce = 0; }
		}

		videomem[y*4+(3-(x>>3))] |= 0x80>>(x&7);	//set dot
                
                //P2OUT = 0;

	} while( winner < 0 );

	//passes info of winner to tally on score screen
	scoreboard( winner );
}

//function to play tone at collision
void bing( unsigned int fr ) {
	sde = freq = fr;
	play = 100;
}