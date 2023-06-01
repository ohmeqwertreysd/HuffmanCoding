#pragma once

#include <string>
#include <memory>

struct HuffmanTreeNodeCmp;

class HuffmanTreeNode
{
public:
	HuffmanTreeNode();
	HuffmanTreeNode(const char& data, const uint32_t& amount);
	HuffmanTreeNode(std::shared_ptr<HuffmanTreeNode>&& left, std::shared_ptr<HuffmanTreeNode>&& right);
	~HuffmanTreeNode();

	friend HuffmanTreeNodeCmp;
public:
	char _data;
	uint32_t _amount;
	std::string _bitCode;
	std::shared_ptr<HuffmanTreeNode> _left;
	std::shared_ptr<HuffmanTreeNode> _right;
};

struct HuffmanTreeNodeCmp
{
	bool operator()(const std::shared_ptr<HuffmanTreeNode>& r, const std::shared_ptr<HuffmanTreeNode>& l);
};