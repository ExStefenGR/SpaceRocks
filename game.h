
//{{BLOCK(game)

//======================================================================
//
//	game, 512x256@4, 
//	+ palette 256 entries, not compressed
//	+ 90 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 512 + 2880 + 4096 = 7488
//
//	Time-stamp: 2021-02-11, 15:31:02
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GAME_H
#define GRIT_GAME_H

#define gameTilesLen 2880
extern const unsigned short gameTiles[1440];

#define gameMapLen 4096
extern const unsigned short gameMap[2048];

#define gamePalLen 512
extern const unsigned short gamePal[256];

#endif // GRIT_GAME_H

//}}BLOCK(game)
