#include "Huffman.h"
#include <wtypes.h>

void printCodes(Node* root, string str, vector<pair<char, string>> &code)
{
	if (!root)
		return;

	if (root->data != '$')
	{
		cout << root->data << ": " << str << "\n";
		char x = root->data;
		string temp = str;
		code.push_back(make_pair(x, temp));
	}

	printCodes(root->left, str + "0",code);
	printCodes(root->right, str + "1",code);
}


void HuffmanCompress(vector<char> letter, vector<int> freq, vector<pair<char, string>> &code)
{
	Node *left, *right, *top;

	priority_queue<Node*, vector<Node*>, compare> minHeap;
	for (int i = 0; i < letter.size(); i++)
		minHeap.push(new Node(letter[i], freq[i]));

	while (minHeap.size() != 1)
	{

		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();

		top = new Node('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		minHeap.push(top);
	}

	
	printCodes(minHeap.top(), "",code);
	cout << endl;
}

string HuffmanOut(vector<char> inputString, vector<pair<char, string>> code)
{
	string output;
	for (char c : inputString)
	{
		for (auto pair : code)
		{
			if (c == pair.first)
			{
				output += pair.second;
			}
		}
	}
	return output;
}
void writeHuffmanFile(string str,char *output)
{
	freopen(output, "wb", stdout);
	int k = 0;
	int i = 0;
	vector<string> arr;
	string temp;

	while (k < str.length())
	{
		if (i == 8 || k == str.length() - 1)
		{
			arr.push_back(temp);
			temp = "";
			i = 0;
			k++;
		}
		else {
			temp += str[k++];
			i++;
		}
	}
	for (string val : arr)
	{
		if (val.length() != 8)
		{
			int left = 8 - val.length();
			for (int j = 0; j < left; j++)
				val = '0' + val;

		}
		BYTE x = static_cast<BYTE>(std::stoi(val, 0, 2));
		cout << x;
	}
	
}