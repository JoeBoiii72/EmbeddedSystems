#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Keyboard.h"

class Keyboard
{	
	int startX;
	int startY;
	int keySize;
public:
	void initialize();
	void draw();
	char handleTouch(int x, int y);
};

#endif
