#include "GameScene.h"
#include "TitleScene.h"
#include <Windows.h>
#include "Over.h"
#include "Clear.h"
#include "Player.h"
#include "Enemy.h"


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
    // Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	
	KamataEngine::Initialize(L"AL3");

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	

	
	scene = Scene::kTitle;
	titleScene = new TitleScene;
	titleScene->Initialize();

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

void ChageScene() 
{
	switch (scene) 
	{
	 case Scene::kTitle:
		if (titleScene->IsFinished()) {

			scene = Scene::kGame;
			delete titleScene;
			titleScene = nullptr;
			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;
	 case Scene::kGame:
		// 02_12 30枚目

		// シーン変更
		if (gameScene->GetPlayer()->IsDead()) {
			scene = Scene::kOver;
			delete gameScene;
			gameScene = nullptr;
			gameOverScene =new Over;
			gameOverScene->Initialize();
		} else if (gameScene->AreAllEnemiesDefeated()) {
			scene = Scene::kClear;
			delete gameScene;
			gameScene = nullptr;
			gameClearScene = new Clear;
			gameClearScene->Initialize();
		}
		break;
	 case Scene::kClear:
		if (gameClearScene->IsFinished()) {
			scene = Scene::kTitle;
			delete gameClearScene;
			gameClearScene = nullptr;
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;
	 case Scene::kOver:
		if (gameOverScene->IsFinished()) {
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
