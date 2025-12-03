#pragma once
#include "KamataEngine.h"
#include "Math.h"


class Player;

class CameraController
{
public:

	struct Rect {
		float left = 0.0f;   // 左端
		float right = 1.0f;  // 右端
		float bottom = 0.0f; // した端
		float top = 1.0f;    // 上端
	};

	void Initialize(KamataEngine::Camera* camera);

	void Update();

	void SetTarget(Player* target) { target_ = target; }
	

	void Reset();

	void SetMovableArea(Rect area) { movableArea_= area; }

	

private:

	KamataEngine::Camera* camera_ = nullptr;
    Player* target_ = nullptr;
	
	//追従対象とカメラの座標の差（オフセット）
	KamataEngine::Vector3 target0ffset_ = {0, 0, -15.0f};
	// カメラ移動範囲
	Rect movableArea_ = {0, 100, 0, 100};
	// カメラの目標座標
	KamataEngine::Vector3 destination_;
	//座標補間割合
	static inline const float kInterpolationRate = 0.1f;
	//速度掛け率
	static inline const float kVelocityBias = 15.0f;
	
	//追従対象の各方向へのカメラ移動範囲
	static inline const Rect targetMargin = {-9.0f, 9.0f, -5.0f, 5.0f};
};
