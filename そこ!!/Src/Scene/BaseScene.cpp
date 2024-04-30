#include "BaseScene.h"
#include<Dxlib.h>

BaseScene::BaseScene(float screenSizeX, float  screenSizeY):screenSize_(screenSizeX, screenSizeY)
{
	
	screenID_ = MakeScreen(screenSize_.x, screenSize_.y, true);
	TitleBackImg_ = LoadGraph("Src/Img/parallax-space-backgound.png");
	meteoriteImg_ = LoadGraph("Src/Img/Asteroid 01 - Base.png");
	LStickImg_ = LoadGraph("Src/Img/‘I‘ð.png");
	LoadDivGraph("Src/img/button.png", 16, 4, 4, 25, 25, buttonImg);
	StartImg_ = LoadGraph("Src/Img/Œˆ’è.png");

}

BaseScene::~BaseScene()
{
}

void BaseScene::Draw(void)
{
	DrawGraph(0, 0, screenID_, false);

}
