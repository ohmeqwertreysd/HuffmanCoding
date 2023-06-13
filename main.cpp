#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"


int main(int argc, char* argv[])
{
	{
		HuffmanEncoder encoder;
		encoder.encode("test.txt", "test.hff");
		
		HuffmanDecoder decoder;
		decoder.decode("test.hff", "decode.txt");
	}

	return 0;
}
