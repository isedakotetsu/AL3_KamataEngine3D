#include "Bullet.h"

void Bullet::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position, const KamataEngine::Vector3& velocity) {
	assert(model);
	model_ = model;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	camera_ = camera;

	velocity_ = velocity;
}

void Bullet::Update() {
	worldTransform_.translation_.x += velocity_.x ;
	worldTransform_.translation_.y += velocity_.y / 4;
	worldTransform_.translation_.z += velocity_.z ;
	updatetransform_->WorldTransformUpdate(worldTransform_);
}

void Bullet::Draw() { model_->Draw(worldTransform_, *camera_); }