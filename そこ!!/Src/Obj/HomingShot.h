#pragma once
#include<list>
#include<vector>
#include<memory>
#include "Shot.h"
#include "Player.h"

class Player;
class GameScene;

class HomingShot :
    public Shot
{
public: 
    HomingShot(std::shared_ptr<Player>  player, std::vector<std::shared_ptr<Player> > player2);
    ~HomingShot();
    void Init(void);
    void Update();
    void Draw();

private:
    std::shared_ptr<GameScene> gameScene_;
    std::vector < std::shared_ptr<Player>> player2_;
    void Shoot(Vector2 pos);
    void  HomingPos(bool Flag);
    const int MaxNum = 3;
    float speed = 15.0f; //弾のスピード
    Vector2 playerPos[4];
    Vector2 finalPos;
    //Vector2 
    Vector2 homingPos;
    int soundH;
    float distance[4]{999999.0f,999999.0f,999999.0f,999999.0f };//二点間の距離
    float minPos = 0.0f;

};

