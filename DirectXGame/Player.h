#pragma once
#include "KamataEngine.h"
#include "Math.h"
#include "Updatetransform.h"
class MapChipField;
class Enemy;
class Player {
public:
	enum class Behavior
	{
		kUnknown = -1, 
		kRoot,
		kAttack,
	};
	enum class LRDirection {
		kRight,
		kLeft,
	};

	enum Corner {
		kRightBottom, // 右下
		kLeftBottom,  // 左下
		kRightTop,    // 右上
		kLeftTop,     // 左上
		kNumCorner    // 要素数

	};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void UpDate();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	void InputMove();

	void BehaviorRootUpdate();
	void BehaviorAttackUpdate();
	//衝突応答
	void OnCollision(const Enemy* enemy);

	void BehaviorRootInitialize();
	void BehaviorAttackInitialize();

	const WorldTransform& GetWorldTransform() const { return worldTransform_; }
	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }
	AABB GetAABB();

	Vector3 GetWorldPosition();

	// ですフラグ
	bool isDead_ = false;
	// デスフラグのgetter
	bool IsDead() const { return isDead_; }

private:

	Behavior behavior_ = Behavior::kRoot;
	Behavior behaviorRequest_ = Behavior::kUnknown;
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	Updatetoransform* updatetransform_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	uint32_t attackParameter_ = 0;

	KamataEngine::Camera* camera_ = nullptr;

	Vector3 velocity_ = {};

	static inline const float kAcceleration = 0.1f;
	static inline const float kAttenuation = 0.05f;
	static inline const float kLimitRunSpeed = 0.3f;

	LRDirection lrDirection_ = LRDirection::kRight;

	float turnFirstRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;

	static inline const float kTimeTurn = 0.3f;

	bool onGround_ = true;

	static inline const float kGravityAcceleration = 0.98f;
	static inline const float kLimitFallSpeed = 0.5f;
	static inline const float kJumpAcceleration = 20.0f;

	MapChipField* mapChipField_ = nullptr;

	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	static inline const float kBlank = 0.04f;

	static inline const float kAttenuationLanding = 0.0f;
	static inline const float kGroundSearchHeight = 0.05f;
	static inline const float kAttenuationWall = 0.2f;

	struct CollisionMapInfo {
		bool ceiling = false;
		bool landing = false;
		bool hitWall = false;
		Vector3 move;
	};

	void CheckMapCollision(CollisionMapInfo& info);
	void UpdateOnGround(const CollisionMapInfo& info);
	void UpdateOnWall(const CollisionMapInfo& info);
	void CheckMapCollisionUp(CollisionMapInfo& info);
	void CheckMapCollisionDown(CollisionMapInfo& info);
	void CheckMapCollisionRight(CollisionMapInfo& info);
	void CheckMapCollisionLeft(CollisionMapInfo& info);
	

	Vector3 CornerPosition(const Vector3& center, Corner corner);

	
	

	
};