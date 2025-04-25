#include "Player.h"
#include <cassert>



void Player::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera) { 
	assert(model); 

	model_ = model;
	camera_ = camera;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();

}

void Player::Update() 
{
	worldTransform_.TransferMatrix(); 
}

void Player::Draw() 
{ 
	KamataEngine::DirectXCommon* dxCommon = KamataEngine::DirectXCommon::GetInstance();

	model_->PreDraw(dxCommon->GetCommandList());
	model_->Draw(worldTransform_, *camera_, textureHandle_);
	model_->PostDraw();

}