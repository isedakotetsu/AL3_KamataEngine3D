#pragma once
#include "KamataEngine.h"
#include "Math.h"
#include "Updatetransform.h"

class Bullet {
public:
	void Initialize(Model* model, const Vector3& position);
	void Update();
	void Draw(const Camera& camera);
	


private:
	Model* model_ = nullptr;
	Camera* camera_ = nullptr;
	WorldTransform worldTransform_;
	Updatetoransform* updatetransform_ = nullptr;
	uint32_t textureHandle_ = 0u;
};
