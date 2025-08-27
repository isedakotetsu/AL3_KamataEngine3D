#include "Over.h"
#include "Math.h"
#include <numbers>

Over::~Over() 
{

	delete modelOver_;

	delete fade_;
}

void Over::Initialize() {

	modelOver_ = Model::CreateFromOBJ("GameOver", true);

	// カメラ初期化
	camera_.Initialize();

	fade_ = new Fade();

	fade_->Initialize();

	// 0213 22枚目
	fade_->Start(Fade::Status::FadeIn, 1.0f);

	const float kPlayerTitle = 2.0f;

	worldTransformOver_.Initialize();

	worldTransformOver_.scale_ = {kPlayerTitle, kPlayerTitle, kPlayerTitle};
}

void Over::Update() {

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
	counter_ = std::fmod(counter_, kTimeOverMove);

	float angle = counter_ / kTimeOverMove * 2.0f * std::numbers::pi_v<float>;

	worldTransformOver_.translation_.y = std::sin(angle) + 10.0f;

	camera_.TransferMatrix();

	// アフィン変換～DirectXに転送(タイトル座標)
	updatetransform_->WorldTransformUpdate(worldTransformOver_);

	fade_->Update();
}

void Over::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon->GetCommandList();

	Model::PreDraw(commandList);

	modelOver_->Draw(worldTransformOver_, camera_);

	fade_->Draw();
	Model::PostDraw();
}
