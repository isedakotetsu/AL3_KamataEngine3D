#include "Bullet.h"

void Bullet::Initialize(Model* model, const Vector3& position)
{ 
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("mario.png");

    worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	
}

void Bullet::Update()
{ 
	updatetransform_->WorldTransformUpdate(worldTransform_);

}

void Bullet::Draw(const Camera& camera) 
{ 
	model_->Draw(worldTransform_, camera, textureHandle_); 
}