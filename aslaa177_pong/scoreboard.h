#ifndef scoreboard_included
#define scoreboard_included

//extern unsigned char videomem[24*4];
//extern unsigned int freq;
//extern unsigned int sde;
//extern unsigned volatile int play;

void drawboard (unsigned char *vidmem);

void note( unsigned int fr );

void scoreboard( int player );


#endif // included