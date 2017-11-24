#include <iostream>
#include "Huffman.h"
#include <vector>
#include <wtypes.h>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

int main(int argc, char *argv[])
{
	ArgumentException ex;
	try
	{
		if (argc < 4 || argc > 5)
		{
			throw ex;
		}

		if (strcmp(argv[1], "compress") == 0)
		{
		/*	if (argc != 4)
			{
				throw ex;
			}*/
			vector<char> letter;
			vector<char> inputString;
			vector<int> freq;
			vector<pair<char, string>> code;

			unsigned int f[256];
			memset(f, 0, sizeof(f));
			freopen(argv[2], "rb", stdin);


			Compress::ReadInputFile(f, inputString, letter, freq);	//read source file 

			Node * root = Compress::HuffmanCompress(letter, freq, code);	//build Huffman tree

			//string outputString = Compress::HuffmanOut(inputString, code);	//convert source file to binary

			Compress::writeCompressFile(Compress::HuffmanOut(inputString, code), argv[2]);	//Write compressed letter to source file
			
			freopen(argv[3], "wt", stdout);
			Compress::saveHuffmanTree(root);	//Save Huffman Tree for decompress
		}


		else if (strcmp(argv[1], "uncompress") == 0)
		{

			if (argc != 5)
			{
				throw ex;
			}

			auto hufFile = freopen(argv[3], "rt", stdin);
			Node *root = NULL;
			Uncompress::restoreHuffmanTree(root, hufFile);
			_fcloseall();
			cin.clear();

			auto compressedFile = freopen(argv[2], "rb", stdin);
			string bitString = Uncompress::restoreBitstring(compressedFile);

			auto outFile = freopen(argv[4], "wb", stdout);
			Uncompress::restoreCompressedFile(bitString, root);
		}
		else throw ex;
	}

	catch (ArgumentException& e)
	{
		cout << e.Message() << endl;
	}

	return 0;
}
