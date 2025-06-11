#include "CameraController.h"
#include <algorithm>
#include "Player.h"



void CameraController::Initialize(KamataEngine::Camera* camera) 
{
	camera_ = camera; 

}


void CameraController::Update() 
{
	
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	const Vector3& targetVelocity = target_->GetVelocity();
	destination_ = targetWorldTransform.translation_ + target0ffset_ + targetVelocity * kVelocityBias;

	camera_->translation_ = Lerp(camera_->translation_, destination_, kInterpolationRate);


	//追従対象yが画面外二でないように補正
	camera_->translation_.x = max(camera_->translation_.x, destination_.x + targetMargin.left);
	camera_->translation_.x = min(camera_->translation_.x, destination_.x + targetMargin.right);
	camera_->translation_.y = max(camera_->translation_.y, destination_.y + targetMargin.bottom);
	camera_->translation_.y = min(camera_->translation_.y, destination_.y + targetMargin.top);

	camera_->translation_.x = max(camera_->translation_.x, movableArea_.left);
	camera_->translation_.x = min(camera_->translation_.x, movableArea_.right);
	camera_->translation_.y = min(camera_->translation_.y, movableArea_.bottom);
	camera_->translation_.y = max(camera_->translation_.y, movableArea_.top);

	
	//行列の更新
	camera_->UpdateMatrix();

	
}

void CameraController::Reset() 
{ 
	//追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	//追従対象とオフセットからカメラの座標を計算
	camera_->translation_ = targetWorldTransform.translation_ + target0ffset_;

}
