
//{{BLOCK(gameOverScreen)

//======================================================================
//
//	gameOverScreen, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 116 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 3712 + 2048 = 6272
//
//	Time-stamp: 2021-02-18, 14:36:08
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GAMEOVERSCREEN_H
#define GRIT_GAMEOVERSCREEN_H

#define gameOverScreenTilesLen 3712
extern const unsigned short gameOverScreenTiles[1856];

#define gameOverScreenMapLen 2048
extern const unsigned short gameOverScreenMap[1024];

#define gameOverScreenPalLen 512
extern const unsigned short gameOverScreenPal[256];

#endif // GRIT_GAMEOVERSCREEN_H

//}}BLOCK(gameOverScreen)
