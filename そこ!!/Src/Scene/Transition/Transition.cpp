#include "Transition.h"
#include"../BaseScene.h"
#include"../../../_debug/_DebugConOut.h"
#include"../../../_debug/_DebugDispOut.h"
Transition::Transition(sharedScene beforScene, sharedScene afterScene, float screenSizeX, float screenSizeY)
	:BaseScene(screenSizeX,  screenSizeY)
{
	TRACE("TransitionSceneの生成\n");
	beforScene_ = std::move(beforScene);
	afterScene_ = std::move(afterScene);
}

Transition::~Transition()
{
}

bool Transition::Init(void)
{
	//Trabsitionが終わっていたら次のシーン(afterScene_)

	return true;
}

sharedScene Transition::Update(sharedScene ownScene)
{
	DrawOwnScreen();
	if(UpdateTransition()) //次のシーン(afterScene_)
	{
		return std::move(afterScene_);
	}
	//自身を返す
	return ownScene;
}


