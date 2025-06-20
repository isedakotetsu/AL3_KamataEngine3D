#pragma once
#include "KamataEngine.h"
#include "Math.h"
#include "Updatetransform.h"
class Enemy
{
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void UpDate();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	KamataEngine::WorldTransform worldTransform_;
	Updatetoransform* updatetransform_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;
};