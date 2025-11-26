#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "KamataEngine.h"
#include "Math.h"
#include "Player.h"

enum class MapChipType {
	kBlank, // 空白
	kBlock, // ブロック
};



struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

class MapChipField
{
public:

	struct IndexSet
	{
		uint32_t xIndex;
		uint32_t yIndex;
	};

	struct Rect
	{
		float left;
		float right;
		float bottom;
		float top;
	};
//	// 1ブロックサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	int GetNumBlockViritical() { return kNumBlockVirtical; }
	int GetNumBlockHorizontal() { return kNumBlockHorizontal; }

	void ResetMapChipData();
	void LoadMapChipCsv(const std::string& filePath);
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
	KamataEngine::Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	IndexSet GetMapChipIndexSetByPosition(const KamataEngine::Vector3& position);
	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

private:
//	//ブロック個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;
	MapChipData mapChipData_;


};
