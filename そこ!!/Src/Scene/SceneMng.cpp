#include <DxLib.h>
#include <memory>
#include "SceneMng.h"
#include"Title.h"
#include"GameScene.h"
#include"../../_debug/_DebugConOut.h"
#include"../../_debug/_DebugDispOut.h"

constexpr float ScreenSizeX = 1024.0f;
constexpr float ScreenSizeY = 768.0f;

//�g������
Vector2DFloat SceneMng::GetScreenSize(void)
{
	return { ScreenSizeX,ScreenSizeY };

}

void SceneMng::Run(void)
{
	if (!SysInit())
	{
		return;
	}
	
	//scene_.reset(new BaseScene(ScreenSizeX, ScreenSizeY));
	scene_ = std::make_unique<TitleScene>(ScreenSizeX, ScreenSizeY);


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		InputManager::GetInstance().Update();
		Update();
		Draw();			
 	}

}

void SceneMng::Update(void)
{
	_dbgStartDraw();
	if (!scene_)
	{
		TRACE("scene�̒��g���J��\n");
		return;
	}			
	//���ŕۑ�						//�����L����n��
	scene_ = scene_->Update(std::move(scene_));
}

void SceneMng::Draw(void)
{
	
	if (!scene_)
	{
		TRACE("scene�̒��g���J��\n");
		return;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	scene_->Draw();
	_dbgDraw();
	ScreenFlip();
}

bool SceneMng::SysInit(void)
{
	SetWindowText("2116001 ��������");
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);			//1024�~768�h�b�g��32bit�J���[�ɐݒ�
	ChangeWindowMode(true);

	if (DxLib_Init() == 1)
	{
		//���������s
		return false;						//Dx���C�u�����̏��������s�̂��߃V�X�e���I��
	}
	_dbgSetup(ScreenSizeX, ScreenSizeY, 256);
	return true;
}

SceneMng::SceneMng()
{
}

SceneMng::~SceneMng()
{
}
