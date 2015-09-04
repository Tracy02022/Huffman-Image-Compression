//Written By Dongyu Li 
#pragma once 
#include "HuffmanNode.h"
//holds a pointer to a Huffman node 
class HuffmanNodePtr
{	
public:	
	//store each unique channel data
	HuffmanNode<unsigned char> * pointer;
	
	HuffmanNodePtr()
	{
	}
	bool operator < (HuffmanNodePtr &);
             
};
// overloads operator< to allow comparisons Huffman nodes' occurrences counts
bool HuffmanNodePtr::operator< (HuffmanNodePtr & p)
{
	if(this->pointer->freqCount<p.pointer->freqCount)
		return true;
	else
		return false;
}
