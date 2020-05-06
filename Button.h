#ifndef BUTTON_H
#define BUTTON_H

class Button
{
// members
public:
	int x;
	int y;
	int w;
	int h;
	const char* text;

// methods
public:
	Button();
	Button(int x, int y, int w, int h, const char* test);
	bool isPressed(int touch_x, int touch_y);
};
#endif