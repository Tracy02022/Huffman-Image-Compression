//Written By Dongyu Li  &  Ming Chen
#pragma once 
#include<vector>
#include<iostream>
using namespace std;
template<class T>
class BinaryHeap
{
public:
	vector<T> h;
	BinaryHeap()
	{
		h.push_back(T());
		size=1;
	}
	BinaryHeap(const T &err)
	{
		 h.push_back(err);
	     size=1;
	}
	void insert(T &);
	bool isEmpty() const;
	T deleteMin();
	int size;
	void kill(int);
private:
    void percolateDown (int);
	void percolateUp (int);
};
template<class T>
// teached by teacher in class
void BinaryHeap<T>::percolateUp(int emptySpot)
{
	for(;emptySpot>1;)
	{
		int parent=emptySpot/2;
		if(h[emptySpot]<h[parent])
		{
			T temp(h[emptySpot]);
			h[emptySpot]=h[parent];
			h[parent]=temp;
			emptySpot=parent;
		}
		else
			break;
	}
}

template<class T>
bool BinaryHeap<T>::isEmpty() const
{
	return size==0;
}
// insert data by compare their values correctly 
template<class T>
void BinaryHeap<T>::insert(T & t)
{
	int i=h.size()-1;
	if(i<size)
		h.push_back(t);
	else
		h[size]=t;
	size++;
	percolateUp(size-1);
}
// delete the data that has the lowest number of occurrences
template<class T>
T BinaryHeap<T>::deleteMin()
{
	if(size>1)
	{
		T item=h[1];
		kill(1);
		return item;
	}
	return h[0];
}
// after delete the data,find the appropriate data to fill in 
template<class T>
void BinaryHeap<T>::percolateDown(int emptySpot)
{
	if(emptySpot<1||emptySpot>=size)
		return;
	for(;;)
	{
		int leftchild=emptySpot*2;
		int rightchild=leftchild+1;
		int small;
		if(leftchild>=size)
			break;
		if(rightchild>=size)
			small=leftchild;
		else
		{
			if(h[leftchild]<h[rightchild])
				small=leftchild;
			else
				small=rightchild;
		}
		if(h[small]<h[emptySpot])
		{
			T temp(h[emptySpot]);
			h[emptySpot]=h[small];
			h[small]=temp;
			emptySpot=small;
		}
		else
			break;	
	}
}
// update the heap appropriately
template<class T>
void BinaryHeap<T>::kill(int i)
{
	if(i>=1&&i<size)
	{
		h[i]=h[size-1];
		percolateDown(i);
		size--;
		h.resize(size);
	}
}












