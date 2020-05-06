#include "TypeMenu.h"
#include "Screen.h"
#include <stdio.h>
#include <stdlib.h>
#include "NameMenu.h"

void TypeMenu::initialize()
{
	back_btn   = Button(340,222,50,50,"BACK");
	add_btn    = Button(410,222,50,50,"ADD");
	
	text_index = 0;

	keyboard.initialize();
	
}

void TypeMenu::draw()
{
	screen.drawButton(back_btn);
	screen.drawButton(add_btn);
	keyboard.draw();
	screen.drawString(16, 16, text);
}

void TypeMenu::handleTouch(int x, int y)
{
	if(back_btn.isPressed(x, y))
	{
		screen.clearScreen();
		screen.setMenu(MAIN_MENU);
		return;
	}
	
	if(add_btn.isPressed(x,y))
	{
		uint32_t code = (int)strtoul(text, NULL, 16); 
		name_menu.setCode(code);
		
		screen.clearScreen();
		screen.setMenu(NAME_MENU);
		return;
	}
	
	// if a key was pressed
	char pressed = keyboard.handleTouch(x,y);
	if(pressed != 0)
	{	
		// check if del key
		if(pressed == '<')
		{
			if(text_index >= 1 )
			{
				text[--text_index] = 0;
				screen.clearScreen();
			}
				
		}
		else
		{
			// if we have room left
			if(text_index < 8)
			{
				// add if its a valid hex value
				if(pressed >= '0' && pressed <= '9')
				{
					text[text_index++] = pressed;
				}
				else if(pressed >= 'a' && pressed <= 'f')
				{
					text[text_index++] = pressed - 32;
				}	
			}
				
		}		
		
		// log key pressed
		char boi[80];
		sprintf(boi, "pressed %c button", pressed);
		screen.log(boi);
	}
}

TypeMenu type_menu;
