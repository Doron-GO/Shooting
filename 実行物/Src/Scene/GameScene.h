#include"BaseScene.h"
#include"../Obj/Player.h"
#include"../Obj/Shot.h"
#include"../Obj/HomingShot.h"
#include"../Obj/Armor.h"
#include<vector>
class GameScene :
	public BaseScene
{
public:

	GameScene(float screenSizeX, float screenSizeY, int playerNumber);
	~GameScene();
	 std::vector<std::shared_ptr<Player>>  players_ ;

private:
	bool Init(void) override; //îhê∂ë§Ç…ÇÕoverride
	sharedScene Update(sharedScene ownScene) override;
	void DrawOwnScreen(void)override;
	void HitUpdate(void);
	void HitShot(void);
	int StartImage_[2];
	int BgImg;

	void Survival();
	int  survivorNum_;
	bool Start(void);
	//std::unique_ptr<Player> player_;
	 std::vector<std::unique_ptr<Shot>>  shots_;
	 std::vector<std::unique_ptr<HomingShot>>  homingsShots_;
	 std::vector<std::unique_ptr<Armor>>  armor_;
	 std::shared_ptr<GameScene> gamaScene_;
	//std::unique_ptr<Shot> shot_;
	//std::unique_ptr<Armor> armor_;
	int count;
	Player::TYPE type_;
	int playerNumber_;
	void Winner(Player::TYPE type);
	
	bool nextFlag;
	int soundH[3];
	int title_or_battleImg_[2];
	int minPos = 0;
	int bpCount;
	int backPlanet_[77];
	int winImg_[5];

};

