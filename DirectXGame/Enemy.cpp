#include "Enemy.h"
#include <numbers>
#include "MapChipField.h"
#include "Math.h"
#include <algorithm>
#include <cassert>
void Enemy::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const Vector3& position) {
	assert(model);
	// モデル
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * 3.0f / 2.0f;
	velocity_ = {-kWalkSpeed, 0, 0};
	camera_ = camera;
	walkTimer_ = 0.0f;
}

void Enemy::UpDate() 
{


	walkTimer_ += 1.0f / 60.0f;
	//回転アニメーション
	
	worldTransform_.rotation_.x = std::sin(std::numbers::pi_v<float> * 2.0f * walkTimer_ / kWalkMotionTime);
	/*float param = std::sin(std::numbers::pi_v<float> * 2.0f * walkTimer_ / kWalkMotionTime);
	float degree = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f;
	worldTransform_.rotation_.x = ;*/
	worldTransform_.translation_ += velocity_;
	// ワールド行列更新（アフィン変換～DirectXに転送）
	updatetransform_->WorldTransformUpdate(worldTransform_);
}

void Enemy::Draw() 
{
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	model_->Draw(worldTransform_, *camera_);

	Model::PostDraw();
}
