#include <iostream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

const int UniqueSymbols = 1 << CHAR_BIT;
typedef vector<bool> HuffCode;
typedef map<char, HuffCode> HuffCodeMap;

class INode
{
public:
	const int f;

	virtual ~INode() {}

protected:
	INode(int f) : f(f) {}
};

class InternalNode : public INode
{
public:
	INode *const left;
	INode *const right;

	InternalNode(INode* c0, INode* c1) : INode(c0->f + c1->f), left(c0), right(c1) {}
	~InternalNode()
	{
		delete left;
		delete right;
	}
};

class LeafNode : public INode
{
public:
	const char c;

	LeafNode(int f, char c) : INode(f), c(c) {}
};

struct NodeCmp
{
	bool operator()(const INode* lhs, const INode* rhs) const { return lhs->f > rhs->f; }
};

INode* BuildTree(const int(&frequencies)[UniqueSymbols])
{
	priority_queue<INode*, vector<INode*>, NodeCmp> trees;

	for (int i = 0; i < UniqueSymbols; ++i)
	{
		if (frequencies[i] != 0)
			trees.push(new LeafNode(frequencies[i], (char)i));
	}
	while (trees.size() > 1)
	{
		INode* childR = trees.top();
		trees.pop();

		INode* childL = trees.top();
		trees.pop();

		INode* parent = new InternalNode(childR, childL);
		trees.push(parent);
	}
	return trees.top();
}

void GenerateCodes(const INode* node, const HuffCode& prefix, HuffCodeMap& outCodes)
{
	if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
	{
		outCodes[lf->c] = prefix;
	}
	else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
	{
		HuffCode leftPrefix = prefix;
		leftPrefix.push_back(false);
		GenerateCodes(in->left, leftPrefix, outCodes);

		HuffCode rightPrefix = prefix;
		rightPrefix.push_back(true);
		GenerateCodes(in->right, rightPrefix, outCodes);
	}
}

string read(ifstream &inf) {
	string temp;
	string temp2 = "";

	while (!inf.eof()) {
		getline(inf, temp);
		temp2 += temp + "\n";
	}
	return temp2;
}

void outputencodingfile(ofstream & outf, string inputfile, int stringlength, string SampleString, HuffCodeMap codes)
{

	outf << "asdlkjfsadoutput\n" + inputfile + "\n";
	for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it)
	{
		outf << it->first;
		copy(it->second.begin(), it->second.end(),
			ostream_iterator<bool>(outf));
		outf << endl;
	}
	outf << "|" << endl;
	for (int i = 0; i < stringlength; i++)
	{
		for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it)
		{
			if (SampleString[i] == it->first)
			{
				stringstream buffer;
				copy(it->second.begin(), it->second.end(),
					ostream_iterator<bool>(buffer));
				string encoded = buffer.str();
				outf << encoded;

				int counter = 0;
				string bitss = "";
				char ascii;
				for (int k = 0; k < encoded.length(); k++)
				{
					if (counter != 8)
					{
						bitss += encoded[k];
						counter++;
					}
				}
			}
		}
	}
}

int mainV()
{
	// Build frequency table
	int frequencies[UniqueSymbols] = { 0 };
	ifstream inf;
	string inputfile;
	//Getting userinput
	//-------------------------------------
	char check;
	cout << "Do you want to compress?\n";
	cin >> check;
	if (check == 'Y' || 'y')
	{
		//reading in file and Compressing it.(Has map)
		cout << "Type in the file location\n";
		cin >> inputfile;
		inf.open(inputfile);
		cout << endl << "Type in the file output location" << endl;
		string outputfile;
		cin >> outputfile;
		ofstream outf;
		outputfile += "compression.crazy";
		outf.open(outputfile);
		//-------------------------------------

		string temper = read(inf);
		const char* SampleString = &temper[0u];
		const char* ptr = SampleString;
		while (*ptr != '\0')
			++frequencies[*ptr++];
		inf.close();
		INode* root = BuildTree(frequencies);

		HuffCodeMap codes;
		GenerateCodes(root, HuffCode(), codes);
		delete root;

		int stringlength = 0;
		stringlength = temper.length();
		outputencodingfile(outf, inputfile, stringlength, SampleString, codes);
		outf.close();
	}
	else
	{
		cout << "Please type in the file location to decompress:\n";
		cin >> inputfile;
		inf.open(inputfile + "compression.crazy");
		string decompress = "";
		string security = "";
		inf >> security;
		if (security != "asdlkjfsadoutput")
		{
			cout << "NOPE we are not decompressing this for you. GO away!";
			system("Pause");
			return 0;
		}
		else
		{
			inf.ignore(numeric_limits<streamsize>::max(), '\n');
			inf.ignore(numeric_limits<streamsize>::max(), '\n');
			vector<string> decode;
			int i = 0;
			string input = "";
			string compressedinformation = "";
			while (!inf.eof())
			{

				inf >> input;
				if (input == "|")
					break;
				else {
					decode.push_back(input);
					//cout << decode[i][0]<<endl;
					i++;
				}
			}
			while (!inf.eof())
			{
				inf >> input;
				compressedinformation += input;
				//cout << compressedinformation;
			}

			for (int j = 2; j < decode.size(); j++)
			{
				int lengthofdecode = decode[j].length();
				string binary = "";
				for (int k = 0; k < lengthofdecode; k++)
				{
					if (k != 0)
					{
						binary += decode[j][k];
					}
				}

			}

			int lengthof = compressedinformation.length();
			string checker = "";
			for (int i = 0; i <= lengthof; i++)
			{
				if (compressedinformation[i] == 1)
					checker += "1";
				else
					checker += "0";

				for (int j = 2; j < decode.size(); j++)
				{
					int lengthofdecode = decode[j].length();
					string binary = "";
					for (int k = 0; k < lengthofdecode; k++)
					{
						if (k != 0)
						{
							binary += decode[j][k];
						}
					}
					if (checker == binary)
					{
						cout << decode[j][0] << endl;
						cout << checker;
						checker = "";
					}
				}
			}
		}
		inf.close();
	}

	system("Pause");
	return 0;
}