//Written By Dongyu Li 
#pragma once
//the nodes are used to compute the Huffman code for each channel value
template <class T>
class HuffmanNode
{

public:
	T data;
	HuffmanNode<T> *left;
	HuffmanNode<T> *right;
	int freqCount;

	HuffmanNode(T & t)
	{
		data=t;
		left=NULL; 
		right=NULL;
		freqCount=0;
	}
	HuffmanNode():data()
	{
		freqCount=0;
	}

	~HuffmanNode(void);
};

