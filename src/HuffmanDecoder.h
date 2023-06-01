#pragma once

#include "HuffmanTree.h"
#include <string>
#include <unordered_map>
#include <memory>

class HuffmanDecoder
{
public:
	void decode(const std::string& inputEncodeFile, const std::string& outputDecodeFile);
private:
	void deserializeTreeAndBuildCodeTable(std::ifstream& ifs);
	bool readBit(std::ifstream& ifs, char& byte, uint8_t& counter);
private:
	std::shared_ptr<HuffmanTreeNode> _huffmanTree;
	std::unordered_map<std::string, char> _huffmanCodeTable;
};