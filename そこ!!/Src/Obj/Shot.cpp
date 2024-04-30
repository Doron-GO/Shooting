#include "Shot.h"


Shot::Shot(float Screenx, float Screeny, std::shared_ptr<Player> player)//:player_(player)
{
	player_ = player;
	screensize.x = Screenx;
	screensize.y = Screeny;
	explode_frame = 0;

}
Shot::~Shot(void)
{

}
void Shot::Init(void)
{
	//soundH[0] = LoadSoundMem("Src/Sound/nc93363.mp3");
	soundH[1] = LoadSoundMem("Src/Sound/nc177541.wav");
	soundH[2] = LoadSoundMem("Src/Sound/nc177746.wav");
	soundH[3] = LoadSoundMem("Src/Sound/shoot3.mp3");
	ChangeVolumeSoundMem(150, soundH[3]);

	explodeH = LoadGraph("Src/Img/explode.png");
	explode_frame = 0;
	bulletImg_=LoadGraph("Src/Img/beam2.png");
	LoadDivGraph("Src/img/green.png", 20, 5, 4, 64, 64, hitImg_);

	for (int b = 0; b < MaxNum; b++){
		bullets.emplace_back(Bullet());
	}
}


void Shot::Update()
{	//“¯Žž‚Éo‚é‚æ‚¤‚É‚·‚é
	Shoot(player_->GetPlayerPos(), player_->GetReticlePos());
}


void Shot::Shoot(Vector2  pos, Vector2 reti)
{
	auto& pad =InpMngInstance;
	if (player_->life_> 0)
	{
		if (pad.IsPadBtnNew(player_->padNumber_,InputManager::JOYPAD_BTN::R_1))//ƒvƒŒƒCƒ„[‚P‚Ì’e”­ŽË
		{
			//if (!lastShotButton)
			{
				int count = 0;
				if (shotframe % 6 == 0)//ˆê”­‚¸‚Â”­ŽË
				{
					for (auto& b : bullets) {
						if (!b.isActive) {
							b.pos =player_->GetPlayerPos();	//Œ»Ý’n
							//‡@Æ€‚ð‘_‚¤’e‚ðì‚é‚É‚Í,I“_(Æ€)‚©‚çŽn“_iŽ©Àj‚ðˆø‚¢‚½ƒxƒNƒgƒ‹‚ðì‚é  
							//‡A³‹K‰»‚µ‚Ä“K“–‚ÈƒXƒs[ƒh‚ð‘‚¯‚é
							//Ž©‹@À•WF player_->GetPlayerPos()
							//Æ€À•WFplayer_->reti_.pos
							//™ƒQƒbƒgŠÖ”‚ðŽg‚¤‚©‚Ç‚¤‚©‚Í¡—~‚µ‚¢‚©A‚ÅŒˆ‚ß‚é

							PlaySoundMem(soundH[3], DX_PLAYTYPE_BACK);
							b.vel = player_->GetReticlePos() - player_->GetPlayerPos(); //‡@
							b.vel.Normalize();			  //‡A³‹K‰»‚Å’·‚³‚ð‚P‚É
							b.vel *= speed;	//‡AƒXƒs[ƒh‚ðŠ|‚¯‚é
							b.isActive = true;
							count++;
						}
						else{
							lastShotButton = false;
							shotframe = 0;
						}
						if (count >= 1){
							break;
						}
					}
				}
				++shotframe;
			}
		}
		for (auto& b : bullets) {
			if (!b.isActive) {
				continue;
			}
			b.pos += b.vel;
			//DrawCircle(b.pos.x, b.pos.y, b.bulletRadius, 0x0000ff, false, 4.0f);
			if (b.pos.x + 6 < 0 || b.pos.x - 6 > 1024 ||
				b.pos.y - 6 < 0 || b.pos.y - 6 > 768) {
				b.isActive = false;
				b.history.clear();
			}
		}
	}	
}

void Shot::HitEffect(Vector2 pos, Vector2 vel)
{
	double angle = atan2(vel.x, vel.y);
	DrawRectRotaGraph2F(pos.x, pos.y, 0, 0,
		64.0f, 64.0f, 64.0f, 0.0f, 1.0, angle, hitImg_[5], true);
}


const Player::TYPE Shot::GetPlayerType()
{
	return player_->type_;
}


std::vector<Shot::Bullet>& Shot::GetBullets()
{
	return bullets;
}

void Shot::Draw(void)
{
	if (player_->IsAlive())
	{
		for (auto& b : bullets) {
			if (!b.isActive) {
				continue;
			}
			float deg = atan2f(b.vel.y, b.vel.x);
			auto rad = 90 * (DX_PI_F / 180.0f);
			auto angle = deg + rad;
			//	DrawRotaGraph(b.pos.x, b.pos.y, 1.0, angle, bulletImg_, true, false);
			SetDrawBright(player_->playerColor.intx, player_->playerColor.inty, player_->playerColor.intz);
			DrawRectRotaGraph2F(b.pos.x, b.pos.y, 0, 0, 50, 80, 25, 40, 1.0, angle, bulletImg_, true);
			SetDrawBright(255, 255, 255);

			auto pos = b.pos;
			float thickness = 5.0;
			for (const auto& h : b.history) {
				//DrawLineAA(pos.x, pos.y, h.x, h.y, 0xffffff, thickness);
				thickness *= 0.9;
				pos = h;
			}
		}
	}
	if (explode_frame > 0)
	{
		DrawRectRotaGraph2(player_->GetPlayerPos().x, player_->GetPlayerPos().y,
			128 * ((36 - explode_frame) / 3), 0, 128, 128, 64, 96, 1.0f, 0.0f, explodeH, true);
		--explode_frame;
	}
}
