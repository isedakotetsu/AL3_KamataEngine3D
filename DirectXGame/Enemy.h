#pragma once
#include "KamataEngine.h"
#include "Math.h"
#include "Updatetransform.h"
class Player;
class Bullet;
class Enemy
{
public:
	enum class Behavior {
		kUnknown = -1, // 無効な状態
		kWalk,         // 歩行状態
		kDefeated,     // やられ状態
	};
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

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
	void OnCollisionBullet(const Bullet* bullet);

	
	bool IsDead() const { return isDead_; }

	bool IsCollisionDisabled() const { return isCollisionDisabled_; }

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

	KamataEngine::Vector3 velocity_ = {};

	KamataEngine::Vector3 GetWorldPosition();
	bool isDead_ = false;

	Behavior behavior_ = Behavior::kWalk;
	Behavior behaviorRequest_ = Behavior::kUnknown;

	static inline const float kDefeatedTime = 0.6f;
	static inline const float kDefeatedMotionAngleStart = 0.0f;
	static inline const float kDefeatedMotionAngleEnd = -60.0f;
	float counter_ = 0.0f; // カウンター

	bool isCollisionDisabled_ = false;
};