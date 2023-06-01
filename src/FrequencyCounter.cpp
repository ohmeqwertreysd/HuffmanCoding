#include "FrequencyCounter.h"
#include <fstream>

const std::unordered_map<char, uint32_t>& FrequencyCounter::getFrequency()
{
	return _freq;
}

void FrequencyCounter::readFile(const std::string& fileName)
{
	std::ifstream file(fileName, std::ios::in | std::ios::binary);

	while (!file.eof())
	{
		char byte;
		file.read(reinterpret_cast<char*>(&byte), sizeof(byte));
		++_freq[byte];
	}

	file.close();
}

void FrequencyCounter::clear()
{
	_freq.clear();
}

std::unordered_map<char, uint32_t>::const_iterator FrequencyCounter::begin() const
{
	return _freq.cbegin();
}

std::unordered_map<char, uint32_t>::const_iterator FrequencyCounter::end() const
{
	return _freq.cend();
}