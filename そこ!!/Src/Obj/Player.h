#pragma once
#include"../Manager/InputManager.h"
#include"../AbeUtility/Geometry.h"
//#include"Shot.h"

class Shot;
class Armor;
class homingShot;
#define InpMngInstance InputManager::GetInstance()

class Player
{public:

	const enum class TYPE
	{
		PLAYER1,
		PLAYER2,
		PLAYER3,
		PLAYER4
	};

	Player( float Screenx,  float Screeny, TYPE type );
	~Player();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Move(void);
	void ReticleMove();
	void Damage();
	Vector2 GetPlayerPos(void);	//�v���C���[�̍��W�����
	Vector2 GetReticlePos(void);	//�Ə��̍��W
	float GetRadius(void);//���a
	InputManager::JOYPAD_NO padNumber_;
	int life_ ;

	const bool IsAlive(void);
	const Player::TYPE GetType();	//��������P�Ȃ�̂������
	TYPE type_;
	bool aliveFlag_;
	Vector2 playerColor = { 0,0,0,0,0 };	//���e�B�N���̐F

protected:
	struct Reticle{
		Vector2 pos;
		Vector2 vel;
		Vector2 accel = { 0,0 };//�����x
	};
	Reticle reti_;
	Vector2 pos_;
	Vector2 vel_;
	Vector2 accel_ = { 0,0 };//�����x
private:

	int pidx;
	int Pspeed = 4;
	Vector2 screensize;
	void CalcDeg();
	//�v���C���[�̉摜�n���h��
	int playerH[10];
	int AddImg_;
	//�L�����N�^�[�t���[���Ǘ��p
	unsigned int frame = 0;
	int explodeH ;
	int explode_frame = 0;
	int explodeH2 ;
	int explode_frame2 = 0;

	//�v���C���[���a
	float playerRadius;
	float playerRadiusFull = 20.0f;
	float playerRadiusMedi = 15.0f;
	float playerRadiusLow = 10.0f;
	int soundH[3];
	//�v���C���[�ƏƏ��̊p�x
	Vector2 span_;
	float degree_;
	float reticleRadius = 9.0f;	//���e�B�N�����S���W
	int reticleImg_[121];
	int reticleCount_;
	int damageCount_ = 0;

};

