#pragma once
#include "KamataEngine.h"
#include "Math.h"
using namespace KamataEngine;

class Bullet 
{
public:
	

	void Initialize(Model* model,Camera* camera, const Vector3& position, const Vector3& direction, float speed);
	void Update();
	void Draw();

	bool IsAlive() const { return alive_; }

private:
	Model* model_ = nullptr;
	Camera* camera_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	Vector3 position_;
	Vector3 direction_;
	float speed_ = 0.0f;
	bool alive_ = true;
};
