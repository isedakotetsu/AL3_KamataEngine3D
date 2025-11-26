#pragma once

#include <KamataEngine.h>
#include <math.h>
#include <time.h>
#define _USE_MATH_DEFINE
#include <assert.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>



//class Math {
//public:

	// 円周率
	const float PI = 3.141592654f;

	struct AABB {
	    KamataEngine::Vector3 min;
	    KamataEngine::Vector3 max;
	};

	const KamataEngine::Vector3 operator+(const KamataEngine::Vector3& lhv, const KamataEngine::Vector3& rhv);

	const KamataEngine::Vector3 operator*(const KamataEngine::Vector3& v1, const float f);

	KamataEngine::Vector3 Lerp(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2, float t);


	// 代入演算子オーバーロード
    KamataEngine::Vector3& operator+=(KamataEngine::Vector3& lhs, const KamataEngine::Vector3& rhv);
    KamataEngine::Vector3& operator-=(KamataEngine::Vector3& lhs, const KamataEngine::Vector3& rhv);
    KamataEngine::Vector3& operator*=(KamataEngine::Vector3& v, float s);
    KamataEngine::Vector3& operator/=(KamataEngine::Vector3& v, float s);

	 float EaseInOut(float start, float end, float t);
    float EaseIn(float x1, float x2, float t);
     float EaseOut(float x1, float x2, float t);

	// 加算
     KamataEngine::Vector3 Add(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

	// 減算
     KamataEngine::Vector3 Subtract(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

	// スカラー倍
     KamataEngine::Vector3 Multiply(float scalar, const KamataEngine::Vector3& v1);

	// 内積
     float Dot(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

	// 長さ(ノルム)
     float Length(const KamataEngine::Vector3& v1);

	// 正規化
     KamataEngine::Vector3 Normalize(const KamataEngine::Vector3& v);

	// 1.行列の加法
     KamataEngine::Matrix4x4 Add(const KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2);

	// 2.行列の減法
     KamataEngine::Matrix4x4 Subtract(const KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2);

	// 3.行列の積
     KamataEngine::Matrix4x4 Multiply(const KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2);

	// 4.逆行列
     KamataEngine::Matrix4x4 Inverse(const KamataEngine::Matrix4x4& m);

	// 5.転置行列
     KamataEngine::Matrix4x4 Transpose(const KamataEngine::Matrix4x4& m);

	// 6.単位行列の作成
     KamataEngine::Matrix4x4 MakeIdenity4x4();

	// 1.平行移動行列
     KamataEngine::Matrix4x4 MakeTranslateMatrix(const KamataEngine::Vector3& translate);

	// 2.拡大縮小行列
     KamataEngine::Matrix4x4 MakeScaleMatrix(const KamataEngine::Vector3& scale);

	// 3.座標変換
     KamataEngine::Vector3 Transform(const KamataEngine::Vector3& vector, const KamataEngine::Matrix4x4& matrix);

	// X軸回転行列
     KamataEngine::Matrix4x4 MakeRotateXMatrix(float radian);

	// Y軸回転行列
     KamataEngine::Matrix4x4 MakeRotateYMatrix(float radian);

	// Z軸回転行列
     KamataEngine::Matrix4x4 MakeRotateZMatrix(float radian);

	// 3次元アフィン変換行列
     KamataEngine::Matrix4x4 MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rotate, const KamataEngine::Vector3& translate);
	
	float Lerp(float x1, float x2, float t);

	bool IsCollision(const AABB &aabb1, const AABB &aabb2);

	// 代入演算子オーバーロード
    KamataEngine::Matrix4x4& operator*=(KamataEngine::Matrix4x4& lhm, const KamataEngine::Matrix4x4& rhm);

	// 2項演算子オーバーロード
    KamataEngine::Matrix4x4 operator*(const KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2);


//};

