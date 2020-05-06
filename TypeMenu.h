#ifndef TYPE_MENU_H
#define TYPE_MENU_H

#include "Button.h"
#include "Menu.h"
#include "Keyboard.h"

class TypeMenu : public Menu
{
// members
public:
	
	Button back_btn;
	Button add_btn;
	Keyboard keyboard;
	int    text_index;
	char   text[9];
	
public:
	void initialize();
	void draw();
	void handleTouch(int x, int y);
};

extern TypeMenu type_menu;
#endif
