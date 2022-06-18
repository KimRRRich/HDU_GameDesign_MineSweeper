#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<windows.h>
#include<iostream>
#include<sstream>
#define GRIDSIZE 25
#define LVL1_WIDTH 9
#define LVL1_HEIGHT 9
#define LVL1_NUM 10
#define LVL2_WIDTH 16
#define LVL2_HEIGHT 16
#define LVL2_NUM 40
#define LVL3_WIDTH 30
#define LVL3_HEIGHT 16
#define LVL3_NUM 99

//int mouseAction;
//sf::Vector2i mousePoint;

typedef enum MOUSEFUCTION {
	RButtonDownFunc,
	LButtonDownFunc,
	LButtonDblClkFunc
};

typedef enum GRIDSTATE {
	ncNULL,        //空地
	ncUNDOWN,      //背景方块
	ncMINE,        //地雷
	ncONE,         //数字1
	ncTWO,         //数字2
	ncTHREE,       //数字3
	ncFOUR,        //数字4
	ncFIVE,        //数字5
	ncSIX,         //数字6
	ncSEVEN,       //数字7
	ncEIGHT,       //数字8
	ncFLAG,        //标记
	ncQ,           //问号
	ncX,           //备用
	ncBOMBING,     //爆炸的雷
	ncUNFONUD      //未检测出来的雷

};

typedef enum GAMEOVERSTAGE {
	ncNO,    //游戏未结束
	ncWIN,   //游戏胜利
	ncLOSE   //游戏失败
};

class LEI {
public:
	int mState;
	int mStateBackup;
	bool isPressed;
};

class Game
{
public:
	sf::RenderWindow window;
	Game();
	~Game();
	int Window_width, Window_height, stageWidth, stageHeight,mMineNum,mFlagclc;
	int gamelvl, mTime;//游戏难度，游戏计时
	bool gameOver, gameQuit;
	LEI mGameData[LVL3_HEIGHT][LVL3_WIDTH];
	bool isGameBegin;  //游戏是否开始
	int isGameOverState;//游戏结束的状态
	sf::Vector2i mCornPoint; //舞台的做顶点坐标
	int gridsize;
	int imgBGNo, imgSkinNo;
	int mouse_RL_ClkReady;
	bool RL_ClkJudge_flag, mouseDlbClkReady;
	float Xscale, Yscale;


	sf::Texture tBackground, tTitles, tButtons, tNum, tTimer, tCounter, tGameOver; //创建纹理对象
	sf::Sprite sBackground, sTitles, sButtons, sNum, sTimer, sCounter, sGameOver; //创建精灵对象
	sf::IntRect ButtonRectEasy, ButtonRectNormal, ButtonRectHard, ButtonRectBG, ButtonRectSkin, ButtonRectRestart, ButtonRectQuit;

	sf::SoundBuffer sbWin, sbBoom;
	sf::Sound soundWin,soundBoom;
	sf::Music bkMusic;

	sf::Clock gameClock, mouseClickTimer;

	void Run();

	void InitialStage();
	void Initial();
	void IniData();
	void LoadMediaData();
	void MineSet(int Py, int Px); //布雷

	void ButtonReleased(sf::Vector2i mPoint);
	void Input();
	void NullClick(int j, int i);
	void RButtonDown(sf::Vector2i mPoint);  //鼠标右击
	void LButtonDown(sf::Vector2i mPoint);  //鼠标左击
	void LButtonDblClk(sf::Vector2i mPoint); //鼠标左键双击
	void RL_ButtonDown(sf::Vector2i mPoint);//鼠标左右击
	

	void Logic();
	void updownOpen();
	void isWin();
	void unCover();

	void Draw();
	void DrawGrid();
	void DrawButton();
	void DrawScore();
	void DrawTimer();
	void DrawGameEnd();

};

