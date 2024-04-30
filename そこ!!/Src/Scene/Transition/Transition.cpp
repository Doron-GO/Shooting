#include "Transition.h"
#include"../BaseScene.h"
#include"../../../_debug/_DebugConOut.h"
#include"../../../_debug/_DebugDispOut.h"
Transition::Transition(sharedScene beforScene, sharedScene afterScene, float screenSizeX, float screenSizeY)
	:BaseScene(screenSizeX,  screenSizeY)
{
	TRACE("TransitionScene�̐���\n");
	beforScene_ = std::move(beforScene);
	afterScene_ = std::move(afterScene);
}

Transition::~Transition()
{
}

bool Transition::Init(void)
{
	//Trabsition���I����Ă����玟�̃V�[��(afterScene_)

	return true;
}

sharedScene Transition::Update(sharedScene ownScene)
{
	DrawOwnScreen();
	if(UpdateTransition()) //���̃V�[��(afterScene_)
	{
		return std::move(afterScene_);
	}
	//���g��Ԃ�
	return ownScene;
}


