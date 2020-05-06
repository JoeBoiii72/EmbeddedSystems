#include "Screen.h"
#include "Button.h"
#include "stm32f7xx_hal.h"

// menus
#include "SendMenu.h"
#include "MainMenu.h"
#include "RecvMenu.h"
#include "TypeMenu.h"
#include "NameMenu.h"
#include "ListenMenu.h"

// whoa infrared!
#include "Infrared.h"

extern GLCD_FONT GLCD_Font_16x24;
extern GLCD_FONT GLCD_Font_6x8;

void Screen::initialize()
{
	// init touch and glcd
	GLCD_Initialize();
	Touch_Initialize();
	
	// init menu screens
	send_menu.initialize();
	main_menu.initialize();
	recv_menu.initialize();
	type_menu.initialize();
	name_menu.initialize();
	listen_menu.initialize();
	
	//init perhiphalrs
	infrared.initialize();
	
	GLCD_SetBackgroundColor(GLCD_COLOR_WHITE);
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
	GLCD_SetFont(&GLCD_Font_16x24);
	GLCD_ClearScreen();
	
	// set current menu
	curMenu = &main_menu;
}

void Screen::drawString(int x, int y, const char* text)
{
	GLCD_DrawString(x,y,text);
}

void Screen::clearScreen()
{
	GLCD_ClearScreen();
}

void Screen::sleep(int millys)
{
	HAL_Delay(millys);
}

void Screen::drawButton(Button& btn)
{
	GLCD_DrawRectangle(btn.x, btn.y, btn.w, btn.h);
	GLCD_DrawString(btn.x, btn.y+16, btn.text);
}


void Screen::log(const char* text)
{
	GLCD_SetFont(&GLCD_Font_6x8);
	char cleared_line[GLCD_WIDTH];
	for(int i = 0; i < GLCD_WIDTH; i++)
		cleared_line[i] = ' ';
	GLCD_DrawString(0,GLCD_HEIGHT-9, cleared_line);
	GLCD_DrawString(2,GLCD_HEIGHT-9, text);
	GLCD_SetFont(&GLCD_Font_16x24);
}


void Screen::draw()
{
	curMenu->draw();
}


void Screen::setMenu(uint8_t menu_no)
{
	switch(menu_no)
	{
		case ::MAIN_MENU  : curMenu = &main_menu;break;
		case ::SEND_MENU  : curMenu = &send_menu;break;
		case ::RECV_MENU  : curMenu = &recv_menu;break;
		case ::TYPE_MENU  : curMenu = &type_menu;break;
		case ::NAME_MENU  : curMenu = &name_menu;break;
		case ::LISTEN_MENU: curMenu = &listen_menu;break;
	}
}

void Screen::setMenu(Menu* menu)
{
	curMenu = menu;
}

void Screen::updateTouchState()
{
	Touch_GetState(&tsc_state);
}

uint8_t Screen::isTouched()
{
	return tsc_state.pressed;
}

void Screen::handleTouch()
{
	// use current menus handler
	curMenu->handleTouch(tsc_state.x, tsc_state.y);
}

Screen screen;
