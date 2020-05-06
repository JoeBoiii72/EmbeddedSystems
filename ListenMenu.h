#ifndef LISTEN_MENU_H
#define LISTEN_MENU_H

#include "Button.h"
#include "Menu.h"
#include "Keyboard.h"

class ListenMenu : public Menu
{
// members
public:
	
	Button back_btn;
	Button add_btn;
	bool signalFoundFlag;
public:
	void initialize();
	void draw();
	void handleTouch(int x, int y);
};

extern ListenMenu listen_menu;
#endif