#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "KamataEngine.h"

enum class MapChipType {
	kBlank, // 空白
	kBlock, // ブロック
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};
/*
struct Vector3 {
	float x;
	float y;
	float z;
};
*/
class MapChipField
{
public:
//	// 1ブロックサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
//
//	void ResetMapChipData();
//	void LoadMapChipCsv(const std::string& filePath);
//	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
//    Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);
//	
//
private:
//	//ブロック個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;
	MapChipData mapChipData_;


};
