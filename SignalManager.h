#ifndef SIGNAL_MANAGER_H
#define SIGNAL_MANAGER_H

#define MAX_NUM_OF_SIGNALS 16

#include "InfraredSignal.h"

// hold all signals
class SignalManager
{	
public:
	int num_of_signals;
	InfraredSignal signals[MAX_NUM_OF_SIGNALS];
	void initialize();
	void addSignal(const char* name, int32_t code);
};

extern SignalManager signal_manager;
#endif