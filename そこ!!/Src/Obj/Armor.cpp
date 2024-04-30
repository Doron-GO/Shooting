#include "Armor.h"

Armor::Armor( float Screenx, float Screeny, std::shared_ptr<Player> player)// : player_(player)
{
	player_ = player;
	ScreenSize.x = Screenx;
	ScreenSize.y = Screeny;
}

Armor::~Armor(void)
{
}

void Armor::Init(void)
{
	//LoadDivGraph("Src/img/G_sarasara.png", 20, 4, 5, 64, 64, barrierH);

	LoadDivGraph("Src/img/storm_gabi.png", 12, 4, 3, 64, 104, stormH);
	LoadDivGraph("Src/img/Attac.png", 10, 10, 1, 32, 32, FlagmentImg_);
	switch (player_->GetType())
	{
	case Player::TYPE::PLAYER1:
		LoadDivGraph("Src/img/senkeiG.png", 20, 4, 5, 64, 64, barrierImg_);
		//LoadDivGraph("Src/img/ololol.png", 20, 4, 5, 64, 64, barrierH);
		color = 0x0000ff;
		break;
	case Player::TYPE::PLAYER2:
		LoadDivGraph("Src/img/senkeiR.png", 20, 4, 5, 64, 64, barrierImg_);
		color = 0x0000ff;
		break;
	case Player::TYPE::PLAYER3:
		color = 0x00ff00;
		LoadDivGraph("Src/img/hokannasiblue.png", 20, 4, 5, 64, 64, barrierImg_);
		break;
	case Player::TYPE::PLAYER4:
		color = 0xfff000;
		LoadDivGraph("Src/img/hokannasiblue.png", 20, 4, 5, 64, 64, barrierImg_);
		break;
	default:
		break;
	}
	AllFragmentFlag = false;
	AllShieldFlag = true;
	for (int shotNum = 0; shotNum < MaxShotNum; shotNum++)
	{
		armorShots_.emplace_back(ARMOR_SHOT());
	}
	for (int shieldNum = 0; shieldNum < MaxShieldNum; shieldNum++)
	{
		armorShields_.emplace_back(ARMOR_SHIELD());
	}
}

void Armor::Update()
{
	CastOff();
	Shield();
}


void Armor::Draw(void)
{
	FlagmentIdx_ ;
	for (auto& shot : armorShots_){
		if (shot.isActive){
			//DrawCircle(shot.pos.x, shot.pos.y, shot.bulletRadius, color, true);
			SetDrawBright(player_->playerColor.intx, player_->playerColor.inty, player_->playerColor.intz);
			DrawRectRotaGraph2F(shot.pos.x, shot.pos.y, 0.0f, 0.0f,
				32.0f, 32.0f, 16.0f, 16.0f, 2.0f, 0.0f, FlagmentImg_[FlagmentIdx_/5], true);
			SetDrawBright(255, 255, 255);

		}
	}
	if (FlagmentIdx_ > 50) { FlagmentIdx_ = 0; }


	barrierIdx = (shieldFrame/5%16)+3;
	for (auto& shield : armorShields_) {
		if (shield.isActive) {
			//DrawGraphF(shield.pos.x, shield.pos.y, barrierH[5], true);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (shield.life*90)-10);
			DrawRectRotaGraph2F(shield.pos.x,shield.pos.y, 0, 0,
				64.0f, 64.0f, 32.0f, 32.0f, 1.0, 0, barrierImg_[barrierIdx], true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	if (castoffFrame > 0){
		SetDrawBright(player_->playerColor.intx, player_->playerColor.inty, player_->playerColor.intz);
		DrawRectRotaGraph2F(player_->GetPlayerPos().x, player_->GetPlayerPos().y,
			0, 0,64.0f, 104.0f, 32.0f, 52.0f, 2.0, 0, stormH[castoffFrame], true);
		SetDrawBright(255, 255, 255);
		--castoffFrame;
	}
	++shieldFrame;
	FlagmentIdx_++;
}

void Armor::CastOff()
{
	auto& pad = InpMngInstance;
	if(player_->life_>0)
	{//ï˙éÀíeÇé¿ëï
		if (pad.IsPadBtnTrgDown(player_->padNumber_, InputManager::JOYPAD_BTN::R_TRIGGER) &&!AllFragmentFlag)
		{
			//ÅôÉQÉbÉgä÷êîÇégÇ§Ç©Ç«Ç§Ç©ÇÕç°ó~ÇµÇ¢Ç©ÅAÇ≈åàÇﬂÇÈ
			float angle =atan2f(player_->GetPlayerPos().y, player_->GetPlayerPos().x);
			AllFragmentFlag = true;
			for (auto& fragment : armorShots_)
			{
				if (fragment.isActive) {
					continue;
				}
				//äpìxÇàÍÇ¬Ç∏Ç¬ïœÇ¶ÇÈ
				fragment.pos = player_->GetPlayerPos();
				const float theta =30.0f/ DX_TWO_PI_F ;//àÍâÒÇ†ÇΩÇËÇ…êiÇﬁäpìx
				fragment.vel={ cosf(angle),sinf(angle) };
				fragment.vel *= (fragment.speed);
				fragment.isActive = true;
				angle +=theta;
			}
			player_->Damage();
			if (castoffFrame <= 0){
				castoffFrame = 12;
			}
		} 
	}
	for (auto& fragment : armorShots_) {
		if (!fragment.isActive) {
			continue;
		}
		fragment.pos += fragment.vel;
		//fragment.vel *= 1.03f;
		//íeÇéEÇ∑
		if (fragment.pos.x + 12.0f < 0 || fragment.pos.x - 12.0f > ScreenSize.x ||
			fragment.pos.y + 24.0f < 0 || fragment.pos.y - 24.0f > ScreenSize.y) {
			fragment.isActive = false;		
			FragmentCount++;
		}
		if (FragmentCount >= MaxShotNum-1){
			AllFragmentFlag = false;
			fragment.speed =5.0f;
			FragmentCount = 0;
		}

	}

}

void Armor::Shield()
{
	auto& pad = InpMngInstance;
	if (player_->life_ > 0)	{
		if (pad.IsPadBtnTrgDown(player_->padNumber_, InputManager::JOYPAD_BTN::L_TRIGGER))	{
			if (AllShieldFlag)
			{
				Vector2 vel = player_->GetReticlePos()-player_->GetPlayerPos();
				float angle = atan2f(vel.y, vel.x);
				const float theta = static_cast<float>(30.0f)/DX_TWO_PI_F ;//àÍâÒÇ†ÇΩÇËÇ…êiÇﬁäpìx
				const float theta2 = static_cast<float>(90.0f)/DX_TWO_PI_F ;//àÍâÒÇ†ÇΩÇËÇ…êiÇﬁäpìx
				angle -= theta2;
				for (auto& shield : armorShields_){
					if (shield.isActive) {
						continue;
					}
					shield.pos = player_->GetPlayerPos();
					shield.vel = { cosf(angle), sinf(angle) };
					shield.vel.Normalize();
					shield.vel *= (55.0f);				
					shield.pos += shield.vel;
					shield.isActive = true;
					angle += theta;
				}
				AllShieldFlag = false;
				player_->Damage();
			}
		}
	}
	for (auto& shield : armorShields_) {
		if (!shield.isActive) {
			continue;
		}
		if (shield.life <= 0) {
			shield.isActive = false;
			shieldCount++;
		}
	}
	if (shieldCount >= MaxShieldNum){				
		AllShieldFlag = true;
		shieldCount = 0;
		for (auto& shield : armorShields_) 
		{
			shield.life = 3;
		}
	}
	if (player_->life_ > 0) {
		if (pad.IsPadBtnTrgDown(player_->padNumber_, InputManager::JOYPAD_BTN::LEFT)) {
			for (auto& shield : armorShields_) {
				if (!shield.isActive) {
					continue;
				}
				shield.isActive = false;
			}
		}
	}

}

float Armor::GetRadius()
{
	return 12.0f;
}

void Armor::HitFragmrnt(void)
{
	FragmentCount++;
}

const Player::TYPE Armor::GetPlayerType()
{
	return player_->type_;
}

std::vector<Armor::ARMOR_SHOT>& Armor::GetArmorShot()
{
	return armorShots_;
}

std::vector<Armor::ARMOR_SHIELD>& Armor::GetArmorShield(void)
{
	return armorShields_;
}
