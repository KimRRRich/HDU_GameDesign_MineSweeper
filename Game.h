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
	ncNULL,        //�յ�
	ncUNDOWN,      //��������
	ncMINE,        //����
	ncONE,         //����1
	ncTWO,         //����2
	ncTHREE,       //����3
	ncFOUR,        //����4
	ncFIVE,        //����5
	ncSIX,         //����6
	ncSEVEN,       //����7
	ncEIGHT,       //����8
	ncFLAG,        //���
	ncQ,           //�ʺ�
	ncX,           //����
	ncBOMBING,     //��ը����
	ncUNFONUD      //δ����������

};

typedef enum GAMEOVERSTAGE {
	ncNO,    //��Ϸδ����
	ncWIN,   //��Ϸʤ��
	ncLOSE   //��Ϸʧ��
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
	int gamelvl, mTime;//��Ϸ�Ѷȣ���Ϸ��ʱ
	bool gameOver, gameQuit;
	LEI mGameData[LVL3_HEIGHT][LVL3_WIDTH];
	bool isGameBegin;  //��Ϸ�Ƿ�ʼ
	int isGameOverState;//��Ϸ������״̬
	sf::Vector2i mCornPoint; //��̨������������
	int gridsize;
	int imgBGNo, imgSkinNo;
	int mouse_RL_ClkReady;
	bool RL_ClkJudge_flag, mouseDlbClkReady;
	float Xscale, Yscale;


	sf::Texture tBackground, tTitles, tButtons, tNum, tTimer, tCounter, tGameOver; //�����������
	sf::Sprite sBackground, sTitles, sButtons, sNum, sTimer, sCounter, sGameOver; //�����������
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
	void MineSet(int Py, int Px); //����

	void ButtonReleased(sf::Vector2i mPoint);
	void Input();
	void NullClick(int j, int i);
	void RButtonDown(sf::Vector2i mPoint);  //����һ�
	void LButtonDown(sf::Vector2i mPoint);  //������
	void LButtonDblClk(sf::Vector2i mPoint); //������˫��
	void RL_ButtonDown(sf::Vector2i mPoint);//������һ�
	

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

