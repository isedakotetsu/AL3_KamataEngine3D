#include "Math.h"
#include "Clear.h"
#include <numbers>

Clear::~Clear() {

	delete modelClear_;

	delete fade_;
}

void Clear::Initialize() {

	modelClear_ = Model::CreateFromOBJ("GameClear", true);

	// カメラ初期化
	camera_.Initialize();

	fade_ = new Fade();

	fade_->Initialize();

	// 0213 22枚目
	fade_->Start(Fade::Status::FadeIn, 1.0f);

	const float kPlayerTitle = 2.0f;

	worldTransformClear_.Initialize();

	worldTransformClear_.scale_ = {kPlayerTitle, kPlayerTitle, kPlayerTitle};
}

void Clear::Update() {

	//// 02_12 27枚目
	// if (Input::GetInstance()->PushKey(DIKSPACE)) {
	//    finished = true;
	// }

	switch (phase_) {
	case Phase::kFadeIn:
		fade_->Update();

		if (fade_->IsFinished()) {
			phase_ = Phase::kMain;
		}
		break;
	case Phase::kMain:
		if (Input::GetInstance()->PushKey(DIK_SPACE)) {
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			phase_ = Phase::kFadeOut;
		}
		break;
	case Phase::kFadeOut:
		fade_->Update();
		if (fade_->IsFinished()) {
			finished_ = true;
		}
		break;
	}

	counter_ += 1.0f / 60.0f;
	counter_ = std::fmod(counter_, kTimeClearMove);

	float angle = counter_ / kTimeClearMove * 2.0f * std::numbers::pi_v<float>;

	worldTransformClear_.translation_.y = std::sin(angle) + 10.0f;

	camera_.TransferMatrix();

	// アフィン変換～DirectXに転送(タイトル座標)
	updatetransform_->WorldTransformUpdate(worldTransformClear_);

	fade_->Update();
}

void Clear::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon->GetCommandList();

	Model::PreDraw(commandList);

	modelClear_->Draw(worldTransformClear_, camera_);

	fade_->Draw();
	Model::PostDraw();
}
