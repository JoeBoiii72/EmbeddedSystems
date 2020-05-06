#ifndef SCREEN_H
#define SCREEN_H

#include "Button.h"
#include "Menu.h"

extern "C"
{
	#include "Board_GLCD.h"
	#include "GLCD_Config.h"
	#include "Board_Touch.h"
}

enum MENU_STATE
{
	MAIN_MENU,
	SEND_MENU,
	RECV_MENU,
	TYPE_MENU,
	LISTEN_MENU,
	NAME_MENU,
};

class Screen
{	
private:
	Menu* curMenu;
	TOUCH_STATE tsc_state;
public:
	void initialize();
	void drawButton(Button& btn);
	void draw();
	void setMenu(uint8_t menu_no);
	void setMenu(Menu* menu);
	void updateTouchState();
	void drawString(int x, int y, const char* text);
	void clearScreen();
	void handleTouch();
	void sleep(int millys);
	void log(const char* text);
	uint8_t isTouched();
};

// global screen object
extern Screen screen;
#endif
