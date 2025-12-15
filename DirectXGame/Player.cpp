#define NOMINMAX

#include "Player.h"
#include "MapChipField.h"
#include "Math.h"

#include <algorithm>
#include <cassert>
#include <numbers>
#include "GameScene.h"


Player::~Player() 
{
	for (Bullet* bullet : bullets_) 
	{
		delete bullet;
	}
}

void Player::Initialize(KamataEngine::Model* model, 
	KamataEngine::Camera* camera, const KamataEngine::Vector3& position) 
{

	assert(model);
	// モデル
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	camera_ = camera;

	Bulletmodel_ = KamataEngine::Model::CreateFromOBJ("attack", true);
}


void Player::BehaviorRootInitialize() 
{

}
void Player::BehaviorAttackInitialize() 
{
	velocity_ = {};

	
	
}


void Player::InputMove() 
{

	if (onGround_) {

		// 左右移動操作
		if (KamataEngine::Input::GetInstance()->PushKey(DIK_D) || KamataEngine::Input::GetInstance()->PushKey(DIK_A)) {

			// 左右加速
			KamataEngine::Vector3 acceleration = {};
			if (KamataEngine::Input::GetInstance()->PushKey(DIK_D)) {

				if (velocity_.x < 0.0f) {
					// 旋回の最初は移動減衰をかける
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAcceleration / 60.0f;
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;
				}
			} else if (KamataEngine::Input::GetInstance()->PushKey(DIK_A)) {
				if (velocity_.x > 0.0f) {
					// 旋回の最初は移動減衰をかける
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x -= kAcceleration / 60.0f;
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;
				}
			}
			velocity_ += acceleration;
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
		} else {
			// 非入力時は移動減衰をかける
			velocity_.x *= (1.0f - kAttenuation);
		}

		// ほぼ0の場合に0にする
		if (std::abs(velocity_.x) <= 0.0001f) {
			velocity_.x = 0.0f;
		}

		if (KamataEngine::Input::GetInstance()->PushKey(DIK_SPACE)) {
			// ジャンプ初速
			velocity_ += KamataEngine::Vector3(0, kJumpAcceleration / 60.0f, 0);
		}
	} else {
		// 落下速度
		velocity_ += KamataEngine::Vector3(0, -kGravityAcceleration / 60.0f, 0);
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}

	
}


void Player::Shot(const KamataEngine::Vector3& position)
{
	if (!KamataEngine::Input::GetInstance()->PushKey(DIK_E)) 
	{
		return;
	}

	const float kBulletSpeed = 0.5f;

	KamataEngine::Vector3 dir = {0, 0, 0};

	
	if (KamataEngine::Input::GetInstance()->PushKey(DIK_W)) 
	{
		dir.y = 1.0f; // 上
	} else if (KamataEngine::Input::GetInstance()->PushKey(DIK_S)) 
	{
		dir.y = -1.0f; // 下
	} else if (KamataEngine::Input::GetInstance()->PushKey(DIK_D))
	{
		dir.x = 1.0f; // 右
	} else if (KamataEngine::Input::GetInstance()->PushKey(DIK_A))
	{
		dir.x = -1.0f; // 左
	} else {
		// 方向キーが押されていないときは向いている方向
		dir.x = (lrDirection_ == LRDirection::kRight) ? 1.0f : -1.0f;
	}

	Bullet* newBullet = new Bullet();
	KamataEngine::Vector3 BulletPos = position;
	KamataEngine::Vector3 velocity = dir * kBulletSpeed;
	newBullet->Initialize(Bulletmodel_, camera_, BulletPos, velocity);
	newBullet->SetBulletType(currentBulletType_);
	newBullet->SetMapChipField(mapChipField_);
	bullets_.push_back(newBullet);
}



void Player::OnCollision(const Enemy* enemy) { 
	(void)enemy;
	

	isDead_ = true;
}


void Player::CheckMapCollision(CollisionMapInfo& info) 
{
	CheckMapCollisionUp(info); 
	CheckMapCollisionDown(info);
	CheckMapCollisionRight(info);
	CheckMapCollisionLeft(info);
}

void Player::UpdateOnGround(const CollisionMapInfo& info) 
{ 
	if (onGround_) {
		if (velocity_.y > 0.0f) {
			onGround_ = false;
		} else {

			std::array<KamataEngine::Vector3, kNumCorner> positionsNew;
			for (uint32_t i = 0; i < positionsNew.size(); ++i) {
				positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
			}

			bool hit = false;
			MapChipType mapChipType;
			// 左下点の判定
			MapChipField::IndexSet indexSet;
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom] + KamataEngine::Vector3(0, -kGroundSearchHeight, 0));
			mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

			if (mapChipType == MapChipType::kBlock) {
				hit = true;
			}
			// 右下点の判定
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom] + KamataEngine::Vector3(0, -kGroundSearchHeight, 0));
			mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

			if (mapChipType == MapChipType::kBlock) {
				hit = true;
			}
			// 落下開始
			if (!hit) {
				// 空中状態に切り替える
				onGround_ = false;
			}
		}
	} 
	else 
	{
		if (info.landing) {
			// 着地状態に切り替える（落下を止める）
			onGround_ = true;
			// 着地時にX速度を減衰
			velocity_.x *= (1.0f - kAttenuationLanding);
			// Y速度をゼロにする
			velocity_.y = 0.0f;
		}
	}
}

void Player::UpdateOnWall(const CollisionMapInfo& info) 
{ 
	if (info.hitWall)
	{
		velocity_.x *= (1.0f - kAttenuationWall);
	}

}


void Player::CheckMapCollisionUp(CollisionMapInfo& info) {

	// 02_07スライド20枚目 上昇あり?
	if (info.move.y <= 0) {
		return;
	}

	// 02_07 スライド19枚目（下のfor文も）
	std::array<KamataEngine::Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}

	// 02_07 スライド28枚目（下のfor文も）
	MapChipType mapChipType;
	// 真上の当たり判定を行う
	bool hit = false;

	// 左上点の判定
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}

	// 右上点の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}

	// ブロックにヒット？ 02_07 スライド34枚目
	if (hit) {
		// 現在座標が壁の外か判定
		MapChipField::IndexSet indexSetNow;
		indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + KamataEngine::Vector3(0, +kHeight / 2.0f, 0));
		if (indexSetNow.yIndex != indexSet.yIndex) {
			// めり込みを排除する方向に移動量を設定する
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + info.move + KamataEngine::Vector3(0, +kHeight / 2.0f, 0));
			MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
			info.move.y = std::max(0.0f, rect.bottom - worldTransform_.translation_.y - (kHeight / 2.0f + kBlank));
			info.ceiling = true;
		}
	}
}

void Player::CheckMapCollisionDown(CollisionMapInfo& info) 
{ 
	if (info.move.y >= 0)
	{
		return;
	}
	std::array<KamataEngine::Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}
	MapChipType mapChipType;

	//真下の当たり判定を行う
	bool hit = false;
	// 左下点の判定
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	
	if (mapChipType == MapChipType::kBlock) 
	{
		hit = true;
	}
	//右下点の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	

	if (mapChipType == MapChipType::kBlock) 
	{
		hit = true;
	}

	if (hit)
	{
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + info.move + KamataEngine::Vector3(0, -kHeight / 2.0f, 0));
			// めり込み先ブロックの範囲矩形
			MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
			info.move.y = std::min(0.0f, rect.top - worldTransform_.translation_.y + (kHeight / 2.0f + kBlank));
			info.landing = true;
	}

}

void Player::CheckMapCollisionRight(CollisionMapInfo& info) 
{
	if (info.move.x <= 0) {
		return;
	}
	std::array<KamataEngine::Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}
	MapChipType mapChipType;
	// 真下の当たり判定を行う
	bool hit = false;
	// 右の判定
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	// 右下点の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}

	if (hit) {
		
		MapChipField::IndexSet indexSetNow;
		indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + KamataEngine::Vector3(+kWidth / 2.0f, 0, 0));
		if (indexSetNow.xIndex != indexSet.xIndex)
		{
			// めり込みを排除する方向に移動量を設定する
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + info.move + KamataEngine::Vector3(+kWidth / 2.0f, 0, 0));
			// めり込み先ブロックの範囲矩形
			MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
			info.move.x = std::max(0.0f, rect.left - worldTransform_.translation_.x - (kWidth / 2.0f + kBlank));
			info.hitWall = true;
		}
	}
}

void Player::CheckMapCollisionLeft(CollisionMapInfo& info) 
{
	if (info.move.x >= 0) {
		return;
	}

	std::array<KamataEngine::Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}

	MapChipType mapChipType;
	
	bool hit = false;

	
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}

	
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}

	
	if (hit) {
	
		MapChipField::IndexSet indexSetNow;
		indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + KamataEngine::Vector3(-kWidth / 2.0f, 0, 0));

		if (indexSetNow.xIndex != indexSet.xIndex) {
		
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + info.move + KamataEngine::Vector3(-kWidth / 2.0f, 0, 0));
			MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
			info.move.x = std::max(0.0f, rect.right - worldTransform_.translation_.x - (kWidth / 2.0f + kBlank));
			info.hitWall = true;
		}
	}
}


KamataEngine::Vector3 Player::CornerPosition(const KamataEngine::Vector3& center, Corner corner) {

	KamataEngine::Vector3 offsetTable[] = {
	    {+kWidth / 2.0f, -kHeight / 2.0f, 0}, //  kRightBottom
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0}, //  kLeftBottom
	    {+kWidth / 2.0f, +kHeight / 2.0f, 0}, //  kRightTop
	    {-kWidth / 2.0f, +kHeight / 2.0f, 0}  //  kLeftTop
	};

	return center + offsetTable[static_cast<uint32_t>(corner)];
}



KamataEngine::Vector3 Player::GetWorldPosition() 
{ 
	KamataEngine::Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;

}



AABB Player::GetAABB() 
{ 
	KamataEngine::Vector3 worldPos = GetWorldPosition();
	AABB aabb;

    aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};
	return aabb;
}
void Player::BehaviorRootUpdate() 
{
	// 移動入力(02_07 スライド10枚目)
	InputMove();

	// 衝突情報を初期化(02_07 スライド13枚目)
	CollisionMapInfo collisionMapInfo = {};
	collisionMapInfo.move = velocity_;
	collisionMapInfo.landing = false;
	collisionMapInfo.hitWall = false;

	// マップ衝突チェック(02_07 スライド13枚目)
	CheckMapCollision(collisionMapInfo);

	// 移動(02_07 スライド36枚目)
	worldTransform_.translation_ += collisionMapInfo.move;

	// 天井接触による落下開始(02_07 スライド38枚目)
	if (collisionMapInfo.ceiling) {
		velocity_.y = 0;
	}

	// 02_08 スライド27枚目 壁接触している場合の処理
	UpdateOnWall(collisionMapInfo);

	// 接地判定
	UpdateOnGround(collisionMapInfo);

	// 旋回制御
	if (turnTimer_ > 0.0f) {
		// タイマーを進める
		turnTimer_ = std::max(turnTimer_ - (1.0f / 60.0f), 0.0f);

		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};

		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

		worldTransform_.rotation_.y = EaseInOut(destinationRotationY, turnFirstRotationY_, turnTimer_ / kTimeTurn);
	}
	
	 
	
}



void Player::BehaviorAttackUpdate() 
{
	
	
}




void Player ::UpDate() 
{ 
	
	
	BehaviorRootUpdate();

	// デバッグ用：キーで武器切り替え
	if (KamataEngine::Input::GetInstance()->TriggerKey(DIK_1)) 
	{
		currentBulletType_ = BulletType::Straight;
	}
	if (KamataEngine::Input::GetInstance()->TriggerKey(DIK_2)) 
	{
		currentBulletType_ = BulletType::Bounce;
	}


	// 発射タイマー更新
	if (shotTimer_ > 0) {
		shotTimer_--;
	}

	// 攻撃パターン
	if (shotTimer_ == 0) {
		Shot(worldTransform_.translation_);
		shotTimer_ = kShotInterval_; // 次の発射までの待ち時間
	}

	// 弾の更新
	for (Bullet* bullet : bullets_) {
		bullet->Update();
	}
	bullets_.remove_if([](Bullet* bullet) 
		{
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
	// ワールド行列更新（アフィン変換～DirectXに転送）
	updatetransform_->WorldTransformUpdate(worldTransform_);


}

void Player::Draw() {
	KamataEngine::DirectXCommon* dxCommon = KamataEngine::DirectXCommon::GetInstance();

	KamataEngine::Model::PreDraw(dxCommon->GetCommandList());

	model_->Draw(worldTransform_, *camera_);
	for (Bullet* bullet : bullets_) 
	{
		bullet->Draw();
	}

	KamataEngine::Model::PostDraw();
}
