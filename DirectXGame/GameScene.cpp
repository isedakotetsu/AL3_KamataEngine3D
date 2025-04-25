#include "GameScene.h"
#include "Player.h"


using namespace KamataEngine;
GameScene::~GameScene()
{ 
	delete model_;
	delete player_;

}
void GameScene::Initialize() 
{ 
	textureHandle_ = TextureManager::Load("aaa.png"); 

	model_ = Model::Create();

	camera_.Initialize();

	player_ = new Player();

	player_->Initialize(model_, textureHandle_, &camera_);
}

void GameScene::Update() 
{ 
	player_->Update(); 

}

void GameScene::Draw() 
{ 
	player_->Draw();
}