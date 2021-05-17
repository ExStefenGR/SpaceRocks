//Lib includes
#include <string.h>
#include <tonc.h>
#include <time.h>
#include <stdlib.h>

//Project files includes
#include "mainMenu.h"
#include "playButton.h"
#include "game.h"
#include "pauseMenu.h"
#include "gameOverScreen.h"
#include "playerSprite.h"
#include "enemySprite.h"
#include "main.h"
#include "shoot.h"
#include "healthBar0.h"
#include "healthBar1.h"
#include "healthBar1.h"
#include "healthBar2.h"
#include "healthBar3.h"
#include "enemySpriteExploding.h"
#include "enemySpriteExploding2.h"
#include "enemySpriteExploding3.h"
#include "enemySpriteExploding4.h"
#include "healthPowerUp.h"
#include "speedPowerUp.h"
#include "bulletPowerUp.h"

//Global variables
#define NUM_ENEMIES 10
#define NUM_PBULLETS 10
#define NUM_POWERUPS 3
#define NUM_HIGHSCORE 3
#define RESPAWN 300
#define BEHAVIOUR 4

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;

//Score
char display[50];
int high_score[5];
int score = 0;
bool scoreCheck = true;

//Background Moving
int backgroundX;
int backgroundY;
int pauseX = 0;
int pauseY = 0;
int framesBGX = 0;
int framesBGY = 0;

//Game

int gamestate = 0;
int frames = 0;
bool isHit = false; //options

//=========PLAYER==========
/*
OBJ_ATTR *playerSprite = &obj_buffer[1]; 
int num_Health = 3;

int frameCHK = 0;
int shieldTimer = 0;
bool isPlayerHit = false;
bool isPlayerAlive = true;
int playerX = 0;
int playerY = 0;
*/
Player player;

//=========HEALTHBARS======
OBJ_ATTR *healthBar0 = &obj_buffer[NUM_ENEMIES + NUM_PBULLETS + 2];

u32 health_pb = 0;
u32 health_tid = 144;

//=========SHOOT========
Pbullets pbullets[NUM_PBULLETS];

//=========POWER UPS======
PowerUp powerups[NUM_POWERUPS];

//Enemy - Check main.h
Enemy enemies[NUM_ENEMIES];

//declaration of functions
void obj_playButton();
void obj_player();
void obj_enemy();
void obj_shoot(int b);

void init();
void loadGameBG();

void shootUpdate();
void shootCollision();
void playerCollision();
void killEnemy(int i);
void enemyState();
void health(int h);
void createPowerUp(int i);
void powerUpCollision();
void powerUpUpdate();
void killPowerUp(int i);

int main()
{		
	//Initialize random
	srand(time(NULL));
	
	memcpy(pal_bg_mem, mainMenuPal, mainMenuPalLen);
	memcpy(&tile_mem[0][0], mainMenuTiles, mainMenuTilesLen);
	memcpy(&se_mem[30][0], mainMenuMap, mainMenuMapLen);
	
	//loading sprites on memory
	
	//playbutton
	memcpy(&tile_mem[4][0], playButtonTiles, playButtonTilesLen);
	memcpy(pal_obj_mem, playButtonPal, playButtonPalLen);
	
	//player
	memcpy(&tile_mem[4][32], playerSpriteTiles, playerSpriteTilesLen);
	memcpy(pal_obj_mem, playerSpritePal, playerSpritePalLen);
	
	//enemy
	memcpy(&tile_mem[4][36], enemySpriteTiles, enemySpriteTilesLen);
	memcpy(pal_obj_mem, enemySpritePal, enemySpritePalLen);

	//shoot
	memcpy(&tile_mem[4][44], shootTiles, shootTilesLen);
	memcpy(pal_obj_mem, shootPal, shootPalLen);	
	
	//healthbars
	memcpy(&tile_mem[4][48], healthBar0Tiles, healthBar0TilesLen);
	memcpy(pal_obj_mem, healthBar0Pal, healthBar0PalLen);
	
	memcpy(&tile_mem[4][80], healthBar1Tiles, healthBar1TilesLen);
	memcpy(pal_obj_mem, healthBar1Pal, healthBar1PalLen);
	
	memcpy(&tile_mem[4][112], healthBar2Tiles, healthBar2TilesLen);
	memcpy(pal_obj_mem, healthBar2Pal, healthBar2PalLen);
	
	memcpy(&tile_mem[4][144], healthBar3Tiles, healthBar3TilesLen);
	memcpy(pal_obj_mem, healthBar3Pal, healthBar3PalLen);
	
	//enemy explosion animation
	memcpy(&tile_mem[4][176], enemySpriteExplodingTiles, enemySpriteExplodingTilesLen);
	memcpy(pal_obj_mem, enemySpriteExplodingPal, enemySpriteExplodingPalLen);
	
	memcpy(&tile_mem[4][180], enemySpriteExploding2Tiles, enemySpriteExploding2TilesLen);
	memcpy(pal_obj_mem, enemySpriteExploding2Pal, enemySpriteExploding2PalLen);
	
	memcpy(&tile_mem[4][184], enemySpriteExploding3Tiles, enemySpriteExploding3TilesLen);
	memcpy(pal_obj_mem, enemySpriteExploding3Pal, enemySpriteExploding3PalLen);
	
	memcpy(&tile_mem[4][188], enemySpriteExploding4Tiles, enemySpriteExploding4TilesLen);
	memcpy(pal_obj_mem, enemySpriteExploding4Pal, enemySpriteExploding4PalLen);
	
	//power ups
	//bullet
	memcpy(&tile_mem[4][193], bulletPowerUpTiles, bulletPowerUpTilesLen);
	memcpy(pal_obj_mem, bulletPowerUpPal, bulletPowerUpPalLen);
	//health
	memcpy(&tile_mem[4][194], healthPowerUpTiles, healthPowerUpTilesLen);
	memcpy(pal_obj_mem, healthPowerUpPal, healthPowerUpPalLen);
	//speed
	memcpy(&tile_mem[4][195], speedPowerUpTiles, speedPowerUpTilesLen);
	memcpy(pal_obj_mem, speedPowerUpPal, speedPowerUpPalLen);
	
	oam_init(obj_buffer,128);

	REG_BG1CNT= BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_32x32;
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;
	
	//Initialize screen write and highscores variables
	int s;
	int highScoreTemp = 0;
	bool flagScore = false;
	
	for(s = 0; s < NUM_HIGHSCORE; s++)
	{
		high_score[0] = 0;
	}
	
	tte_init_se_default(0, BG_CBB(1)|BG_SBB(29));

	REG_BG1HOFS= backgroundX;
	REG_BG1VOFS= backgroundY;

	//clear the screen
	tte_write("#{es}");
	
	memcpy(pal_bg_mem, gamePal, gamePalLen);
	
	
	while(1)
	{
		vid_vsync();
		key_poll();

		switch(gamestate)
		{
			case 0:
				//Start Screen
				obj_playButton();
				
				break;
			case 1:
				//Gameplay					
				obj_player();
				obj_enemy();
				shootUpdate();
				powerUpUpdate();

				tte_write("#{P:80,0}");	
				sprintf(display,"#{cx:0x5000}Score: %d",score);
				tte_write(display);
				
				oam_copy(oam_mem,obj_buffer,128);
					
			break;
				
			case 2:
				//Pause	
				pauseX=0,pauseY=0;
				
				REG_BG1HOFS= pauseX;
				REG_BG1VOFS= pauseY;

				memcpy(pal_bg_mem, pauseMenuPal, pauseMenuPalLen);
				memcpy(&tile_mem[0][0], pauseMenuTiles, pauseMenuTilesLen);
				memcpy(&se_mem[30][0], pauseMenuMap, pauseMenuMapLen);
				
				REG_BG0CNT= BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_32x32; //Loading  background
				//REG_BG1CNT= BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_32x32;
				
				if (key_hit(KEY_START))
				{			
					loadGameBG();
					//REG_DISPCNT= DCNT_MODE0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D; //re-adding the sprites
					REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;
					
					tte_write("#{es}"); // clear screen
					gamestate = 1;
					break;
				}
			break;
				
			case 3:
				//gameover and score
								
				backgroundX = 0;
				backgroundY = 0;
				
				REG_BG1HOFS= backgroundX;
				REG_BG1VOFS= backgroundY;
								
				memcpy(pal_bg_mem, gameOverScreenPal, gameOverScreenPalLen);
				memcpy(&tile_mem[0][0], gameOverScreenTiles, gameOverScreenTilesLen);
				memcpy(&se_mem[30][0], gameOverScreenMap, gameOverScreenMapLen);
				
				REG_BG1CNT= BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_32x32; //Loading  gameover
				
				//Code to set highscores into an array
				for(s = 0; s < NUM_HIGHSCORE; s++)
				{
					if(score > high_score[s])
					{
						highScoreTemp = high_score[s];
						high_score[s] = score;
						score = highScoreTemp;
						flagScore = true;
					}
				}
				
				if(flagScore == true)
				{
					tte_write("#{es}");//clear the screen
					tte_write("#{P:58,82}");
					tte_write("#{cx:0x5000}NEW HIGH SCORE!!!");
				}else if(flagScore == false)
				{
					tte_write("#{es}");//clear the screen
					tte_write("#{P:58,82}");
					tte_write("#{cx:0x5000}HIGH SCORE RANK!!!");
				}
				
				tte_write("#{P:80,100}");	
				sprintf(display,"#{cx:0x6000}1st Score: %d",high_score[0]);
				tte_write(display);
				
				tte_write("#{P:80,115}");	
				sprintf(display,"#{cx:0x6000}2nd Score: %d",high_score[1]);
				tte_write(display);
				
				tte_write("#{P:80,130}");	
				sprintf(display,"#{cx:0x6000}3rd Score: %d",high_score[2]);
				tte_write(display);
				
				if (key_hit(KEY_START))
				{
					flagScore = false;
					score = 0;
					
					memcpy(pal_bg_mem, mainMenuPal, mainMenuPalLen);
					memcpy(&tile_mem[0][0], mainMenuTiles, mainMenuTilesLen);
					memcpy(&se_mem[30][0], mainMenuMap, mainMenuMapLen);
					
					REG_DISPCNT = DCNT_MODE0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;
					
					gamestate = 0;
				}
			oam_copy(oam_mem,obj_buffer,128);
			break;
		}
	}
	return 0;
}

void obj_playButton()
{
	player.health = 3;
	health_tid = 144;
	
	score = 0;
	
	int x = 50; //Option 1 pos x
	int y = 50; //option 1 pos y
	
	backgroundX = 0, backgroundY = 0;
	
	//Defining what the specifications for the sprites are
	u32 tid=0, pb = 0;
	
	OBJ_ATTR *playButton = &obj_buffer[0];
	
	obj_set_attr(playButton,
				 ATTR0_WIDE,
				 ATTR1_SIZE_64,
				 ATTR2_PALBANK(pb) | tid);
	obj_set_pos(playButton, x, y);
		
	x = 1;
	y = 80;
		
	if(key_hit(KEY_A))
	{
		pb = key_hit(KEY_A) ? 3:0;
		//delay
		isHit = true;
		//gamestate = 1;
	}
			
	if(key_is_up(KEY_A))
	{
		pb = key_is_down(KEY_A) ? 0:0;
	}

	if(isHit == true)
	{
		frames++;
			
		if (frames == 60)
		{
			init();
			gamestate = 1;
					
			tte_write("#{es}");//clear the screen
				
			frames = 0;
			isHit = false;
			obj_hide(playButton);
					
			memcpy(pal_bg_mem, gamePal, gamePalLen);
			memcpy(&tile_mem[0][0], gameTiles, gameTilesLen);
			memcpy(&se_mem[30][0], gameMap, gameMapLen);
			REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;
			REG_BG1CNT= BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_32x32;
		}		
	}
			
	playButton->attr2= ATTR2_BUILD(tid,pb,0);
	obj_set_pos(playButton,x,y);
	oam_copy(oam_mem, obj_buffer, 1);
}
	
void obj_player()
{
	framesBGX++;
	framesBGY++;
	player.frameCHK--;
	
	if (key_hit(KEY_START))
	{
		gamestate = 2;
		REG_DISPCNT= DCNT_MODE0 | DCNT_BG0; 	
	}
	if (key_hit(KEY_A) && player.frameCHK <= 0)
	{
		int b;
		for (b = 0; b < NUM_PBULLETS; b++)
		{
			if (player.bullets > NUM_PBULLETS)
			{
				player.bullets = NUM_PBULLETS;
			}
			if (pbullets[b].isBulletAlive == false && player.bullets > 0 && player.bullets <= NUM_PBULLETS)
			{
				obj_shoot(b);
				player.frameCHK = 10;
				break;
			}
		}
	}
	
	player.posX += player.speed*key_tri_horz();	
	player.posY += player.speed*key_tri_vert();
	
	obj_set_pos(player.sprite,player.posX,player.posY);
	
	if(framesBGX > 2)
	{
		backgroundX++;
		framesBGX = 0;
	}
	if(framesBGY > 100)
	{
		backgroundY+=1;
		framesBGY = 0;
	}
	
	REG_BG1HOFS= backgroundX;
	REG_BG1VOFS= backgroundY;
		
	// ===== POSITION CHECK =====
	if (player.posX <= 0) player.posX = 0;		
	if (player.posY <= 0) player.posY = 0;
	if (player.posX >= 224) player.posX = 224;
	if (player.posY >= 144) player.posY = 144;
	
	//===========PUP COLLISION============//
	powerUpCollision();	
	
	oam_copy(oam_mem, obj_buffer,2);
}

void obj_shoot(int b) 
{
	pbullets[b].shootX = player.posX + 15;
	pbullets[b].shootY = player.posY + 6;
	pbullets[b].isBulletAlive = true;
	obj_unhide(pbullets[b].sprite,ATTR0_REG);
	obj_set_pos(pbullets[b].sprite,pbullets[b].shootX,pbullets[b].shootY);
	
	player.bullets --;
}

void shootUpdate()
{
	int b;
	for (b = 0; b <NUM_PBULLETS; b++)
	{
		if(pbullets[b].isBulletAlive  == true)
		{
			pbullets[b].frameCHKX++;
			if(pbullets[b].frameCHKX > 2)
			{
				pbullets[b].shootX+=6;
				pbullets[b].frameCHKX = 0;
			}
			
			obj_set_pos(pbullets[b].sprite,pbullets[b].shootX,pbullets[b].shootY);
			
			if(pbullets[b].shootX >=232)
			{
				player.bullets ++;
				pbullets[b].shootX = -260;
				obj_hide(pbullets[b].sprite);
				pbullets[b].isBulletAlive = false;
			}
		}
	}
}

void loadGameBG()
{
	memcpy(&tile_mem[0][0], gameTiles, gameTilesLen);
	memcpy(&se_mem[30][0], gameMap, gameMapLen);
	
	REG_BG1CNT = BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_32x32;
	tte_init_se_default(0, BG_CBB(1)|BG_SBB(29));
}

void init()
{	
//======================SCORE=====================
	int i;
	
	//=====================Backrground===========
	backgroundX = 0;
	backgroundY = 0;
	framesBGX = 0;
	framesBGY = 0;
  
 // =====================PLAYER================
	player.sprite = & obj_buffer[1];
	player.health = 3;
	player.bullets = 1;
	player.frameCHK = 0;
	player.shieldTimer = 0;
	player.isPlayerHit = false;
	player.isPlayerAlive = true;
	player.speed = 1;

	player.posX = 40;
	player.posY = 20;
	
	player.tid = 32;
	player.pb = 0;
	
	obj_set_pos(player.sprite,player.posX,player.posY);
	
	obj_set_attr(player.sprite,
				 ATTR0_SQUARE,
				 ATTR1_SIZE_16,
				 ATTR2_PALBANK(player.pb) | player.tid);				 
	player.sprite->attr2 = ATTR2_BUILD(player.tid,player.pb,0);
	
	oam_copy(oam_mem, obj_buffer,128);
	//===========================================//	
	
	// =====================ENEMY================//		
	
	for (i = 0; i < NUM_ENEMIES; i++)
	{
		enemies[i].spawnTimer = -10;
		enemies[i].explosionTimer = 20;
		enemies[i].isExploding = false;
		enemies[i].state = rand()%BEHAVIOUR;
		enemies[i].posX = 160+i*15;
		enemies[i].posY = i*35;
		enemies[i].sprite = & obj_buffer[2+i];
		enemies[i].tid= 36;
		enemies[i].pb= 0 + i;
		enemies[i].eDead = false;
		enemies[i].speed = 1;
			
		obj_set_attr(enemies[i].sprite,
					 ATTR0_SQUARE,
					 ATTR1_SIZE_16,
					 ATTR2_PALBANK(enemies[i].pb) | enemies[i].tid);
		enemies[i].sprite->attr2 = ATTR2_BUILD(enemies[i].tid,enemies[i].pb,0);	
		obj_set_pos(enemies[i].sprite, enemies[i].posX, enemies[i].posY);
	}
	
	oam_copy(oam_mem, obj_buffer,128);
	
	//======================SHOOT================//
	
	int b;
	for (b = 0; b <NUM_PBULLETS; b++)
	{
	pbullets[b].shootX = 40;
	pbullets[b].shootY = 20;
	pbullets[b].sprite = & obj_buffer[2+NUM_ENEMIES+b];
	pbullets[b].tid = 44;
	pbullets[b].pb = 0;
	
	obj_set_attr(pbullets[b].sprite,
				 ATTR0_SQUARE,
				 ATTR1_SIZE_8,
				 ATTR2_PALBANK(pbullets[b].pb) | pbullets[b].tid);				 
	pbullets[b].sprite->attr2 = ATTR2_BUILD(pbullets[b].tid,pbullets[b].pb,0);	
	
	obj_set_pos(pbullets[b].sprite, pbullets[b].shootX, pbullets[b].shootY);
	obj_hide(pbullets[b].sprite);
	}
	
	oam_copy(oam_mem, obj_buffer,128);
	//===========HEALTHBARS========================//
	int healthX = 0;
	int healthY = 0;
	
	obj_set_pos(healthBar0, healthX, healthY);
	
	obj_set_attr(healthBar0,
				 ATTR0_WIDE,
				 ATTR1_SIZE_64,
				 ATTR2_PALBANK(health_pb) | health_tid);			 
	healthBar0->attr2 = ATTR2_BUILD(health_tid,health_pb,0);
	
	//===========POWER UPS========================//
	
	for (i = 0; i < NUM_POWERUPS; i++)
	{
		powerups[i].posX = -16;
		powerups[i].posY = -16;
		powerups[i].isPowerUpAlive = false;
		powerups[i].tid = 193+i;
		powerups[i].state = i;
		powerups[i].sprite = & obj_buffer[3+NUM_ENEMIES+NUM_PBULLETS + i];
		
		obj_set_attr(powerups[i].sprite,
				 ATTR0_SQUARE,
				 ATTR1_SIZE_8,
				 ATTR2_PALBANK(powerups[i].pb) | powerups[i].tid);				 
		powerups[i].sprite->attr2 = ATTR2_BUILD(powerups[i].tid,powerups[i].pb,0);
		
		obj_set_pos(powerups[i].sprite, powerups[i].posX, powerups[i].posY);
	}
	
	oam_copy(oam_mem, obj_buffer,128);
}

void shootCollision()
{
	int b = 0;
	int i = 0;
	
	for(i = 0; i < NUM_ENEMIES; i++)
	{	
		for(b = 0; b < NUM_PBULLETS; b++)
		{
			if ((pbullets[b].shootX >= enemies[i].posX  && pbullets[b].shootX <= enemies[i].posX+14) && (pbullets[b].shootY >= enemies[i].posY && pbullets[b].shootY <= enemies[i].posY+16))
			{
				createPowerUp(i);
				obj_hide(pbullets[b].sprite);
				pbullets[b].shootX = -250;
				pbullets[b].isBulletAlive = false;
				killEnemy(i);
				score+=100;
				player.bullets ++;
			}
			if ((pbullets[b].shootX + 4 >= enemies[i].posX  && pbullets[b].shootX + 4 <= enemies[i].posX+14) && (pbullets[b].shootY >= enemies[i].posY && pbullets[b].shootY <= enemies[i].posY+16))
			{
				createPowerUp(i);
				obj_hide(pbullets[b].sprite);
				pbullets[b].shootX = -250;
				pbullets[b].isBulletAlive = false;
				killEnemy(i);	
				score+=100;
				player.bullets ++;
			}
			if ((pbullets[b].shootX + 4 >= enemies[i].posX  && player.posX + 16 <= enemies[i].posX+14) && (pbullets[b].shootY + 4 >= enemies[i].posY && pbullets[b].shootY + 4 <= enemies[i].posY+16))
			{
				createPowerUp(i);
				obj_hide(pbullets[b].sprite);
				pbullets[b].shootX = -250;
				pbullets[b].isBulletAlive = false;
				killEnemy(i);
				score+=100;
				player.bullets ++;
			}
			if ((pbullets[b].shootX >= enemies[i].posX  && pbullets[b].shootX <= enemies[i].posX+14) && (pbullets[b].shootY + 4 >= enemies[i].posY && pbullets[b].shootY + 4 <= enemies[i].posY+16))
			{
				createPowerUp(i);
				obj_hide(pbullets[b].sprite);
				pbullets[b].shootX = -250;
				pbullets[b].isBulletAlive = false;
				killEnemy(i);
				score+=100;
				player.bullets ++;
			}
		}
	}
}

void playerCollision()
{
	int i;
	
	if (player.shieldTimer > 0)
	{
		player.shieldTimer --;
	}
	if (player.shieldTimer <= 0)
	{
		player.sprite->attr2 = ATTR2_BUILD(32,0,0);
	}
	
	for(i=0;i<NUM_ENEMIES;i++)
	{
		if ((player.posX + 2 >= enemies[i].posX  && player.posX + 2 <= enemies[i].posX+14) && (player.posY >= enemies[i].posY && player.posY <= enemies[i].posY+16) && enemies[i].eDead == false)
		{
			if (player.shieldTimer > 0)
			{
				killEnemy(i);
			}
			if (player.shieldTimer <= 0)
			{
			player.sprite->attr2 = ATTR2_BUILD(32,3,0);
			killEnemy(i);
			health(-1);
			player.shieldTimer = 600;
			}
		}
		
		if ((player.posX + 16 >= enemies[i].posX  && player.posX + 16 <= enemies[i].posX+14) && (player.posY >= enemies[i].posY && player.posY <= enemies[i].posY+16) && enemies[i].eDead == false)
		{	
			if (player.shieldTimer > 0)
			{
				killEnemy(i);
			}
			if (player.shieldTimer <= 0)
			{
			player.sprite->attr2 = ATTR2_BUILD(32,3,0);
			killEnemy(i);
			health(-1);
			player.shieldTimer = 600;
			}
		}
		
		if ((player.posX + 16 >= enemies[i].posX  && player.posX + 16 <= enemies[i].posX+14) && (player.posY+16 >= enemies[i].posY && player.posY+16 <= enemies[i].posY+16) && enemies[i].eDead == false)
		{
			if (player.shieldTimer > 0)
			{
				killEnemy(i);
			}
			if (player.shieldTimer <= 0)
			{
			player.sprite->attr2 = ATTR2_BUILD(32,3,0);
			killEnemy(i);
			health(-1);
			player.shieldTimer = 600;
			}
		}
		
		if ((player.posX + 2 >= enemies[i].posX  && player.posX +2 <= enemies[i].posX+14) && (player.posY+16 >= enemies[i].posY && player.posY+16 <= enemies[i].posY+16) && enemies[i].eDead == false)
		{	
			if (player.shieldTimer > 0)
			{
				killEnemy(i);
			}
			if (player.shieldTimer <= 0)
			{
			player.sprite->attr2 = ATTR2_BUILD(32,3,0);
			killEnemy(i);
			health(-1);
			player.shieldTimer = 600;
			}
		}
	}
}

void killEnemy(int i)
{
	enemies[i].eDead = true;
	enemies[i].explosionFrame = 0;
	enemies[i].explosionTimer = 2;
	enemies[i].isExploding = true;
	enemies[i].tid = 176;
	
	enemies[i].sprite->attr2 = ATTR2_BUILD(enemies[i].tid,enemies[i].pb,0);
	
	scoreCheck = true;
}

void obj_enemy()
{
	int posY = rand()%140;
	int i;
	
	for (i=0; i <NUM_ENEMIES; i++)
	{			
		enemies[i].spawnTimer--;
		
		if (enemies[i].eDead == true && enemies[i].spawnTimer <= 0 && enemies[i].isExploding == false)
		{
			enemies[i].tid = 36;
			enemies[i].posX = 240;
			enemies[i].posY = posY;
			enemies[i].eDead = false;
			enemies[i].isExploding = false;
			enemies[i].pb = i;
			enemies[i].sprite->attr2 = ATTR2_BUILD(enemies[i].tid,enemies[i].pb,0);
		}
				
		if(enemies[i].spawnTimer < -10)
		{
			enemies[i].spawnTimer = -10;
		}
		if(enemies[i].isExploding == true)
		{
			enemies[i].explosionTimer --;
			
			if (enemies[i].explosionTimer < 0)
			{
				enemies[i].tid = 180 + enemies[i].explosionFrame * 4;
				enemies[i].explosionFrame ++;
				
				if(enemies[i].explosionFrame > 3)
				{
					enemies[i].posX = 240;
					enemies[i].isExploding = false;
					enemies[i].spawnTimer = RESPAWN;
					enemies[i].state = rand()%BEHAVIOUR;
				}
				enemies[i].explosionTimer = 2;
			}
			// 176, 180, 184, 188
			enemies[i].sprite->attr2 = ATTR2_BUILD(enemies[i].tid,enemies[i].pb,0);
		}
		enemyState(i);
		
		playerCollision();
		shootCollision();
		
		obj_set_pos(enemies[i].sprite,enemies[i].posX,enemies[i].posY);	
	}
}

void enemyState(int i)
{
	
	enemies[i].randomBehavior = rand()%100;	
	
	if(scoreCheck == true && score != 0 && score % 2500 == 0)
	{
	enemies[i].speed ++;
	scoreCheck = false;
	}
	if(enemies[i].eDead == false && enemies[i].isExploding == false)
	{
		switch(enemies[i].state)
		{
			case 0:
				//Enemy goes right to left
				enemies[i].posX -= enemies[i].speed;	
			break;
			
			case 1:
				//enemy random behavior
				if (enemies[i].posY < 0 )
				{
					enemies[i].goingDown = true;
				}
				
				if (enemies[i].posY > 140 )
				{
					enemies[i].goingDown = false;
				}
				if (enemies[i].randomBehavior < 30)
				{
					if(enemies[i].goingDown == false)
					{
					enemies[i].posX -= enemies[i].speed;
					enemies[i].posY -= enemies[i].speed;
					}
					if(enemies[i].goingDown == true)
					{
					enemies[i].posX -= enemies[i].speed;
					enemies[i].posY += enemies[i].speed;
					}
				}	
				if ((enemies[i].randomBehavior >= 30 && enemies[i].randomBehavior <= 60))
				{
					enemies[i].posX -= enemies[i].speed;
				}
				if (enemies[i].randomBehavior > 60)
				{
					if(enemies[i].goingDown == false)
					{
					enemies[i].posY -= enemies[i].speed;
					}
					if(enemies[i].goingDown == true)
					{
					enemies[i].posY += enemies[i].speed;
					}
				}
			break; 
			
			case 2:
				//Enemy follow player
				enemies[i].posX -= enemies[i].speed;
				
				if(enemies[i].posY > player.posY +8) 
				{
					if(enemies[i].posX <= player.posX +10)
					{
					enemies[i].posY +=0;
					}	
				}
				else
				{
					enemies[i].posY += enemies[i].speed;
				}
				
				if(enemies[i].posY < player.posY - 8)
				{
					if(enemies[i].posX <= player.posX +10)
					{
					enemies[i].posY += 0;
					}
				}
				else
				{	
					enemies[i].posY -= enemies[i].speed;		
				}
			break;
			
			case 3:
				//Enemy zigzag
				if (enemies[i].posY < 0 )
				{
					enemies[i].goingDown = true;
				}
				if (enemies[i].posY > 140 )
				{
					enemies[i].goingDown = false;
				}
				if (enemies[i].goingDown == true)
				{
					enemies[i].posX -= enemies[i].speed;
					enemies[i].posY += enemies[i].speed+1;					
				}
				if (enemies[i].goingDown == false)
				{
					enemies[i].posX -= enemies[i].speed;
					enemies[i].posY -= enemies[i].speed+1;					
				}						
				if(enemies[i].posX == 0) 
				{
					enemies[i].posX = 250;	
				}
			break;
		}
		if(enemies[i].eDead == true && enemies[i].isExploding == true)
		{
			enemies[i].posX -= 3;
		}
		if (enemies[i].posX < -16)
		{
			killEnemy(i);
		}
		if (enemies[i].posX > 240)
		{
			killEnemy(i);
		}
		if (enemies[i].posY < -16)
		{
			killEnemy(i);
		}
		if (enemies[i].posY > 160)
		{
			killEnemy(i);
		}
	}
}
void health(int h)
{
	int i;
	//health reacts to player/enemy collision
	player.health = player.health + h;
	
	if(player.health > 3)
	{
		player.health = 3;
		player.sprite->attr2 = ATTR2_BUILD(32,3,0);
		player.shieldTimer = 1000;
	}
	if(player.health == 3)
	{
		health_tid = 144;
	}
	if(player.health == 2)
	{
		health_tid = 112;
	}
	if(player.health == 1)
	{
		health_tid = 80;
	}
	if(player.health == 0)
	{
		health_tid = 48;
	}
	if(player.health < 0)
	{
		gamestate = 3;
		REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1; 
		
		for(i = 1; i < 128; i++)
		{
			obj_hide(&obj_buffer[i]);
		}
	}
	healthBar0->attr2= ATTR2_BUILD(health_tid,health_pb,0);
	oam_copy(oam_mem, obj_buffer, 128);
}

void createPowerUp(int i)
{	
    int p = rand() % NUM_POWERUPS;
	
	while(powerups[p].isPowerUpAlive == true)
	{
		p = rand() % NUM_POWERUPS;
	}
	
	if(score % 500 == 0 && score != 0)
	{
	powerups[p].spawnTimer = 300;
	powerups[p].posX = enemies[i].posX;
	powerups[p].posY = enemies[i].posY;
	powerups[p].isPowerUpAlive = true;
	obj_set_pos(powerups[p].sprite, powerups[i].posX, powerups[i].posY);
	}
}

void powerUpCollision()
{
	int i;
	int playerMaxSizeX = player.posX + 16;
	int playerMaxSizeY = player.posY + 16;
	int powerUpMaxSizeX;
	int powerUpMaxSizeY;
	
	for(i=0;i<NUM_POWERUPS;i++)
	{
		powerUpMaxSizeX = powerups[i].posX + 8;
		powerUpMaxSizeY = powerups[i].posY + 8;
	
		if(playerMaxSizeX > powerups[i].posX && powerUpMaxSizeX > player.posX && 
				playerMaxSizeY > powerups[i].posY && powerUpMaxSizeY > player.posY && powerups[i].isPowerUpAlive == true)
		{
			killPowerUp(i);
			
			if(powerups[i].state == 0)
			{
				//bullet
				if(player.bullets < NUM_PBULLETS)
				{
					player.bullets ++;
				}
			}
			if(powerups[i].state == 1)
			{
				//health
				health(1);
			}
			if(powerups[i].state == 2)
			{
				//speed
				player.speed ++;
			}
		}
	}
}
void powerUpUpdate()
{
	int i;
	
	for(i=0;i<NUM_POWERUPS;i++)
	{
		if(powerups[i].isPowerUpAlive == true && powerups[i].spawnTimer > 0)
		{
			powerups[i].spawnTimer --;
			
			if(powerups[i].posX <= 0)
			{
				killPowerUp(i);
			}
			if(powerups[i].spawnTimer % 2 == 0)
			{
				powerups[i].posX --;
			}
		}
		if(powerups[i].spawnTimer <= 0)
		{
			killPowerUp(i);
		}
		
		obj_set_pos(powerups[i].sprite, powerups[i].posX, powerups[i].posY);
	}
}

void killPowerUp(int i)
{
	powerups[i].posX = -16;
	powerups[i].posY = -16;
	powerups[i].spawnTimer = 0;
	powerups[i].isPowerUpAlive = false;
	
	obj_set_pos(powerups[i].sprite, powerups[i].posX, powerups[i].posY);
}