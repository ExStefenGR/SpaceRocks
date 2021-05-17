
//{{BLOCK(main)

//======================================================================
//
//
//======================================================================

#ifndef MAIN_H
#define MAIN_H

typedef struct Enemy
{
	bool eDead; 
	bool goingDown;
	bool isExploding;
	bool movedX;
	
	int explosionTimer;
	int explosionFrame;
	int posX;
	int posY;
	int randomBehavior;
	int spawnTimer;
	int state;
	int speed;
	
	OBJ_ATTR *sprite;
	
	u32 pb;
	u32 tid;
	
} Enemy;

typedef struct Player
{
	bool isPlayerHit;
	bool isPlayerAlive;
	
	int posX;
	int posY;
	int bullets;
	int health;
	int speed;
	int shieldTimer;
	int frameCHK;
	
	OBJ_ATTR *sprite;
	
	u32 pb;
	u32 tid;
	
} Player;

typedef struct Pbullets
{
	bool isBulletAlive;
	
	int frameCHKX;
	int shootX;
	int shootY;
	
	OBJ_ATTR *sprite;
	
	u32 pb;
	u32 tid;

} Pbullets;

typedef struct PowerUp
{
	bool goingDown;
	bool movedX;
	bool isPowerUpAlive;
	
	int posX;
	int posY;
	int spawnTimer;
	int speed;
	int state;
	
	OBJ_ATTR *sprite;
	
	u32 pb;
	u32 tid;
	
} PowerUp;


#endif // MAIN_H

//}}BLOCK(main)