#ifndef IR_SIGNAL_H
#define IR_SIGNAL_H

#include <stdint.h>

class InfraredSignal
{	
public:
	char name[18];
	uint32_t signal;
	InfraredSignal();
	InfraredSignal(const char* name, uint32_t signal);
};
#endif