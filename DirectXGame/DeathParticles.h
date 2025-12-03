#pragma once
#include "KamataEngine.h"
#include "Math.h"
#include "Updatetransform.h"
#include <algorithm>
#include <array>
#include <numbers>

class DeathParticles {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	void Update();

	void Draw();

	bool isFinished_ = false;

	bool IsFnished() const { return isFinished_; }

private:
	Updatetoransform* updatetransform_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;

	static inline const uint32_t kNumParticles = 8;

	static inline const float kDuration_ = 2.0f;

	static inline const float kSpeed_ = 0.05f;

	static inline const float kAngleUnit_ = 2.0f * std::numbers::pi_v<float> / kNumParticles;

	float counter_ = 0.0f;

	std::array<KamataEngine::WorldTransform, kNumParticles> worldTransforms_;
	// 色変更オブジェクト
	KamataEngine::ObjectColor objectColor_;
	// 色の数値
	KamataEngine::Vector4 color_;
};