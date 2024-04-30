#pragma once
#include<list>
#include<memory>
#include<vector>
#include"Player.h"
#include"Shot.h"
#include"../Manager/InputManager.h"

class Player;
class Armor
{
public:
	Armor( float Screenx, float Screeny, std::shared_ptr<Player> player);
	~Armor(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	const Player::TYPE GetPlayerType();
	float GetRadius(void);
	void HitFragmrnt(void);

	struct ARMOR_SHOT
	{
		Vector2 pos{-10,-10};//座標++
		Vector2 vel;//速度
		Vector2 accel = { 0,0 };//加速度 使うかも
		bool isActive = false;//弾が生きているか
		float bulletRadius = 32.0f;	//弾の半径]
		float speed = 5.0f;
	};
	 std::vector<ARMOR_SHOT>& GetArmorShot(void);

	struct ARMOR_SHIELD
	{
		Vector2 pos;//座標
		Vector2 vel;
		int life =3;
		bool isActive = false;//弾が生きているか
		float shieldRadius = 30.0f;	//盾の半径

	};
	std::vector<ARMOR_SHIELD>& GetArmorShield(void);

private:
	std::shared_ptr<Player>player_;
	std::vector<ARMOR_SHOT>armorShots_;
	std::vector<ARMOR_SHIELD>armorShields_;
	Vector2 ScreenSize;

	void CastOff(void);	//全方位弾
	void Shield(void);	//盾の設置
	int color;
	const float bullet_speed = 5.0f;//弾のスピード

	int FlagmentImg_[10];
	int FlagmentIdx_;

	int barrierImg_[20]; //シールドのグラフィックハンドル
	int barrierIdx;

	int stormH[12];
	int stormIdx;
	unsigned int shieldFrame = 0;//フレーム管理用
	unsigned int castoffFrame = 0;//フレーム管理用
	unsigned int FlagmentFrame = 0;//フレーム管理用


	int FragmentCount = 0;
	const float MaxShotNum = 25;	//全方位弾の最大弾数
	bool AllFragmentFlag;

	int MaxShieldNum = 4;
	bool AllShieldFlag;
	int shieldCount = 0;


};

