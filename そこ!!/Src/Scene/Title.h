#pragma once
#include<vector>
#include"BaseScene.h"


class TitleScene:
	public BaseScene
{
public:
	TitleScene(float screenSizeX, float screenSizeY);
	 ~TitleScene();
	
private:
	 bool Init(void) override; //îhê∂ë§Ç…ÇÕoverride
	  sharedScene Update(sharedScene ownScene) override;
	 void DrawOwnScreen(void)override;

	 bool startFlag_;
	 int titleStartImg_;
	 int titleLogoImg_;
	 int selectImg_[4];
	 int controllerNum_;
	 int count;
	 int waitCount_ = 0;


	 //std::vector<int> playNum_;
	 int x;
	 int soundH[3];
};

