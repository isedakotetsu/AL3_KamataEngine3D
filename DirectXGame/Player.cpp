#include "Player.h"

#include <cassert>

using namespace KamataEngine;

void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = {10.3f, 10.0f, 0.0f};

	worldTransform_.rotation_ = {0.0f, 1.5f, 0.0f};
	camera_ = camera;
}

void Player::UpDate() {

	// アフィン変換行列の生成
	worldTransform_.matWorld_ = math_->MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 定数バッファに転送する
	worldTransform_.TransferMatrix();
}
void Player::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	model_->Draw(worldTransform_, *camera_);

	Model::PostDraw();
}
