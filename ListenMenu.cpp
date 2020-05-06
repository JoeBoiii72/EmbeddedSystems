#include "ListenMenu.h"
#include "Screen.h"
#include "NameMenu.h"
#include "Infrared.h"
#include <stdio.h>

void ListenMenu::initialize()
{
	back_btn   = Button(340,222,50,50,"BACK");
	add_btn    = Button(410,222,50,50,"ADD");
	signalFoundFlag = false;	
}

void ListenMenu::draw()
{
	screen.drawButton(back_btn);
	screen.drawButton(add_btn);
	
	if(!signalFoundFlag)
	{
		while(!infrared.pollSignal())
		{
			screen.drawString(100,100,"LISTENING...");
		}
		uint32_t code = infrared.receiveSignal();
		char signalStr[80];
		sprintf(signalStr, "RECEIEVD %x", code);
		screen.drawString(100,100, signalStr);
		signalFoundFlag = true;
		name_menu.setCode(code);
	}

}

void ListenMenu::handleTouch(int x, int y)
{
	
	if(back_btn.isPressed(x, y))
	{
		screen.clearScreen();
		screen.setMenu(MAIN_MENU);
	}
	
	else if(add_btn.isPressed(x,y))
	{
		screen.clearScreen();
		screen.setMenu(NAME_MENU);
		signalFoundFlag = false;
	}
}

ListenMenu listen_menu;
