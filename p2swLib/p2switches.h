#ifndef p2switches_included
#define p2switches_included


#define SW5 BIT3           //switch5 is p1.3
#define SWITCHLOW SW5

unsigned int p2sw_read();
void  switch5_interrupt_handler();

void p2sw_init(unsigned char mask);

#endif // included
