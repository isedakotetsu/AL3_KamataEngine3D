#pragma once
#include "KamataEngine.h"
#include "Math.h"
#include "Updatetransform.h"

class Player {
public:
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

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	Math* math_ = nullptr;

	Updatetoransform* updatetransform_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	KamataEngine::Camera* camera_ = nullptr;

	Vector3 velocity_ = {};

	static inline const float kAcceleration = 0.02f;


};