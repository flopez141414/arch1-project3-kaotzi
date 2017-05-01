#ifndef switches_included
#define switches_included

#include "msp430.h"

#define SW5 BIT3           //switch5 is p1.3
#define SWITCHLOW SW5

unsigned int p2sw_read();
void p2sw_init(unsigned char mask);

#endif // included
