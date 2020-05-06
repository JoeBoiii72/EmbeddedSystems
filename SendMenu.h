#ifndef SEND_MENU_H
#define SEND_MENU_H

#include "Button.h"
#include "Menu.h"

#define SIGNALS_ON_SCREEN 4

class SendMenu : public Menu
{
// members
public:
	int display_offset;
  Button up_btn;
	Button down_btn;
	Button back_btn;
	Button send_btns[SIGNALS_ON_SCREEN];
	
public:
	void initialize();
	void draw();
	void handleTouch(int x, int y);
};

extern SendMenu send_menu;
#endif