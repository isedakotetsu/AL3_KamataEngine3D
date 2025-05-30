#pragma once
#include "KamataEngine.h"
#include "Math.h"
#include "Player.h"
#include <vector>
#include "Skydome.h"
#include "MapChipField.h"
#include "CameraController.h"

using namespace KamataEngine;

// ゲームシーン
class GameScene {
public:
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	~GameScene();
	void GenerateBlocks();

private:
	////テクスチャーハンドル
	uint32_t textureHandle_ = 0;

	Sprite* sprite_ = nullptr;

	//////3Dモデル
	Model* model_ = nullptr;

	// ブロックの3Dモデル
	Model* blockModel_ = nullptr;

	WorldTransform worldTransform_;
	//
	////カメラ
	Camera camera_;

	MapChipField* mapChipField_;

	

	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	DebugCamera* debugCamera_ = nullptr;

	// 自キャラ
	Player* player_ = nullptr;

	

	Model* modelskydome_ = nullptr;
	Model* modelplayer_ = nullptr;
	/*Model* modelblock_ = nullptr;*/
	

	Skydome* skydome_ = nullptr;

	CameraController* CController_ = nullptr;

	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
};
