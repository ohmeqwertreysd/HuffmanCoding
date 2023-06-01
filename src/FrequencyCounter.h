#pragma once

#include <string>
#include <unordered_map>

class FrequencyCounter
{
public:
	const std::unordered_map<char, uint32_t>& getFrequency();
	void readFile(const std::string& fileName);
	void clear();
	std::unordered_map<char, uint32_t>::const_iterator begin() const;
	std::unordered_map<char, uint32_t>::const_iterator end() const;
private:
	std::unordered_map<char, uint32_t> _freq;
};