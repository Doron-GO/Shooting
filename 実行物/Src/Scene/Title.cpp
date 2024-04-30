#include<DxLib.h>
#include"GameScene.h"
#include"Transition/CrossOver.h"
#include "Title.h"
#include"../../_debug/_DebugConOut.h"
#include"../../_debug/_DebugDispOut.h"
														//↓ここでこの引数で初期化しての予約をするじゃなきゃデフォルトコンストラクタが呼ばれる	
TitleScene::TitleScene(float screenSizeX, float screenSizeY) :BaseScene(screenSizeX, screenSizeY)
{
	Init();
 	TRACE("TitleSceneの生成\n");
	DrawOwnScreen();
}

TitleScene::~TitleScene()
{
	TRACE("TitleSceneの破棄\n");
}

bool TitleScene::Init(void)
{
	titleLogoImg_ = LoadGraph("Src/Img/rogo.png");
	titleStartImg_ = LoadGraph("Src/Img/titleStart.png");
	LoadDivGraph("Src/Img/仮セレクト.png", 4, 1, 4, 283, 75, selectImg_);
	startFlag_ = false;
	playerNumber = 0;
	playNumDecisionFlag_ = false;
	count = 0;
	controllerNum_ = GetJoypadNum();
	soundH[0] = LoadSoundMem("Src/Sound/カーソル移動5.mp3");
	soundH[1] = LoadSoundMem("Src/Sound/決定ボタンを押す33.mp3");
	playNum_ = 2;
	x = 0;
	return true;
}

sharedScene TitleScene::Update(sharedScene ownScene)
{
	controllerNum_ = GetJoypadNum();
	DrawOwnScreen();
	
	auto& ins = InputManager::GetInstance();
	auto cstate = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
	if (!startFlag_){
		if (ins.IsPadBtnTrgUp(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT)||
			ins.IsPadBtnTrgUp(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::TOP)||
			ins.IsPadBtnTrgUp(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN)||
				ins.IsPadBtnTrgUp(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::LEFT))
		{
			PlaySoundMem(soundH[1], DX_PLAYTYPE_BACK);
			startFlag_ = true;
		}
	}

	if (startFlag_)
	{
		newkey_ = cstate.AKeyLY;

		if (controllerNum_ <= 4) {
			if (playNum_ <controllerNum_){
				if (cstate.AKeyLY >= 30 && oldkey_ < 30)
				{
					PlaySoundMem(soundH[0], DX_PLAYTYPE_BACK);
					playNum_++;
				}
			}
			if (playNum_ > 2){
				if (cstate.AKeyLY <= -30 && oldkey_ > -30){
					PlaySoundMem(soundH[0], DX_PLAYTYPE_BACK);
					playNum_--;
				}
			}
			if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT)&&!(playNum_<=1))
			{
				PlaySoundMem(soundH[1], DX_PLAYTYPE_BACK);
				playNumDecisionFlag_ = true;

			}
			if (playNumDecisionFlag_&&waitCount_ > 100&&!(playNum_<=1)) {
				return  std::make_unique<CrossOver>(std::move(ownScene), std::make_shared<GameScene>(screenSize_.x, screenSize_.y, playNum_), screenSize_.x, screenSize_.y);
			}
			if (playNumDecisionFlag_) {waitCount_++;}
			oldkey_ = newkey_;
		}
	}
		return ownScene;
}
 
void TitleScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(0, 0, TitleBackImg_, true); 

	if (!startFlag_)
	{
	   DrawRectRotaGraph2F(screenSize_.x / 2.0f, screenSize_.y / 3.0f, 0, 0, 600, 200, 300, 100, 1, 0, titleLogoImg_, true);
	   if ((count / 30) % 2 == 0)
	   {
		  DrawRectRotaGraph2F(screenSize_.x /2.0f, screenSize_.y-(screenSize_.y / 4.0f), 0, 0, 600, 200, 300, 100, 1, 0, titleStartImg_, true);
	   }
	}

	if (startFlag_)
	{
		for (int select = 2; select <= controllerNum_; select++) {
			if (select ==playNum_){

				if (playNumDecisionFlag_)
				{
					int alpha=((count/4)% 2) == 0 ? 0:1;
					if(alpha==0){SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);}
					if(alpha ==1) { SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); }
				}
				else {SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);}
			}
			else {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
			}

			if ((controllerNum_ >= 2) &&!(select==1)) { 

				DrawRectRotaGraph2F(screenSize_.x / 2.0f, (0 + (screenSize_.y / 3.0f)) + (select - 1) * 125,
				0, 0, 283, 75, 141, 38, 2, 0, selectImg_[select - 1], true);
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}	
		DrawRectRotaGraph2F(screenSize_.x / 2.0f, screenSize_.y - 100,
			0, 0, 600, 100, 300, 50, 0.7, 0, StartImg_, true);
		DrawRectRotaGraph2F(screenSize_.x / (2.0f), screenSize_.y - ((screenSize_.y / 4.0f) - 50.0f),
			0.0f, 0.0f, 600.0f, 100.0f, 300.0f, 50.0f, 0.7f, 0.0f, LStickImg_, true);

		if ((controllerNum_ <= 1) ) {
			playNum_ = 0;
			DrawRectRotaGraph2F(screenSize_.x / 2.0f, (0 + (screenSize_.y / 3.0f)) + (1 - 1) * 125,
				0, 0, 283, 75, 141, 38, 2, 0, selectImg_[0], true);
		}

	}
	count++;
}
