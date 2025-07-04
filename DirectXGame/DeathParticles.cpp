#include "DeathParticles.h"

void DeathParticles::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const Vector3& position) {
	assert(model);
	// モデル
	model_ = model;

	camera_ = camera;

	for (WorldTransform& worldTransform : worldTransforms_)
	{
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};
}

void DeathParticles::Update() 
{ 
	if (isFinished_) {
		return;
	}
	for (uint32_t i = 0; i < kNumParticles; ++i) 
	{
		//基本となる速度ベクトル
		Vector3 velocity = {kSpeed_, 0, 0};
		//回転角を計算する
		float angle = kAngleUnit_ * i;
		//z軸周り回転行列
		Matrix4x4 matrixRotation = MakeRotateZMatrix(angle);
		//基本ベクトルを回転させて速度ベクトルを得る
		velocity = Transform(velocity, matrixRotation);

		// 移動処理
		worldTransforms_[i].translation_ += velocity;
	}
	//カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;
	//存続時間の上限を達したら
	if (counter_ >= kDuration_)
	{
		counter_ = kDuration_;
		//終了扱いにする
		isFinished_ = true;
	}
	
	
	color_.w = std::clamp(1.0f - counter_ / kDuration_, 0.0f, 1.0f);

	//色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);

	for (WorldTransform& worldTransform : worldTransforms_)
	{
		updatetransform_->WorldTransformUpdate(worldTransform);
	}

}

void DeathParticles::Draw() 
{ 
	if (isFinished_) {
		return;
	}
	for (WorldTransform& worldTransform : worldTransforms_) 
	{
		DirectXCommon* dxCommon = DirectXCommon::GetInstance();
		Model::PreDraw(dxCommon->GetCommandList());
		model_->Draw(worldTransform, *camera_, &objectColor_);
		Model::PostDraw();
	}
	

}
