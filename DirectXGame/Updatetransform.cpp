#include "Updatetransform.h"

	void Updatetoransform::WorldTransformUpdate(WorldTransform& worldTransform) {

	Matrix4x4 affin_mat =MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);

	worldTransform.matWorld_ = affin_mat;

	// 定数バッファに転送する
	worldTransform.TransferMatrix();
}

