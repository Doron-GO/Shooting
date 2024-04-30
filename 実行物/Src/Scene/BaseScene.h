#pragma once
#include"../AbeUtility/Geometry.h"
#include"../Vector2D.h"
#include<memory>

class BaseScene;//���ꂪ�Ȃ��ƃG���[���o�遫��������
using sharedScene = std::shared_ptr<BaseScene>;

class BaseScene
{
public:

	 BaseScene(float screenSizeX , float screenSizeY);

	 //�o�[�`�������f�X�g���N�^��t���Ȃ��ƁA����̃f�X�g���N�^�����Ă΂ꂸ
	 //�h���̃f�X�g���N�^���Ă΂�Ȃ��Ȃ��Ă��܂�
	virtual ~ BaseScene();

	virtual bool Init(void)=0; 
	virtual  sharedScene Update(sharedScene ownScene)=0;
	virtual void Draw(void);

	enum class PLAYER_NUMBER
	{
		MIN,
		TWO_PLAYER,
		THREE_PLAYER,
		FOUR_PLAYER
	};

	int playerNumber ;
private:
	
protected:
	int TitleBackImg_;
	int meteoriteImg_;
	int playNum_;
	bool playNumDecisionFlag_;
	int oldkey_;
	int newkey_;
	int waitCount_ = 0;
	int LStickImg_;
	int StartImg_;
	int buttonImg[16];
	int screenID_;
	Vector2D screenSize_;
	virtual void DrawOwnScreen(void )= 0;

};

