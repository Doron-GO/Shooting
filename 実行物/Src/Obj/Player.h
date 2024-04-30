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
	Vector2 GetPlayerPos(void);	//プレイヤーの座標を取る
	Vector2 GetReticlePos(void);	//照準の座標
	float GetRadius(void);//半径
	InputManager::JOYPAD_NO padNumber_;
	int life_ ;

	const bool IsAlive(void);
	const Player::TYPE GetType();	//自分が何Pなんのかを取る
	TYPE type_;
	bool aliveFlag_;
	Vector2 playerColor = { 0,0,0,0,0 };	//レティクルの色

protected:
	struct Reticle{
		Vector2 pos;
		Vector2 vel;
		Vector2 accel = { 0,0 };//加速度
	};
	Reticle reti_;
	Vector2 pos_;
	Vector2 vel_;
	Vector2 accel_ = { 0,0 };//加速度
private:

	int pidx;
	int Pspeed = 4;
	Vector2 screensize;
	void CalcDeg();
	//プレイヤーの画像ハンドル
	int playerH[10];
	int AddImg_;
	//キャラクターフレーム管理用
	unsigned int frame = 0;
	int explodeH ;
	int explode_frame = 0;
	int explodeH2 ;
	int explode_frame2 = 0;

	//プレイヤー半径
	float playerRadius;
	float playerRadiusFull = 20.0f;
	float playerRadiusMedi = 15.0f;
	float playerRadiusLow = 10.0f;
	int soundH[3];
	//プレイヤーと照準の角度
	Vector2 span_;
	float degree_;
	float reticleRadius = 9.0f;	//レティクル中心座標
	int reticleImg_[121];
	int reticleCount_;
	int damageCount_ = 0;

};

