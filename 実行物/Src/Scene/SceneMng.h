#pragma once
#include<memory>
#include "BaseScene.h"
		//
#define lpSceneMng SceneMng::GetInstance()


class SceneMng
{
public:
	//静的		この場合SceneManagerはこのプログラム実行中はずっといてほしいので静的にする
	static SceneMng& GetInstance(void)
	{
		static SceneMng s_Instance;
		return s_Instance;
	}
	Vector2DFloat GetScreenSize(void);

	//動的
	//static SceneMng* Create(void) 
	//{
	//	if (s_Instance == nullptr)				//	実体がないときにコンストラクタなどを呼べるようにする
	//	{
	//		s_Instance = new SceneMng();
	//	}
	//	return s_Instance;
	//}
	//static void Destroy(void)
	//{
	//	delete s_Instance;
	//	s_Instance = nullptr;					//	実体だけでなくアドレス情報も消去する
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

