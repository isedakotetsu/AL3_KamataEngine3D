#include "GameScene.h"


using namespace KamataEngine;


void GameScene::Initialize() {
	

	model_ = Model::Create();

	worldTransform_.Initialize();

	
	// カメラの初期化
	camera_.Initialize();

	blockModel_ = Model::CreateFromOBJ("block");



	// 02_03天球
	// skydome生成
	skydome_ = new Skydome();
	// 初期化
	modelskydome_ = Model::CreateFromOBJ("skyDome", true);
	skydome_->Initialize(modelskydome_, &camera_);
	

	



	mapChipField_ = new MapChipField;

	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");

	GenerateBlocks();

	// 自キャラの生成
	player_ = new Player();

	modelplayer_ = Model::CreateFromOBJ("player", true);

	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(2, 18);

	player_->SetMapChipField(mapChipField_);
	// 自キャラの初期化
	player_->Initialize(modelplayer_, &camera_, playerPosition);


	
	
	
	

	modelenemy_ = Model::CreateFromOBJ("enemy", true);

	for (int32_t i = 0; i < 2; ++i) {
		Enemy* newEnemy = new Enemy();
		Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(50 + i * 5,18 );
		// 自キャラの初期化
		newEnemy->Initialize(modelenemy_, &camera_, enemyPosition);

		enemies_.push_back(newEnemy);
	}


	camera_.farZ = 1000.0f;


	CController_ = new CameraController();//生成
	CController_->Initialize(&camera_);//初期化
	CController_->SetTarget(player_);//追従対象をセット
	CController_->Reset();//リセット

	CameraController::Rect cameraArea = {12.0f, 100 - 12.0f, 6.0f, 6.0f};
	CController_->SetMovableArea(cameraArea);//移動範囲の指定

	deathParticle_model_ = Model::CreateFromOBJ("deathParticle");
	
	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);
	
}

void GameScene::GenerateBlocks() 
{
	// 要素数
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockViritical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	// 要素数を変更する

	worldTransformBlocks_.resize(numBlockVirtical);

	// キューブの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}
	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}
void GameScene::CheckAllCollisions() 
{

		// 判定対象1と2の座標
		AABB aabb1, aabb2;

#pragma region 自キャラと敵キャラの当たり判定
		{
			// 自キャラの座標
		    aabb1 = player_->GetAABB();

			// 自キャラと敵弾全ての当たり判定
		    for (Enemy* enemy : enemies_) {

				// コリジョン無効の敵はスキップ
				if (enemy->IsCollisionDisabled())
					continue;

				// 敵弾の座標
				aabb2 = enemy->GetAABB();

				// AABB同士の交差判定
				if (IsCollision(aabb1, aabb2)) {
					// 自キャラの衝突時コールバックを呼び出す
				    player_->OnCollision(enemy);
					// 敵弾の衝突時コールバックを呼び出す
				    enemy->OnCollision(player_);
				}
			}
		}
#pragma endregion
	
}

void GameScene::ChagePhase()
{
	switch (phase_)
	{ 
		case Phase::kPlay:
		
		if (player_->IsDead()) {
			// 死亡演出
			phase_ = Phase::kDeath;

			const Vector3& deathParticlesPosition = player_->GetWorldPosition();

			deathParticles_ = new DeathParticles;
			deathParticles_->Initialize(deathParticle_model_, &camera_, deathParticlesPosition);
			
		}

		    break;
	    case Phase::kDeath:

		    break;
	}

}

bool GameScene::AreAllEnemiesDefeated() const
{ 
  for (const Enemy* enemy : enemies_) {
		if (!enemy->IsDead())
			return false;
	}
	return true;
}

void GameScene::Update()
{


	// 0215 7枚目 デスフラグの立った敵を削除
	enemies_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});


	enemies_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});



	ChagePhase();
	switch (phase_)
	{ 
		case Phase::kFadeIn:
		fade_->Update();
		if (fade_->IsFinished()) 
		{
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			phase_ = Phase::kPlay;
		}

		skydome_->Update();
		CController_->Update();
		
		player_->UpDate();

		for (Enemy* enemy : enemies_) {
			enemy->UpDate();
		}
		 

	
		

		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform*& worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;
				// アフィン変換行列の生成
				worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);

				// 定数バッファに転送する
				worldTransformBlock->TransferMatrix();
			}
		}
		break;
		case Phase::kPlay:

			skydome_->Update();
		    CController_->Update();
		    player_->UpDate();
		   
			
		    for (Enemy* enemy : enemies_) 
			{
			    enemy->UpDate();
		    }


		   
		    CheckAllCollisions();
		break;
	    case Phase::kDeath:
		   
			if (deathParticles_ && deathParticles_->IsFnished())
			{
			    phase_ = Phase::kFadeOut;
			}

			skydome_->Update();
		    CController_->Update();

			for (Enemy* enemy : enemies_) {
			    enemy->UpDate();
		    }

		    if (deathParticles_) {
			    deathParticles_->Update();
		    }

		    break;
	    case Phase::kFadeOut:
		    fade_->Update();
		    if (fade_->IsFinished()) {
			    finished_ = true;
		    }

		    skydome_->Update();
		    CController_->Update();
		  
		    for (Enemy* enemy : enemies_) {
			    enemy->UpDate();
		    }

		    break;

	}


}

void GameScene::Draw() 
{

	if (!player_->IsDead())
		player_->Draw();
       
	
	for (Enemy* enemy : enemies_) {
		enemy->Draw();
	}

	if (deathParticles_) 
	{
		deathParticles_->Draw();
	}
	// 天球描画
	skydome_->Draw();
	
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform*& worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			blockModel_->Draw(*worldTransformBlock, camera_);
		}
	}
	Model::PostDraw();


	
	fade_->Draw();
}

GameScene::~GameScene() 
{

	

	delete model_;

	delete blockModel_;

	delete skydome_;

	delete modelplayer_;

	delete player_;

	delete deathParticle_model_;

	


	

	for (Enemy* enemy : enemies_) {
		delete enemy;
	}

	delete modelenemy_;
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform*& worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();

	delete mapChipField_;
}

