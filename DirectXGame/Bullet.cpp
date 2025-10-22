#include "Bullet.h"

void Bullet::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const Vector3& position, const Vector3& direction, float speed) 
{
	model_ = model;
	camera_ = camera;
	position_ = position;
	direction_ = direction; 
	speed_ = speed;
	alive_ = true;
}

void Bullet::Update() 
{
	if (!alive_)
		return;

	
	position_ += direction_ * speed_;

	// 画面外判定
	if (position_.x < -100.0f || position_.x > 100.0f || position_.y < -100.0f || position_.y > 100.0f) {
		alive_ = false;
	}
}


void Bullet::Draw() 
{
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	model_->Draw(worldTransform_, *camera_);

	Model::PostDraw();
}
