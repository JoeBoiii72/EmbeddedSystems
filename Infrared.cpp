#include "Infrared.h"

extern "C" {
	#include "dwt_delay.h"
	#include "stm32f7xx_hal.h"
}

// signal is active low
#define IR_ACTIVE   GPIO_PIN_RESET
#define IR_INACTIVE GPIO_PIN_SET

#define IR_SEND_PORT GPIOC
#define IR_SEND_PIN  GPIO_PIN_6

#define IR_RECV_PORT GPIOC
#define IR_RECV_PIN  GPIO_PIN_7

void Infrared::initialize()
{
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	DWT_Delay_Init();
	
	// emitter
	GPIO_InitTypeDef gpio; 
	gpio.Pin       = IR_SEND_PIN;
	gpio.Mode      = GPIO_MODE_OUTPUT_PP;
	gpio.Speed     = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(IR_SEND_PORT, &gpio);
	
	// receiver
	gpio.Pin       = IR_RECV_PIN;
	gpio.Mode      = GPIO_MODE_INPUT;
	gpio.Pull      = GPIO_PULLUP;
	HAL_GPIO_Init(IR_RECV_PORT, &gpio);
}

/**
RECV STUFF
**/

//true if signal detected
//false if not
bool Infrared::pollSignal()
{
	return !HAL_GPIO_ReadPin(IR_RECV_PORT, IR_RECV_PIN);
}

// receive data using NEC protocol
uint32_t Infrared::receiveSignal()
{
	uint32_t code = 0;
	uint32_t mask = 1U << 31;
	
	// already seen lead edge of start pulse

	// 9ms of active, whilst its active, wait
	while (HAL_GPIO_ReadPin (IR_RECV_PORT, IR_RECV_PIN) == IR_ACTIVE)
		continue;

	 // 4.5ms of inactive, whilst its inactive, wait
	while (HAL_GPIO_ReadPin (IR_RECV_PORT, IR_RECV_PIN) == IR_INACTIVE)
		continue; 
	
	while(mask != 0)
	{
		while (HAL_GPIO_ReadPin (IR_RECV_PORT, IR_RECV_PIN) == IR_ACTIVE)
				continue;
			
		DWT_Delay(562 + (563/2));
		
		if(HAL_GPIO_ReadPin (IR_RECV_PORT, IR_RECV_PIN) == IR_INACTIVE)
		{
			code |= mask;
			
			while (HAL_GPIO_ReadPin (IR_RECV_PORT, IR_RECV_PIN) == IR_INACTIVE)
					continue;
		}
		
		mask >>= 1;
	}

	return code;
}


/**
SENDING STUFF
**/
static void MARK(uint32_t time_micros, uint32_t Khz)
{
	
	int pulse_length   = 1000/Khz;
	int timeHigh       = pulse_length / 2;
	int timeLow        = pulse_length / 2;
	int pulse_number   = time_micros  / pulse_length;
	
	for(int i = 0; i < pulse_number; i++)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
		DWT_Delay (timeHigh);
		
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
		DWT_Delay (timeLow);
	}
}

static void SPACE(uint32_t time_micros)
{
	DWT_Delay(time_micros);
}

void Infrared::sendSignal(uint32_t code)
{
	/*
	uint32_t mask = 1U << 31;
	
	// header
	MARK(9000, 38);
	SPACE(4500);
	
	while ( mask != 0 )
	{
  	MARK(562, 38);
		SPACE( (code & mask) ? 1687 : 562 );
		mask >>= 1;
	}
	
	// end of transmission
	MARK(562, 38);
	SPACE(10000);*/
	uint32_t mask = 1U << 31;
	
	// header
	MARK(4633, 38);
	SPACE(4321);
	
	while ( mask != 0 )
	{
  	MARK(712, 38);
		SPACE( (code & mask) ? 1520 : 398 );
		mask >>= 1;
	}
	
	// end of transmission
	MARK(712, 38);
	SPACE(10000);
}

Infrared infrared;
