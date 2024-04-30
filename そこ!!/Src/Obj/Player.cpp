#include <DxLib.h>
#include "Player.h"
Player::Player(float Screenx, float Screeny, TYPE type)
{
	type_ = type;
	Pspeed = 4;
	screensize.x = Screenx;
	screensize.y = Screeny;
	Init();
}

Player::~Player()
{
}

void Player::Init(void)
{
	explodeH = LoadGraph("Src/img/explode.png");
	explodeH2 = LoadGraph("Src/img/explosion-2.png");
	AddImg_ = LoadGraph("Src/img/Particle04_clear_soft.png");
	soundH[0] = LoadSoundMem("Src/Sound/大砲1.mp3");
	soundH[1] = LoadSoundMem("Src/Sound/爆発.mp3");
	ChangeVolumeSoundMem(255, soundH[0]);
	ChangeVolumeSoundMem(200, soundH[1]);

	pidx = (frame / 4 % 2) * 5 + 2;
	//各プレイヤーの初期化
	//別ファイルから読み込めるようにしたい
	life_ = 3;		
	span_ = reti_.pos - pos_;
	degree_ = atan2f(span_.y, span_.x);
	playerRadius = playerRadiusFull;
	reticleCount_ = 0;
	LoadDivGraph("Src/img/spritesheet.png", 121, 11, 11, 100, 100, reticleImg_);
	aliveFlag_ = true;
	switch (type_)
	{
	case Player::TYPE::PLAYER1:
		pos_.x = 0 + playerRadiusFull;
		pos_.y = 0 + 20.0f;
		reti_.pos = { 1024 / 2 ,768 / 2 - 3 };
		LoadDivGraph("Src/img/player.png", 10, 5, 2, 16, 24, playerH);
		playerColor ={0,0, 0,255,0 };
		padNumber_ = InputManager::JOYPAD_NO::PAD1;
		break;
	case Player::TYPE::PLAYER2:
		pos_.x = screensize.x - playerRadiusFull;
		pos_.y = screensize.y - playerRadiusFull;
		reti_.pos = { 1024 / 2 + 30 ,768 / 2 };
		LoadDivGraph("Src/img/player2.png", 10, 5, 2, 16, 24, playerH);
		playerColor = { 0,0,255, 100,0 };
		padNumber_ = InputManager::JOYPAD_NO::PAD2;
		break;
	case Player::TYPE::PLAYER3:
		pos_.x = 0 + playerRadiusFull;
		pos_.y = screensize.y - playerRadiusFull;
		reti_.pos = { 1024 / 2 -30 ,768 / 2 };
		LoadDivGraph("Src/img/player2.png", 10, 5, 2, 16, 24, playerH);
		playerColor = { 0,0,0,100,255 };
		padNumber_ = InputManager::JOYPAD_NO::PAD3;
		break;
	case Player::TYPE::PLAYER4:
		pos_.x = screensize.x - playerRadiusFull;
		pos_.y = 0 + 20.0f;
		reti_.pos = { 1024 / 2 + 30 ,768 / 2 };
		LoadDivGraph("Src/img/player2.png", 10, 5, 2, 16, 24, playerH);
		playerColor = { 0,0, 200,0,255 };
		padNumber_ = InputManager::JOYPAD_NO::PAD4;
		break;
	default:
		break;
	}
	
}

void Player::Update(void)
{
	if (IsAlive()){
		Move();
		ReticleMove();
		CalcDeg();
	}
}

void Player::Draw(void)
{
	//DrawFormatString(20, 400, 0xFFFFFF, " P%d", Life2);
	//DrawFormatString(20, 450, 0xFFFFFF, " P%d", P[1].Life);
	//キャラクターのアニメーション　数字の範囲を作れるように練習しなきゃ
	if (IsAlive()) {
		//プレイヤー１の描画
		if (life_ == 2) {
			playerRadius = playerRadiusMedi;
		}
		if (life_ == 1) {
			playerRadius = playerRadiusLow;
		}
		//DrawCircle(pos_.x, pos_.y, playerRadius, playerColor, true);
		//DrawCircle(reti_.pos.x, reti_.pos.y, reticleRadius, playerColor, false, 5);

		SetDrawBright(playerColor.intx, playerColor.inty, playerColor.intz);
		DrawRectRotaGraph2(reti_.pos.x, reti_.pos.y, 0, 0, 100, 100, 50.0f, 50.0f, 0.5f,1, reticleImg_[reticleCount_], true);
		SetDrawBright(255, 255, 255);

		//とりあえず戦闘機
		auto red = 90.0f * (DX_PI_F / 180.0f);
		//DrawRotaGraph(pos_.x, pos_.y, 2.0f, degree_ + red, playerH[pidx], true);

		//プレイヤーのHPによって点滅するようにしている
		if (life_ <=2){
			if((damageCount_ / (30*life_)+2 ) % 2* life_ == 0){
				SetDrawBright(230, 120, 120);
			}
			else {
				SetDrawBright(255, 255, 255);
			}
		}

		DrawRectRotaGraph2(pos_.x, pos_.y, 0, 0, 16, 24, 8.0f, 12.0f, 2.0f, degree_ + red, playerH[pidx], true);
		
		SetDrawBlendMode(DX_BLENDMODE_ADD, 80);
		
		DrawRectRotaGraph2(pos_.x, pos_.y, 0, 0, 256, 256, 128.0f, 128.0f, 0.25f, degree_ + red, AddImg_, true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawBright(255, 255, 255);


		if (explode_frame > 0){
			//数学で習ったやつ
			DrawRectRotaGraph2(pos_.x, pos_.y,
				128 * ((36 - explode_frame) / 3), 0,
				128, 128, 64, 96, 1.0f, 0.0f, explodeH, true);
			--explode_frame;
		}
	}
	if (explode_frame2 > 0){
		DrawRectRotaGraph2(pos_.x, pos_.y,
			192 * ((64 - explode_frame2) / 3),
			0, 192, 192, 96, 96, 1.5f, 0.0f, explodeH2, true);
		--explode_frame2;
	}
	damageCount_++;
	if (reticleCount_ >=120) { reticleCount_ = 0; }
	reticleCount_++;

}

void Player::Move(void)
{
	auto controllerStick = InpMngInstance.GetJPadInputState(padNumber_);
	pidx = (frame / 4 % 2) * 5 + 2;
	if (controllerStick.AKeyLX>0){
		pos_.x = min(screensize.x - playerRadius, pos_.x + Pspeed);
		pidx = (frame / 4 % 2) * 5 + 4;
		reti_.pos.x = min(screensize.x - playerRadius, reti_.pos.x + Pspeed);
	}
	if (controllerStick.AKeyLX < 0){
		pos_.x = max(0 + playerRadius, pos_.x - Pspeed);
		pidx = (frame / 4 % 2) * 5 ;
		reti_.pos.x = max(0 + playerRadius, reti_.pos.x - Pspeed);
	}
	if (controllerStick.AKeyLY > 0){
		pos_.y = min(screensize.y - playerRadius, pos_.y + Pspeed);
		reti_.pos.y = min(screensize.y - playerRadius, reti_.pos.y + Pspeed);
	}
	if (controllerStick.AKeyLY < 0){
		pos_.y = max(0 + playerRadius, pos_.y - Pspeed);
		reti_.pos.y = max(0 + playerRadius, reti_.pos.y - Pspeed);
	}
	frame++;
}

//void Player::ReticleMove(Vector2 Player, Vector2& Reticle, InputManager::JOYPAD_NO Pad, float Radius)
void Player::ReticleMove()
{	
	float maxlen = 100.0f;//照準が自機から離れる最大距離 1
	//auto pPos1 = Player;
	auto diffX = reti_.pos.x - pos_.x;//行った先から行った元
	auto diffY = reti_.pos.y - pos_.y;
	auto dis  = hypotf(diffX, diffY); // 斜辺7

	if (dis > maxlen){
		//プレイヤーから照準への方向
		Vector2 diff = reti_.pos;
		diff.x -= pos_.x;
		diff.y -= pos_.y;
		diff.x /= dis;
		diff.y /= dis;
		auto dirV3 = diff;
		// 方向に対して、円の半径を掛け算し、
	    // プレイヤーからの移動量を取る(相対座標となる)
		Vector2 movePow =
		{
			static_cast<int>(roundf(dirV3.x * maxlen)),
			static_cast<int>(roundf(dirV3.y * maxlen))
		};
		// プレイヤー座標に移動量を加えて、
	   // 照準の座標を更新する
		Vector2 newPos = pos_;
		newPos.x += movePow.x;
		newPos.y += movePow.y;
		reti_.pos = newPos;
	}
	auto controllerStick = InpMngInstance.GetJPadInputState(padNumber_);
	//右スティック上下左右
	if (controllerStick.AKeyRX > 0){
		reti_.pos.x = min(screensize.x - playerRadius, reti_.pos.x + 8);
	}
	if (controllerStick.AKeyRX < 0){
		reti_.pos.x = max(0 + playerRadius, reti_.pos.x - 8);
	}
	if (controllerStick.AKeyRY < 0){
		reti_.pos.y = max(0 + playerRadius, reti_.pos.y - 8);
	}
	if (controllerStick.AKeyRY > 0){
		reti_.pos.y = min(screensize.y - playerRadius, reti_.pos.y + 8);
	}
}

//void Player::Reticle2(Vector2 Player, Vector2& Reticle, InputManager::JOYPAD_NO Pad, float Radius)

void Player::CalcDeg()
{
	span_ = reti_.pos - pos_;
	degree_ = atan2f(span_.y, span_.x);//角度をとる
}

 void Player::Damage()
{ 
	StartJoypadVibration(static_cast<int>(padNumber_), 500, 150, -1);
   if (explode_frame <= 0){
	   explode_frame = 32;
   }
   if (life_ > 1){   PlaySoundMem(soundH[0], DX_PLAYTYPE_BACK);}
   life_ -= 1;
}

Vector2 Player::GetPlayerPos()
{
	return pos_;
}

 Vector2 Player::GetReticlePos()
{
	return reti_.pos;	
}

 float Player::GetRadius()
 {	
	 return playerRadius;
 }

const bool Player::IsAlive(void)
{
	 if (life_ > 0){
		return true;
	 }
	 if (aliveFlag_){
		 explode_frame2 = 64;
		 PlaySoundMem(soundH[1], DX_PLAYTYPE_BACK);
		 StartJoypadVibration(static_cast<int>(padNumber_), 500, 400, -1);
	 }
	 return false;
}


 const Player::TYPE Player::GetType()
 {
	 return type_;
 }


 
