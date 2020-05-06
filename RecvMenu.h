#ifndef RECV_MENU_H
#define RECV_MENU_H

#include "Button.h"
#include "Menu.h"

class RecvMenu : public Menu
{
// members
public:
  Button type_btn;
	Button listen_btn;
	Button back_btn;
	
public:
	void initialize();
	void draw();
	void handleTouch(int x, int y);
};

extern RecvMenu recv_menu;
#endif
