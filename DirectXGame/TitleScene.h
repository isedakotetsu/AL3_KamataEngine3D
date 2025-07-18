#pragma once
#include "KamataEngine.h"
#include "Updatetransform.h"
#include "Fade.h"

using namespace KamataEngine;

class TitleScene
{
public:
	enum class Phase
	{
		kFadeIn,
		kMain,
		kFadeOut,
	};
	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

	

	bool IsFinished() const { return finished_; }



private:
	bool finished_ = false;

	Phase phase_ = Phase::kFadeIn;

	static inline const float kTimeTitleMove = 2.0f;

	// ビュープロジェクション
	Camera camera_;
	WorldTransform worldTransformTitle_;
	WorldTransform worldTransformPlayer_;
	Updatetoransform* updatetransform_ = nullptr;

	Model* modelPlayer_ = nullptr;
	Model* modelTitle_ = nullptr;
	Fade* fade_ = nullptr;


	float counter_ = 0.0f;
};
