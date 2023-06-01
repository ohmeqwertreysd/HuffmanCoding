#pragma once

#include "HuffmanTree.h"
#include "FrequencyCounter.h"
#include <string>
#include <memory>
#include <unordered_map>

class HuffmanEncoder
{
public:
	void encode(const std::string& inputDecodeFile, const std::string& outputEncodeFile);
private:
	void buildHuffmanTree(const FrequencyCounter& freq);
	void buildHuffmanCodeTable();
	void serializeTree(std::ofstream& ofs);
	void writeBit(std::ofstream& ofs, const bool bit, uint8_t& buf, uint8_t& counter);
private:
	std::shared_ptr<HuffmanTreeNode> _huffmanTree;
	std::unordered_map<char, std::string> _huffmanCodeTable;
};