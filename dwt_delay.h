#include <stdint.h>

#ifndef INC_DWT_DELAY_H_
#define INC_DWT_DELAY_H_

void DWT_Delay_Init (void);
void DWT_Delay      (volatile uint32_t microseconds);

#endif