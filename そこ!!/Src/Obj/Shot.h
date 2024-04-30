#pragma once
#include<list>
#include<vector>
#include<memory>
#include"../Manager/InputManager.h"
#include"Player.h"

class Player;
class GameScene;

class Shot
{
public:
	Shot(float Screenx, float Screeny, std::shared_ptr<Player>  player);
	~Shot(void);
	void Init(void);
	void Update();
	void Draw(void);
	const Player::TYPE GetPlayerType();
	const bool IsPlayerAlive();

	struct Bullet
	{
		Vector2 pos;//À•W 
		Vector2 vel;//‘¬“x
		Vector2 accel = { 0,0 };//‰Á‘¬“x
		bool isActive = false;//’e‚ª¶‚«‚Ä‚¢‚é‚©
		int count;
		std::list<Position2> history;
		float bulletRadius = 8.0f;	//’e‚Ì”¼Œa
	};
	std::vector<Bullet>& GetBullets();
	void HitEffect(Vector2 pos, Vector2 vel);	 
	std::shared_ptr<Player> player_;
protected:	
	Vector2 screensize;
	std::vector<Bullet> bullets;//1P‚Ì’e
	const int MaxNum = 3;
	//const Player& player_;
	float speed = 15.0f; //’e‚ÌƒXƒs[ƒh
	//friend Player;
	int soundH[4];
	int explodeH;
	int explode_frame;
	int hitImg_[20];
	int bulletImg_;
	unsigned int shotframe = 0;

private:

	void Shoot(Vector2 pos, Vector2  reti);
	bool lastShotButton = false;

};

