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
		Vector2 pos{-10,-10};//���W++
		Vector2 vel;//���x
		Vector2 accel = { 0,0 };//�����x �g������
		bool isActive = false;//�e�������Ă��邩
		float bulletRadius = 32.0f;	//�e�̔��a]
		float speed = 5.0f;
	};
	 std::vector<ARMOR_SHOT>& GetArmorShot(void);

	struct ARMOR_SHIELD
	{
		Vector2 pos;//���W
		Vector2 vel;
		int life =3;
		bool isActive = false;//�e�������Ă��邩
		float shieldRadius = 30.0f;	//���̔��a

	};
	std::vector<ARMOR_SHIELD>& GetArmorShield(void);

private:
	std::shared_ptr<Player>player_;
	std::vector<ARMOR_SHOT>armorShots_;
	std::vector<ARMOR_SHIELD>armorShields_;
	Vector2 ScreenSize;

	void CastOff(void);	//�S���ʒe
	void Shield(void);	//���̐ݒu
	int color;
	const float bullet_speed = 5.0f;//�e�̃X�s�[�h

	int FlagmentImg_[10];
	int FlagmentIdx_;

	int barrierImg_[20]; //�V�[���h�̃O���t�B�b�N�n���h��
	int barrierIdx;

	int stormH[12];
	int stormIdx;
	unsigned int shieldFrame = 0;//�t���[���Ǘ��p
	unsigned int castoffFrame = 0;//�t���[���Ǘ��p
	unsigned int FlagmentFrame = 0;//�t���[���Ǘ��p


	int FragmentCount = 0;
	const float MaxShotNum = 25;	//�S���ʒe�̍ő�e��
	bool AllFragmentFlag;

	int MaxShieldNum = 4;
	bool AllShieldFlag;
	int shieldCount = 0;


};

