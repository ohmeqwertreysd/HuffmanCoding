#include "HuffmanTree.h"

HuffmanTreeNode::HuffmanTreeNode()
	: _data('\0'), _amount(0U) {}

HuffmanTreeNode::HuffmanTreeNode(const char& data, const uint32_t& amount)
	: _data(data), _amount(amount) {}

HuffmanTreeNode::HuffmanTreeNode(std::shared_ptr<HuffmanTreeNode>&& left, std::shared_ptr<HuffmanTreeNode>&& right)
	: _data('\0'), _amount(left->_amount + right->_amount), _left(std::move(left)), _right(std::move(right)) {}

HuffmanTreeNode::~HuffmanTreeNode()
{
	_left.reset();
	_right.reset();
}

bool HuffmanTreeNodeCmp::operator()(const std::shared_ptr<HuffmanTreeNode>& r, const std::shared_ptr<HuffmanTreeNode>& l)
{
	return r->_amount > l->_amount;
}