#include<DxLib.h>
#include "CrossOver.h"
#include"../../../_debug/_DebugDispOut.h"
#include"../../../_debug/_DebugConOut.h"

CrossOver::CrossOver(sharedScene beforScene, sharedScene afterScene, float screenSizeX, float screenSizeY)
	:Transition(std::move(beforScene), std::move(afterScene), screenSizeX, screenSizeY)
{
	count_ = 0;
	TRACE("CrossOver‚Ì¶¬\n");
}

CrossOver::~CrossOver()
{
	TRACE("CrossOver‚Ì”jŠü\n");
}

bool CrossOver::UpdateTransition(void)
{
	if (++count_ >= 255)
	{
		return true;
	}
	
	return false;
}

void CrossOver::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - count_);
	beforScene_->Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA,  count_);
	afterScene_->Draw();

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);


}
