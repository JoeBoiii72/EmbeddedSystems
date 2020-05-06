#include "Keyboard.h"
#include "Button.h"
#include "Screen.h"


void Keyboard::initialize()
{
	startX = 0;
	startY = 55;
	keySize = 40;
}

void Keyboard::draw()
{	
	const char* keys = "1234567890qwertyuiopasdfghjkl.zxcvbnm...";

	// draw keyboard
	for(int i = 0; i < 40;  i++)
	{
		const char letter[1] = {keys[i]};
		int bx = startX+((i%10))*(keySize+2);
		int by = startY+((keySize+2)*(i/10));
		Button b = Button(bx,by,keySize,keySize,letter);
		screen.drawButton(b);
	}
	
	// delete key and space bar
	const char* delKey   = "<-";
	const char* spaceBar = "  ";
	int lastY = startY+((keySize+2)*(4));
	Button spc = Button(startX,lastY,7*keySize,keySize,spaceBar);
	Button del = Button(startX+(7*keySize),lastY,keySize,keySize,delKey);
	screen.drawButton(del);
	screen.drawButton(spc);
}


char Keyboard::handleTouch(int x, int y)
{
	
	const char* keys = "1234567890qwertyuiopasdfghjkl.zxcvbnm...";
	
	for(int i = 0; i < 40;  i++)
	{
		int bx = startX+((i%10))*(keySize+2);
		int by = startY+((keySize+2)*(i/10));
		
		if(x >= bx && x <= bx + keySize)
			if(y >= by && y <= by + keySize)
				return keys[i];
	}
	
	// check space
	int spacex = startX;
	int spacey = startY+(keySize*4);
		
	if(x >= spacex && x <= spacex+(keySize*7))
		if(y >= spacey && y <= spacey+keySize)
			return ' ';
	
	int delx = startX+(keySize*7);
	int dely = startY+(keySize*4);
		
	if(x >= delx && x <= delx + keySize)
		if(y >= dely && y <= dely + keySize)
			return '<';
	
	return 0;
}