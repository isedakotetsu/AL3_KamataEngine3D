#pragma once
#include "KamataEngine.h"


class Skydome
{
public:
	void Initialize(KamataEngine::Model* model_, KamataEngine::Camera* camera_);
	void Update();
	void Draw();
	

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::Model* model_ = nullptr;

};
