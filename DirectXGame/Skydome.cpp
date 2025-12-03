#include "Skydome.h"



void Skydome::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera) { 
	
	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();

	
}

void Skydome::Update() 
{ 
	worldTransform_.TransferMatrix();
}

void Skydome::Draw()
{
	
	KamataEngine::DirectXCommon* dxcommon = KamataEngine::DirectXCommon::GetInstance();
	KamataEngine::Model::PreDraw(dxcommon->GetCommandList());
	model_->Draw(worldTransform_, *camera_);
	KamataEngine::Model::PostDraw();
	
}