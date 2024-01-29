#include "LPC17xx.h"
//for Pclk_Timer0 we have : 100M / 4 = 25MHz
void TIMER3_IRQHandler (void) 
{  
  LPC_TIM3->IR=1;								//To clear flag
	LPC_TIM3->IR=2;								//To clear flag
	LPC_GPIO0->FIOPIN++;
}

void init_timer3()
{
	LPC_PINCON->PINSEL1 |= (0x3<<14);
	LPC_TIM3->PR=0;						//To set prescaler to zero 
	LPC_TIM3->MR0=8;						//Timer interval
	LPC_TIM3->MR1=8+14;		//Timer interval
	LPC_TIM3->MCR=(3<<3) | (1);				    //To have interrupt and reset on MR0
	NVIC_EnableIRQ(TIMER3_IRQn);
	LPC_TIM3->CTCR=1;						//To Counte with both edge of cap3.0
	LPC_TIM3->TCR=1;
}

int main()
{	    		
  LPC_GPIO0->FIODIR=0xFFFFFFFF;
  init_timer3( );
  while(1){}
}