#include "CameraController.h"
#include <algorithm>
#include "Player.h"



void CameraController::Initialize(KamataEngine::Camera* camera) 
{
	camera_ = camera; 
}


void CameraController::Update() 
{

}

void CameraController::Reset() 
{ 
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	camera_->translation_ = math_->Add( targetWorldTransform.translation_,target0ffset_);

}
