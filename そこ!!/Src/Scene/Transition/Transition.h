#pragma once
#include"../BaseScene.h"
class Transition:
	public BaseScene
{
public:
	Transition(sharedScene beforScene,sharedScene afterScene, float screenSizeX, float screenSizeY);
	~Transition();

private:
	bool Init(void) override; //îhê∂ë§Ç…ÇÕoverride
	sharedScene Update(sharedScene ownScene) override;
	virtual bool UpdateTransition(void) =0;

protected:
	sharedScene beforScene_;
	sharedScene afterScene_;
};

