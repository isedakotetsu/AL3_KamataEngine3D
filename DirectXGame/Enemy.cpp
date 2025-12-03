#include "Enemy.h"
#include <numbers>
#include "MapChipField.h"
#include "Math.h"
#include <algorithm>
#include <cassert>
void Enemy::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position) {
	assert(model);
	// モデル
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * 3.0f / 2.0f;
	velocity_ = {-kWalkSpeed, 0, 0};
	camera_ = camera;
	walkTimer_ = 0.0f;
}

void Enemy::UpDate() 
{

	if (behaviorRequest_ != Behavior::kUnknown) {
		// 振るまいを変更する
		behavior_ = behaviorRequest_;

		// 各振るまいごとの初期化を実行
		switch (behavior_) {
		case Behavior::kDefeated:
		default:
			counter_ = 0;
			break;
		}

		// 振るまいリクエストをリセット
		behaviorRequest_ = Behavior::kUnknown;
	}

	// 02_15 13枚目
	switch (behavior_) {
	// 歩行
	case Behavior::kWalk:
		//// 02_09 16枚目 移動
		//worldTransform_.translation_ += velocity_;

		// 02_09 20枚目
		walkTimer_ += 1.0f / 60.0f;

		// 02_09 23枚目 回転アニメーション
		worldTransform_.rotation_.x = std::sin(std::numbers::pi_v<float> * 2.0f * walkTimer_ / kWalkMotionTime);

		// 02_09 スライド8枚目 ワールド行列更新
		updatetransform_->WorldTransformUpdate(worldTransform_);
		break;
	// やられ
	case Behavior::kDefeated:
		// 02_15 15枚目
		counter_ += 1.0f / 60.0f;

		worldTransform_.rotation_.y += 0.3f;
		worldTransform_.rotation_.x = EaseOut(kDefeatedMotionAngleStart, kDefeatedMotionAngleEnd, counter_ / kDefeatedTime);

		updatetransform_->WorldTransformUpdate(worldTransform_);

		if (counter_ >= kDefeatedTime) {
			isDead_ = true;
		}
		break;
	}

}

void Enemy::Draw() 
{
	KamataEngine::DirectXCommon* dxCommon = KamataEngine::DirectXCommon::GetInstance();

	KamataEngine::Model::PreDraw(dxCommon->GetCommandList());

	model_->Draw(worldTransform_, *camera_);

	KamataEngine::Model::PostDraw();
}
KamataEngine::Vector3 Enemy::GetWorldPosition() {
	KamataEngine::Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

AABB Enemy::GetAABB() 
{ 
	KamataEngine::Vector3 worldPos = GetWorldPosition();
	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};
	return aabb;

}

void Enemy::OnCollision(const Player* player) 
{ 
	
	(void)player; 
	

	if (behavior_ == Behavior::kDefeated) {
		// 敵がやられているなら何もしない
		return;
	}

	
}

