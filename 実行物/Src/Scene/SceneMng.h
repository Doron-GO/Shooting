#pragma once
#include<memory>
#include "BaseScene.h"
		//
#define lpSceneMng SceneMng::GetInstance()


class SceneMng
{
public:
	//�ÓI		���̏ꍇSceneManager�͂��̃v���O�������s���͂����Ƃ��Ăق����̂ŐÓI�ɂ���
	static SceneMng& GetInstance(void)
	{
		static SceneMng s_Instance;
		return s_Instance;
	}
	Vector2DFloat GetScreenSize(void);

	//���I
	//static SceneMng* Create(void) 
	//{
	//	if (s_Instance == nullptr)				//	���̂��Ȃ��Ƃ��ɃR���X�g���N�^�Ȃǂ��Ăׂ�悤�ɂ���
	//	{
	//		s_Instance = new SceneMng();
	//	}
	//	return s_Instance;
	//}
	//static void Destroy(void)
	//{
	//	delete s_Instance;
	//	s_Instance = nullptr;					//	���̂����łȂ��A�h���X������������
	//}
	void Run(void);
private:

	bool SysInit(void);
	SceneMng();
	~SceneMng();
	void Update(void);
	void Draw(void);


	sharedScene scene_;
	
};

