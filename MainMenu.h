#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Button.h"
#include "Menu.h"

class MainMenu : public Menu
{
// members
public:
  Button send_btn;
	Button recv_btn;
	
public:
	void initialize();
	void draw();
	void handleTouch(int x, int y);
};

extern MainMenu main_menu;
#endif
