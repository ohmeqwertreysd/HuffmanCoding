#include "HuffmanEncoder.h"
#include <queue>
#include <stack>
#include <bitset>
#include <fstream>

void HuffmanEncoder::encode(const std::string& inputDecodeFile, const std::string& outputEncodeFile)
{
	FrequencyCounter freqCounter;
	freqCounter.readFile(inputDecodeFile);
	buildHuffmanTree(freqCounter);
	buildHuffmanCodeTable();

	std::ifstream fileInput(inputDecodeFile, std::ios::in | std::ios::binary);
	std::ofstream fileOutput(outputEncodeFile, std::ios::out | std::ios::binary);

	serializeTree(fileOutput);

	uint8_t buf = 0;
	uint8_t counter = 0;
	
	while (!fileInput.eof())
	{
		char byte;
		fileInput.read(reinterpret_cast<char*>(&byte), sizeof(byte));
	
		for (const char& bit : _huffmanCodeTable[byte])
		{
			writeBit(fileOutput, bool(bit - '0'), buf, counter);
		}
	}

	fileInput.close();
	fileOutput.close();
}

void HuffmanEncoder::buildHuffmanTree(const FrequencyCounter& freq)
{
	////////////////////////////////////////
	//		  | priority_queue | list     //
	// push	  | O(1) + O(logn) | O(1)	  //
	// sort	  |		  -	       | O(nlogn) //
	////////////////////////////////////////

	std::priority_queue<std::shared_ptr<HuffmanTreeNode>, std::vector<std::shared_ptr<HuffmanTreeNode>>, HuffmanTreeNodeCmp> huffmanTrees;

	for (const auto& [key, value] : freq)
	{
		huffmanTrees.push(std::make_shared<HuffmanTreeNode>(key, value));
	}

	while (huffmanTrees.size() > 1)
	{
		std::shared_ptr<HuffmanTreeNode> left = huffmanTrees.top();
		huffmanTrees.pop();
		std::shared_ptr<HuffmanTreeNode> right = huffmanTrees.top();
		huffmanTrees.pop();
		huffmanTrees.push(std::make_shared<HuffmanTreeNode>(std::move(left), std::move(right)));
	}
	_huffmanTree = huffmanTrees.top();
}

void HuffmanEncoder::buildHuffmanCodeTable()
{
	std::queue<std::shared_ptr<HuffmanTreeNode>> q;
	q.push(_huffmanTree);

	while (!q.empty())
	{
		std::shared_ptr<HuffmanTreeNode> root = q.front();
		q.pop();
		if (root->_left)
		{
			root->_left->_bitCode = root->_bitCode;
			root->_left->_bitCode.push_back('0');
			q.push(root->_left);
		}
		if (root->_right)
		{
			root->_right->_bitCode = root->_bitCode;
			root->_right->_bitCode.push_back('1');
			q.push(root->_right);
		}
		if (!root->_left && !root->_right)
		{
			_huffmanCodeTable[root->_data] = root->_bitCode;
		}
	}
}

void HuffmanEncoder::serializeTree(std::ofstream& ofs)
{
	std::stack<std::shared_ptr<HuffmanTreeNode>> s;
	std::shared_ptr<HuffmanTreeNode> currentNode = _huffmanTree;
	uint8_t buf = 0;
	uint8_t counter = 0;
	while (!s.empty() || currentNode)
	{
		while (currentNode)
		{
			if (!currentNode->_left && !currentNode->_right)
			{
				writeBit(ofs, (bool)1, buf, counter);
				std::bitset<CHAR_BIT> b(currentNode->_data);
				for (int i = CHAR_BIT - 1; i >= 0; --i)
				{
					writeBit(ofs, b[i], buf, counter);
				}
			}
			else
			{
				writeBit(ofs, (bool)0, buf, counter);
			}
			s.push(currentNode);
			currentNode = currentNode->_left;
		}

		currentNode = s.top();
		s.pop();
		currentNode = currentNode->_right;
	}

	if (buf)
	{
		ofs.write(reinterpret_cast<char*>(&buf), sizeof(buf));
	}
}

void HuffmanEncoder::writeBit(std::ofstream& ofs, const bool bit, uint8_t& buf, uint8_t& counter)
{
	buf |= bit << (CHAR_BIT - counter - 1);
	++counter;
	if (counter == CHAR_BIT)
	{
		counter = 0;
		ofs.write(reinterpret_cast<char*>(&buf), sizeof(buf));
		buf = 0;
	}
}