
//{{BLOCK(pauseMenu)

//======================================================================
//
//	pauseMenu, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 158 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 5056 + 2048 = 7616
//
//	Time-stamp: 2021-02-18, 14:49:09
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PAUSEMENU_H
#define GRIT_PAUSEMENU_H

#define pauseMenuTilesLen 5056
extern const unsigned short pauseMenuTiles[2528];

#define pauseMenuMapLen 2048
extern const unsigned short pauseMenuMap[1024];

#define pauseMenuPalLen 512
extern const unsigned short pauseMenuPal[256];

#endif // GRIT_PAUSEMENU_H

//}}BLOCK(pauseMenu)
