// Lib includes
#include <string.h>
#include <tonc.h>
#include <time.h>
#include <stdlib.h>

// Project files includes
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
#include "healthBar2.h"
#include "healthBar3.h"
#include "enemySpriteExploding.h"
#include "enemySpriteExploding2.h"
#include "enemySpriteExploding3.h"
#include "enemySpriteExploding4.h"
#include "healthPowerUp.h"
#include "bulletPowerUp.h"
#include <tonc_memdef.h>

// -----------------------------------------------------------------
// Global Definitions
// -----------------------------------------------------------------
#define NUM_ENEMIES    10
#define NUM_PBULLETS   10
#define NUM_POWERUPS   3
#define NUM_HIGHSCORE  3
#define RESPAWN       300
#define BEHAVIOUR      4

// Useful screen constants
#define SCREEN_WIDTH   240
#define SCREEN_HEIGHT  160

// Video buffers and affine memory
OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer = (OBJ_AFFINE *)obj_buffer;

// Score and game variables
char display[50];
int high_score[NUM_HIGHSCORE];
int score = 0;
bool scoreCheck = true;

// Background movement
int backgroundX = 0, backgroundY = 0;
int pauseX = 0, pauseY = 0;
int framesBGX = 0, framesBGY = 0;

// Game state variables
int gamestate = 0;  // 0 = Start, 1 = Gameplay, 2 = Pause, 3 = Game Over
int frames = 0;
bool isHit = false;

// Player (structure defined in main.h)
Player player;

// Healthbar – using one object from the object buffer
OBJ_ATTR *healthBar0 = &obj_buffer[NUM_ENEMIES + NUM_PBULLETS + 2];
u32 health_pb = 0;
u32 health_tid = 144;

// Bullets and PowerUps
Pbullets pbullets[NUM_PBULLETS];
PowerUp powerups[NUM_POWERUPS];

// Enemies (structure defined in main.h)
Enemy enemies[NUM_ENEMIES];

// -----------------------------------------------------------------
// Helper Macros
// -----------------------------------------------------------------
// Use tonclib’s macros as needed; this macro is provided for our collision checks.
#define COLLIDES(ax, ay, aw, ah, bx, by, bw, bh) \
    (((ax) < (bx) + (bw)) && (((ax) + (aw)) > (bx)) && \
     ((ay) < (by) + (bh)) && (((ay) + (ah)) > (by)))

// -----------------------------------------------------------------
// Function Prototypes
// -----------------------------------------------------------------
void update_start(void);
void update_gameplay(void);
void update_pause(void);
void update_gameover(void);

void obj_playButton(void);
void obj_player(void);
void obj_enemy(void);
void obj_shoot(int b);

void init(void);
void loadGameBG(void);

void shootUpdate(void);
void shootCollision(void);
void playerCollision(void);
void killEnemy(int i);
void enemyState(int i);
void health(int h);
void createPowerUp(int i);
void powerUpCollision(void);
void powerUpUpdate(void);
void killPowerUp(int i);

// -----------------------------------------------------------------
// Added: Clear unused OAM entries
// -----------------------------------------------------------------
void clear_unused_oam(void)
{
    // Only indices 0 to 25 are used; hide the rest.
    for (int i = 26; i < 128; i++)
        obj_hide(&obj_buffer[i]);
}

// -----------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------
int main(void)
{
    int s;
    srand(time(NULL));

    // Initialise main menu assets
    dma3_cpy(pal_bg_mem, mainMenuPal, mainMenuPalLen);
    dma3_cpy(&tile_mem[0][0], mainMenuTiles, mainMenuTilesLen);
    dma3_cpy(&se_mem[30][0], mainMenuMap, mainMenuMapLen);

    // Load sprites into video memory
    dma3_cpy(&tile_mem[4][0], playButtonTiles, playButtonTilesLen);
    dma3_cpy(pal_obj_mem, playButtonPal, playButtonPalLen);
    dma3_cpy(&tile_mem[4][32], playerSpriteTiles, playerSpriteTilesLen);
    dma3_cpy(pal_obj_mem, playerSpritePal, playerSpritePalLen);
    dma3_cpy(&tile_mem[4][36], enemySpriteTiles, enemySpriteTilesLen);
    dma3_cpy(pal_obj_mem, enemySpritePal, enemySpritePalLen);
    dma3_cpy(&tile_mem[4][44], shootTiles, shootTilesLen);
    dma3_cpy(pal_obj_mem, shootPal, shootPalLen);

    // Healthbar tiles
    dma3_cpy(&tile_mem[4][48], healthBar0Tiles, healthBar0TilesLen);
    dma3_cpy(pal_obj_mem, healthBar0Pal, healthBar0PalLen);
    dma3_cpy(&tile_mem[4][80], healthBar1Tiles, healthBar1TilesLen);
    dma3_cpy(pal_obj_mem, healthBar1Pal, healthBar1PalLen);
    dma3_cpy(&tile_mem[4][112], healthBar2Tiles, healthBar2TilesLen);
    dma3_cpy(pal_obj_mem, healthBar2Pal, healthBar2PalLen);
    dma3_cpy(&tile_mem[4][144], healthBar3Tiles, healthBar3TilesLen);
    dma3_cpy(pal_obj_mem, healthBar3Pal, healthBar3PalLen);

    // Enemy explosion animations
    dma3_cpy(&tile_mem[4][176], enemySpriteExplodingTiles, enemySpriteExplodingTilesLen);
    dma3_cpy(pal_obj_mem, enemySpriteExplodingPal, enemySpriteExplodingPalLen);
    dma3_cpy(&tile_mem[4][180], enemySpriteExploding2Tiles, enemySpriteExploding2TilesLen);
    dma3_cpy(pal_obj_mem, enemySpriteExploding2Pal, enemySpriteExploding2PalLen);
    dma3_cpy(&tile_mem[4][184], enemySpriteExploding3Tiles, enemySpriteExploding3TilesLen);
    dma3_cpy(pal_obj_mem, enemySpriteExploding3Pal, enemySpriteExploding3PalLen);
    dma3_cpy(&tile_mem[4][188], enemySpriteExploding4Tiles, enemySpriteExploding4TilesLen);
    dma3_cpy(pal_obj_mem, enemySpriteExploding4Pal, enemySpriteExploding4PalLen);

    // Powerup sprites (bullet and health)
    dma3_cpy(&tile_mem[4][193], bulletPowerUpTiles, bulletPowerUpTilesLen);
    dma3_cpy(pal_obj_mem, bulletPowerUpPal, bulletPowerUpPalLen);
    dma3_cpy(&tile_mem[4][194], healthPowerUpTiles, healthPowerUpTilesLen);
    dma3_cpy(pal_obj_mem, healthPowerUpPal, healthPowerUpPalLen);

    oam_init(obj_buffer, 128);
    REG_BG1CNT = BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_32x32;
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;

    for (s = 0; s < NUM_HIGHSCORE; s++)
        high_score[s] = 0;

    tte_init_se_default(0, BG_CBB(1) | BG_SBB(29));
    REG_BG1HOFS = backgroundX;
    REG_BG1VOFS = backgroundY;
    tte_write("#{es}");
    dma3_cpy(pal_bg_mem, gamePal, gamePalLen);

    // Main loop
    while (1)
    {
        vid_vsync();
        key_poll();

        switch (gamestate)
        {
            case 0:
                update_start();
                break;
            case 1:
                update_gameplay();
                break;
            case 2:
                update_pause();
                break;
            case 3:
                update_gameover();
                break;
            default:
                return 0;
        }
        // Hide unused OAM entries before updating the hardware OAM
        clear_unused_oam();
        oam_copy(oam_mem, obj_buffer, 128);
    }
    return 0;
}

// -----------------------------------------------------------------
// State Update Functions
// -----------------------------------------------------------------
void update_start(void)
{
    obj_playButton();
}

void update_gameplay(void)
{
    obj_player();
    obj_enemy();
    shootUpdate();
    powerUpUpdate();
    // Collision routines are called once per frame
    shootCollision();
    playerCollision();

    tte_write("#{P:80,0}");
    sprintf(display, "#{cx:0x5000}Score: %d", score);
    tte_write(display);
}

void update_pause(void)
{
    pauseX = pauseY = 0;
    REG_BG1HOFS = pauseX;
    REG_BG1VOFS = pauseY;

    memcpy(pal_bg_mem, pauseMenuPal, pauseMenuPalLen);
    memcpy(&tile_mem[0][0], pauseMenuTiles, pauseMenuTilesLen);
    memcpy(&se_mem[30][0], pauseMenuMap, pauseMenuMapLen);
    REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_32x32;

    if (key_hit(KEY_START))
    {
        loadGameBG();
        REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;
        tte_write("#{es}");
        gamestate = 1;
    }
}

void update_gameover(void)
{
    int s, highScoreTemp = 0;
    bool flagScore = false;

    backgroundX = backgroundY = 0;
    REG_BG1HOFS = backgroundX;
    REG_BG1VOFS = backgroundY;

    memcpy(pal_bg_mem, gameOverScreenPal, gameOverScreenPalLen);
    memcpy(&tile_mem[0][0], gameOverScreenTiles, gameOverScreenTilesLen);
    memcpy(&se_mem[30][0], gameOverScreenMap, gameOverScreenMapLen);
    REG_BG1CNT = BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_32x32;

    for (s = 0; s < NUM_HIGHSCORE; s++)
    {
        if (score > high_score[s])
        {
            highScoreTemp = high_score[s];
            high_score[s] = score;
            score = highScoreTemp;
            flagScore = true;
        }
    }
    if (flagScore)
    {
        tte_write("#{es}");
        tte_write("#{P:58,82}");
        tte_write("#{cx:0x5000}NEW HIGH SCORE!!!");
    }
    else
    {
        tte_write("#{es}");
        tte_write("#{P:58,82}");
        tte_write("#{cx:0x5000}HIGH SCORE RANK!!!");
    }
    tte_write("#{P:80,100}");
    sprintf(display, "#{cx:0x6000}1st Score: %d", high_score[0]);
    tte_write(display);
    tte_write("#{P:80,115}");
    sprintf(display, "#{cx:0x6000}2nd Score: %d", high_score[1]);
    tte_write(display);
    tte_write("#{P:80,130}");
    sprintf(display, "#{cx:0x6000}3rd Score: %d", high_score[2]);
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
}

// -----------------------------------------------------------------
// Gameplay Object Functions
// -----------------------------------------------------------------
void obj_playButton(void)
{
    // Reset game parameters for a new game
    player.health = 3;
    health_tid = 144;
    score = 0;
    backgroundX = backgroundY = 0;

    int x = 50, y = 50;
    u32 tid = 0, pb = 0;

    OBJ_ATTR* playButton = &obj_buffer[0];
    obj_set_attr(playButton, ATTR0_WIDE, ATTR1_SIZE_64, ATTR2_PALBANK(pb) | tid);
    obj_set_pos(playButton, x, y);

    // Provide visual feedback for key press
    x = 1; y = 80;
    if (key_hit(KEY_A))
    {
        pb = 3;
        isHit = true;
    }
    else if (key_is_up(KEY_A))
    {
        pb = 0;
    }
    if (isHit)
    {
        frames++;
        if (frames >= 60)
        {
            init();
            gamestate = 1;
            tte_write("#{es}");
            frames = 0;
            isHit = false;
            obj_hide(playButton);
            memcpy(pal_bg_mem, gamePal, gamePalLen);
            memcpy(&tile_mem[0][0], gameTiles, gameTilesLen);
            memcpy(&se_mem[30][0], gameMap, gameMapLen);
            REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;
            REG_BG1CNT = BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_32x32;
        }
    }
    playButton->attr2 = ATTR2_BUILD(tid, pb, 0);
    obj_set_pos(playButton, x, y);
}

void obj_player(void)
{
    framesBGX++; framesBGY++;
    player.frameCHK--;

    if (key_hit(KEY_START))
    {
        gamestate = 2;
        REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
    }
    if (key_hit(KEY_A) && player.frameCHK <= 0)
    {
        for (int b = 0; b < NUM_PBULLETS; b++)
        {
            if (player.bullets > NUM_PBULLETS)
                player.bullets = NUM_PBULLETS;
            if (!pbullets[b].isBulletAlive && player.bullets > 0)
            {
                obj_shoot(b);
                player.frameCHK = 10;
                break;
            }
        }
    }

    player.posX += player.speed * key_tri_horz();
    player.posY += player.speed * key_tri_vert();

    // Clamp player within screen bounds (adjust if desired)
    if (player.posX < 0) player.posX = 0;
    if (player.posY < 0) player.posY = 0;
    if (player.posX > 224) player.posX = 224;
    if (player.posY > 144) player.posY = 144;

    obj_set_pos(player.sprite, player.posX, player.posY);

    if (framesBGX > 2) { backgroundX++; framesBGX = 0; }
    if (framesBGY > 100) { backgroundY++; framesBGY = 0; }

    REG_BG1HOFS = backgroundX;
    REG_BG1VOFS = backgroundY;

    // Check for power-up collisions
    powerUpCollision();
}

void obj_shoot(int b)
{
    pbullets[b].shootX = player.posX + 15;
    pbullets[b].shootY = player.posY + 6;
    pbullets[b].isBulletAlive = true;
    obj_unhide(pbullets[b].sprite, ATTR0_REG);
    obj_set_pos(pbullets[b].sprite, pbullets[b].shootX, pbullets[b].shootY);
    player.bullets--;
}

void shootUpdate(void)
{
    for (int b = 0; b < NUM_PBULLETS; b++)
    {
        if (pbullets[b].isBulletAlive)
        {
            pbullets[b].frameCHKX++;
            if (pbullets[b].frameCHKX > 2)
            {
                pbullets[b].shootX += 6;
                pbullets[b].frameCHKX = 0;
            }
            obj_set_pos(pbullets[b].sprite, pbullets[b].shootX, pbullets[b].shootY);
            if (pbullets[b].shootX >= 232)
            {
                player.bullets++;
                pbullets[b].shootX = -260;
                obj_hide(pbullets[b].sprite);
                pbullets[b].isBulletAlive = false;
            }
        }
    }
}

void shootCollision(void)
{
    // Check each bullet against every enemy using the COLLIDES macro.
    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        for (int b = 0; b < NUM_PBULLETS; b++)
        {
            if (pbullets[b].isBulletAlive &&
                COLLIDES(pbullets[b].shootX, pbullets[b].shootY, 4, 4,
                         enemies[i].posX, enemies[i].posY, 15, 17))
            {
                createPowerUp(i);
                obj_hide(pbullets[b].sprite);
                pbullets[b].shootX = -250;
                pbullets[b].isBulletAlive = false;
                killEnemy(i);
                score += 100;
                player.bullets++;
            }
        }
    }
}

void loadGameBG(void)
{
    memcpy(&tile_mem[0][0], gameTiles, gameTilesLen);
    memcpy(&se_mem[30][0], gameMap, gameMapLen);
    REG_BG1CNT = BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_32x32;
    tte_init_se_default(0, BG_CBB(1) | BG_SBB(29));
}

void init(void)
{
    int i;
    // Reset background and frame counters
    backgroundX = backgroundY = framesBGX = framesBGY = 0;

    // Initialise Player
    player.sprite = &obj_buffer[1];
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
    obj_set_pos(player.sprite, player.posX, player.posY);
    obj_set_attr(player.sprite, ATTR0_SQUARE, ATTR1_SIZE_16,
                 ATTR2_PALBANK(player.pb) | player.tid);
    player.sprite->attr2 = ATTR2_BUILD(player.tid, player.pb, 0);

    // Initialise Enemies
    for (i = 0; i < NUM_ENEMIES; i++)
    {
        enemies[i].spawnTimer = -10;
        enemies[i].explosionTimer = 20;
        enemies[i].isExploding = false;
        enemies[i].state = rand() % BEHAVIOUR;
        enemies[i].posX = 160 + i * 15;
        enemies[i].posY = i * 35;
        enemies[i].goingDown = true;
        enemies[i].sprite = &obj_buffer[2 + i];
        enemies[i].tid = 36;
        enemies[i].pb = i;
        enemies[i].eDead = false;
        enemies[i].speed = 1;
        obj_set_attr(enemies[i].sprite, ATTR0_SQUARE, ATTR1_SIZE_16,
                     ATTR2_PALBANK(enemies[i].pb) | enemies[i].tid);
        enemies[i].sprite->attr2 = ATTR2_BUILD(enemies[i].tid, enemies[i].pb, 0);
        obj_set_pos(enemies[i].sprite, enemies[i].posX, enemies[i].posY);
    }

    // Initialise Bullets
    for (int b = 0; b < NUM_PBULLETS; b++)
    {
        pbullets[b].shootX = 40;
        pbullets[b].shootY = 20;
        pbullets[b].sprite = &obj_buffer[2 + NUM_ENEMIES + b];
        pbullets[b].tid = 44;
        pbullets[b].pb = 0;
        obj_set_attr(pbullets[b].sprite, ATTR0_SQUARE, ATTR1_SIZE_8,
                     ATTR2_PALBANK(pbullets[b].pb) | pbullets[b].tid);
        pbullets[b].sprite->attr2 = ATTR2_BUILD(pbullets[b].tid, pbullets[b].pb, 0);
        obj_set_pos(pbullets[b].sprite, pbullets[b].shootX, pbullets[b].shootY);
        obj_hide(pbullets[b].sprite);
    }

    // Initialise Health Bar
    {
        int healthX = 0, healthY = 0;
        obj_set_pos(healthBar0, healthX, healthY);
        obj_set_attr(healthBar0, ATTR0_WIDE, ATTR1_SIZE_64,
                     ATTR2_PALBANK(health_pb) | health_tid);
        healthBar0->attr2 = ATTR2_BUILD(health_tid, health_pb, 0);
    }

    // Initialise Power Ups
    for (i = 0; i < NUM_POWERUPS; i++)
    {
        powerups[i].posX = -16;
        powerups[i].posY = -16;
        powerups[i].isPowerUpAlive = false;
        powerups[i].tid = 193 + i;
        powerups[i].state = i;
        powerups[i].sprite = &obj_buffer[3 + NUM_ENEMIES + NUM_PBULLETS + i];
        obj_set_attr(powerups[i].sprite, ATTR0_SQUARE, ATTR1_SIZE_8,
                     ATTR2_PALBANK(powerups[i].pb) | powerups[i].tid);
        powerups[i].sprite->attr2 = ATTR2_BUILD(powerups[i].tid, powerups[i].pb, 0);
        obj_set_pos(powerups[i].sprite, powerups[i].posX, powerups[i].posY);
    }
}

void playerCollision(void)
{
    if (player.shieldTimer > 0)
        player.shieldTimer--;
    else
        player.sprite->attr2 = ATTR2_BUILD(32, 0, 0);

    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        if (!enemies[i].eDead &&
            COLLIDES(player.posX + 2, player.posY, 14, 16,
                      enemies[i].posX, enemies[i].posY, 15, 17))
        {
            if (player.shieldTimer > 0)
                killEnemy(i);
            else
            {
                player.sprite->attr2 = ATTR2_BUILD(32, 3, 0);
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
    enemies[i].sprite->attr2 = ATTR2_BUILD(enemies[i].tid, enemies[i].pb, 0);
    scoreCheck = true;
}

void obj_enemy(void)
{
    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        enemies[i].spawnTimer--;
        if (enemies[i].eDead && enemies[i].spawnTimer <= 0 && !enemies[i].isExploding)
        {
            enemies[i].tid = 36;
            enemies[i].posX = 240;
            enemies[i].posY = rand() % 140;
            enemies[i].eDead = false;
            enemies[i].isExploding = false;
            enemies[i].pb = i;
            enemies[i].sprite->attr2 = ATTR2_BUILD(enemies[i].tid, enemies[i].pb, 0);
        }
        if (enemies[i].spawnTimer < -10)
            enemies[i].spawnTimer = -10;
        // Explosion animation update
        if (enemies[i].isExploding)
        {
            enemies[i].explosionTimer--;
            if (enemies[i].explosionTimer < 0)
            {
                enemies[i].tid = 180 + enemies[i].explosionFrame * 4;
                enemies[i].explosionFrame++;
                if (enemies[i].explosionFrame > 3)
                {
                    enemies[i].posX = 240;
                    enemies[i].isExploding = false;
                    enemies[i].spawnTimer = RESPAWN;
                    enemies[i].state = rand() % BEHAVIOUR;
                }
                enemies[i].explosionTimer = 2;
            }
            enemies[i].sprite->attr2 = ATTR2_BUILD(enemies[i].tid, enemies[i].pb, 0);
        }
        enemyState(i);
        obj_set_pos(enemies[i].sprite, enemies[i].posX, enemies[i].posY);
    }
}

void enemyState(int i)
{
    enemies[i].randomBehavior = rand() % 100;
    if (scoreCheck && score != 0 && score % 2500 == 0)
    {
        enemies[i].speed++;
        scoreCheck = false;
    }
    if (!enemies[i].eDead && !enemies[i].isExploding)
    {
        switch (enemies[i].state)
        {
            case 0:
                enemies[i].posX -= enemies[i].speed;
                break;
            case 1:
                if (enemies[i].posY < 0)
                    enemies[i].goingDown = true;
                if (enemies[i].posY > 140)
                    enemies[i].goingDown = false;
                if (enemies[i].randomBehavior < 30)
                {
                    enemies[i].posX -= enemies[i].speed;
                    enemies[i].posY += (enemies[i].goingDown ? enemies[i].speed : -enemies[i].speed);
                }
                else if (enemies[i].randomBehavior <= 60)
                    enemies[i].posX -= enemies[i].speed;
                else
                    enemies[i].posY += (enemies[i].goingDown ? enemies[i].speed : -enemies[i].speed);
                break;
            case 2:
                enemies[i].posX -= enemies[i].speed;
                if (enemies[i].posY < player.posY)
                    enemies[i].posY += enemies[i].speed;
                else if (enemies[i].posY > player.posY)
                    enemies[i].posY -= enemies[i].speed;
                break;
            case 3:
                if (enemies[i].posY < 0)
                    enemies[i].goingDown = true;
                if (enemies[i].posY > 140)
                    enemies[i].goingDown = false;
                enemies[i].posX -= enemies[i].speed;
                enemies[i].posY += (enemies[i].goingDown ? enemies[i].speed + 1 : -enemies[i].speed - 1);
                if (enemies[i].posX == 0)
                    enemies[i].posX = 250;
                break;
            default:
                if (enemies[i].posX < -16 || enemies[i].posX > 240 ||
                    enemies[i].posY < -16 || enemies[i].posY > 160)
                    killEnemy(i);
                break;
        }
    }
}

void health(int h)
{
    int i;
    player.health += h;
    if (player.health > 3)
    {
        player.health = 3;
        player.sprite->attr2 = ATTR2_BUILD(32, 3, 0);
        player.shieldTimer = 1000;
    }
    if (player.health == 3)
        health_tid = 144;
    else if (player.health == 2)
        health_tid = 112;
    else if (player.health == 1)
        health_tid = 80;
    else if (player.health == 0)
        health_tid = 48;
    if (player.health < 0)
    {
        gamestate = 3;
        REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1;
        for (i = 1; i < 128; i++)
            obj_hide(&obj_buffer[i]);
    }
    healthBar0->attr2 = ATTR2_BUILD(health_tid, health_pb, 0);
    oam_copy(oam_mem, obj_buffer, 128);
}

void createPowerUp(int i)
{
    int p = rand() % NUM_POWERUPS;
    while (powerups[p].isPowerUpAlive)
        p = rand() % NUM_POWERUPS;
    if ((score % 500 == 0) && (score != 0))
    {
        powerups[p].spawnTimer = 300;
        powerups[p].posX = enemies[i].posX;
        powerups[p].posY = enemies[i].posY;
        powerups[p].isPowerUpAlive = true;
        obj_set_pos(powerups[p].sprite, powerups[p].posX, powerups[p].posY);
    }
}

void powerUpCollision(void)
{
    for (int i = 0; i < NUM_POWERUPS; i++)
    {
        if (powerups[i].isPowerUpAlive &&
            COLLIDES(player.posX, player.posY, 16, 16,
                      powerups[i].posX, powerups[i].posY, 8, 8))
        {
            killPowerUp(i);
            if (powerups[i].state == 0)
            {
                if (player.bullets < NUM_PBULLETS)
                    player.bullets++;
            }
            else if (powerups[i].state == 1)
                health(1);
            else if (powerups[i].state == 2)
                player.speed++;
        }
    }
}

void powerUpUpdate(void)
{
    for (int i = 0; i < NUM_POWERUPS; i++)
    {
        if (powerups[i].isPowerUpAlive && powerups[i].spawnTimer > 0)
        {
            powerups[i].spawnTimer--;
            if (powerups[i].posX <= 0)
                killPowerUp(i);
            if (powerups[i].spawnTimer % 2 == 0)
                powerups[i].posX--;
        }
        if (powerups[i].spawnTimer <= 0)
            killPowerUp(i);
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
