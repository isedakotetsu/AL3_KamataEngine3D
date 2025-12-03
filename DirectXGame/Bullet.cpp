#include "Bullet.h"

void Bullet::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position, const KamataEngine::Vector3& velocity) {
	assert(model);
	model_ = model;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	camera_ = camera;

	velocity_ = velocity;
}

AABB Bullet::GetAABB()
{
	KamataEngine::Vector3 worldPos = GetWorldPosition();
	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};
	return aabb;
}
void Bullet::OnCollision(const Enemy* enemy) 
{
	(void)enemy;

	isDead_ = true;
}
void Bullet::Update() {
	worldTransform_.translation_.x += velocity_.x ;
	worldTransform_.translation_.y += velocity_.y / 4;
	worldTransform_.translation_.z += velocity_.z ;
	updatetransform_->WorldTransformUpdate(worldTransform_);
}

void Bullet::Draw() { model_->Draw(worldTransform_, *camera_); }