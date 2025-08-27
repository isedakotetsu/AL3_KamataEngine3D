#pragma once
#include "Fade.h"
#include "KamataEngine.h"
#include "Updatetransform.h"

using namespace KamataEngine;

class Clear {
public:
	enum class Phase {
		kFadeIn,
		kMain,
		kFadeOut,
	};
	~Clear();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() const { return finished_; }

private:
	bool finished_ = false;

	Phase phase_ = Phase::kFadeIn;

	static inline const float kTimeClearMove = 2.0f;

	// ビュープロジェクション
	Camera camera_;
	WorldTransform worldTransformClear_;
	WorldTransform worldTransformPlayer_;
	Updatetoransform* updatetransform_ = nullptr;
	Model* modelClear_ = nullptr;
	Fade* fade_ = nullptr;

	float counter_ = 0.0f;
};
