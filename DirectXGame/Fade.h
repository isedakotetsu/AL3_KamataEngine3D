#pragma once
#include "KamataEngine.h"
#include "MapChipField.h"
#include "Math.h"
#include <algorithm>
#include <cassert>
#include <numbers>


class Fade
{
public:
	enum class Status
	{
		None,
		FadeIn,
		FadeOut,
	};

	void Initialize();

	void Update();

	void Draw();

	void Start(Status status, float duration);

	void Stop();

	bool IsFinished() const;

private:
	KamataEngine::Sprite* sprite_ = nullptr;

	Status status_ = Status::None;
	//フェードの持続時間
	float duration_ = 0.0f;
	//経過時間カウンター
	float counter_ = 0.0f;
};
