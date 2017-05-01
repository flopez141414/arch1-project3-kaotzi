//Score Screen Code

#include <msp430.h>
#include "graphics.ci"

#include "ponggame.h"
#include "scoreboard.h"


//Keeps track of players scores
unsigned int score1;
unsigned int score2;


const unsigned int song[] = {
	4,
	3,
	3,
	5,
	5,
	4,
	4
};

void drawboard (unsigned char *vidmem){
     int y;
     for( y = 0; y<24*4; y++) 
	{
	   UCB0TXBUF = vidmem[y];		/**< send data */
	}
};


void scoreboard( int player ) {
	int y;
	
	//Tally's player 1's score
	if(player==0){
	    score1++;
	}
	
	//Tally's player 2's score
	if(player==1){
	    score2++;
	}
	
	//black out screen
	for( y = 95; y>=0; y--) {
		videomem[y] = 0;
	}
        
        //draw score 
	for( y = 0; y<5; y++ ) {
		videomem[(1+y)*4+3] = score[(y)*3+2];
		videomem[(1+y)*4+2] = score[(y)*3+1];
		videomem[(1+y)*4+1] = score[y*3];
	}
	
	//draw P1
	for( y = 0; y<5; y++ ) {
		videomem[(7+y)*4+3] = player1[y*2+1];
		videomem[(7+y)*4+2] = player1[y*2];
	}

        //draw P2
        for( y = 0; y<5; y++ ) {
		videomem[(14+y)*4+3] = player2[y*2+1];
		videomem[(14+y)*4+2] = player2[y*2];
	}
	
	//draw score of player 1
	for( y = 0; y<5; y++ ) {
		videomem[(7+y)*4] = number[score1][y];
	}
        
        //draw score of player 2
	for( y = 0; y<5; y++ ) {
		videomem[(14+y)*4] = number[score2][y];
	}
	
	y = 0;
	
	while(1) {
				
		//Draws player 1 winner 
		if(score1 == 3 && score2 < 3 ){
		    for( y = 0; y<24*4; y++) 
	             {
                drawboard(videomem);		/**< send data */
		        videomem[y] = player1wins[y];
		        score1 = score2 = 0;
                drawboard(videomem);		/**< send data */
		     }
		     if( (~P2IN & FIRE) != 0) break;
		} 
				
		//P2OUT = 0;
		
		//Draws player 1 winner 
		if(score2 == 3 & score1 <3){
		    for( y = 0; y<24*4; y++) 
	             {
                drawboard(videomem);		/**< send data */
		        videomem[y] = player2wins[y];
		        score1 = score2 = 0;
                drawboard(videomem);		/**< send data */
	             }
	             if( (~P2IN & FIRE) != 0) break;
		}
		
		//P2OUT = 0xff;
		//play a melody
		if( y < (sizeof(song)>>1) && play == 0) {
			note( song[y++] );
			
		}
		
                drawboard(videomem);		/**< send data */
		if( (~P2IN & FIRE) != 0 ) break;
        }	
}

void note( unsigned int fr ) {
	sde = freq = fr;
	play = 2000;
}
