#include <bits/stdc++.h>
#include "bitfile.cpp"
#include "bitfile.h"
#define ll long long int
using namespace std;
map <int,string> table;
map <string,int> table2;

struct MinHeapNode
{
    char data;
    unsigned freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

struct compare
{
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};

void printCodes(struct MinHeapNode* root, string str)
{
    if (!root)
        return;

    if (root->left==NULL and root->right==NULL)
        {//cout << root->data <<" "<< int(root->data)<<" "<< ": " << str << "\n";
    	table.insert(pair<int,string>(int(root->data),str));
}

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void HuffmanCodes(char data[], ll freq[], int size )
{
    struct MinHeapNode *left, *right, *top;


    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    while (minHeap.size() != 1)
    {

        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();


        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }


    printCodes(minHeap.top(), "");
}

int main(int args,char ** argv)
{
   ifstream ifile;
   ofstream ofile;
   ifile.open(argv[1]);
   ll freq[256]={0};
    char c;
    while(ifile.get(c)) {
      freq[(unsigned int)c]++;;

    }

    ifile.close();
    char str[256];ll fre[256];
    int k=0;
    for (int i=0;i<256;i++)
    {
        if (freq[i]!=0)
          {
            str[k]=char(i);

            fre[k]=freq[i];

            k++;
            }
    }
    HuffmanCodes(str, fre, k);
    map<int,string>::iterator it;
    ofile.open("key.txt");
    for(it=table.begin();it!=table.end();it++)
    	{
    		ofile<<it->first<<" "<<it->second<<"\n";
		}
		ofile.close();
    string enCoded = "";

    ifile.open(argv[1]);
     while(ifile.get(c)) {
       enCoded+=table[int(c)];
    }
    ifile.close();
     bit_file_c bf;
     bf.Open("compressed", BF_WRITE);
     int i=0;
    while(i<enCoded.size())
    {
    	bf.PutBit(int(enCoded[i]-48));
    	i++;

    }
 	bf.Close();
 	 cout<<"\nFile is Compressed...\n";
 	return 0;
}
