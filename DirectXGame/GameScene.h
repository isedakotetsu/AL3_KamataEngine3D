#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "Skydome.h"
#include "MapChipField.h"
#include "CameraController.h"
#include "Math.h"
#include "DeathParticles.h"
#include "TitleScene.h"
#include "Fade.h"








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

	void CheckAllCollisions();
	void ChagePhase();



	bool IsFnished() const { return finished_; }

	bool AreAllEnemiesDefeated() const;

	Player* GetPlayer() const { return player_; }
	


private:
	enum class Phase {
		kFadeIn,
		kPlay,  // ゲームプレイ
		kDeath, // デス演出
		kFadeOut,
	};

	bool finished_ = false;
	////テクスチャーハンドル
	uint32_t textureHandle_ = 0;

	Fade* fade_ = nullptr;
	Phase phase_;

	Sprite* sprite_ = nullptr;

	//////3Dモデル
	Model* model_ = nullptr;

	WorldTransform worldTransform_;

	// カメラ
	Camera camera_;

	// 自キャラ
	Player* player_ = nullptr;
	
	//敵
	std::list<Enemy*> enemies_;
	// 自キャラモデル
	Model* modelplayer_ = nullptr;
	//敵モデル
	Model* modelenemy_ = nullptr;

	Model* deathParticle_model_ = nullptr;

	
	
	// ブロックの3Dモデル
	Model* blockModel_ = nullptr;

	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;


	Model* modelskydome_ = nullptr;

	
	Skydome* skydome_ = nullptr;

	MapChipField* mapChipField_;


	CameraController* CController_ = nullptr;

	DeathParticles* deathParticles_ = nullptr;

	


	
	
};
