#ifndef IR_INTERFACE_H
#define IR_INTERFACE_H

#include <stdint.h>

class Infrared
{	
public:
	void initialize();
	bool pollSignal();
	void sendSignal(uint32_t code);
	uint32_t receiveSignal();
};

extern Infrared infrared;

#endif
