#include "HuffmanDecoder.h"
#include <fstream>
#include <stack>
#include <bitset>

void HuffmanDecoder::decode(const std::string& inputEncodeFile, const std::string& outputDecodeFile)
{
	std::ifstream fileInput(inputEncodeFile, std::ios::in | std::ios::binary);
	std::ofstream fileOutput(outputDecodeFile, std::ios::out | std::ios::binary);

	deserializeTreeAndBuildCodeTable(fileInput);

	std::string code = "";
	char byte;
	fileInput.read(reinterpret_cast<char*>(&byte), sizeof(byte));
	uint8_t counter = 0;

	while (!fileInput.eof())
	{
		bool bit = readBit(fileInput, byte, counter);

		code.push_back(char(bit + '0'));
		if (_huffmanCodeTable.find(code) != _huffmanCodeTable.end())
		{
			fileOutput.write(reinterpret_cast<char*>(&_huffmanCodeTable[code]), sizeof(_huffmanCodeTable[code]));
			code = "";
		}
	}
	
	fileInput.close();
	fileOutput.close();
}

void HuffmanDecoder::deserializeTreeAndBuildCodeTable(std::ifstream& ifs)
{
	std::stack<std::shared_ptr<HuffmanTreeNode>> s;
	_huffmanTree = std::make_shared<HuffmanTreeNode>();
	s.push(_huffmanTree);

	char byte;
	ifs.read(reinterpret_cast<char*>(&byte), sizeof(byte));
	uint8_t counter = 0;

	while (!s.empty())
	{
		std::shared_ptr<HuffmanTreeNode> currentNode = s.top();
		s.pop();

		bool bit = readBit(ifs, byte, counter);
		if (bit)
		{
			for (int i = CHAR_BIT - 1; i >= 0; --i)
			{
				bit = readBit(ifs, byte, counter);
				currentNode->_data |= bit << i;
			}
			_huffmanCodeTable[currentNode->_bitCode] = currentNode->_data;
		}
		else
		{
			currentNode->_left = std::make_shared<HuffmanTreeNode>();
			currentNode->_left->_bitCode = currentNode->_bitCode;
			currentNode->_left->_bitCode.push_back('0');

			currentNode->_right = std::make_shared<HuffmanTreeNode>();
			currentNode->_right->_bitCode = currentNode->_bitCode;
			currentNode->_right->_bitCode.push_back('1');

			s.push(currentNode->_right);
			s.push(currentNode->_left);
		}
	}
}

bool HuffmanDecoder::readBit(std::ifstream& ifs, char& byte, uint8_t& counter)
{
	bool bit = byte & (1 << (CHAR_BIT - counter - 1));
	++counter;
	if (counter == CHAR_BIT)
	{
		counter = 0;
		ifs.read(reinterpret_cast<char*>(&byte), sizeof(byte));
	}
	return bit;
}