#pragma once
#include "KamataEngine.h"
#include "Math.h"


class Player;

class CameraController
{
public:
	void Initialize(KamataEngine::Camera* camera);

	void Update();

	void SetTarget(Player* target) { target_ = target; }
	

	void Reset();

private:

	KamataEngine::Camera* camera_ = nullptr;
    Player* target_ = nullptr;
	Math* math_ = nullptr;
	Vector3 target0ffset_ = {0, 0, -15.0f};
};
