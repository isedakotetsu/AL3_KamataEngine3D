#pragma once
#include "KamataEngine.h"
#include "Math.h"
#include "Updatetransform.h"

class Enemy;
class MapChipField;
class Bullet {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position, const KamataEngine::Vector3& velocity);
	void Update();
	void Draw();
	AABB GetAABB();
	void OnCollision(const Enemy* enemy);
	KamataEngine::Vector3 GetWorldPosition();
	void SetMapChipField(MapChipField* mapchipField) { mapchipField_ = mapchipField; }


	// ですフラグ
	bool isDead_ = false;
	// デスフラグのgetter
	bool IsDead() const { return isDead_; }

private:

	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	KamataEngine::WorldTransform worldTransform_;
	Updatetoransform* updatetransform_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::Vector3 velocity_ = {};
	MapChipField* mapchipField_ = nullptr;
};