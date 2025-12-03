#pragma once
#include "KamataEngine.h"
#include "Math.h"
#include "Updatetransform.h"

class Bullet {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position, const KamataEngine::Vector3& velocity);
	void Update();
	void Draw();
	

private:
	KamataEngine::WorldTransform worldTransform_;
	Updatetoransform* updatetransform_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::Vector3 velocity_ = {};
};