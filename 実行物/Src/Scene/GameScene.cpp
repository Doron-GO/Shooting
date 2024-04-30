#include<DxLib.h>
#include "Title.h"
#include "GameScene.h"
#include"../AbeUtility/AbeUtility.h"
#include"Transition/CrossOver.h"
#include"../../_debug/_DebugConOut.h"
#include"../../_debug/_DebugDispOut.h"

GameScene::GameScene(float screenSizeX, float screenSizeY, int playerNumber) :BaseScene(screenSizeX, screenSizeY)
{	
	//プレイ人数で生成する数を変えるplayerNumber_
	playerNumber_ =  playerNumber;
	survivorNum_ = playerNumber_;
	for (int i = 0; i < playerNumber_; i++)
	{
	  type_ = static_cast<Player::TYPE> (i);
	  players_.emplace_back(std::make_shared<Player>(screenSizeX, screenSizeY, type_));
	  shots_.emplace_back(std::make_unique<Shot>(screenSizeX, screenSizeY, players_[i]));
	  armor_.emplace_back(std::make_unique<Armor>(screenSizeX, screenSizeY, players_[i]));
	}
	for (int i = 0; i < playerNumber_; i++)
	{
		homingsShots_.emplace_back(std::make_unique<HomingShot>(shots_[i].get()->player_, this->players_));
	}	
	soundH[0] = LoadSoundMem("Src/Sound/w006.wav");
	soundH[1] = LoadSoundMem("Src/Sound/カーソル移動5.mp3");
	soundH[2] = LoadSoundMem("Src/Sound/決定ボタンを押す33.mp3");

	Init();
	TRACE("GameSceneの生成\n");
	DrawOwnScreen();
}

GameScene::~GameScene()
{
	TRACE("GameSceneの破棄\n");
}
bool GameScene::Init(void)
{
	count = 0;
	nextFlag = false;
	for (const auto & player : players_){
		player->Init();
	}
	for (const auto& shot : shots_){
		shot->Init();
	}
	for (const auto& homingsShot : homingsShots_) {
		homingsShot->Init();
	}
	for (const auto& armor : armor_){
		armor->Init();
	}
	LoadDivGraph("Src/Img/start_mes.png", 2, 1, 2, 420, 150, &StartImage_[0]);
	LoadDivGraph("Src/Img/Earth-Like planet.png", 77, 77, 1, 96, 96, backPlanet_);
	LoadDivGraph("Src/Img/win.png", 5, 1, 5, 600, 200, winImg_);
	LoadDivGraph("Src/Img/title_or_battle2.png", 2, 1, 2, 300, 100, title_or_battleImg_);
	playNumDecisionFlag_ = false;
	ChangeVolumeSoundMem(130, soundH[0]);
	bpCount = 0;
	playNum_ = 0;
	nextFlag = false;
	PlaySoundMem(soundH[0], DX_PLAYTYPE_LOOP, true);

	return true;
}

sharedScene GameScene::Update(sharedScene ownScene)
{
	auto cstate = InpMngInstance.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
	//ここの引数渡しもっとスマートにできるはず

	if (!Start()) {
		//各アップデート
		for (const auto& player : players_) {
			player->Update();
		}
		for (const auto& shot : shots_) {
			shot->Update();
		}
		for (const auto& homingsShot : homingsShots_) {
			homingsShot->Update();
		}
		for (const auto& a : armor_) {
			a->Update();
		}
	}
	DrawOwnScreen();
	if (!Start()) {
		//当たり判定が凄く行が増えたから関数に
		HitUpdate();
		Survival();
		if (nextFlag) {
			if (playNum_==1) {
				if (playNumDecisionFlag_ && waitCount_ > 100) {
					StopSoundMem(soundH[0]);
					return  std::make_unique<CrossOver>(std::move(ownScene),
						std::make_shared<GameScene>(screenSize_.x, screenSize_.y, playerNumber_), screenSize_.x, screenSize_.y);
				}
			}
			if (playNum_ == 0) {
				if (playNumDecisionFlag_ && waitCount_ > 100) {
					StopSoundMem(soundH[0]);
					return  std::make_unique<CrossOver>(std::move(ownScene),
						std::make_shared<TitleScene>(screenSize_.x, screenSize_.y), screenSize_.x, screenSize_.y);
				}
			}
			if (playNumDecisionFlag_) { waitCount_++; }

		}
	}		
	return ownScene;
}

void GameScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	if (bpCount >= 770)
	{
		bpCount = 0;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawGraph(0, 0, TitleBackImg_, true);

	DrawRectRotaGraph2F(screenSize_.x / 2.0f, screenSize_.y / 2.0f,0,0,96.0f,96.0f,48.0f, 48.0f, 10.0f, 0.0f, backPlanet_[bpCount/10], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	bpCount++;
	for (const auto& player : players_){
		player->Draw();
	}	
	for (const auto& shot : shots_){

		shot->Draw();
	}
	for (const auto& homingsShot : homingsShots_) {
		homingsShot->Draw();
	}
	for (const auto& a : armor_){
		a->Draw();
	}
	int id = count / 140 < 2 ? count / 140 : 1;
	if (count >= (120 + 70)){	
		return;
	}	
	count++;
	//DrawGraph((800 - 420) / 2, (600 - 150) / 2, StartImage_[id], true);
	DrawRectRotaGraph2F(screenSize_.x/2.0f, (screenSize_.y/2.0f)+(id*50.0f),
		0, 0,420.0f, 300.0f, 210.0f, 150.0f, 1.0f*(1.5f+id), 0, StartImage_[id], true);
}

void GameScene::HitUpdate(void)
{
	HitShot();
	//全方位弾とプレイヤー
	for (const auto& player : players_) {
		for (const auto& armor : armor_) {
			if (player->GetType() == armor->GetPlayerType()) {
				continue;
			}
			for (auto& armorshot : armor->GetArmorShot()) {
				if (!armorshot.isActive) {
					continue;
				}
				//全方位弾とプレイヤーとの当たり判定
				if (AbeUtility::IsHIt(player->GetPlayerPos(), armorshot.pos, armorshot.bulletRadius, player->GetRadius())) {
					armorshot.isActive = false;
					armor->HitFragmrnt();
					player->Damage();
				}
			}
		}
	}
	//shieldと弾
	for(auto& shots:shots_ )
	{
		for (auto& armors : armor_)
		{
			if (shots->GetPlayerType() == armors->GetPlayerType())
			{
				continue;
			}
			for (auto& shot : shots->GetBullets())
			{
				if (!shot.isActive)
				{
					continue;
				}
				for (auto& armorshield : armors->GetArmorShield())
				{
					if (!armorshield.isActive) 
					{
						continue;
					}
					if (AbeUtility::IsHIt(shot.pos, armorshield.pos, shot.bulletRadius, armorshield.shieldRadius))
					{
						shot.isActive = false;
						armorshield.life--;
						shot.history.clear();
					}
				}
			}
		}
	}
	//shieldと弾
	for(auto& homingshot:homingsShots_ )
	{
		for (auto& armors : armor_)
		{
			if (homingshot->GetPlayerType() == armors->GetPlayerType())
			{
				continue;
			}
			for (auto& shot : homingshot->GetBullets())
			{
				if (!shot.isActive)
				{
					continue;
				}
				for (auto& armorshield : armors->GetArmorShield())
				{
					if (!armorshield.isActive) 
					{
						continue;
					}
					if (AbeUtility::IsHIt(shot.pos, armorshield.pos, shot.bulletRadius, armorshield.shieldRadius))
					{
						shot.isActive = false;
						armorshield.life--;
						shot.history.clear();
					}
				}
			}
		}
	}
}
	
void GameScene::HitShot(void)
{

	//当たり判定弾
	for (const auto& p : players_) {
		
		//弾とキャラとの当たり判定
		for (const auto& p : players_) {
			if (!p->aliveFlag_)
			{
				continue;
			}
			for (const auto& s : shots_) {
				if (p->GetType() == s->GetPlayerType()) {
					continue;
				}
				for (auto& bullet : s->GetBullets()) {
					if (!bullet.isActive) {
						continue;
					}
					if (AbeUtility::IsHIt(p->GetPlayerPos(), bullet.pos, bullet.bulletRadius, p->GetRadius())) {
						bullet.isActive = false;
						bullet.history.clear();
						p->Damage();
					}
				}
			}
			for (const auto& homingshot : homingsShots_) {
				if (p->GetType() == homingshot->GetPlayerType()) {
					continue;
				}
				for (auto& bullet : homingshot->GetBullets()) {
					if (!bullet.isActive) {
						continue;
					}
					if (AbeUtility::IsHIt(p->GetPlayerPos(), bullet.pos, bullet.bulletRadius, p->GetRadius())) {
						bullet.isActive = false;
						bullet.history.clear();
						p->Damage();
					}
				}
			}

		}
	}

}

void GameScene::Survival()
{
	//DrawFormatString(0, 200, 0xffffff, "%d", survivorNum_);
	for (auto& player : players_) {

		if (!player->IsAlive()&&player->aliveFlag_) {
			player->aliveFlag_ = false;
			survivorNum_ -=1;

		}
		if (((playerNumber_ + 1) - playerNumber_)==survivorNum_ ) {
			if (player->aliveFlag_) {
			Winner(player->GetType());
			}
		}

	}

}

void GameScene::Winner(Player::TYPE type)
{
	auto& ins = InputManager::GetInstance();
	auto cstate = InpMngInstance.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);

	switch (type)
	{
	case Player::TYPE::PLAYER1:
		DrawRectRotaGraph2F(screenSize_.x/ 2.0f, screenSize_.y/2.0f, 0, 0, 600, 200, 300, 100, 1, 0, winImg_[0], true);
		break;
	case Player::TYPE::PLAYER2:
		DrawRectRotaGraph2F(screenSize_.x / 2.0f, screenSize_.y / 2.0f, 0, 0, 600, 200, 300, 100, 1, 0, winImg_[1], true);
		break;
	case Player::TYPE::PLAYER3:
		DrawRectRotaGraph2F(screenSize_.x / 2.0f, screenSize_.y / 2.0f, 0, 0, 600, 200, 300, 100, 1, 0, winImg_[2], true);

		break;
	case Player::TYPE::PLAYER4:
		DrawRectRotaGraph2F(screenSize_.x / 2.0f, screenSize_.y / 2.0f, 0, 0, 600, 200, 300, 100, 1, 0, winImg_[3], true);
		break;
	default:
		DrawRectRotaGraph2F(screenSize_.x / 2.0f, screenSize_.y / 2.0f, 0, 0, 600, 200, 300, 100, 1, 0, winImg_[4], true);
		break;
	}

	newkey_ = cstate.AKeyLY;
	if (playNum_ < 1) 
	{
		if (cstate.AKeyLX >= 30 && oldkey_ < 30)
		{
			PlaySoundMem(soundH[1], DX_PLAYTYPE_BACK);
			playNum_++;
		}
	}
	if (playNum_ > 0) {
		if (cstate.AKeyLX <= -30 && oldkey_ > -30) {
			PlaySoundMem(soundH[1], DX_PLAYTYPE_BACK);
			playNum_--;
		}
	}

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	{
		PlaySoundMem(soundH[2], DX_PLAYTYPE_BACK);
		playNumDecisionFlag_ = true;
		nextFlag = true;
	}

	for (int c = 0; c < 2; c++)
	{
		if (c == playNum_) {

			if (playNumDecisionFlag_)
			{
				int alpha = ((count / 4) % 2) == 0 ? 0 : 1;
				if (alpha == 0) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60); }
				if (alpha == 1) { SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); }
			}
			else { SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); }
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
		}

			DrawRectRotaGraph2F((screenSize_.x / (3.0f) + (screenSize_.x / (3.0f) * c)), screenSize_.y - ((screenSize_.y / 3.0f) - 40.0f),
				0.0f, 0.0f, 300.0f, 100.0f, 150.0f, 50.0f, 1.0f, 0.0f, title_or_battleImg_[c], true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}	
	DrawRectRotaGraph2F(screenSize_.x / (2.0f), screenSize_.y - ((screenSize_.y / 4.0f) - 50.0f),
		0.0f, 0.0f, 600.0f, 100.0f, 300.0f, 50.0f, 0.7f, 0.0f, LStickImg_, true);
	DrawRectRotaGraph2F(screenSize_.x / 2.0f, screenSize_.y - 100,
		0, 0, 600, 100, 300, 50, 0.7f, 0, StartImg_, true);



	oldkey_ = newkey_;

}

bool GameScene::Start(void)
{
	count++;
	if (count >= (140 + 60)){
		return false;
	}
	return true;
}
