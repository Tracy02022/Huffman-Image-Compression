//Written By Dongyu Li  &  Ming Chen
#pragma once 
#include"BinaryHeap.h"
#include"HuffmanNodePtr.h"
#include"Pixel.h"
#include <string>
#include <fstream>


class ImgCompressor
{
public:
	int width,height,maxVal;
	string PPMstyle;
	BinaryHeap<HuffmanNodePtr> huffmanHeap;
	vector<pair<int,string>> freqCodes;
	vector<Pixel> dataInorder;
	void skip_comments_spaces(ifstream &);
	void inputFile(string);
	HuffmanNodePtr  ptr;
	HuffmanNodePtr  ptr1;
	unsigned char rgb[3];
	vector<Pixel>::iterator iter;
	vector<pair<int,string>>::iterator itr;
	void countfreq();
	void insertheap();
	void build_tree();
	void outputFile(string);
	void assignCodes(HuffmanNode<unsigned char>*,string);
	
};
//copy from my teacher
void ImgCompressor::skip_comments_spaces(ifstream &file)
{
	string buffer;
	int ch=file.peek();

	while(ch=='#'||isspace(ch))
	{
		if(ch=='#')getline(file,buffer);
		else
		{
			while(isspace(ch))
			{
				file.get();
				ch=file.peek();
			}
		}
		ch=file.peek();
	}
}
//read in data in vector
void ImgCompressor::inputFile(string filename)
{
	ifstream file (filename.c_str(),std::ios::in|std::ios::binary);
	if(file.fail())
	{
		cout << "unable to open file" << endl;
		return;
	}
	file>>PPMstyle;// read "P6" 
	skip_comments_spaces(file);
	file>>width;     //read width
	skip_comments_spaces(file);
	file>>height;   //read height
	skip_comments_spaces(file);
	file>>maxVal;  //read maxVal

	file.get();
	for(int i=0;i<width*height;i++)	
    {
		rgb[0]=file.get();
	    rgb[1]=file.get();
	    rgb[2]=file.get();
	    Pixel pix(rgb[0],rgb[1],rgb[2]);
	    dataInorder.push_back(pix);
	}
}
//count the frequency		
void ImgCompressor::countfreq()
{
		for(iter=dataInorder.begin();iter!=dataInorder.end();++iter)
	{
		freqCodes.resize(256);
		//teached by teacher,Dr. Gothard
		(freqCodes.at((*iter).red)).first++;
		(freqCodes.at((*iter).green)).first++;
		(freqCodes.at((*iter).blue)).first++;
	}
}

//inseart data into the heap by their frequency
void ImgCompressor::insertheap()
{
	int i=0;
    for (itr=freqCodes.begin(); itr!=freqCodes.end(); itr++)
    {
		if(freqCodes.at(i).first!=0)
		{
		unsigned char un=(unsigned char)i;
		//For each unique channel,dynamically allocate a Huffman node object
		HuffmanNode<unsigned char>* n= new HuffmanNode<unsigned char>(un);
	    HuffmanNodePtr p;
		p.pointer=n;
		p.pointer->freqCount=freqCodes.at(i).first;
		//Insert a Huffman node pointer object into the heap
		huffmanHeap.insert(p);
		}
		i++;
	
    }

}
//Huffman codes algorithm 
void ImgCompressor::build_tree()
{
	while (huffmanHeap.size>2)
	{   
		ptr=huffmanHeap.deleteMin();
		ptr1=huffmanHeap.deleteMin();
		HuffmanNodePtr p;
		HuffmanNode<unsigned char>* node= new HuffmanNode<unsigned char>;
		node->left=ptr.pointer;
		node->right=ptr1.pointer;
		node->freqCount=ptr.pointer->freqCount+ptr1.pointer->freqCount; 
		p.pointer=node;
        huffmanHeap.insert(p);
	 }
}
//output file in "UDCPS 3" format
void ImgCompressor::outputFile(string outfileName)
{
	int uniquechannel =0;
	assignCodes(huffmanHeap.h[1].pointer,"");
 
	ofstream output(outfileName.c_str(),
		std::ios::out|std::ios::binary|std::ios::app);
	if(output.fail())
	{
		cout << "unable to open file" << endl;
		return;
	}
	
	int j=0;
	for (itr=freqCodes.begin(); itr!=freqCodes.end(); itr++)
	{
		if(freqCodes.at(j).first!=0)
		// get the number of unique colors
		uniquechannel++;
		j++;
	}
	int i=0;
	output<< "UDCPS" << " " <<  "3"  <<endl;
	output<<width<< " " << height <<endl;
	output<<uniquechannel << endl;	
	for (itr=freqCodes.begin(); itr!=freqCodes.end(); itr++)
	{
		if(freqCodes.at(i).first!=0)
			output<<freqCodes.at(i).second<<" "<<i<<endl;
		i++;
	}
	
	for(iter=dataInorder.begin(); iter!=dataInorder.end(); iter++)
	{
		if(freqCodes.at((*iter).red).first!=0)
		output<<freqCodes.at((*iter).red).second;
		if(freqCodes.at((*iter).green).first!=0)
		output<<freqCodes.at((*iter).green).second;
		if(freqCodes.at((*iter).blue).first!=0)
		output<<freqCodes.at((*iter).blue).second;
		
    }

 }
//assign huffman codes to channel values
void  ImgCompressor::assignCodes(HuffmanNode<unsigned char>* node, string code)
{  
	if(node)
	{   
		if(node->left==NULL &&node->right ==NULL)
		{
			freqCodes.at((int)(*node).data).second=code;
		}
		else
		{
			assignCodes(node->left,code+"0");
            assignCodes(node->right,code+"1");	
		}
	}
}

