#include "MainMenu.h"
#include "Screen.h"
#include "SignalManager.h"

void MainMenu::initialize()
{
	send_btn = Button(10,10,50,50, "SEND");
	recv_btn = Button(10,60,50,50,"RECV");
}

void MainMenu::draw()
{
	screen.drawButton(send_btn);
	screen.drawButton(recv_btn);
}

void MainMenu::handleTouch(int x, int y)
{
	if(send_btn.isPressed(x,y))
	{
		screen.clearScreen();
		screen.setMenu(SEND_MENU);
	}
	else if(recv_btn.isPressed(x, y))
	{
		screen.clearScreen();
		screen.setMenu(RECV_MENU);
	}
}

MainMenu main_menu;
