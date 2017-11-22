// C++ program for Huffman Coding
#include <iostream>
#include "Huffman.h"
#include <vector>
using namespace std;


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
			vector<char> letter;
			vector<char> inputString;
			vector<int> freq;
			vector<pair<char, string>> code;

			unsigned int f[256];
			memset(f, 0, sizeof(f));
			freopen(argv[2], "rb", stdin);

			//read byte by byte from file
			while (!cin.eof())
			{
				char x;
				cin.read(&x, 1);
				f[x]++;
				inputString.push_back(x);
			}

			for (int i = 0; i < 256; i++)
			{
				if (f[i]>0)
				{
					letter.push_back((char)i);
					freq.push_back(f[i]);
				}
			}
			
			HuffmanCompress(letter, freq,code);

			string outputString = HuffmanOut(inputString, code);
			writeHuffmanFile(outputString, argv[3]);
		}
		else if (strcmp(argv[1], "uncompress") == 0)
		{
		}
		else throw ex;
	}

	catch(ArgumentException& e)
	{
		cout << e.Message() << endl;
	}

	return 0;
}
