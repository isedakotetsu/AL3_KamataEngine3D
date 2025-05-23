#include "Player.h"
#include <numbers>
#include <cassert>


using namespace KamataEngine;

void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const Vector3& position) 
{

	assert(model);

	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	worldTransform_.translation_ = {10.3f, 10.0f, 0.0f};

	worldTransform_.rotation_ = {0.0f, 1.5f, 0.0f};
	camera_ = camera;
}

void Player::UpDate() {

	// アフィン変換行列の生成
	worldTransform_.matWorld_ = math_->MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 定数バッファに転送する
	worldTransform_.TransferMatrix();
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) 
	{
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT))
		{
			acceleration.x += kAcceleration;
		} 
		else if (Input::GetInstance()->PushKey(DIK_LEFT))
		{
			acceleration.x -= kAcceleration;
		}
		velocity_ = math_->Add(velocity_,acceleration);
	}
	worldTransform_.translation_ = math_->Add(velocity_, worldTransform_.translation_);
	updatetransform_->WorldTransformUpdate(worldTransform_);

}
void Player::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	model_->Draw(worldTransform_, *camera_);

	Model::PostDraw();
}