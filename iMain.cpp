
/*
	Ahsanullah University Of Science & Technology
	
	Department Of Computer Science & Engineering

	"Naruto - The Unfinished Page"
	Course No : CSE 1200 (Game Project)
	1st Year 2nd Semester

	Authors: 
	Asif Imtiaz Shaafi
	Sudipta Biswas
	Sayef Reyadh Khan
*/
# include "iGraphics.h"
#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<string>
#include<cmath>
#include<map>
#include<algorithm>
using namespace std;

boolean musicOn = true;

#define PI 3.14159265
#define screenHeight 665 
#define screenWidth 1200  
#define screenWidthCut 10 
#define screenDifference 120  
#define heightDifference 97 
#define jump 300 
#define screenSpeed 10
#define groundSpeed 12
#define jumpSpeed 15
//The Below Block DEFINE Controls the iSetTimer
#define narutoCondition 3
#define screenCondition 1
#define groundCondition 1
#define narutoJumpCondition 1
#define birdoneCondition 4 
#define video1Condition 3
#define obstracleCondition 4
#define groundEnemyNumber 3
#define birdOneNumber 6
#define BossOneCondition 15 // controls the boss interval
#define BossOneConditionCheck 3
#define BossBulletHit 1
#define BossBirdMoveFront 15
int mposx, mposy;

int t1; // iSetTimer variable
boolean isPaused = false;
boolean isPower = false;
boolean isPausedPower = false;

/// Structure for saving scores
struct players
{
	char name[20];
	int playerScore;
}plyScore[12], temp;  //9-2-16 modified: temp structure for swaping 

FILE *fp;

int scoredPlayer = 0;
boolean editName = true;
boolean backgroundChange = false;
boolean nameFieldOn = false;
boolean nameLimit = true;
boolean emptyNameField = false; // 9-2-16:: added: if true then there is no name in the namefield

int nameField_x = 450, nameField_y = 250;
char str[20], playerName[20];
int len, i;

int ap_x = 350, ap_y = 300, score = 0;
char s[100] = "SCORE =";
string scoreText;
char gu[100];

boolean isGameOver = false;
boolean isRestart = false;

char bc2Main[10][15] = { "stage2\\1.bmp", "stage2\\2.bmp", "stage2\\3.bmp", "stage2\\4.bmp", "stage2\\5.bmp", "stage2\\6.bmp", "stage2\\7.bmp", "stage2\\8.bmp", "stage2\\9.bmp", "stage2\\10.bmp" };
char bc2Main2[10][15] = { "stage2\\11.bmp", "stage2\\22.bmp", "stage2\\33.bmp", "stage2\\44.bmp", "stage2\\55.bmp", "stage2\\66.bmp", "stage2\\77.bmp", "stage2\\88.bmp", "stage2\\99.bmp", "stage2\\100.bmp" };
///start
int stageChange = 1;
char bcMain[10][15] = { "new\\1.bmp", "new\\2.bmp", "new\\3.bmp", "new\\4.bmp", "new\\5.bmp", "new\\6.bmp", "new\\7.bmp", "new\\8.bmp", "new\\9.bmp", "new\\10.bmp" };
char bcMain2[10][15] = { "new\\11.bmp", "new\\22.bmp", "new\\33.bmp", "new\\44.bmp", "new\\55.bmp", "new\\66.bmp", "new\\77.bmp", "new\\88.bmp", "new\\99.bmp", "new\\100.bmp" };
char high[8][15] = { "score\\s.bmp" };
//char naruto[6][15] = { "char\\1.bmp", "char\\2.bmp", "char\\3.bmp", "char\\4.bmp", "char\\5.bmp", "char\\6.bmp" };
char naruto[8][15] = { "char\\1.bmp", "char\\2.bmp", "char\\3.bmp", "char\\4.bmp", "char\\5.bmp", "char\\6.bmp", "char\\7.bmp", "char\\8.bmp" };
char narutoJ[2][15] = { "char\\Jump.bmp", "char\\Jump2.bmp" }; // jump image
char narutoShoot[15] = "char\\z.bmp";
char narutoHit[20] = "char\\narutoHit.bmp";
boolean narutoShootBool = false;
boolean narutoHitBool = false;

//obstracle images
char obstracle[10][20] = { "enemy\\obs (1).bmp", "enemy\\obs (2).bmp", "enemy\\obs (3).bmp", "enemy\\obs (4).bmp", "enemy\\obs (5).bmp", "enemy\\obs (6).bmp", "enemy\\obs (7).bmp", "enemy\\obs (8).bmp", "enemy\\obs (9).bmp", "enemy\\obs (10).bmp" };
struct groundEnemy{
	int obstracleIndex;// = 0;
	int obstracle_x;// = screenWidth, 
	int obstracle_y; // = 70;
	int obstracleConditionCheck;// = 0;
	int obstracleHit;// = 2;
	int obstracleHitValue;
};
struct groundEnemy grEnemy[groundEnemyNumber];

//Enemy variables
char birdOne[10][20] = { "enemy\\birdone1.bmp", "enemy\\birdone2.bmp", "enemy\\birdone3.bmp", "enemy\\birdone4.bmp", "enemy\\birdone5.bmp", "enemy\\birdone6.bmp", "enemy\\birdone7.bmp", "enemy\\birdone8.bmp", "enemy\\birdone9.bmp", "enemy\\birdone10.bmp" };
struct enemybirdone{

	int birdoneIndex; // = 0;
	int birdoneCheck; // = 0;
	int birdone_x; // = 1000;
	int birdone_y; // = 500;
	//int birdPos = 0;
	int birdoneHit;// = 0;
	int birdoneHitValue;// = 3;
	int bird_y_change;// = 2;

	int bird_movement_area; // = 50;
	int bird_up;// = birdone_y + bird_movement_area;
	int bird_down;// = birdone_y - bird_movement_area;

};

struct enemybirdone bird1[birdOneNumber];
//bird2 variables
char newbird[10][20] = { "enemy\\bird1.bmp", "enemy\\bird2.bmp", "enemy\\bird3.bmp", "enemy\\bird4.bmp", "enemy\\bird5.bmp", "enemy\\bird6.bmp", "enemy\\bird7.bmp", "enemy\\bird8.bmp", "enemy\\bird9.bmp", "enemy\\bird10.bmp" };
//birdthree variables
char birdthree[10][23] = { "enemy\\birdthree1.bmp", "enemy\\birdthree2.bmp", "enemy\\birdthree3.bmp", "enemy\\birdthree4.bmp", "enemy\\birdthree5.bmp", "enemy\\birdthree6.bmp", "enemy\\birdthree7.bmp", "enemy\\birdthree8.bmp", "enemy\\birdthree9.bmp", "enemy\\birdthree10.bmp" };

struct background
{
	int sc_x;
	int gr_x;
};

background backGroundScreen[10];
int sc1_y = heightDifference; /// BackGround Screen Cordinates
int gr1_y = 0;  ///Ground Cordinates
int scr1_x = 0, scr1_y = 0;  ///High Score Cordinates
int val = -4;// Play Mode Variable

//Pause Menu Variables
boolean resumePauseMenu = true;
boolean restartPauseMenu = false;
boolean mainPauseMenu = false;
boolean exitPauseMenu = false;
//homepage Menu
boolean playMenu_with_Keyboard = true;
boolean insMenu_with_Keyboard = false;
boolean scoreMenu_with_Keyboard = false;
boolean exitMenu_with_Keyboard = false;
boolean creditsMenu_with_Keyboard = false;
int LX = -62, LY = 53;
int LYY = 10;

//video variables
int iVideo = 0;
int kVideo = 0;
char video1[150][30] = { "video1\\v (1)_result.bmp", "video1\\v (2)_result.bmp", "video1\\v (3)_result.bmp", "video1\\v (4)_result.bmp", "video1\\v (5)_result.bmp", "video1\\v (6)_result.bmp", "video1\\v (7)_result.bmp", "video1\\v (8)_result.bmp", "video1\\v (9)_result.bmp", "video1\\v (10)_result.bmp", "video1\\v (11)_result.bmp", "video1\\v (12)_result.bmp", "video1\\v (13)_result.bmp", "video1\\v (14)_result.bmp", "video1\\v (15)_result.bmp", "video1\\v (16)_result.bmp", "video1\\v (17)_result.bmp", "video1\\v (18)_result.bmp", "video1\\v (19)_result.bmp", "video1\\v (20)_result.bmp", "video1\\v (21)_result.bmp", "video1\\v (22)_result.bmp", "video1\\v (23)_result.bmp", "video1\\v (24)_result.bmp", "video1\\v (25)_result.bmp", "video1\\v (26)_result.bmp", "video1\\v (27)_result.bmp", "video1\\v (28)_result.bmp", "video1\\v (29)_result.bmp", "video1\\v (30)_result.bmp", "video1\\v (31)_result.bmp", "video1\\v (32)_result.bmp", "video1\\v (33)_result.bmp", "video1\\v (34)_result.bmp", "video1\\v (35)_result.bmp", "video1\\v (36)_result.bmp", "video1\\v (37)_result.bmp", "video1\\v (38)_result.bmp", "video1\\v (39)_result.bmp", "video1\\v (40)_result.bmp", "video1\\v (41)_result.bmp", "video1\\v (42)_result.bmp", "video1\\v (43)_result.bmp", "video1\\v (44)_result.bmp", "video1\\v (45)_result.bmp", "video1\\v (46)_result.bmp", "video1\\v (47)_result.bmp", "video1\\v (48)_result.bmp", "video1\\v (49)_result.bmp", "video1\\v (50)_result.bmp", "video1\\v (51)_result.bmp", "video1\\v (52)_result.bmp", "video1\\v (53)_result.bmp", "video1\\v (54)_result.bmp", "video1\\v (55)_result.bmp", "video1\\v (56)_result.bmp", "video1\\v (57)_result.bmp", "video1\\v (58)_result.bmp", "video1\\v (59)_result.bmp", "video1\\v (60)_result.bmp", "video1\\v (61)_result.bmp", "video1\\v (62)_result.bmp", "video1\\v (63)_result.bmp", "video1\\v (64)_result.bmp", "video1\\v (65)_result.bmp", "video1\\v (66)_result.bmp", "video1\\v (67)_result.bmp", "video1\\v (68)_result.bmp", "video1\\v (69)_result.bmp", "video1\\v (70)_result.bmp", "video1\\v (71)_result.bmp", "video1\\v (72)_result.bmp", "video1\\v (73)_result.bmp", "video1\\v (74)_result.bmp", "video1\\v (75)_result.bmp", "video1\\v (76)_result.bmp", "video1\\v (77)_result.bmp", "video1\\v (78)_result.bmp", "video1\\v (79)_result.bmp", "video1\\v (80)_result.bmp", "video1\\v (81)_result.bmp", "video1\\v (82)_result.bmp", "video1\\v (83)_result.bmp", "video1\\v (84)_result.bmp", "video1\\v (85)_result.bmp", "video1\\v (86)_result.bmp", "video1\\v (87)_result.bmp", "video1\\v (88)_result.bmp", "video1\\v (89)_result.bmp", "video1\\v (90)_result.bmp", "video1\\v (91)_result.bmp", "video1\\v (92)_result.bmp", "video1\\v (93)_result.bmp", "video1\\v (94)_result.bmp", "video1\\v (95)_result.bmp", "video1\\v (96)_result.bmp", "video1\\v (97)_result.bmp", "video1\\v (98)_result.bmp", "video1\\v (99)_result.bmp", "video1\\v (100)_result.bmp", "video1\\v (101)_result.bmp", "video1\\v (102)_result.bmp", "video1\\v (103)_result.bmp", "video1\\v (104)_result.bmp", "video1\\v (105)_result.bmp", "video1\\v (106)_result.bmp", "video1\\v (107)_result.bmp", "video1\\v (108)_result.bmp", "video1\\v (109)_result.bmp", "video1\\v (110)_result.bmp", "video1\\v (111)_result.bmp", "video1\\v (112)_result.bmp", "video1\\v (113)_result.bmp", "video1\\v (114)_result.bmp", "video1\\v (115)_result.bmp", "video1\\v (116)_result.bmp", "video1\\v (117)_result.bmp", "video1\\v (118)_result.bmp", "video1\\v (119)_result.bmp", "video1\\v (120)_result.bmp", "video1\\v (121)_result.bmp", "video1\\v (122)_result.bmp", "video1\\v (123)_result.bmp", "video1\\v (124)_result.bmp", "video1\\v (125)_result.bmp", "video1\\v (126)_result.bmp", "video1\\v (127)_result.bmp", "video1\\v (128)_result.bmp", "video1\\v (129)_result.bmp", "video1\\v (130)_result.bmp", "video1\\v (131)_result.bmp", "video1\\v (132)_result.bmp", "video1\\v (133)_result.bmp", "video1\\v (134)_result.bmp", "video1\\v (135)_result.bmp", "video1\\v (136)_result.bmp", "video1\\v (137)_result.bmp", "video1\\v (138)_result.bmp", "video1\\v (139)_result.bmp" };
char video1TEXT[] = { "Press Enter to Skip All" };
boolean video1Check = false;
int video1ConditionCheck = 0;

//Enemy boss
boolean isBossOne = false;
boolean isBossTwo = false;
char bossBird[10][20] = { "boss\\a (1).bmp", "boss\\a (2).bmp", "boss\\a (3).bmp", "boss\\a (4).bmp", "boss\\a (5).bmp", "boss\\a (6).bmp", "boss\\a (7).bmp", "boss\\a (8).bmp", "boss\\a (9).bmp", "boss\\a (10).bmp" };
char boss1gun[3][20] = { "boss\\1shot.bmp", "boss\\1shot2.bmp", "boss\\1shot3.bmp" };
char boss2gun[3][30] = { "boss\\Boss2\\g (1).bmp", "boss\\Boss2\\g (2).bmp", "boss\\Boss2\\g (3).bmp" };
int bossGunIndex = 0;
int boss_x = 1000, boss_y = 300;
int bossIndex = 0;
int bossBirdIndex = 0;
int bossMoveY = 5;
int bossTimeCount = 0;
int bossBirdConditionCheck = 0;
int bossBulletHit = 0;
int bossGunMoveY = 2;
int bossGun_y = 70;
int bossBirdMoveFront = 0;
int bossGunX = boss_x - 40; 
int bossGunY = boss_y + bossGun_y;
int bossGunXmove = boss_x - 40;
int bossGunYmove = boss_y + bossGun_y;

//Health Boss
int xHealthBoss = -50;
int yHealthBoss = 300;
int bossHealth= 300;

//Naruto Cordinate Variables and Bullet New variables 
int n_x = 15 + 256, n_y = 80, n_y_jump = 0; // Naruto Starting Point Variable
boolean narutoJump = false;
int narutoMotionIndex = 0; // Naruto Picture Index
int narutoJumpIndex = 0;
int narutoConditionCheck = 0;
int screenConditionCheck = 0;
int groundConditionCheck = 0;
int narutoJumpConditionCheck = 0;

boolean narutoJumpUpCheck = false;
boolean narutoJumpDownCheck = false;
boolean Jcheck = true; //Double Jump is stopped superman debug variable :P
boolean startGame = false; //First gun calling debug.

//Health
int xHealth = 20;
int yHealth = 300;
int narutoHealth = 300;

// Giant Rasengan
int xGiant = 60;
int yGiant = 300;
int giantFull = 300;

// power bar
int xPower = 20;
int yPower = 270;
int powerFull = 60;

//item variables
int itemHealth_x = 0;
int itemHealth_y = 0;
int itemPower_x = 0;
int itemPower_y = 0;
int itemGiant_x = 0;
int itemGiant_y = 0;

//New Gun
int bullet_x[50];
int bullet_y[50];
boolean showBullet[50];
int bulletIndex = 0;
int bulletLoop = 50;
int bulletMiniRasenganIndex = 0;
char bulletMiniRasengan[4][20] = { "char\\kunai.bmp", "char\\kunai2.bmp", "char\\kunai3.bmp", "char\\kunai4.bmp" };
int bulletMotionSpeed = 0;
int bulletSpeed = 10;
int qeta[50];

// gun2
int bullet_x2[50];
int bullet_y2[50];
boolean showBullet2[50];
int bulletIndex2 = 0;
int bulletLoop2 = 50;
int bulletMiniRasenganIndex2 = 0;
char bulletMiniRasengan2[10][30] = { "char\\gun2\\gun2 (1).bmp", "char\\gun2\\gun2 (2).bmp", "char\\gun2\\gun2 (3).bmp", "char\\gun2\\gun2 (4).bmp", "char\\gun2\\gun2 (5).bmp", "char\\gun2\\gun2 (6).bmp", "char\\gun2\\gun2 (7).bmp", "char\\gun2\\gun2 (8).bmp", "char\\gun2\\gun2 (9).bmp", "char\\gun2\\gun2 (10).bmp" };
int bulletMotionSpeed2 = 0;
int bulletSpeed2 = 10;
int totalUsedGun2 = 10;
boolean powerGunStart = true;

// Power
char narutoPower[40][30] = { "char\\pow\\3 (1).bmp", "char\\pow\\3 (2).bmp", "char\\pow\\3 (3).bmp", "char\\pow\\3 (4).bmp", "char\\pow\\3 (5).bmp", "char\\pow\\3 (6).bmp", "char\\pow\\3 (7).bmp", "char\\pow\\3 (8).bmp", "char\\pow\\3 (9).bmp", "char\\pow\\3 (10).bmp", "char\\pow\\3 (11).bmp", "char\\pow\\3 (12).bmp", "char\\pow\\3 (13).bmp", "char\\pow\\3 (14).bmp", "char\\pow\\3 (15).bmp", "char\\pow\\3 (16).bmp", "char\\pow\\3 (17).bmp", "char\\pow\\3 (18).bmp", "char\\pow\\3 (19).bmp", "char\\pow\\3 (20).bmp", "char\\pow\\3 (21).bmp", "char\\pow\\3 (22).bmp", "char\\pow\\3 (23).bmp", "char\\pow\\3 (24).bmp", "char\\pow\\3 (25).bmp", "char\\pow\\3 (26).bmp", "char\\pow\\3 (27).bmp", "char\\pow\\3 (28).bmp", "char\\pow\\3 (29).bmp", "char\\pow\\3 (30).bmp", "char\\pow\\3 (31).bmp", "char\\pow\\3 (32).bmp", "char\\pow\\3 (33).bmp", "char\\pow\\3 (34).bmp", "char\\pow\\3 (35).bmp", "char\\pow\\3 (36).bmp", "char\\pow\\3 (37).bmp", "char\\pow\\3 (38).bmp", "char\\pow\\3 (39).bmp", "char\\pow\\3 (40).bmp" };
int narutoPowerIndex = 0;
boolean narutoPowerStart = true;
int narutoPowerNumber = 3;
int dx[40] = { 0, 8, 4, -16, 8, 4, -16, 0, -2, -2, 0, -30, -23, -8, -6, -9, -8, -7, -5, -7, -2, -6, -7, -7, -43, -39, -43, -24, -46, 65, 77, 55, -33, -33, -33, -33, -17 };
int dy[40] = { 0, 0, -2, -1, 0, -2, -1, 0, 0, 0, 0, 0, 1, 0, -1, 0, -1, -2, -3, -1, -1, -4, -1, -4, 0, -1, -1, -1, -4, -5, -3, -9, -2, -2, -1, -1, -1, -1, -1, -9 };

//keyBoard menu selection
int menu_button = 4;
int button_selected = 5;
boolean home_page = true;


///Functions Prototype
void timer();
void changeScreen();
void changeGround();
void narutoMotion();
void change();
void enemyBoss();
void enemy();
void groundImage();
void screenImage();
void enterName();
void bulletChangeMotion();
void restart();
void obstracleChangeMove();
void sideMenu();
void pauseMenu();
void power();
void item();
void Menu_with_keyBoard();
void restartSomeVariables();
void moveGun();
void readScore();
void updateScore();

void iDraw()
{
	
	iClear();
	if (val == -4){
		iShowBMP(0, 0, "hs//as_page.bmp");
	}
	else if (val == -3) //story line
	{
		iShowBMP(0,0,"hs//storyline.bmp");
		iSetColor(0, 0, 0);
	}
	else if (val == -2){

		iShowBMP(0, 0, "hs//storyline2.bmp"); // before boss 2 
		iSetColor(0, 0, 0);
	}

	else if (val == -1)
	{
		iShowBMP(0, 0, video1[iVideo]);
		iText(500 - 30, 600, video1TEXT, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	
	else if (val == 0)
		Menu_with_keyBoard();
	
	else if (val == 1 && editName){
		screenImage();
		groundImage();
		iShowBMP(scr1_x, scr1_y, high[0]);
		enterName();
	}

	else if (val == 1 && !editName && !isPaused && !isGameOver){
		if (!isPower){
			screenImage();
			groundImage();
		}
		else
		{
			iShowBMP(0, 0, "char\\pow\\powpic.bmp");
		}
		if (!isPower){
			if (!narutoShootBool && !narutoHitBool){
				if (!narutoJump)
					iShowBMP2(n_x, n_y, naruto[narutoMotionIndex], 0);
				else if (narutoJump)
					iShowBMP2(n_x, n_y + n_y_jump, narutoJ[narutoJumpIndex], 0);
			}
			else if (narutoShootBool)
			{
				if (!narutoJump)
					iShowBMP2(n_x, n_y, narutoShoot, 0);
				else if (narutoJump)
					iShowBMP2(n_x, n_y + n_y_jump, narutoShoot, 0);
				narutoShootBool = false;
			}
			else if (narutoHitBool)
			{
				if (!narutoJump)
					iShowBMP2(n_x, n_y, narutoHit, 0);
				else if (narutoJump)
					iShowBMP2(n_x, n_y + n_y_jump, narutoHit, 0);

				narutoHitBool = false;
			}
		}


		for (int i = 0; i < birdOneNumber; i++){
			if (i < birdOneNumber / 2)
				iShowBMP2(bird1[i].birdone_x, bird1[i].birdone_y, newbird[bird1[i].birdoneIndex], 0);
			else
				iShowBMP2(bird1[i].birdone_x, bird1[i].birdone_y, birdthree[bird1[i].birdoneIndex], 0);
		}

		for (int i = 0; i < groundEnemyNumber; i++)
			iShowBMP2(grEnemy[i].obstracle_x, grEnemy[i].obstracle_y, obstracle[grEnemy[i].obstracleIndex], 0);


		//boss
		if (isBossOne && BossOneCondition <= bossTimeCount && !isBossTwo){
			iShowBMP2(bossGunX, bossGunY, boss1gun[bossGunIndex], 255);
			iShowBMP2(bossGunXmove, bossGunYmove, boss1gun[bossGunIndex], 255);
			iShowBMP2(boss_x, boss_y, "boss//1.bmp", 255);
			iShowBMP2(boss_x - 110, boss_y - 200, bossBird[bossBirdIndex], 0);

		}
		else if (isBossTwo && BossOneCondition <= bossTimeCount && !isBossOne){
			iShowBMP2(bossGunX, bossGunY , boss2gun[bossGunIndex], 0);
			iShowBMP2(bossGunXmove, bossGunYmove, boss2gun[bossGunIndex], 0);
			iShowBMP2(boss_x, boss_y, "boss//Boss2//2 (1).bmp", 255);
			iShowBMP2(boss_x - 110, boss_y - 200, bossBird[bossBirdIndex], 0);
		}


		if (isPower)
		{
			iShowBMP2(n_x + dx[narutoPowerIndex], n_y + 10 + dy[narutoPowerIndex], narutoPower[narutoPowerIndex], 255);
		}

		//item
		iShowBMP2(itemGiant_x, itemGiant_y, "char\\grasan.bmp", 0);
		iShowBMP2(itemHealth_x, itemHealth_y, "char\\life.bmp", 0);
		iShowBMP2(itemPower_x, itemPower_y, "char\\pow.bmp", 0);

		sideMenu();

		// New gun 
		for (int i = 0; i < bulletLoop; i++)
		{
			if (showBullet[i]){
				iShowBMP2(bullet_x[i], bullet_y[i], bulletMiniRasengan[bulletMiniRasenganIndex], 0);
			}
		}

		for (int i = 0; i < bulletLoop2; i++)
		{
			if (showBullet2[i]){
				iShowBMP2(bullet_x2[i], bullet_y2[i], bulletMiniRasengan2[bulletMiniRasenganIndex2], 0);
			}
		}

	}

	else if (val == 1 && !editName && isGameOver && !isPaused)//showing score of the player after game
	{
		
		
		if (narutoHealth > 0){
			iShowBMP(0, 0, "hs//playerscore2.bmp");
			iSetColor(0, 0, 0);
			iSetColor(0, 255, 0);
			iText(420+35, 60, "YOUR SCORE IS : ", GLUT_BITMAP_TIMES_ROMAN_24);
			iSetColor(0, 255, 0);
			iText2(420 + 230+35, 60, to_string(score), GLUT_BITMAP_TIMES_ROMAN_24);

		}
		else{
			iShowBMP(0, 0, "hs//playerscore.bmp");
			iSetColor(0, 0, 0);
			iSetColor(0, 255, 0);
			iText(420, 160, "YOUR SCORE IS : ", GLUT_BITMAP_TIMES_ROMAN_24);
			iSetColor(0, 255, 0);
			iText2(420 + 300, 160, to_string(score), GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if (isRestart){
			updateScore();
			restart();
			isRestart = false;
			val = 0;
			if (musicOn){
				PlaySound("music\\home", NULL, SND_LOOP | SND_ASYNC);
			}
		}

	}

	else if (val == 1 && !editName && isPaused  && !isGameOver)
	{
		pauseMenu();
	}


	else if (val == 2)

	{
		iShowBMP(0, 0, "hs\\ins_page.bmp");
	}
	else if (val == 4)
	{
		iShowBMP(0, 0, "hs\\as_page.bmp");
	}
	else if (val == 3)
	{
		int score_x = 80, score_y = 665-250;
		char num[10] = "0 : ";
		iShowBMP(0, 0, "hs\\highScoreImg.bmp");
		iSetColor(255, 0, 0);
		for (int i = 0; i < 5; i++){
			if (strlen(plyScore[i].name) > 0){
				num[0] = i + 48 + 1;
				iText(score_x, score_y - i * 50, num, GLUT_BITMAP_TIMES_ROMAN_24);
				iText(score_x+50, score_y - i * 50, plyScore[i].name, GLUT_BITMAP_TIMES_ROMAN_24);
				iText2(score_x + 250, score_y - i * 50, to_string(plyScore[i].playerScore), GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
	}
}


void iMouseMove(int mx, int my)
{
	//place your codes here
}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

void iPassiveMouseMove(int mx, int my)
{
	mposx = mx;
	mposy = my;
	if (mx == 2){}        
	else if (my == 2){}   

}

void iKeyboard(unsigned char key)
{
	if (val == -4){
		if (key == '\r' || key == ' '){
			val = -3;
		}
	}
	else if (val == -3){
		if (key == '\r' || key == ' '){
			val = -1;
			restart();
			if (musicOn){
				PlaySound("music\\song2", NULL, SND_LOOP | SND_ASYNC);
			}
		}
	}
	else if (val == -2){
		if (key == '\r' || key == ' '){
			stageChange = 2;
			restartSomeVariables();
			val = 1;
		}
	}
	else if (val == -1)
	{
		if (key == '\r'){
			val = 0;
			if (musicOn){
				PlaySound("music\\home", NULL, SND_LOOP | SND_ASYNC);
			}
		}
	}
	else if (val == 0){
		if (key == '\r'){
			if (playMenu_with_Keyboard){

				val = 1;
				if (musicOn){
					PlaySound(0, 0, 0);
				}
			}

			else if (insMenu_with_Keyboard)
			{
				val = 2;
			}
			else if (scoreMenu_with_Keyboard)
			{
				val = 3;
			}
			else if (creditsMenu_with_Keyboard){
				val = 4;
			}
			else if (exitMenu_with_Keyboard)
			{
				exit(0);
			}

		}

	}


	else if (val == 1 && !editName && isGameOver){
		if (key == '\r'){
			isRestart = true;
		}

	}

	else if (val == 1 && !editName && isPaused)
	{
		if (key == '\t')
		{
			iResumeTimer(t1);
			isPaused = false;
		}
		if (key == '\r')
		{
			if (resumePauseMenu)
			{
				iResumeTimer(t1);
				isPaused = false;
			}
			else if (restartPauseMenu)
			{
				restart();
				PlaySound(0,0,0);
			}
			else if (mainPauseMenu)
			{
				restart();
				val = 0;
				if (musicOn){
					PlaySound("music\\home", NULL, SND_LOOP | SND_ASYNC);
				}
			}
			else if (exitPauseMenu)
			{
				exit(0);
			}
		}
	}
	else if (val == 1){
		if (editName){
			if (!nameFieldOn){

				if (key == '\b'){
					val = 0;
				}
				else if (key == '\r'){
					nameFieldOn = true;
				}
			}

			else if (nameFieldOn)
			{
				if (key == '\r') // takes the name and starts the game
				{
					if (str[0] != NULL){
						nameFieldOn = false;
						strcpy(playerName, str);

						for (i = 0; i < len; i++)
							str[i] = NULL;
						len = 0;

						nameFieldOn = false;
						emptyNameField = false;
						editName = false;
						backgroundChange = true;
						startGame = true;
						if (musicOn){
							PlaySound("music\\playgame", NULL, SND_LOOP | SND_ASYNC);
						}
					}
					else{
						emptyNameField = true;
					}
				}
				else if (nameLimit)
				{
					if (key == '\b'){// deletes the char of name when backspace pressed
						if (len != 0)
						{
							str[--len] = '\0';
						}
					}
					else if (key != ' '){
						str[len] = key;
						len++;
						if (len >= 15){
							nameLimit = false;
						}
					}
				}
			}
		}



		if (startGame){
			if (key == '\t')
			{

				if (!isPaused)
				{
					iPauseTimer(t1);
					isPaused = true;
				}

			}
			if (!isPaused && !isPower){
				if (key == 'w')
				{
					if ((n_y <= 80)){
						n_y += 5;
						n_x -= 2;
					}
				}
				if (key == 's')
				{
					if ((n_y >= 5))
					{
						n_y -= 5;
						n_x += 2;
					}
				}

				if (key == 'a')
				{
					if (n_x >= 230)
					{
						n_x -= 5;
					}
				}

				if (key == 'd')
				{
					if (n_x <= 900)
					{
						n_x += 5;
					}
				}
				if (key == ' ')
				{
					if (Jcheck){ /// Double Jump is stopped superman debug :P
						narutoJump = true;
						narutoJumpUpCheck = true;
						narutoJumpIndex = 0;
						Jcheck = false;
					}
				}

				if (key == '1' || key == '2')
				{
					if (key == '1')
						qeta[bulletIndex] = 0;
					if (key == '2')
						qeta[bulletIndex] = 45;


					narutoShootBool = true;
					if (!narutoJump){

						bullet_x[bulletIndex] = n_x + 100;
						bullet_y[bulletIndex] = n_y + 58;
						showBullet[bulletIndex] = true;
						bulletIndex++;
						if (bulletIndex >= 50)
						{
							bulletIndex = 0;
						}

					}
					else if (narutoJump){

						bullet_x[bulletIndex] = n_x + 100;
						bullet_y[bulletIndex] = n_y + n_y_jump + 58;
						showBullet[bulletIndex] = true;
						bulletIndex++;

						if (bulletIndex >= 50)
						{
							bulletIndex = 0;
						}


					}
				}


				if (key == '3' && powerGunStart)
				{
					narutoHealth = 300;
					if (totalUsedGun2 != 0)
					{
						totalUsedGun2--;

					}
					if (totalUsedGun2 <= 0)
					{
						powerGunStart = false;
					}
					if (powerGunStart){
						narutoShootBool = true;
						if (!narutoJump){

							bullet_x2[bulletIndex2] = n_x + 100;
							bullet_y2[bulletIndex2] = n_y + 58;
							showBullet2[bulletIndex2] = true;
							bulletIndex2++;
							if (bulletIndex2 >= 50)
							{
								bulletIndex2 = 0;
							}

						}
						else if (narutoJump){

							bullet_x2[bulletIndex2] = n_x + 100;
							bullet_y2[bulletIndex2] = n_y + n_y_jump + 58;
							showBullet2[bulletIndex2] = true;
							bulletIndex2++;

							if (bulletIndex2 >= 50)
							{
								bulletIndex2 = 0;
							}


						}
					}
				}
				if (key == '4' && narutoPowerStart)
				{
					narutoPowerNumber--;

					isPower = true;
					if (narutoPowerNumber <= 0)
					{
						narutoPowerStart = false;
					}
				}
			}
		}
	}


	else if (val == 2 || val == 3 || val == 4)
	{
		if (key == '\b')
		{
			val = 0;
		}
	}
}


void iSpecialKeyboard(unsigned char key)
{
	if (val == 1){
		if (startGame){

			if (val == 1 && !editName && isPaused)
			{
				if (key == GLUT_KEY_DOWN)
				{
					if (resumePauseMenu)
					{
						resumePauseMenu = false;
						restartPauseMenu = true;
					}
					else if (restartPauseMenu)
					{
						restartPauseMenu = false;
						mainPauseMenu = true;
					}
					else if (mainPauseMenu)
					{
						mainPauseMenu = false;
						exitPauseMenu = true;
					}
					else if (exitPauseMenu)
					{
						exitPauseMenu = false;
						resumePauseMenu = true;
					}


				}
				if (key == GLUT_KEY_UP)
				{
					if (resumePauseMenu)
					{
						resumePauseMenu = false;
						exitPauseMenu = true;
					}
					else if (restartPauseMenu)
					{
						restartPauseMenu = false;
						resumePauseMenu = true;
					}
					else if (mainPauseMenu)
					{
						mainPauseMenu = false;
						restartPauseMenu = true;
					}
					else if (exitPauseMenu)
					{
						exitPauseMenu = false;
						mainPauseMenu = true;
					}
				}
			}

			if (!isPaused && !isPower){
				if (key == GLUT_KEY_END)
				{
					//updateScore(); //updating the score file before exit...
					exit(0);
				}
				if (key == GLUT_KEY_LEFT)
				{
					if (n_x >= 230)
					{
						n_x -= 5;
					}
				}
				if (key == GLUT_KEY_RIGHT)
				{
					if (n_x <= 900)
					{
						n_x += 5;
					}
				}
				if (key == GLUT_KEY_UP)
				{
					if (n_y <= 80){
						n_y += 5;
						n_x -= 2;
					}
				}
				if (key == GLUT_KEY_DOWN)
				{
					if (n_y >= 5)
					{
						n_y -= 5;
						n_x += 2;
					}
				}
			}
		}
	}
	//Home  Selection
	else if (val == 0){
		if (key == GLUT_KEY_DOWN)
		{

			if (playMenu_with_Keyboard)
			{
				playMenu_with_Keyboard = false;
				insMenu_with_Keyboard = true;
			}
			else if (insMenu_with_Keyboard)
			{
				insMenu_with_Keyboard = false;
				scoreMenu_with_Keyboard = true;
			}
			else if (scoreMenu_with_Keyboard)
			{
				scoreMenu_with_Keyboard = false;
				creditsMenu_with_Keyboard = true;
			}

			else if (creditsMenu_with_Keyboard)
			{
				creditsMenu_with_Keyboard = false;
				exitMenu_with_Keyboard = true;
			}
			else if (exitMenu_with_Keyboard)
			{
				exitMenu_with_Keyboard = false;
				playMenu_with_Keyboard = true;
			}



		}

		if (key == GLUT_KEY_UP)
		{
			if (playMenu_with_Keyboard)
			{
				playMenu_with_Keyboard = false;
				exitMenu_with_Keyboard = true;
			}
			else if (insMenu_with_Keyboard)
			{
				insMenu_with_Keyboard = false;
				playMenu_with_Keyboard = true;
			}
			else if (scoreMenu_with_Keyboard)
			{
				scoreMenu_with_Keyboard = false;
				insMenu_with_Keyboard = true;
			}

			else if (creditsMenu_with_Keyboard)
			{
				creditsMenu_with_Keyboard = false;
				scoreMenu_with_Keyboard = true;
			}
			else if (exitMenu_with_Keyboard)
			{
				exitMenu_with_Keyboard = false;
				creditsMenu_with_Keyboard = true;
			}


		}
	}
	if (key == GLUT_KEY_INSERT)
	{
		if (musicOn)
		{
			musicOn = false;
			PlaySound(0, 0, 0);
		}
		else if (!musicOn)
		{
			if (val == -1)
			{
				PlaySound("music\\song2", NULL, SND_LOOP | SND_ASYNC);
			}
			else if (val == 0)
			{
				PlaySound("music\\home", NULL, SND_LOOP | SND_ASYNC);
			}
			else if (val == 1)
			{
				PlaySound("music\\playgame", NULL, SND_LOOP | SND_ASYNC);
			}
			musicOn = true;
		}
	}

}

void timer()
{
	if (val == 1 && backgroundChange && !isPower  && !isGameOver && !isPaused){
		changeScreen();
		changeGround();
		narutoMotion();
		if (isBossOne || isBossTwo){
			enemyBoss();
		}
		moveGun();
		enemy();
		bulletChangeMotion();
		obstracleChangeMove();
		item();
		//score++; // For Naruto Distance score
	}

	else if (val == 1 && isPower)
	{
		power();
	}
	else if (val == -1)
	{
		change();
	}
}

void sideMenu()
{
	//coloring the score back
	iSetColor(0, 0, 0);
	iShowBMP(scr1_x, scr1_y, high[0]);

	//Health Bar
	iSetColor(255, 0, 0);
	iText(xHealth - 10, yHealth + 300 + 20, "Health", GLUT_BITMAP_HELVETICA_12);
	iSetColor(0, 0, 0);
	iFilledRectangle(xHealth, yHealth - 5, 20, 300 + 10);
	iSetColor(255, 0, 0);
	iFilledRectangle(xHealth + 5, yHealth, 10, narutoHealth);

	//Giant Rasengan Bar
	iSetColor(0, 145, 36);
	iText(xGiant, yGiant + 300 + +20 + 20, "Giant", GLUT_BITMAP_HELVETICA_12);
	iText(xGiant, yGiant + 300 + 20, "Rasengan", GLUT_BITMAP_HELVETICA_12);
	iSetColor(0, 0, 0);
	iFilledRectangle(xGiant, yGiant - 5, 20, 300 + 10);
	iSetColor(0, 255, 0);
	iFilledRectangle(xGiant + 5, yGiant, 10, totalUsedGun2 * 30);

	iSetColor(0, 0, 255);
	iText(xPower, yPower, "Power", GLUT_BITMAP_HELVETICA_12);
	iSetColor(0, 0, 0);
	iFilledRectangle(xPower - 5, yPower - 5 - 20, 60 + 10, 20);
	iSetColor(0, 0, 255);
	iFilledRectangle(xPower, yPower - 20, narutoPowerNumber * 20, 10);

	//Health Bar
	if (isBossOne || isBossTwo){
		iSetColor(255, 0, 0);
		iText(xHealthBoss + 200, yHealthBoss + 300 + 35, "Boss", GLUT_BITMAP_HELVETICA_12);
		iSetColor(0, 0, 0);
		iFilledRectangle(xHealthBoss + 200, yHealthBoss - 5, 20, 300 + 10);
		iSetColor(255, 0, 0);
		iFilledRectangle(xHealthBoss + 5 + 200, yHealthBoss, 10, bossHealth);
	}

	iSetColor(0, 0, 0);

	//showing the score 
	iText(2, 125, "Press   \"End\"   to Exit", GLUT_BITMAP_HELVETICA_12);
	iText(2, 145, "Press \"INSERT\" to Turn On/Off Music", GLUT_BITMAP_HELVETICA_12);
	iText(2, 165, "Press  \"TAB\"   to Pause", GLUT_BITMAP_HELVETICA_12);
	iText(10, 50, s, GLUT_BITMAP_TIMES_ROMAN_24);
	scoreText = to_string(score); //converting score to string
	iText2(120, 50, scoreText, GLUT_BITMAP_TIMES_ROMAN_24); //user modified function
}

void screenImage()
{
	for (int i = 0; i < 10; i++){
		if (stageChange == 1)
			iShowBMP(backGroundScreen[i].sc_x, sc1_y, bcMain[i]);
		else if (stageChange == 2)
			iShowBMP(backGroundScreen[i].sc_x, sc1_y, bc2Main[i]);
	}
}
void changeScreen()
{
	screenConditionCheck++;
	if (screenConditionCheck == screenCondition)
	{
		int s = screenSpeed;
		for (int i = 0; i < 10; i++)
		{
			backGroundScreen[i].sc_x -= s;
			if (backGroundScreen[i].sc_x <= 0)
			{
				backGroundScreen[i].sc_x = screenWidth;
				if (backGroundScreen[0].sc_x == screenWidth && i == 0){
					bossTimeCount++;
					if (bossTimeCount >= BossOneCondition)
					{
						if (stageChange == 1)
						{
							isBossOne = true;
						}
						else if (stageChange == 2)
						{
							isBossTwo = true;
						}
					}
				}
			}
		}
		screenConditionCheck = 0;
	}
}
void groundImage()
{
	for (int i = 0; i < 10; i++){
		if (stageChange == 1)
			iShowBMP(backGroundScreen[i].gr_x, gr1_y, bcMain2[i]);
		else if (stageChange == 2)
			iShowBMP(backGroundScreen[i].gr_x, gr1_y, bc2Main2[i]);
	}

}
void changeGround()
{
	groundConditionCheck++;
	if (groundConditionCheck == groundCondition)
	{
		int s = groundSpeed;
		for (int i = 0; i < 10; i++)
		{
			backGroundScreen[i].gr_x -= s;
			if (backGroundScreen[i].gr_x <= 0)
			{
				backGroundScreen[i].gr_x = screenWidth;
			}
		}
		groundConditionCheck = 0;
	}
}

void narutoMotion()
{
	///Motion Jump Added
	if (narutoJump == 0){
		narutoConditionCheck++;
		if (narutoCondition == narutoConditionCheck) // controls the iSetTimer
		{
			narutoMotionIndex++;
			if (narutoMotionIndex == 8) // new char
			{
				narutoMotionIndex = 0;
			}
			narutoConditionCheck = 0;
		}
	}
	else if (narutoJump)
	{
		narutoJumpConditionCheck++;
		if (narutoJumpConditionCheck == narutoJumpCondition)
		{
			if (narutoJumpUpCheck)
			{
				if (n_y_jump <= jump)
				{
					n_y_jump += jumpSpeed;
					if (n_y_jump == jump)
					{
						narutoJumpUpCheck = false;
						narutoJumpDownCheck = true;
						narutoJumpIndex = 1;
					}
				}
			}
			else if (narutoJumpDownCheck)
			{
				if (n_y_jump >= 0)
				{
					n_y_jump -= jumpSpeed;
					if (n_y_jump == 0)
					{
						narutoJumpDownCheck = false;
						narutoJump = false;
						Jcheck = true;
					}
				}
			}
			narutoJumpConditionCheck = 0;
		}
	}
}

//gun move

void moveGun(){

	for (int i = 0; i < bulletLoop; i++)
	{
		if (showBullet[i])
		{
			bullet_x[i] += bulletSpeed*cos(qeta[i] * PI / 180);
			bullet_y[i] += bulletSpeed*sin(qeta[i] * PI / 180);

			///Collision

			for (int j = 0; j < birdOneNumber; j++){
				if (bullet_x[i] >= bird1[j].birdone_x && bullet_x[i] <= bird1[j].birdone_x + 95 && bullet_x[i] < (screenWidth - screenWidthCut))
				{
					if (bullet_y[i] + 27 >= bird1[j].birdone_y && bullet_y[i] <= bird1[j].birdone_y + 70)
					{
						bird1[j].birdoneHit++;

						if (bird1[j].birdoneHit == bird1[j].birdoneHitValue){
							score += 100 * stageChange; // For Naruto Hitting score
							bird1[j].birdone_x = bird1[j].birdone_y = -1;
							bird1[j].birdoneHit = 0;
						}
						bullet_x[i] = bullet_y[i] = -1;
						showBullet[i] = false;
					}
				}
			}

			for (int j = 0; j < groundEnemyNumber; j++)
			{
				if (bullet_x[i] >= grEnemy[j].obstracle_x && bullet_x[i] <= grEnemy[j].obstracle_x + 140 && bullet_x[i] < (screenWidth - screenWidthCut))
				{
					if (bullet_y[i] + 27 >= grEnemy[j].obstracle_y && bullet_y[i] <= grEnemy[j].obstracle_y + 100)
					{
						grEnemy[j].obstracleHit++;

						if (grEnemy[j].obstracleHit == grEnemy[j].obstracleHitValue){
							score += 200 * stageChange; // For Naruto Hitting score
							grEnemy[j].obstracle_x = grEnemy[j].obstracle_y = -1;
							grEnemy[j].obstracleHit = 0;
						}
						bullet_x[i] = bullet_y[i] = -1;
						showBullet[i] = false;
					}
				}
			}


			if (isBossOne || isBossTwo)
			{
				if (bullet_x[i] >= boss_x && bullet_x[i] <= boss_x + 195 && bullet_y[i] >= boss_y - 200 && bullet_y[i] <= boss_y + 77)
				{
					bossBulletHit++;
					if (BossBulletHit*stageChange == bossBulletHit){
						score += 1000 * stageChange; // For Naruto Hitting score
						bossHealth -= 5 / stageChange;
						bossBulletHit = 0;
					}
					bullet_x[i] = bullet_y[i] = -1;
					showBullet[i] = false;
				}
			}
		}
	}

	for (int i = 0; i < bulletLoop2; i++)
	{
		if (showBullet2[i])
		{
			bullet_x2[i] += bulletSpeed2;

			///doesnot colide  done copy the whole segment

			for (int j = 0; j < birdOneNumber; j++){
				if (bullet_x2[i] + 102 > bird1[j].birdone_x)
				{
					if (bird1[j].birdone_x >= bullet_x2[i] && bird1[j].birdone_x <= bullet_x2[i] + 104 && bird1[j].birdone_y + 70 >= bullet_y2[i] && bird1[j].birdone_y <= bullet_y2[i] + 104)
					{

						score += 100;
						bird1[j].birdone_x = bird1[j].birdone_y = -1;
					}
				}

				if (bullet_x2[i] >= screenWidth - screenWidthCut)
				{
					bullet_x2[i] = bullet_y2[i] = -1;
					//bullet_hit[i] = true;
					showBullet2[i] = false;
				}

			}

			for (int j = 0; j < groundEnemyNumber; j++){
				if (bullet_x2[i] + 102 > grEnemy[j].obstracle_x)
				{
					if (bullet_x2[i] + 130 >= grEnemy[j].obstracle_x  && bullet_x2[i] - 95 <= grEnemy[j].obstracle_x)
					{
						if (bullet_y2[i] - 70 <= grEnemy[j].obstracle_y && bullet_y2[i] + 160 >= grEnemy[j].obstracle_y)
						{

							score += 200 * stageChange;
							grEnemy[j].obstracle_x = grEnemy[j].obstracle_x = -1;
						}
					}
				}

				if (bullet_x2[i] >= screenWidth - screenWidthCut)
				{
					bullet_x2[i] = bullet_y2[i] = -1;
					//bullet_hit[i] = true;
					showBullet2[i] = false;
				}

			}

			//collision for boss
			if (isBossOne || isBossTwo)
			{
				if (bullet_x2[i] +200>= boss_x && bullet_x2[i] <= boss_x + 195 && bullet_y2[i] >= boss_y - 200 && bullet_y2[i] <= boss_y + 77)
				{
					bossBulletHit++;
					if (BossBulletHit*stageChange == bossBulletHit){
						score += 1000*stageChange; // For Naruto Hitting score
						bossHealth -= 10 / stageChange;
						bossBulletHit = 0;
					}
					bullet_x2[i] = bullet_y2[i] = -1;
					showBullet2[i] = false;
				}
			}

		}
	}
	if (bossHealth <= 0 && stageChange == 1)
	{
		val = -2;
		isBossOne = false;
	}
	else if (bossHealth <= 0 && stageChange == 2)
	{
		isGameOver = true;
		isBossTwo = false;
		//updateScore();
	}

}

//score updating and sorting in assending order
void readScore()
{
	//FILE *fp;
	fp = fopen("ScoreStore.txt", "r"); //  a file for saving scores
	if (fp == NULL)
	{
		fp = fopen("ScoreStore.txt", "w");  //if the file doesn't exist,, creating it
		fclose(fp);
		fp = fopen("ScoreStore.txt", "r");
	}

	char name[20];
	int pScore;
	int i = 0;
	while (fscanf(fp, "%s %d", &name, &pScore) != EOF){


		if (strlen(name) > 0){
			strcpy(plyScore[i].name, name);
			plyScore[i++].playerScore = pScore;

			scoredPlayer++;
		}

	}
	scoredPlayer++;
	fclose(fp);

}
void updateScore(){

	//cout << "updatescore " << endl;
	fp = fopen("ScoreStore.txt", "w");//opening file for new score recoding

	strcpy(plyScore[scoredPlayer].name, playerName);
	plyScore[scoredPlayer].playerScore = score;

	for (int i = 0; i <= scoredPlayer; i++){
		for (int j = i + 1; j <= scoredPlayer; j++){
			if (plyScore[i].playerScore < plyScore[j].playerScore){
				temp = plyScore[i];
				plyScore[i] = plyScore[j];
				plyScore[j] = temp;
			}
		}

	}

	for (int i = 0; i < 10; i++){
		if (plyScore[i].name[0] != NULL || strlen(plyScore[i].name) != 0)
			fprintf(fp, "%s\n%d\n", plyScore[i].name, plyScore[i].playerScore);
	}
	fclose(fp);
}

//entering name
void enterName()
{
	iShowBMP2(nameField_x + 20, nameField_y + 100, "nameEdit\\name_title.bmp", 0);

	if (!nameFieldOn){
		iShowBMP2(nameField_x, nameField_y, "nameEdit\\name.bmp", 0);
		iSetColor(0, 0, 0);
		iText(nameField_x, nameField_y - 20, "Click to activate the box, enter to finish.", GLUT_BITMAP_9_BY_15);
	}
	else{
		iShowBMP2(nameField_x, nameField_y - 15, "nameEdit\\name2.bmp", 255);

		iSetColor(0, 0, 0);
		iText(nameField_x + 130, nameField_y + 30, str, GLUT_BITMAP_TIMES_ROMAN_24);

		if (!nameLimit){

			iSetColor(255, 255, 255);
			iFilledRectangle(nameField_x + 100, nameField_y - 40, 180, 30);


			iSetColor(255, 0, 0);
			iText(nameField_x + 110, nameField_y - 30, "Name Limit reached", GLUT_BITMAP_HELVETICA_18);
		}
		else if (emptyNameField){
			iSetColor(255, 255, 255);
			iFilledRectangle(nameField_x + 60, nameField_y - 40, 250, 30);


			iSetColor(255, 0, 0);
			iText(nameField_x + 75, nameField_y - 30, "Please Enter a Name First", GLUT_BITMAP_HELVETICA_18);
		}
	}
}

void Menu_with_keyBoard() // 4/2/16
{
	iShowBMP(0, 0, "hs\\naruto.bmp");
	if (!playMenu_with_Keyboard)
		iShowBMP2(120 + LX, 400 + LY + LYY * 4, "hs\\play.bmp", 255);
	else
		iShowBMP2(120 + LX - 50, 400 + LY + LYY * 4, "hs\\play2.bmp", 255);

	if (!insMenu_with_Keyboard)
		iShowBMP2(120 + LX, 300 + LY + LYY * 3, "hs\\ins.bmp", 255);
	else
		iShowBMP2(120 + LX - 50, 300 + LY + LYY * 3, "hs\\ins2.bmp", 255);

	if (!scoreMenu_with_Keyboard)
		iShowBMP2(120 + LX, 200 + LY + LYY * 2, "hs\\score.bmp", 255);
	else
		iShowBMP2(120 + LX - 50, 200 + LY + LYY * 2, "hs\\score2.bmp", 255);

	if (!creditsMenu_with_Keyboard)
		iShowBMP2(120 + LX, 100 + LY + LYY, "hs\\credits.bmp", 255);
	else
		iShowBMP2(120 + LX - 50, 100 + LY + LYY, "hs\\credits2.bmp", 255);

	if (!exitMenu_with_Keyboard)
		iShowBMP2(120 + LX, 0 + LY, "hs\\Exit.bmp", 255);
	else
		iShowBMP2(120 + LX - 50, 0 + LY, "hs\\Exit2.bmp", 255);

}

void change()
{
	video1ConditionCheck++;
	if (video1ConditionCheck == video1Condition){
		if (kVideo <= 10)
			kVideo++;
		else
		{
			iVideo++;
			if (iVideo == 139)
			{
				video1Check = true;
				iVideo = 130;
			}
		}
		video1ConditionCheck = 0;
	}
}

void enemy()
{

	for (int i = 0; i < birdOneNumber; i++){
		bird1[i].birdoneCheck++;
		if (bird1[i].birdoneCheck == birdoneCondition){
			bird1[i].birdoneIndex++;
			if (bird1[i].birdoneIndex >= 10)
			{
				bird1[i].birdoneIndex = 0;
			}
			bird1[i].birdoneCheck = 0;

		}

		bird1[i].birdone_x -= (5+i*2);
		bird1[i].birdone_y -= bird1[i].bird_y_change;


		if (bird1[i].birdone_y >= bird1[i].bird_up || bird1[i].birdone_y <= bird1[i].bird_down)
		{
			bird1[i].bird_y_change *= (-1);
		}

		///Naruto Collision
		if (n_x + 95 >= bird1[i].birdone_x && n_x <= bird1[i].birdone_x + 90)
		{
			if (!narutoJump)
			{
				if (n_y <= bird1[i].birdone_y && n_y + 100 >= bird1[i].birdone_y)
				{
					if (!narutoHitBool)
					{
						bird1[i].birdone_x = -1;
						narutoHealth -= 10;
						narutoHitBool = true;
					}

				}
			}
			else if (narutoJump)
			{
				if (n_y + n_y_jump <= bird1[i].birdone_y && n_y + n_y_jump + 100 >= bird1[i].birdone_y)
				{
					if (!narutoHitBool)
					{
						bird1[i].birdone_x = -1;
						narutoHealth -= 10;
						narutoHitBool = true;
					}
				}
			}
		}



		if (bird1[i].birdone_x < 80)
		{
			bird1[i].birdone_x = screenWidth + rand() % 500;
			if (i < birdOneNumber / 2)
				bird1[i].birdone_y = 100 + rand() % 300;
			else
				bird1[i].birdone_y = 100 + 300 + rand() % 300;

			bird1[i].bird_up = bird1[i].birdone_y + bird1[i].bird_movement_area;
			bird1[i].bird_down = bird1[i].birdone_y - bird1[i].bird_movement_area;

		}
	}

	if (narutoHealth <= 0){
		isGameOver = true;
	}

}


void enemyBoss(){

	if (BossOneCondition <= bossTimeCount){
		bossBirdConditionCheck++;
		bossBirdMoveFront++;

		

		if (BossOneConditionCheck == bossBirdConditionCheck){
			bossBirdIndex++;
			bossGunIndex++;
			if (bossGunIndex == 3)
			{
				bossGunIndex = 0;
			}
			if (bossBirdIndex >= 10){
				bossBirdIndex = 0;
			}

			boss_y += bossMoveY;
			if (boss_y + 120 >= 665 || boss_y - 200 <= 0){
				bossMoveY *= -1;
			}
			bossBirdConditionCheck = 0;
		}

		bossGun_y += bossGunMoveY;
		if (bossGun_y + 48 >= boss_y + 110 || bossGun_y <= boss_y + 100){
			bossGunMoveY *= -1;
		}

		bossGunX = boss_x - 40;
		bossGunY = boss_y + bossGun_y;

		bossGunXmove -= 10;
		bossGunYmove -= 2;
		//boss power collision
		if (n_x + 95 >= bossGunXmove && n_x - 60 <= bossGunXmove)
		{
			if (!narutoJump)
			{
				if (n_y - 60 <= bossGunYmove && n_y + 100 >= bossGunYmove)
				{
					bossGunXmove = -1;
					narutoHealth -= 20 * stageChange;
					
				}
			}
			else if (narutoJump)
			{
				if (n_y + n_y_jump - 60 <= bossGunYmove  && n_y + n_y_jump + 100 >= bossGunYmove)
				{
					bossGunXmove = -1; 
					narutoHealth -= 20*stageChange;
					
				}
			}
		}

		if (bossGunXmove < 100)
		{
			bossGunXmove = boss_x - 40;
			bossGunYmove = boss_y + bossGun_y;
		}

		if (narutoHealth <= 0){
			isGameOver = true;
		}
	}

}


void bulletChangeMotion()
{
	bulletMotionSpeed++;
	if (bulletMotionSpeed == 2)
	{
		bulletMiniRasenganIndex++;
		bulletMiniRasenganIndex2++;
		if (bulletMiniRasenganIndex >= 4)
		{
			bulletMiniRasenganIndex = 0;
		}
		if (bulletMiniRasenganIndex2 >= 10)
		{
			bulletMiniRasenganIndex2 = 0;
		}
		bulletMotionSpeed = 0;
	}
}

/// Restarts the game still processing
void restart()
{
	editName = true;
	backgroundChange = false;
	nameFieldOn = false;
	nameLimit = true;
	emptyNameField = false;
	isGameOver = false;
	isRestart = false;
	nameField_x = 450,
	nameField_y = 250;
	score = 0;

	str[0] = '\0';
	playerName[0] = '\0';
	len = 0;
	i = 0;
	scoreText[0] = '0';
	scoreText[0] = '\0';

	isPaused = false;
	iResumeTimer(t1);
	isPower = false;
	isPausedPower = false;
	isGameOver = false;
	isRestart = false;
	stageChange = 1;
	narutoShootBool = false;
	narutoHitBool = false;

	restartSomeVariables(); // calls some variables (helps to update difficulty)

	sc1_y = heightDifference; /// BackGround Screen Cordinates
	gr1_y = 0;  ///Ground Cordinates
	int screenSum = screenDifference;
	for (int i = 0; i < 10; i++)
	{
		backGroundScreen[i].sc_x = screenSum;
		backGroundScreen[i].gr_x = screenSum;
		screenSum += screenDifference;
	}

	resumePauseMenu = true;
	restartPauseMenu = false;
	mainPauseMenu = false;
	exitPauseMenu = false;
	playMenu_with_Keyboard = true;
	insMenu_with_Keyboard = false;
	scoreMenu_with_Keyboard = false;
	exitMenu_with_Keyboard = false;
	creditsMenu_with_Keyboard = false;

	isBossOne = false;
	isBossTwo = false;

	startGame = false; //First gun calling debug and modified 

	menu_button = 4;
	button_selected = 5;
	home_page = true;
}

void restartSomeVariables()
{

	for (int i = 0; i < birdOneNumber; i++)
	{

		if (i * 2 < 10)
			bird1[i].birdoneIndex = i * 2;
		else
			bird1[i].birdoneIndex = 0;

		bird1[i].birdoneCheck = 0;
		bird1[i].birdone_x = screenWidth + rand() % 200 * (i + 1);

		if (i <= birdOneNumber / 2)
			bird1[i].birdone_y = 100 + rand() % 300;
		else
			bird1[i].birdone_y = 100 + 300 + rand() % 300;

		bird1[i].birdoneHit = 0;
		//change the value
		if (i <= birdOneNumber / 2)
			bird1[i].birdoneHitValue = stageChange;
		else
			bird1[i].birdoneHitValue = 1 + stageChange;

		bird1[i].bird_y_change = 2;
		if (i % 2 == 1)
			bird1[i].bird_y_change *= (-1);

		bird1[i].bird_movement_area = 50;
		bird1[i].bird_up = bird1[i].birdone_y + bird1[i].bird_movement_area;
		bird1[i].bird_down = bird1[i].birdone_y - bird1[i].bird_movement_area;
	}

	for (int i = 0; i < groundEnemyNumber; i++)
	{
		if (i * 2 < 10)
			grEnemy[i].obstracleIndex = i * 2;// = 0;
		else
			grEnemy[i].obstracleIndex = 0;

		grEnemy[i].obstracle_x = screenWidth + rand() % 200 * (i * 2 + 1);// = screenWidth,
		grEnemy[i].obstracle_y = rand() % 90; // = 70;
		grEnemy[i].obstracleConditionCheck = 0;// = 0;
		grEnemy[i].obstracleHit = 0;// = 2;
		grEnemy[i].obstracleHitValue = stageChange * 2;
	}

	n_x = 15 + 256;
	n_y = 80;
	n_y_jump = 0;
	bossGunIndex = 0;
	boss_x = 1000, boss_y = 300;
	bossIndex = 0;
	bossBirdIndex = 0;
	bossMoveY = 5;
	bossTimeCount = 0;
	bossBirdConditionCheck = 0;
	bossBulletHit = 0;
	bossGunMoveY = 2;
	bossGun_y = 70;
	bossBirdMoveFront = 0;
	bossGunX = boss_x - 40;
	bossGunY = boss_y + bossGun_y;
	bossGunXmove = boss_x - 40;
	bossGunYmove = boss_y + bossGun_y;
	xHealthBoss = -50;
	yHealthBoss = 300;
	bossHealth = 300;
	narutoJump = false;
	narutoMotionIndex = 0; // Naruto Picture Index
	narutoJumpIndex = 0;
	///Condition Check Variable
	narutoConditionCheck = 0;
	screenConditionCheck = 0;
	groundConditionCheck = 0;
	///Condition Variables Updated by - 9-1-2015
	narutoJumpConditionCheck = 0;
	narutoJumpUpCheck = false;
	narutoJumpDownCheck = false;
	Jcheck = true; //Double Jump is stopped superman debug variable :P
	xHealth = 20;
	yHealth = 300;
	narutoHealth = 300;
	// Giant Rasengan
	xGiant = 60;
	yGiant = 300;
	giantFull = 300;
	// power bar
	xPower = 20;
	yPower = 270;
	powerFull = 60;
	itemHealth_x = 0;
	itemHealth_y = 0;
	itemPower_x = 0;
	itemPower_y = 0;
	itemGiant_x = 0;
	itemGiant_y = 0;
	bulletSpeed = 10;
	bulletMotionSpeed = 0;
	bulletIndex = 0;
	bulletLoop = 50;
	bulletMiniRasenganIndex = 0;

	for (int i = 0; i<50; i++)
	{

		bullet_x[i] = 0;
		bullet_y[i] = 0;
		showBullet[i] = false;
		qeta[i] = 0;

		bullet_x2[i] = 0;
		bullet_y2[i] = 0;
		showBullet2[i] = false;


	}

	bulletIndex2 = 0;
	bulletLoop2 = 50;
	bulletMiniRasenganIndex2 = 0;
	bulletMotionSpeed2 = 0;
	bulletSpeed2 = 10;
	totalUsedGun2 = 10;
	powerGunStart = true;
	narutoPowerIndex = 0;
	narutoPowerStart = true;
	narutoPowerNumber = 3;
}

void obstracleChangeMove()
{
	/// call it in ground function as it moves with the ground..
	for (int i = 0; i < groundEnemyNumber; i++)
	{
		grEnemy[i].obstracle_x -= groundSpeed;

		grEnemy[i].obstracleConditionCheck++;
		if (grEnemy[i].obstracleConditionCheck == obstracleCondition){
			grEnemy[i].obstracleIndex++;
			if (grEnemy[i].obstracleIndex == 10)
			{
				grEnemy[i].obstracleIndex = 0;
			}
			grEnemy[i].obstracleConditionCheck = 0;
		}

		//Collision

		if (n_x + 95 >= grEnemy[i].obstracle_x && n_x - 130 <= grEnemy[i].obstracle_x)
		{
			if (!narutoJump)
			{
				if (n_y - 80 <= grEnemy[i].obstracle_y && n_y + 100 >= grEnemy[i].obstracle_y)
				{
					if (!narutoHitBool)
					{
						grEnemy[i].obstracle_x = -1;
						narutoHealth -= 25;
						narutoHitBool = true;
					}

				}
			}
			else if (narutoJump)
			{
				if (n_y + n_y_jump - 80 <= grEnemy[i].obstracle_y && n_y + n_y_jump + 100 >= grEnemy[i].obstracle_y)
				{
					if (!narutoHitBool)
					{
						grEnemy[i].obstracle_x = -1;
						narutoHealth -= 25;
						narutoHitBool = true;
					}
				}
			}
		}


		if (grEnemy[i].obstracle_x < 10)
		{
			grEnemy[i].obstracle_x = screenWidth + rand() % 200 * (i + 1);
			grEnemy[i].obstracle_y = rand() % 90;
		}

		if (narutoHealth <= 0){
			isGameOver = true;
		}
	}
}


void pauseMenu()
{
	iShowBMP(0, 0, "hs\\pause.bmp");
	if (!resumePauseMenu)
		iShowBMP2(100, screenHeight - 150 - LYY, "hs\\resume.bmp", 255);
	else
		iShowBMP2(100 - 40, screenHeight - 150, "hs\\resume2.bmp", 255);

	if (!restartPauseMenu)
		iShowBMP2(100, screenHeight - 300 - LYY, "hs\\restart.bmp", 255);
	else
		iShowBMP2(100 - 40, screenHeight - 300, "hs\\restart2.bmp", 255);

	if (!mainPauseMenu)
		iShowBMP2(100, screenHeight - 450 - LYY, "hs\\main.bmp", 255);
	else
		iShowBMP2(100 - 40, screenHeight - 450, "hs\\main2.bmp", 255);

	if (!exitPauseMenu)
		iShowBMP2(100, screenHeight - 600 - LYY, "hs\\exitp.bmp", 255);
	else
		iShowBMP2(100 - 40, screenHeight - 600, "hs\\exitp2.bmp", 255);

}
void power()
{
	narutoConditionCheck++;
	if (narutoCondition == narutoConditionCheck)
	{
		narutoPowerIndex++;
		if (narutoPowerIndex == 40) // new char
		{
			narutoPowerIndex = 0;
			isPower = false;
			for (int i = 0; i < birdOneNumber; i++)
			{
				if (bird1[i].birdone_x < screenWidth)
					score += 100;
				bird1[i].birdone_x = -1;
			}
			for (int i = 0; i < groundEnemyNumber; i++)
			{
				if (grEnemy[i].obstracle_x < screenWidth)
					score += 100;
				grEnemy[i].obstracle_x = -1;
			}
			if (isBossOne || isBossTwo)
			{
				bossHealth -= 40 / stageChange;
			}
		}
		narutoConditionCheck = 0;
	}
}


void item()
{

	itemHealth_x -= 10;
	itemPower_x -= 10;
	itemGiant_x -= 10;

	if (itemHealth_x < 80)
	{
		itemHealth_x = screenWidth + rand() % 1000;
		itemHealth_y = 50 + rand() % 300;
	}
	else if (itemGiant_x < 80)
	{
		itemGiant_x = screenWidth + rand() % 800;
		itemGiant_y = 50 + rand() % 300;
	}
	else if (itemPower_x < 80)
	{
		itemPower_x = screenWidth + rand() % 700;
		itemPower_y = 50 + rand() % 300;
	}

	//collision giant rasengun

	if (n_x + 95 >= itemGiant_x && n_x - 16 <= itemGiant_x)
	{
		if (!narutoJump)
		{
			if (n_y - 42 <= itemGiant_y  && n_y + 100 >= itemGiant_y)
			{
				itemGiant_x = -1;
				totalUsedGun2 += 3;
				if (totalUsedGun2 >= 10)
				{
					totalUsedGun2 = 10;
					
					//narutoPowerStart = true;
				}
				powerGunStart = true;
			}
		}
		else if (narutoJump)
		{
			if (n_y + n_y_jump - 42 <= itemGiant_y  && n_y + n_y_jump + 100 >= itemGiant_y)
			{
				itemGiant_x = -1;
				totalUsedGun2 += 3;
				if (totalUsedGun2 >= 10)
				{
					totalUsedGun2 = 10;
					//narutoPowerStart = true;
				}

				powerGunStart = true;
			}
		}
	}

	// collision power

	if (n_x + 95 >= itemPower_x && n_x - 16 <= itemPower_x)
	{
		if (!narutoJump)
		{
			if (n_y - 42 <= itemPower_y && n_y + 100 >= itemPower_y)
			{
				itemPower_x = -1;
				narutoPowerNumber++;
				if (narutoPowerNumber >= 3)
				{
					narutoPowerNumber = 3;
					//powerGunStart = true;
				}

				narutoPowerStart = true;
			}
		}
		else if (narutoJump)
		{
			if (n_y + n_y_jump - 42 <= itemPower_y && n_y + n_y_jump + 100 >= itemPower_y)
			{
				itemPower_x = -1;
				narutoPowerNumber++;
				if (narutoPowerNumber >= 3)
				{
					narutoPowerNumber = 3;
					//powerGunStart = true;
				}

				narutoPowerStart = true;
			}
		}
	}

	// collision life

	if (n_x + 95 >= itemHealth_x && n_x - 16 <= itemHealth_x)
	{
		if (!narutoJump)
		{
			if (n_y - 42 <= itemHealth_y && n_y + 100 >= itemHealth_y)
			{
				itemHealth_x = -1;
				narutoHealth += 50;
				if (narutoHealth >= 300)
				{
					narutoHealth = 300;
				}
			}
		}
		else if (narutoJump)
		{
			if (n_y + n_y_jump - 42 <= itemHealth_y  && n_y + n_y_jump + 100 >= itemHealth_y)
			{
				itemHealth_x = -1;
				narutoHealth += 50;
				if (narutoHealth >= 300)
				{
					narutoHealth = 300;
				}
			}
		}
	}

}

int main()
{
	srand(time(NULL)); // see readScore() function
	restart();
	readScore();
	t1 = iSetTimer(25, timer);
	if (musicOn){
		PlaySound("music\\playgame2", NULL, SND_LOOP | SND_ASYNC);
	}
	iInitialize(screenWidth - screenWidthCut, screenHeight, "Naruto - The Unfinished Page");
	return 0;
}