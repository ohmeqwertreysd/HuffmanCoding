#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"
#include <iostream>
#include <unordered_map>
#include <list>
#include <stack>
#include <queue>
#include <memory>
#include <iostream>



int main()
{
	{
		HuffmanEncoder encoder;
		encoder.encode("test.txt", "test.hff");
		
		HuffmanDecoder decoder;
		decoder.decode("test.hff", "decode.txt");
	}

	return 0;
}
