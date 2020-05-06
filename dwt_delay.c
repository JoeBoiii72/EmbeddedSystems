#include "stm32f7xx_hal.h"
#include "dwt_delay.h"

/*
https://community.st.com/s/question/0D50X0000BGl1A2SQJ/dwtlibrary-not-working-for-stm32f767
*/

volatile unsigned int *DWT_CYCCNT   = (volatile unsigned int *)0xE0001004; // address of the register
volatile unsigned int *DWT_CONTROL  = (volatile unsigned int *)0xE0001000; // address of the register
volatile unsigned int *DWT_LAR      = (volatile unsigned int *)0xE0001FB0; // address of the register
volatile unsigned int *SCB_DEMCR    = (volatile unsigned int *)0xE000EDFC; // address of the register
 

void DWT_Delay_Init(void)
{
  *DWT_LAR      = 0xC5ACCE55; // unlock
  *SCB_DEMCR   |= 0x01000000; // enable scb/debug
  *DWT_LAR      = 0xC5ACCE55; // unlock
  *DWT_CYCCNT   = 0;          // reset the counter
  *DWT_CONTROL |= 1 ;         // enable the counter
}


void DWT_Delay(volatile uint32_t microseconds) // microseconds
{
	microseconds *= (SystemCoreClock/1000000);
	
  unsigned int start, current;
 
  start = *DWT_CYCCNT;
 
  do
  {
    current = *DWT_CYCCNT;
  } while((current - start) < microseconds);
}
