#pragma once
#include "Transition.h"
class CrossOver :
    public Transition
{
public:
	CrossOver(sharedScene beforScene, sharedScene afterScene, float screenSizeX, float screenSizeY);
	~CrossOver();
private:
	
	 bool UpdateTransition(void) override;
	 void  DrawOwnScreen(void)override;
	 int count_;
};

