#define NOMINMAX
#include "Player.h"
#include <numbers>
#include <cassert>
#include <algorithm>
#include "Math.h"


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

void Player::UpDate() 
{

	// アフィン変換行列の生成
	worldTransform_.matWorld_ = math_->MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 定数バッファに転送する
	worldTransform_.TransferMatrix();
	if (onGround_) 
	{
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				if (velocity_.x < 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAcceleration;
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;

					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;
				}

			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
				if (velocity_.x > 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x -= kAcceleration;
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;

					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;
				}
			}
			velocity_ = math_->Add(velocity_, acceleration);

			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
		} else {
			velocity_.x *= (1.0f - kAcceleration);
			
		}
		if (Input::GetInstance()->PushKey(DIK_UP))
		{
			velocity_ = math_->Add(Vector3(0, kJumpAcceleration, 0),velocity_);

		}
	} else 
	{
		velocity_ = math_->Add(Vector3(0, -kGravityAcceleration / 60, 0), velocity_);
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}

	worldTransform_.translation_ = math_->Add(velocity_, worldTransform_.translation_);
	updatetransform_->WorldTransformUpdate(worldTransform_);


	bool landing = false;

	if (velocity_.y < 0)
	{
		if (worldTransform_.translation_.y <= 1.0f)
		{
			landing = true;
		}
	}

	if (onGround_)
	{
		if (velocity_.y > 0.0f)
		{
			onGround_ = false;
		}
	} else 
	{
		if (landing)
		{
			worldTransform_.translation_.y = 1.0f;

			velocity_.x *= (1.0f - kAttenuation);

			velocity_.y = 0.0f;

			onGround_ = true;
		}
	}
	if (turnTimer_ > 0.0f) {
		turnTimer_ = std::max(turnTimer_ - (1.0f / 60.0f), 0.0f);
		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		worldTransform_.rotation_.y = math_->EaseInOut(destinationRotationY, turnFirstRotationY_, turnTimer_ / kTimeTurn);
	}
}
void Player::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	model_->Draw(worldTransform_, *camera_);

	Model::PostDraw();
}