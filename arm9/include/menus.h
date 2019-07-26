#ifndef MENUS_H
#define MENUS_H

#include <nds.h>
#include <string>
#include <vector>

struct TextPos {
	int x;
	int y;
};

extern std::vector<TextPos> aMenuButtons, aMenuEmptySlotButtons, aMenuTopBarButtons, xMenuButtons;

// A Menu //////////////////////////////////////////////////////////////////////

std::string aMenuText(int buttonMode, int i);

void drawAMenuButtons(std::vector<TextPos>& buttons, int buttonMode);

int aMenu(int pkmPos, std::vector<TextPos>& buttons, int buttonMode);

// X Menu //////////////////////////////////////////////////////////////////////

void savePrompt(void);

void drawXMenuButtons(unsigned menuSelection);

bool xMenu(void);

// Misc Menus //////////////////////////////////////////////////////////////////

int selectForm(int dexNo, int currentForm);

int selectNature(int currentNature);

int selectPokeball(int currentBall);

#endif
