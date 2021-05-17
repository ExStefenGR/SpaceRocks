
//{{BLOCK(mainMenu)

//======================================================================
//
//	mainMenu, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 334 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 10688 + 2048 = 13248
//
//	Time-stamp: 2021-02-11, 14:16:29
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAINMENU_H
#define GRIT_MAINMENU_H

#define mainMenuTilesLen 10688
extern const unsigned short mainMenuTiles[5344];

#define mainMenuMapLen 2048
extern const unsigned short mainMenuMap[1024];

#define mainMenuPalLen 512
extern const unsigned short mainMenuPal[256];

#endif // GRIT_MAINMENU_H

//}}BLOCK(mainMenu)
