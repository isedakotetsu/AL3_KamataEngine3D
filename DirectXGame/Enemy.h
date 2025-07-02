#pragma once
#include "KamataEngine.h"
#include "Math.h"
#include "Updatetransform.h"
class Player;
class Enemy
{
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void UpDate();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	AABB GetAABB();

	void OnCollision(const Player* player);

private:
	KamataEngine::WorldTransform worldTransform_;
	Updatetoransform* updatetransform_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;
	//敵のスピード（移動）
	static inline const float kWalkSpeed = 0.05f;
	//最初の角度
	static inline const float kWalkMotionAngleStart = 0.5f;
	//最後の角度
	static inline const float kWalkMotionAngleEnd = 0.5f;
	//アニメーションの周期となる時間
	static inline const float kWalkMotionTime = 0.5f;

	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	float walkTimer_ = 0.0f;

	Vector3 velocity_ = {};

	Vector3 GetWorldPosition();
};