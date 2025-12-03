#pragma once
#include "Fade.h"
#include "KamataEngine.h"
#include "Updatetransform.h"



class Over {
public:
	enum class Phase {
		kFadeIn,
		kMain,
		kFadeOut,
	};
	~Over();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() const { return finished_; }

private:
	bool finished_ = false;

	Phase phase_ = Phase::kFadeIn;

	static inline const float kTimeOverMove = 2.0f;

	// ビュープロジェクション
	KamataEngine::Camera camera_;
	KamataEngine::WorldTransform worldTransformOver_;
	KamataEngine::WorldTransform worldTransformPlayer_;
	Updatetoransform* updatetransform_ = nullptr;

	
	KamataEngine::Model* modelOver_ = nullptr;
	Fade* fade_ = nullptr;

	float counter_ = 0.0f;
};
