#pragma once
#include "KamataEngine.h"
#include "Math.h"

class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera);

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

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	KamataEngine::Camera* camera_ = nullptr;
};
