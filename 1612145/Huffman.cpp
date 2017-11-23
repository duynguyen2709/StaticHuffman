#include "Huffman.h"
#include <wtypes.h>

namespace Compress{

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

		printCodes(root->left, str + "0", code);
		printCodes(root->right, str + "1", code);
	}

	Node* HuffmanCompress(vector<char> letter, vector<int> freq, vector<pair<char, string>> &code)
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


		printCodes(minHeap.top(), "", code);
		cout << endl;

		return top;
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

	void writeCompressFile(string str, char *output)
	{
		freopen(output, "wb", stdout);
		int k = 0;
		int i = 0;
		vector<string> arr;
		string temp;

		while (k <= str.length())
		{
			temp += str[k];
			i++;
			if (i == 8 || k == str.length() - 1)
			{
				arr.push_back(temp);
				temp = "";
				i = 0;
			}
			k++;
		}
		int left = 0;
		for (string val : arr)
		{
			if (val.length() != 8)
			{
				left = 8 - val.length();
				for (int j = 0; j < left; j++)
					val = '0' + val;

			}
			BYTE x = static_cast<BYTE>(std::stoi(val, 0, 2));
			cout << x;

		}
		cout << left;

	}

	void saveHuffmanTree(Node* root)
	{
		if (root == NULL)
		{
			cout << "# ";
			return;
		}
		cout << root->data << " ";
		saveHuffmanTree(root->left);
		saveHuffmanTree(root->right);
	}

	void ReadInputFile(unsigned f[256], vector<char>& inputString, vector<char>& letter, vector<int>& freq)
	{
		//read byte by byte from file
		while (!cin.eof())
		{
			char x;
			cin.read(&x, 1);
			f[x]++;
			inputString.push_back(x);
		}
		auto c = (char)inputString.back();
		f[c]--;
		inputString.pop_back();
		for (int i = 0; i < 256; i++)
		{
			if (f[i] > 0)
			{
				letter.push_back((char)i);
				freq.push_back(f[i]);
			}
		}
	}
}
namespace Uncompress{

	void restoreHuffmanTree(Node *&root,FILE *f)
	{
		char val = 0;

		if (!fscanf(f, "%c ", &val) || val == '#')
			return;

		// Else create node with this item and recur for children
		root = new Node(val,0);
		restoreHuffmanTree(root->left, f);
		restoreHuffmanTree(root->right, f);
		
	}
}