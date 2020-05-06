#include "InfraredSignal.h"
#include <string.h>

InfraredSignal::InfraredSignal()
{
	this->signal = 0;
}

InfraredSignal::InfraredSignal(const char* name, uint32_t signal)
{
	strcpy(this->name, name);
	this->signal = signal;
}
