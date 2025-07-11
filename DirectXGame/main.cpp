#include "GameScene.h"
#include "TitleScene.h"
#include <Windows.h>


GameScene* gameScene = nullptr;

TitleScene* titleScene = nullptr;

enum class Scene 
{
	kUnknown = 0,

	kTitle,
	kGame,
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
	KamataEngine::Finalize();

	return 0;
}

void ChageScene() 
{
	switch (scene) 
	{
	case Scene::kUnknown:

		break;
	case Scene::kTitle:
		if (titleScene->IsFinished())
		{
			scene = Scene::kGame;

			delete titleScene;
			titleScene = nullptr;

			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;
	case Scene::kGame:
		if (gameScene->IsFnished()) {
			// シーン変更
			scene = Scene::kTitle;
			delete gameScene;
			gameScene = nullptr;
			titleScene = new TitleScene;
			titleScene->Initialize();
		}

		break;
	}
}

void UpdateScene() 
{
	switch (scene) 
	{
	case Scene::kUnknown:
		break;
	case Scene::kTitle:
		titleScene->Update();
		break;
	case Scene::kGame:
		gameScene->Update();
		break;
	default:
		break;
	}
}

void DrawScene() 
{
	switch (scene) 
	{
	case Scene::kTitle:

		titleScene->Draw();
		break;
	case Scene::kGame:

		gameScene->Draw();
		break;
	}
}
