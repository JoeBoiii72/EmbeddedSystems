#include "Button.h"

Button::Button()
{
		this->x = -1;
		this->y = -1;
		this->w = -1;
		this->h = -1;
}

Button::Button(int x, int y, int w, int h, const char* text)
{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->text = text;
}

bool Button::isPressed(int touch_x, int touch_y)
{
	if(touch_x >= x && touch_x <= x+w)
		if(touch_y >= y && touch_y <= y+h)
			return true;
	return false;
}