#include "Game.h"

Game::Game() {
	Window_width = 860;
	Window_height = 600;
	mouse_RL_ClkReady = 0;
	RL_ClkJudge_flag = false;
	mouseDlbClkReady = false;

	gamelvl = 2;
	window.create(sf::VideoMode(Window_width, Window_height), L"MineSweeper by zx",sf::Style::Close);
	//window.create(sf::VideoMode(Window_width, Window_height), L"MineSweeper by zx", sf::Style::Titlebar);
	//window.create(sf::VideoMode(Window_width, Window_height), L"MineSweeper by zx",sf::Style::None);
	//window.create(sf::VideoMode(Window_width, Window_height), L"MineSweeper by zx", sf::Style::Default);
}

Game::~Game() {

}

void Game::InitialStage() {
	Xscale = 860.0 / Window_width*1.0;
	Yscale = 600.0 / Window_height * 1.0;

	switch (gamelvl) {
	case 1:
		stageHeight = LVL1_HEIGHT;
		stageWidth = LVL1_WIDTH;
		mMineNum = LVL1_NUM;
		mCornPoint.x = (Window_width - stageWidth * GRIDSIZE) / 2;  //������̨���Ͻǵ�����
		mCornPoint.y = (Window_height - stageHeight * GRIDSIZE) / 2;
		break;
	case 2:
		stageHeight = LVL2_HEIGHT;
		stageWidth = LVL2_WIDTH;
		mMineNum = LVL2_NUM;
		mCornPoint.x = (Window_width - stageWidth * GRIDSIZE) / 2;  //������̨���Ͻǵ�����
		mCornPoint.y = (Window_height - stageHeight * GRIDSIZE) / 2;
		break;
	case 3:
		stageHeight = LVL3_HEIGHT;
		stageWidth = LVL3_WIDTH;
		mMineNum = LVL3_NUM;
		mCornPoint.x = (Window_width - stageWidth * GRIDSIZE) / 2;  //������̨���Ͻǵ�����
		mCornPoint.y = (Window_height - stageHeight * GRIDSIZE) / 2;
		break;

	default:
		break;
	}
}

void Game::Initial() {

	window.setFramerateLimit(90);//ÿ������Ŀ��֡��
	gridsize = GRIDSIZE;//�����λ�õĿ�Ĵ�С
	//window.clear();

	InitialStage();
	

	gameOver = false;
	gameQuit = false;
	isGameOverState = ncNO;    //��ʼ����Ϸ�Ľ���״̬
	mFlagclc = 0;              //��ʼ�����ӵ�����
	isGameBegin = false;       //��ʼ����Ϸ�Ƿ�ʼ
	mTime = 0;                 //��ʼ����Ϸ���е�ʱ��
	imgBGNo = 1;
	imgSkinNo = 1;
	mouse_RL_ClkReady = 0;
	RL_ClkJudge_flag = false;
	
	

	IniData();//��ʼ������
	LoadMediaData();
}

void Game::IniData() {
	int i, j = 0;
	for (j = 0; j < stageHeight; j++) {    //���п�����Ϊ����δ���
		for (i = 0; i < stageWidth; i++) {
			mGameData[j][i].isPressed = false;
			mGameData[j][i].mState = ncUNDOWN;
			//mGameData[j][i].mState = ncFLAG;
		}
	}
}

void Game::LoadMediaData() {
	std::stringstream ss;
	ss << "data/images/BK0" << imgBGNo << ".jpg";
	if (!tBackground.loadFromFile(ss.str())) {
		std::cout << "BK image û���ҵ�"<<std::endl;
	}
	ss.str("");

	ss << "data/images/Game" << imgSkinNo << ".jpg";
	if (!tTitles.loadFromFile(ss.str())) {
		std::cout << "game skin image û���ҵ�" << std::endl;
	}
	ss.str("");
	if (!tNum.loadFromFile("data/images/num.jpg")) {
		std::cout << "num.jpg û���ҵ�" << std::endl;
	}
	if (!tTimer.loadFromFile("data/images/jishiqi.jpg")) {
		std::cout << "jishiqi.jpg û���ҵ�" << std::endl;
	}
	if (!tCounter.loadFromFile("data/images/jishuqi.jpg")) {
		std::cout << "jishuqi.jpg û���ҵ�" << std::endl;
	}
	if (!tButtons.loadFromFile("data/images/button.jpg")) {
		std::cout << "button.jpg û���ҵ�" << std::endl;
	}
	if (!tGameOver.loadFromFile("data/images/gameover.jpg")) {
		std::cout << "gameover.jpg û���ҵ�" << std::endl;
	}

	sBackground.setTexture(tBackground);
	sTitles.setTexture(tTitles);
	sButtons.setTexture(tButtons);
	sNum.setTexture(tNum);
	sTimer.setTexture(tTimer);
	sCounter.setTexture(tCounter);
	sGameOver.setTexture(tGameOver);
}

void Game::MineSet(int Py, int Px) {
	int mCount, i, j, k, l;
	mCount = 0;

	srand(time(NULL));//�õ�ǰϵͳʱ����Ϊ�����������������
	do {
		k = rand() % stageHeight;//���������
		l = rand() % stageWidth;
		//if (k == Py && l == Px) continue;      //���������Ϊ��һ�ε����λ�ã�����������

		if(k>=Py-1&&k<=Py+1&&l>=Px-1&&l<=Px+1) continue; //��Χ������û����


		if (mGameData[k][l].mState == ncUNDOWN) {
			mGameData[k][l].mState = ncMINE;
			mGameData[k][l].mStateBackup = ncMINE;//����״̬
			mCount++;
		}
	} while (mCount != mMineNum);
	//����ֵ
	for (i = 0; i < stageHeight; i++) {
		for (j = 0; j < stageWidth; j++) {
			if (mGameData[i][j].mState != ncMINE) {
				mCount = 0;
				for(k=i-1;k<i+2;k++)
					for(l=j-1;l<j+2;l++)
						if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth) {
							if (mGameData[k][l].mState == ncMINE) {
								mCount++;
							}
						}//���㣨i��j����Χ�׵�����
				switch (mCount) {
				case 0:
					mGameData[i][j].mState = ncNULL;
					break;
				case 1:
					mGameData[i][j].mState = ncONE;
					break;
				case 2:
					mGameData[i][j].mState = ncTWO;
					break;
				case 3:
					mGameData[i][j].mState = ncTHREE;
					break;
				case 4:
					mGameData[i][j].mState = ncFOUR;
					break;
				case 5:
					mGameData[i][j].mState = ncFIVE;
					break;
				case 6:
					mGameData[i][j].mState = ncSIX;
					break;
				case 7:
					mGameData[i][j].mState = ncSEVEN;
					break;
				case 8:
					mGameData[i][j].mState = ncEIGHT;
					break;
				default:
					break;
				}
			}
		}
	}
	

}//����


void Game::ButtonReleased(sf::Vector2i mPoint) {
	int i, j, k, l;
	i = (mPoint.x - mCornPoint.x) / gridsize;
	j = (mPoint.y - mCornPoint.y) / gridsize;
	for (k = j - 1; k < j + 2; k++)
		for (l = i - 1; l < i + 2; l++)  //������Χ�˸�����
			if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth) {
				if (mGameData[k][l].mState == ncX) {
					mGameData[k][l].isPressed = false;
					mGameData[k][l].mState = mGameData[k][l].mStateBackup;
				}
			}
}

void Game::Input() {
	sf::Event event;
	sf::Vector2i p2;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
			gameQuit = true;
		}

		if (event.type == sf::Event::EventType::KeyReleased&&event.key.code==sf::Keyboard::Escape) {
			window.close();
			gameQuit = true;
		}

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			p2 = sf::Mouse::getPosition(window);
			if (isGameOverState == ncNO) {
				if (mouseClickTimer.getElapsedTime().asMilliseconds() > 150) {
					std::cout << "Mouse::Left Pressed" << std::endl;
					LButtonDown(p2);//����������
					mouseDlbClkReady = true;
					mouse_RL_ClkReady++;
					if (mouse_RL_ClkReady == 2) {
						RL_ButtonDown(sf::Mouse::getPosition(window));

					}
				}
				else {
					std::cout << "Mouse::Left Double Clicked" << std::endl;
					LButtonDblClk(p2);//������˫��
					mouseDlbClkReady = false;
				}
			}
			
		}
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
			if (isGameOverState == ncNO) {
				mouseClickTimer.restart();
				std::cout << "Mouse::Left Released" << std::endl;
				mouse_RL_ClkReady = 0;
				//p1 = Mouse::getPosition(window);
				if (isGameBegin == false) {
					if (ButtonRectEasy.contains(event.mouseButton.x, event.mouseButton.y))gamelvl = 1;
					if (ButtonRectNormal.contains(event.mouseButton.x, event.mouseButton.y))gamelvl = 2;
					if (ButtonRectHard.contains(event.mouseButton.x, event.mouseButton.y))gamelvl = 3;
					Initial();
				}
			}
			
			if (ButtonRectBG.contains(event.mouseButton.x, event.mouseButton.y)) {
				imgBGNo++;
				if (imgBGNo > 7) {
					imgBGNo = 1;
				}
				LoadMediaData();
			}
			if (ButtonRectSkin.contains(event.mouseButton.x, event.mouseButton.y)) {
				imgSkinNo++;
				if (imgSkinNo > 6) imgSkinNo = 1;
				LoadMediaData();
			}
			if (ButtonRectRestart.contains(event.mouseButton.x, event.mouseButton.y)) {
				Initial();
			}
			if (ButtonRectQuit.contains(event.mouseButton.x, event.mouseButton.y)) {
				window.close();
				gameQuit = true;
			}
			for (int j = 0; j < stageHeight; j++) {
				for (int i = 0; i < stageWidth; i++) {
					if (mGameData[j][i].mState == ncX) mGameData[j][i].mState == ncUNDOWN;
				}
			}

			ButtonReleased(sf::Mouse::getPosition(window));
		}


		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
			if (isGameOverState == ncNO) {
				mouse_RL_ClkReady++;
				if (mouse_RL_ClkReady == 2) {
					RL_ButtonDown(sf::Mouse::getPosition(window)); //������һ�
				}
				else {
					RButtonDown(sf::Mouse::getPosition(window));
					std::cout << "Mouse::Right Pressed" << std::endl;//����һ�
				}
				
			}
		}
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
			if (isGameOverState == ncNO) {
				mouse_RL_ClkReady = 0;
				ButtonReleased(sf::Mouse::getPosition(window));
				std::cout << "Mouse::Right Released" << std::endl;
			}
			
		}
	}

}

void Game::NullClick(int j, int i) {
	int k, l;
	for (k = j - 1; k < j + 2; k++) {
		for (l = i - 1; l < i + 2; l++) {
			if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth) {
				if (mGameData[k][l].isPressed == false) {
					mGameData[k][l].isPressed = true;
					if (mGameData[k][l].mState == ncNULL) {
						NullClick(k, l);
					}
				}
			}
		}
	}
}

void  Game::RButtonDown(sf::Vector2i mPoint) {
	int i, j;
	i = (mPoint.x - mCornPoint.x) / gridsize;
	j = (mPoint.y - mCornPoint.y) / gridsize;
	if (i >= 0 && i < stageWidth && j>=0 && j < stageHeight) {
		if (isGameBegin == false) {
			LButtonDown(mPoint);
		}
		if (mGameData[j][i].isPressed == false) {
			mGameData[j][i].isPressed = true;
			mGameData[j][i].mStateBackup = mGameData[j][i].mState;
			mGameData[j][i].mState = ncFLAG;
			mFlagclc++;
		}
		else{
			if (mGameData[j][i].mState == ncFLAG) {
				mGameData[j][i].isPressed = true;
				mGameData[j][i].mState = ncQ;
				mFlagclc--;
			}
			else if (mGameData[j][i].mState == ncQ) {
				mGameData[j][i].isPressed = false;
				mGameData[j][i].mState = mGameData[j][i].mStateBackup;
			}

		}
	}


}  //����һ�

void  Game::LButtonDown(sf::Vector2i mPoint) {
	int i, j;
	i = (mPoint.x - mCornPoint.x) / gridsize;
	j = (mPoint.y - mCornPoint.y) / gridsize;
	if (i *Xscale>= 0 && i*Xscale < stageWidth && j *Yscale>= 0 && j *Yscale< stageHeight) {
		if (isGameBegin == false) {
			isGameBegin = true;
			gameClock.restart();
			MineSet(j, i);
		}
		if (mGameData[j][i].mState != ncFLAG) {          //���״̬��������
			if (mGameData[j][i].isPressed == false) {
				mGameData[j][i].isPressed = true;
				if (mGameData[j][i].mState == ncMINE) {
					isGameBegin = false;
					isGameOverState = ncLOSE;
					mGameData[j][i].mState = ncBOMBING;
					unCover();
				}
				if (mGameData[j][i].mState == ncNULL) { //�����ǰ��Ϊ�գ���Χ8���������ף�
					NullClick(j,i);                      //����δ������Ŀտ�
				}
			}
		}
	}


}  //������

void  Game::LButtonDblClk(sf::Vector2i mPoint) {
	int i,j,k,l,lvl;
	bool flag_MineFound=true;
	i = (mPoint.x - mCornPoint.x) / gridsize;
	j = (mPoint.y - mCornPoint.y) / gridsize;

	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight) //�����ڷ�Χ��
	{
		if (mGameData[j][i].isPressed == true)   //��������
		{
			if (mGameData[j][i].mState != ncFLAG)    //��ǰ�鲻������
				for (k = j - 1; k < j + 2; k++)
					for (l = i - 1; l < i + 2; l++)  //������Χ�˸�����
						if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth) 
						{
							if (mGameData[k][l].mState == ncFLAG) 
							{
								if (mGameData[k][l].mStateBackup != ncMINE) 
								{
									isGameOverState = ncLOSE;
									isGameBegin = false;
									unCover();
								}
							}
							else 
							{
								if (mGameData[k][l].isPressed == false) 
								{
									//mGameData[k][l].isPressed = true;
									if (mGameData[k][l].mState == ncMINE) 
									{
										flag_MineFound = false;
										//isGameOverState = ncLOSE;
										//isGameBegin = false;
										//mGameData[k][l].mState = ncBOMBING;
										//unCover();
									}
									//if (mGameData[k][l].mState == ncNULL) 
									//{
										//NullClick(k,l);
									//}
								}
							}
						
					
				
			}
			for (k = j - 1; k < j + 2; k++)
				for (l = i - 1; l < i + 2; l++)  //������Χ�˸�����
					if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth) {
						if (flag_MineFound == false) {
							if (mGameData[k][l].isPressed == false) {
								mGameData[k][l].mStateBackup = mGameData[k][l].mState;
								mGameData[k][l].mState = ncX;
							}
						}
						else {
							if (mGameData[k][l].isPressed == false) {
								mGameData[k][l].isPressed = true;
								if (mGameData[k][l].mState == ncNULL) {
									NullClick(k, l);
								}
							}
						}
					}
		}

	}

	//if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight) //�����ڷ�Χ��
	//{
	//	if (mGameData[j][i].isPressed == true)
	//	{
	//		if(mGameData[j][i].mState!=ncFLAG&&mGameData[j][i].mState!=ncQ)
	//			for(k=j-1;k<j+2;k++)
	//				for(l=i-1;l<i+2;l++)
	//					if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth)
	//						if (mGameData[k][l].isPressed == false)
	//						{
	//							mGameData[k][l].isPressed == true;
	//							mGameData[k][l].mState = ncX;
	//						}
	//	}
	//	else {
	//		for (k = j - 1; k < j + 2; k++)
	//			for (l = i - 1; l < i + 2; l++)
	//				if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth)
	//					if (mGameData[k][l].isPressed == false)
	//					{
	//						mGameData[k][l].isPressed = true;
	//						mGameData[k][l].mState = ncX;
	//					}
	//		mGameData[k][l].isPressed = false;
	//				
	//	}
	//}


} //������˫��

void Game::RL_ButtonDown(sf::Vector2i mPoint) {
	std::cout << "������һ�" << std::endl;
	/*int i, j, k, l;
	i = (mPoint.x - mCornPoint.x) / gridsize;
	j = (mPoint.y - mCornPoint.y) / gridsize;
	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)
	{
		if (mGameData[j][i].isPressed == true)
		{
			if(mGameData[j][i].mState!=ncFLAG&&mGameData[j][i].mState!=ncQ)
				for(k=j-1;k<j+2;k++)
					for(l=i-1;l<i+2;l++)
						if(k>=0&&k<stageHeight&&l>=0&&l<stageWidth)
							if (mGameData[k][l].isPressed == false)
							{
								mGameData[k][l].mStateBackup = mGameData[k][l].mState;
								mGameData[k][l].mState = ncX;
								mGameData[k][l].isPressed == true;

							}
		}
		else {
			for (k = j - 1; k < j + 2; k++)
				for (l = i - 1; l < i + 2; l++)
					if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth)
		}
	}*/
	int i, j, k, l, lvl;
	bool flag_MineFound = true;
	i = (mPoint.x - mCornPoint.x) / gridsize;
	j = (mPoint.y - mCornPoint.y) / gridsize;

	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight) //�����ڷ�Χ��
	{
		if (mGameData[j][i].isPressed == true && mGameData[j][i].mState!=ncFLAG)   //��������
		{
			if (mGameData[j][i].mState != ncFLAG)    //��ǰ�鲻������
				for (k = j - 1; k < j + 2; k++)
					for (l = i - 1; l < i + 2; l++)  //������Χ�˸�����
						if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth)
						{
							if (mGameData[k][l].mState == ncFLAG)
							{
								if (mGameData[k][l].mStateBackup != ncMINE)
								{
									isGameOverState = ncLOSE;
									isGameBegin = false;
									unCover();
								}
							}
							else
							{
								if (mGameData[k][l].isPressed == false)
								{
									if (mGameData[k][l].mState == ncMINE)
									{
										flag_MineFound = false;
									}
								}
							}
						}
			for (k = j - 1; k < j + 2; k++)
				for (l = i - 1; l < i + 2; l++)  //������Χ�˸�����
					if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth) {
						if (flag_MineFound == false) {
							if (mGameData[k][l].isPressed == false) {
								mGameData[k][l].mStateBackup = mGameData[k][l].mState;
								mGameData[k][l].mState = ncX;
							}
						}
						else {
							if (mGameData[k][l].isPressed == false) {
								mGameData[k][l].isPressed = true;
								if (mGameData[k][l].mState == ncNULL) {
									NullClick(k, l);
								}
							}
						}
					}
		}

	}
}



void Game::Logic() {
	sf::Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;
	Window_height = height;
	Window_width = width;
	InitialStage();
	window.setSize(sf::Vector2u(size.x, size.y));
	//std::cout << Window_width << std::endl << Window_height << std::endl;
	isWin();

}

void  Game::isWin(){
	int i, j, c = 0;
	if (mFlagclc == mMineNum) {
		for (i = 0; i < stageWidth; i++)
			for (j = 0; j < stageHeight; j++) {
				if (mGameData[j][i].mState == ncFLAG) {
					if (mGameData[j][i].mStateBackup == ncMINE) {
						c++;
					}
				}
			}
	}
	else {
		if (isGameOverState != ncLOSE) {
			for(i=0;i<stageWidth;i++)
				for (j = 0; j < stageHeight; j++) {
					if (mGameData[j][i].isPressed == false || mGameData[j][i].mState == ncFLAG) ;
				}
		}

	}
	if (c == mMineNum) {
		mFlagclc = mMineNum;
		DrawScore();
		updownOpen();
		isGameBegin = false;
		isGameOverState = ncWIN;
	}

}

void Game::updownOpen() {
	int i, j;
	for (j = 0; j < stageHeight; j++) {
		for (i = 0; i < stageWidth; i++) {
			if (mGameData[j][i].isPressed == false) {
				mGameData[j][i].isPressed = true;
				if (mGameData[j][i].mState == ncMINE) mGameData[j][i].mState = ncFLAG;
			}
		}
	}
}

void  Game::unCover(){
	int i, j;
	for(j=0;j<stageHeight;j++)
		for (i = 0; i < stageWidth; i++)
		{
			if (mGameData[j][i].isPressed == false) {
				if (mGameData[j][i].mState == ncMINE) {
					mGameData[j][i].isPressed = true;
					mGameData[j][i].mState = ncUNFONUD;
				}
			}
		}

}



void Game::Draw() {
	window.clear();

	//���Ʊ���
	sBackground.setPosition(0, 0);
	window.draw(sBackground);

	DrawGrid();
	DrawButton();
	DrawScore();
	DrawTimer();

	if (isGameOverState) {
		DrawGameEnd();
	}

	window.display();//����ʾ����������ʾ����Ļ�ϣ�˫�������

}

void  Game::DrawGrid(){
	int i, j;
	for (j = 0; j < stageHeight; j++) {
		for (i = 0; i < stageWidth; i++) {
			if (mGameData[j][i].isPressed == true) {
				sTitles.setTextureRect(sf::IntRect(mGameData[j][i].mState * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
				sTitles.setPosition(mCornPoint.x + i * GRIDSIZE, mCornPoint.y + j * GRIDSIZE);
			}
			else{
				if (mGameData[j][i].mState == ncX) {
					sTitles.setTextureRect(sf::IntRect(ncX * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
					sTitles.setPosition(mCornPoint.x + i * GRIDSIZE, mCornPoint.y + j * GRIDSIZE);
				}
				else {
					sTitles.setTextureRect(sf::IntRect(ncUNDOWN * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
					sTitles.setPosition(mCornPoint.x + i * GRIDSIZE, mCornPoint.y + j * GRIDSIZE);
					//sTitles.setPosition(stageHeight/2, stageWidth/2);
				}
			}
			window.draw(sTitles);
		}
	}
}

void  Game::DrawButton(){
	sf::Vector2i LeftCorner;
	int ButtonWidth = 60;
	int ButtonHeight = 36;
	int detaX;
	detaX = (Window_width - ButtonWidth * 7) / 8;
	LeftCorner.y = Window_height - GRIDSIZE * 3;

	//ButtonRectEasy
	LeftCorner.x = detaX;
	sButtons.setTextureRect(sf::IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectEasy.left = LeftCorner.x;
	ButtonRectEasy.top = LeftCorner.y;
	ButtonRectEasy.width = ButtonWidth;
	ButtonRectEasy.height = ButtonHeight;
	window.draw(sButtons);
	
	//ButtonRectNormal
	LeftCorner.x = detaX*2+ButtonWidth;
	sButtons.setTextureRect(sf::IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectNormal.left = LeftCorner.x;
	ButtonRectNormal.top = LeftCorner.y;
	ButtonRectNormal.width = ButtonWidth;
	ButtonRectNormal.height = ButtonHeight;
	window.draw(sButtons);

	//ButtonRectHard
	LeftCorner.x = detaX * 3 + ButtonWidth * 2;
	sButtons.setTextureRect(sf::IntRect(2 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectHard.left = LeftCorner.x;
	ButtonRectHard.top = LeftCorner.y;
	ButtonRectHard.width = ButtonWidth;
	ButtonRectHard.height = ButtonHeight;
	window.draw(sButtons);
	
	//ButtonRectBG
	LeftCorner.x = detaX * 4 + ButtonWidth * 3;
	sButtons.setTextureRect(sf::IntRect(3 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectBG.left = LeftCorner.x;
	ButtonRectBG.top = LeftCorner.y;
	ButtonRectBG.width = ButtonWidth;
	ButtonRectBG.height = ButtonHeight;
	window.draw(sButtons);
	
	//ButtonRectSkin
	LeftCorner.x = detaX * 5 + ButtonWidth * 4;
	sButtons.setTextureRect(sf::IntRect(4 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectSkin.left = LeftCorner.x;
	ButtonRectSkin.top = LeftCorner.y;
	ButtonRectSkin.width = ButtonWidth;
	ButtonRectSkin.height = ButtonHeight;
	window.draw(sButtons);
	
	//ButtonRectRestart
	LeftCorner.x = detaX * 6 + ButtonWidth * 5;
	sButtons.setTextureRect(sf::IntRect(5 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectRestart.left = LeftCorner.x;
	ButtonRectRestart.top = LeftCorner.y;
	ButtonRectRestart.width = ButtonWidth;
	ButtonRectRestart.height = ButtonHeight;
	window.draw(sButtons);
	
	// ButtonRectQuit
	LeftCorner.x = detaX * 7 + ButtonWidth * 6;
	sButtons.setTextureRect(sf::IntRect(6 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectQuit.left = LeftCorner.x;
	ButtonRectQuit.top = LeftCorner.y;
	ButtonRectQuit.width = ButtonWidth;
	ButtonRectQuit.height = ButtonHeight;
	window.draw(sButtons);


}

void  Game::DrawScore(){
	int NumSize = sNum.getLocalBounds().height;
	sf::Vector2i LeftCorner;
	LeftCorner.x = Window_width-sCounter.getLocalBounds().width *1.25;
	LeftCorner.y = sCounter.getLocalBounds().height * 0.5;
	sCounter.setPosition(LeftCorner.x , LeftCorner.y );
	window.draw(sCounter);

	LeftCorner.x = LeftCorner.x + NumSize*6.3;
	LeftCorner.y = LeftCorner.y + NumSize*0.35;
	

	int mScore = mMineNum - mFlagclc;
	//int mScore = 999;

	//���Ƹ�λ��������
	int a = mScore % 10;
	sNum.setTextureRect(sf::IntRect(a * NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//����ʮλ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x -= NumSize;
	sNum.setTextureRect(sf::IntRect(a * NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//���ư�λ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x -= NumSize;
	sNum.setTextureRect(sf::IntRect(a * NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
}

void  Game::DrawTimer(){
	
	sf::Vector2i LeftCorner;
	LeftCorner.x = sTimer.getLocalBounds().width * 0.25;
	LeftCorner.y = sTimer.getLocalBounds().height * 0.5;
	sTimer.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sTimer);

	if (isGameBegin) {
		mTime = gameClock.getElapsedTime().asSeconds();
	}
	int NumSize = sNum.getLocalBounds().height;
	LeftCorner.x = LeftCorner.x + sTimer.getLocalBounds().width - NumSize * 1.5;
	LeftCorner.y = LeftCorner.y + sTimer.getGlobalBounds().height * 0.5 - NumSize*0.5;

	int mScore = mTime;
	if (mScore > 999) mScore = 999;
	//���Ƹ�λ��������
	int a = mScore % 10;
	sNum.setTextureRect(sf::IntRect(a * NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//����ʮλ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x -= NumSize;
	sNum.setTextureRect(sf::IntRect(a * NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//���ư�λ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x -= NumSize;
	sNum.setTextureRect(sf::IntRect(a * NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);

}

void  Game::DrawGameEnd(){
	sf::Vector2i LeftCorner;
	int ButtonWidth = 200;
	int ButtonHeight = sGameOver.getLocalBounds().height;
	LeftCorner.x = (Window_width - ButtonWidth) / 2;
	LeftCorner.y = (Window_height - ButtonHeight) / 2;

	sGameOver.setPosition(LeftCorner.x, LeftCorner.y);

	if (isGameOverState == ncWIN) {
		sGameOver.setTextureRect(sf::IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	}
	if (isGameOverState == ncLOSE) {
		sGameOver.setTextureRect(sf::IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	}
	window.draw(sGameOver);
}



void Game::Run() {
	do 
	{
		Initial();
		while (window.isOpen()&&gameOver==false) {
			Input();
			Logic();
			Draw();
		}
	} while (!gameQuit);
}


