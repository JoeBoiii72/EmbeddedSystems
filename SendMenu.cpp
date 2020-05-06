#include "SendMenu.h"
#include "Screen.h"
#include "SignalManager.h"
#include <stdio.h>

#include "Infrared.h"

void SendMenu::initialize()
{
	
	display_offset = 0;
	
	up_btn = Button(10,10,50,50, "UP");
	down_btn = Button(10,60,50,50,"DOWN");
	back_btn = Button(10,110,50,50,"BACK");
	
	for(int i = 0; i < SIGNALS_ON_SCREEN; i++)
		send_btns[i] = Button(400, (40+(55*i)), 50, 50,"SEND");
}

void SendMenu::draw()
{
	
	char signal_num[80];
	sprintf(signal_num, "Number of signals : %d", signal_manager.num_of_signals);
	screen.drawString(90, 16, signal_num);
	
	for(int i = 0; i < SIGNALS_ON_SCREEN; i++)
	{
		char signalStr[80];
		sprintf(signalStr, "%d : %s", i+1+display_offset, signal_manager.signals[i+display_offset].name);
		screen.drawString(90, 40+(50*i)+4, signalStr);
	}
	
	for(int i = 0; i < SIGNALS_ON_SCREEN; i++)
		screen.drawButton(send_btns[i]);
	
	screen.drawButton(up_btn);
	screen.drawButton(down_btn);
	screen.drawButton(back_btn);
}

void SendMenu::handleTouch(int x, int y)
{
	if(up_btn.isPressed(x, y))
	{
		screen.log("pressed UP button");
		if(display_offset >= 1)
			display_offset--;
		screen.clearScreen();
	}
	else if(down_btn.isPressed(x, y))
	{
		screen.log("pressed DOWN button");
		// < (num of signals - num displayed)
		if(display_offset < signal_manager.num_of_signals - SIGNALS_ON_SCREEN)
			display_offset++;
		screen.clearScreen();
	}
	else if(back_btn.isPressed(x, y))
	{
		screen.clearScreen();
		screen.setMenu(MAIN_MENU);
	}
	else
	{
		for(int i = 0; i < SIGNALS_ON_SCREEN; i++)
		{
			if(send_btns[i].isPressed(x, y))
			{
				if(i+display_offset < signal_manager.num_of_signals)
				{
					char str[80];
					sprintf(str, "sending signal -> %x", signal_manager.signals[i+display_offset].signal);
					screen.log(str);
					infrared.sendSignal(signal_manager.signals[i+display_offset].signal);
					screen.sleep(200);
				}
				else
					screen.log("invalid signal!");
			}
			
		}
	}
}

SendMenu send_menu;
