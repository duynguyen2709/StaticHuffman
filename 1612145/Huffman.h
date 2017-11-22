#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <exception>
#include <utility>
using namespace std;

struct Node
{
	unsigned char data;			 // One of the input characters
	unsigned int freq;			 // Frequency of the character
	Node *left, *right; // Left and right child

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

void printCodes(Node* root, string str, vector<pair<char, string>> &code);

void HuffmanCompress(vector<char> letter, vector<int> freq, vector<pair<char, string>> &code);


string HuffmanOut(vector<char> inputString, vector<pair<char, string>> code);

void writeHuffmanFile(string str, char *output);

class ArgumentException :public exception
{
private:
	string message;
public:
	ArgumentException()
	{
		message	="Error in argument !";
	}
	
	const string Message() const throw() { return message; }
	void Message(string val) { message = val; }

};