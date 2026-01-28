#include "KamataEngine.h"
#include "GameScene.h"
#include "TitleScene.h"
#include <Windows.h>
#include "Over.h"
#include "Clear.h"
#include "Player.h"
#include "Enemy.h"
#include "Bgm.h"

using namespace KamataEngine;

GameScene* gameScene = nullptr;
Over* gameOverScene = nullptr;
Clear* gameClearScene = nullptr;
Player* player = nullptr;
Enemy* enemy = nullptr;
TitleScene* titleScene = nullptr;

enum class Scene 
{
	kUnknown = 0,

	kTitle,
	kGame,
	kClear,
	kOver,
};
Scene scene = Scene::kUnknown;

void ChageScene();
void UpdateScene();
void DrawScene();


BGM* bgm_ = nullptr;

uint32_t gameClearBgmHandle_;
uint32_t gamePlayBgmHandle_;
uint32_t titleBgmHandle_;
uint32_t overBgm_;

    // Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	
	KamataEngine::Initialize(L"LE2C_06_イセダ_コテツ_ELF FOREST");

	// DirectXCommonインスタンスの取得
	KamataEngine::DirectXCommon* dxCommon = KamataEngine::DirectXCommon::GetInstance();

	scene = Scene::kTitle;
	titleScene = new TitleScene;
	titleScene->Initialize();

	gameClearBgmHandle_ = Audio::GetInstance()->LoadWave("./BGM/clear.mp3");
	gamePlayBgmHandle_ = Audio::GetInstance()->LoadWave("./BGM/gameplay.mp3");
	titleBgmHandle_ = Audio::GetInstance()->LoadWave("./BGM/title.mp3");
	overBgm_ = Audio::GetInstance()->LoadWave("./BGM/GAMEover.mp3");

	bgm_ = new BGM();
	bgm_->Initialize();
	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

	
		ChageScene(); 
		
		UpdateScene();

		
		// 描画開始
		dxCommon->PreDraw();

		
		DrawScene(); 

		
		dxCommon->PostDraw();
	}

	
	delete titleScene;
	delete gameScene;
	delete gameOverScene;
	delete gameClearScene;
	delete player;
	delete enemy;

	KamataEngine::Finalize();

	return 0;
}
void ChageScene() {
	switch (scene) {
	case Scene::kTitle:
		if (!bgm_->IsPlaying())
			bgm_->BGMPlay(titleBgmHandle_);

		if (titleScene->IsFinished()) {

	
			bgm_->BGMStop();
			bgm_->BGMPlay(gamePlayBgmHandle_);

			scene = Scene::kGame;
			delete titleScene;
			titleScene = nullptr;
			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;

	case Scene::kGame:
		

		if (gameScene->GetPlayer()->IsDead()) {
			
			bgm_->BGMStop();
			bgm_->BGMPlay(overBgm_);

			scene = Scene::kOver;
			delete gameScene;
			gameScene = nullptr;
			gameOverScene = new Over;
			gameOverScene->Initialize();
		} else if (gameScene->AreAllEnemiesDefeated()) {
		
			bgm_->BGMStop();
			bgm_->BGMPlay(gameClearBgmHandle_);

			scene = Scene::kClear;
			delete gameScene;
			gameScene = nullptr;
			gameClearScene = new Clear;
			gameClearScene->Initialize();
		}
		break;

	case Scene::kClear:
	
		if (gameClearScene->IsFinished()) {
			bgm_->BGMStop();

			scene = Scene::kTitle;
			delete gameClearScene;
			gameClearScene = nullptr;
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;

	case Scene::kOver:
		if (gameOverScene->IsFinished()) {
			bgm_->BGMStop();

			scene = Scene::kTitle;
			delete gameOverScene;
			gameOverScene = nullptr;
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;
	}
}


void UpdateScene() 
{
	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();
		break;
	case Scene::kGame:
		gameScene->Update();
		break;
	case Scene::kClear:
		gameClearScene->Update();
		break;
	case Scene::kOver:
		gameOverScene->Update();
		break;
	}
}

void DrawScene() 
{
	switch (scene) {
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	case Scene::kClear:
		gameClearScene->Draw();
		break;
	case Scene::kOver:
		gameOverScene->Draw();
		break;
	}
}
