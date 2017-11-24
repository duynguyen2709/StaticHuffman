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
					val += '0';

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
			cout << "end ";
			return;
		}
		switch (root->data)
		{
		case '\n': cout << "\\n ";
			break;
		case '\r': cout << "\\r ";
			break;
		case '\t': cout << "\\t ";
			break;
		case '\0': cout << "\\0 ";
			break;
		case '$': cout << "node ";
			break;
		default:
			cout << root->data << " ";
			break;
		}
		
		saveHuffmanTree(root->left);
		saveHuffmanTree(root->right);
	}

	void ReadInputFile(unsigned f[256], vector<char>& inputString, vector<char>& letter, vector<int>& freq)
	{
		while (!cin.eof())
		{
			char x;
			cin.read(&x, 1);
			f[(int)(x+128)]++;
			inputString.push_back(x);
		}
		auto c = (char)inputString.back();
		f[(int)(c + 128)]--;
		inputString.pop_back();

		for (int i = 0; i < 256; i++)
		{
			if (f[i] > 0)
			{
				letter.push_back((char)(i-128));
				freq.push_back(f[i]);
			}
		}
	}
}

namespace Uncompress{

	void restoreHuffmanTree(Node *&root, FILE *f)
	{
		string val = "";
		char c = 0;
		if (cin.eof())
			return;

		cin >> val;
		
		if (val == "end" || cin.eof())
			return;

		if (val == "\\n")
			c = '\n';
		else if (val == "\\r")
			c = '\r';
		else if (val == "\\t")
			c = '\t';
		else if (val == "\\0")
			c = '\0';
		else if (val != "node")
			c = val[0];

		root = new Node(c, 0);
		restoreHuffmanTree(root->left, f);
		restoreHuffmanTree(root->right, f);
	}

	string restoreBitstring(FILE *f)
	{
		string bitString;
		char c = 0;
		while (!cin.eof())
		{
			cin >> c;
			bitset<8>binary(c);
			bitString += binary.to_string();
		}
		int dem = (int)(c - '0');
		bitString.resize(bitString.length() - 16 - dem);
		return bitString;

	}

	void restoreCompressedFile(string binaryString, Node *root)
	{
		/*int pos = 0;
		Node *temp = root;
		while (pos < binaryString.length())
		{			
			if (temp == NULL)
				return;
			if (binaryString[pos] == '0')
				temp = temp->left;
			else if (binaryString[pos] == '1')
			{
				temp = temp->right;
			}
			if (temp->data != '$')
			{
				cout << temp->data;
				temp = root;
			}
			pos++;
		}*/

		Node* curr = root;
		for (int i = 0; i < binaryString.size(); i++)
		{
			if (binaryString[i] == '0')
				curr = curr->left;
			else
				curr = curr->right;

			if (curr->left == NULL && curr->right == NULL)
			{				
				if (curr->data == '\n')
					cout << endl;
				else
					cout << curr->data;
				curr = root;
			}
		}

	}

}