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

string read(ifstream &inf){
	string temp;
	string temp2 = "";

	while (!inf.eof()){
		getline(inf, temp);
		temp2 += temp + "\n";
	}
	return temp2;
}

void outputencodingfile(ofstream & outf, int stringlength, string SampleString, HuffCodeMap codes)
{

	outf << "asdlkjfsadoutput\n\n";
	for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it)
	{
		outf << it->first << " ";
		copy(it->second.begin(), it->second.end(),
			ostream_iterator<bool>(outf));
		outf << endl;
	}
	outf << endl;
	for (int i = 0; i < stringlength; i++)
	{
		for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it)
		{
			if (SampleString[i] == it->first)
			{
				int number = 0;

				string tempor = string(it->second.begin(), it->second.end());
				outf << tempor;
			}
		}
	}
}

int main()
{
	// Build frequency table
	int frequencies[UniqueSymbols] = { 0 };
	ifstream inf;
	//Getting userinput
	//-------------------------------------

	//reading in file and Compressing it.(Has map)
	cout << "Type in the file location\n";
	string inputfile;
	cin >> inputfile;
	inf.open(inputfile);
	cout << endl << "Type in the file output location" << endl;
	string outputfile;
	cin >> outputfile;
	ofstream outf;
	outputfile += "compression.crazzzyy";
	outf.open(outputfile);
	//-------------------------------------

	string temper = read(inf);
	const char* SampleString = &temper[0u];
	const char* ptr = SampleString;
	while (*ptr != '\0')
		++frequencies[*ptr++];

	INode* root = BuildTree(frequencies);

	HuffCodeMap codes;
	GenerateCodes(root, HuffCode(), codes);
	delete root;

	int stringlength = 0;
	stringlength = temper.length();

	outputencodingfile(outf, stringlength, SampleString, codes);

	system("Pause");
	return 0;
}