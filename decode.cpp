#include <bits/stdc++.h>
#include "bitfile.cpp"
#include "bitfile.h"
#define ll long long int
using namespace std;
map <string,int> table2;
struct MinHeapNode
{
    int data;
    MinHeapNode *left, *right;

    MinHeapNode(int data)
    {
        left = right = NULL;
        this->data = data;
    }
};

void BuildTree(string temp,struct MinHeapNode *root,int data)
{
    for(int i=0;i<temp.size();i++)
            {
                if(temp[i]=='0')
                    {
                        if(root->left==NULL)
                        root->left=new MinHeapNode(0);
                        root=root->left;
                    }
                    else
                        {
                        if(root->right==NULL)
                        root->right=new MinHeapNode(0);
                        root=root->right;
                    }
                  root->data=data;
            }
}
int main()
{
   ifstream ifile;
   ofstream ofile;
    map<string,int>::iterator it;
     bit_file_c bf;
 	ifile.open("key.txt");
 	int t;string s;
 	while(ifile>>t)
 	{
 		ifile>>s;
 		table2.insert(pair<string,int>(s,t));
 	}
 	ifile.close();
    struct MinHeapNode *root=new MinHeapNode(0);
    for(it=table2.begin();it!=table2.end();it++)
    	{
            BuildTree(it->first,root,it->second);
        }

    ofile.open("uncompressed.txt");
 	 bf.Open("compressed", BF_READ);
    struct MinHeapNode*head=root;
 	int tb;
 	 while((tb=bf.GetBit())!=EOF)
 	 {
 	 	char temp=char(tb+48);
 	 	if(temp=='0')
                    {
                        root=root->left;
                    }
        else if(temp=='1')
                        {
                        root=root->right;
                    }
        if(root->left==NULL and root->right==NULL)
 	 	{
 	 		ofile.put(char(root->data));
 	 		root=head;
 	 	}
 	 }
 	 bf.Close();
 	  ofile.close();
 	  cout<<"\nFile Uncompressed....\n";
    return 0;

}

