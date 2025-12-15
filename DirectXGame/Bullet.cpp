#include "Bullet.h"
#include "MapChipField.h"
void Bullet::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position, const KamataEngine::Vector3& velocity) {
	assert(model);
	model_ = model;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	camera_ = camera;

	velocity_ = velocity;
}

AABB Bullet::GetAABB()
{
	KamataEngine::Vector3 worldPos = GetWorldPosition();
	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};
	return aabb;
}
void Bullet::OnCollision(const Enemy* enemy) 
{
	(void)enemy;

	isDead_ = true;
}

KamataEngine::Vector3 Bullet::GetWorldPosition() { return worldTransform_.translation_; }


void Bullet::Update() 
{
	// 移動
	worldTransform_.translation_ += velocity_;

	// マップ衝突判定
	if (mapchipField_) 
	{
		MapChipField::IndexSet index = mapchipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_);

		MapChipType type = mapchipField_->GetMapChipTypeByIndex(index.xIndex, index.yIndex);

		if (type == MapChipType::kBlock) 
		{
			if (bulletType_ == BulletType::Bounce) 
			{
				// バウンド弾：上下反転（まずは簡易）
				velocity_.y *= -1.0f;
			}
			else 
			{
				// 直進弾：消滅
				isDead_ = true;
				return;
			}
		}
	}

	// ワールド行列更新
	updatetransform_->WorldTransformUpdate(worldTransform_);
}



void Bullet::Draw() 
{ 
	model_->Draw(worldTransform_, *camera_); 
}

