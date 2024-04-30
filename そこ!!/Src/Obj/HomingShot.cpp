#include "HomingShot.h"
#include "../Scene/GameScene.h"

HomingShot::HomingShot(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Player> > player2):Shot(screensize.x, screensize.y,player_)
{
	player_ = player;
	player2_ = player2;
}

HomingShot::~HomingShot()
{


}

void HomingShot::Init(void)
{
	soundH = LoadSoundMem("Src/Sound/Retro_Anime-Gun07-1(1-High).mp3");
	ChangeVolumeSoundMem(255, soundH);

	bulletImg_ = LoadGraph("Src/Img/blue_beams.png");
	switch (player_->GetType())
	{
	case Player::TYPE::PLAYER1:
		break;
	case Player::TYPE::PLAYER2:
		//LoadDivGraph("Src/img/green.png", 20, 5, 4, 64, 64, hitImg_);
		break;
	case Player::TYPE::PLAYER3:
		break;
	case Player::TYPE::PLAYER4:
		break;
	default:
		break;
	}
	for (int b = 0; b < MaxNum; b++) {
		bullets.emplace_back(Bullet());
	}
}

void HomingShot::Update()
{
	 Shoot(player_->GetPlayerPos());
}

void HomingShot::Draw()
{
	for (auto& b : bullets) {
		if (!b.isActive) {
			continue;
		}
		float deg = atan2f(b.vel.y, b.vel.x);
		auto rad = 90 * (DX_PI_F / 180.0f);
		auto angle = deg + rad;
		SetDrawBright(player_->playerColor.intx, player_->playerColor.inty, player_->playerColor.intz);
		auto pos = b.pos;
		float thickness = 5.0;
		for (const auto& h : b.history) {
			DrawLineAA(pos.x, pos.y, h.x, h.y, 0xffffff, thickness);
			thickness *= 0.9;
			pos = h;
		}
		DrawRectRotaGraph2F(b.pos.x, b.pos.y, 0, 0, 50, 80, 25, 40, 1.0, angle, bulletImg_, true);
		SetDrawBright(255, 255, 255);
	}
	if (explode_frame > 0)
	{
		DrawRectRotaGraph2(player_->GetPlayerPos().x, player_->GetPlayerPos().y, 128 * ((36 - explode_frame) / 3), 0, 128, 128, 64, 96, 1.0f, 0.0f, explodeH, true);
		--explode_frame;
	}
}

void HomingShot::Shoot(Vector2 pos)
{
	auto& pad = InpMngInstance;
	if (player_->life_ > 0)
	{
		if (pad.IsPadBtnNew(player_->padNumber_, InputManager::JOYPAD_BTN::L_1))//ƒvƒŒƒCƒ„[‚P‚Ì’e”­ŽË
		{
			int count = 0;
			if (shotframe % 8 == 0)//ˆê”­‚¸‚Â”­ŽË
			{
				for (auto& b : bullets) {
					if (!b.isActive) {
						PlaySoundMem(soundH, DX_PLAYTYPE_BACK);
						b.pos = player_->GetPlayerPos();//Œ»Ý’n
						HomingPos(true);
						b.vel = homingPos - player_->GetPlayerPos(); //‡@
						b.vel.Normalize();//‡A³‹K‰»‚Å’·‚³‚ð‚P‚É
						b.vel *= speed;	//‡AƒXƒs[ƒh‚ðŠ|‚¯‚é
						b.isActive = true;		
						count++;
					}
					else {
						shotframe = 0;
					}
					if (count >= 1) {
						break;
					}
				}
			}
			++shotframe;
		}
	}
	for (auto& b : bullets) {
		if (!b.isActive) {
			b.count = 0;
			continue;
		}
		b.history.push_front(b.pos);
		//7ŒÂ‚½‚Ü‚Á‚½‚çˆê”ÔŒÃ‚¢‚à‚Ì‚ðŽÌ‚Ä‚é
		if (b.history.size() > 5) {
			b.history.pop_back();
		}
		b.pos += b.vel;
		if (b.count <= 40)
		{
			HomingPos(false);
			b.vel = (b.vel + (homingPos - b.pos).Normalized()).Normalized() * 12.0f;
			b.count++;
		}
		if (b.pos.x + 6 < 0 || b.pos.x - 6 > 1024 ||
			b.pos.y - 6 < 0 || b.pos.y - 6 > 768) {
			b.isActive = false;
			b.history.clear();
		}
	}
}

void  HomingShot::HomingPos(bool flag)
{
	int x = 0;
	if(flag)
	{
		for (const auto& p2 : player2_)
		{
			if (player_->type_ == p2->GetType()||!p2->IsAlive()) 
			{
				distance[x] = 99999.0f;
				if (x < 3) { x++; };
				continue;
			}
			distance[x] = 99999.0f;

			Vector2 enemyPos = {  (p2->GetPlayerPos().x),(p2->GetPlayerPos().y )};
			Vector2 ownPos = {(player_->GetPlayerPos().x) , (player_->GetPlayerPos().y) };
			distance[x] = (abs(enemyPos.x - ownPos.x) + abs(enemyPos.y - ownPos.y));
			playerPos[x] = p2->GetPlayerPos();
			if (x < 3) { x++; };
		}
	}
	if (distance[0] <= distance[1] && distance[0] <= distance[2] && distance[0] <= distance[3]) { minPos = distance[0]; }
	if (distance[1] <= distance[0] && distance[1] <= distance[2] && distance[1] <= distance[3]) { minPos = distance[1]; }
	if (distance[2] <= distance[1] && distance[2] <= distance[0] && distance[2] <= distance[3]) { minPos = distance[2]; }
	if (distance[3] <= distance[1] && distance[3] <= distance[2] && distance[3] <= distance[0]) { minPos = distance[3]; }
	for (int x = 0; x < 4; x++)
	{
		if (minPos == distance[x]) { homingPos = player2_[x]->GetPlayerPos(); }
	}
	x = 0;
}


