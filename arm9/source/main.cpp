#include <fat.h>

#include "common/banks.hpp"
#include "config.h"
#include "fileBrowse.h"
#include "flashcard.h"
#include "graphics/colors.h"
#include "graphics/graphics.h"
#include "loader.h"
#include "manager.h"
#include "nitrofs.h"

int main(int argc, char **argv) {
	initGraphics();
	keysSetRepeat(25,5);
	sysSetCardOwner(BUS_OWNER_ARM9);

	drawRectangle(0, 0, 256, 192, DARK_GRAY, true);
	drawRectangle(0, 0, 256, 192, DARK_GRAY, false);

	// Init filesystem
	if(!fatInitDefault()) {
		// Prints error if fatInitDefault() fails
		consoleDemoInit();
		printf("fatInitDefault() failed...");
		while(1) swiWaitForVBlank();
	}

	// Make directories
	mkdir(sdFound() ? "sd:/_nds" : "fat:/_nds", 0777);
	mkdir(sdFound() ? "sd:/_nds/pkmn-chest" : "fat:/_nds/pkmn-chest", 0777);
	mkdir(sdFound() ? "sd:/_nds/pkmn-chest/banks" : "fat:/_nds/pkmn-chest/banks", 0777);
	mkdir(sdFound() ? "sd:/_nds/pkmn-chest/backups" : "fat:/_nds/pkmn-chest/backups", 0777);

	// Try to init NitroFS from argv provided to the game when it was launched
	if(!nitroFSInit(argv[0])) {
		// If that fails, try to init NitroFS on 'pkmn-chest.nds'
		if(!nitroFSInit("pkmn-chest.nds")) {
			if(!nitroFSInit("/_nds/pkmn-chest/pkmn-chest.nds")) {
				// Prints error if nitroFSInit() fails
				consoleDemoInit();
				printf("nitroFSInit() failed...\n\n");
				printf("If you're using a cia install,\n");
				printf("you'll need:\n\n");
				printf("sdmc:/_nds/pkmn-chest/\n");
				printf("                  pkmn-chest.nds");
				while(1) swiWaitForVBlank();
			}
		}
	}
	loadFont();
	printTextCentered("Loading...", 0, 32, false);

	Config::loadConfig();
	Banks::init();
	loadGraphics();

	while(1) {
		if(!loadSave(savePath = browseForSave())) {
			drawRectangle(20, 20, 216, 152, 0xCC00, true);
			printTextCentered("Invalid save file", 0, 24, true);
			for(int i=0;i<120;i++)	swiWaitForVBlank();
			continue;
		}
		currentSaveBox = save->currentBox();
		currentBankBox = 0;
		// Decrypt the box data
		save->cryptBoxData(true);

		drawBoxScreen();
		manageBoxes();
	}

	return 0;
}