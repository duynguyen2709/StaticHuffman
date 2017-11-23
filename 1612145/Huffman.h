#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <exception>
#include <utility>
using namespace std;

class ArgumentException :public exception
{
private:
	string message;
public:
	ArgumentException()
	{
		message = "Error in argument !";
	}

	const string Message() const throw() { return message; }
	void Message(string val) { message = val; }

};

struct Node
{
	unsigned char data;			 
	unsigned int freq;			 
	Node *left, *right; 

	Node(unsigned char data, unsigned int freq)
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

struct compare
{
	bool operator()(Node* l, Node* r)
	{
		return (l->freq > r->freq);
	}
};

namespace Compress{

	void printCodes(Node* root, string str, vector<pair<char, string>> &code);

	Node* HuffmanCompress(vector<char> letter, vector<int> freq, vector<pair<char, string>> &code);

	string HuffmanOut(vector<char> inputString, vector<pair<char, string>> code);

	void writeCompressFile(string str, char *output);

	void saveHuffmanTree(Node *root);
	
	void ReadInputFile(unsigned f[256], vector<char>& inputString, vector<char>& letter,vector<int>& freq);
}


namespace Uncompress
{
	void restoreHuffmanTree(Node *&root, FILE *f);
}