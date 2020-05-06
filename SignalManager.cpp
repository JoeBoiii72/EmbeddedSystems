#include "SignalManager.h"

void SignalManager::initialize()
{
	num_of_signals = 0;
}

void SignalManager::addSignal(const char* name, int32_t code)
{
	signals[num_of_signals++] = InfraredSignal(name, code);
}

SignalManager signal_manager;
