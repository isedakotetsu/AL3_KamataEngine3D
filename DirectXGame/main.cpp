#include <Windows.h>
#include "kamataEngine.h"
#include "GameScene.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) 
{
	KamataEngine::Initialize(L"LE2C_04_イセダ_コテツ_AL3");
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	GameScene* gameScene = new GameScene();

	gameScene->Initialize();

	


	while (true) 
	{

		if (KamataEngine::Update())
		{
			break;
		}
		//ゲームシーンの更新
		gameScene->Update();

		//描画開始
		dxCommon->PreDraw();

		//ゲームシーンの描画
		gameScene->Draw();

		//描画終了
		dxCommon->PostDraw();
	}

	KamataEngine::Finalize();
	delete gameScene;

	gameScene = nullptr;
	
	return 0;
}
