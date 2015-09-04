// project4.cpp : Written By Dongyu Li  &  Ming Chen.
//

#include "stdafx.h"
#include"ImgCompressor.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cout<<"Enter the input file name"<<endl;
	string filename;
	cin>>filename;
	ImgCompressor image;
	image.inputFile(filename);
	image.countfreq();
	image.insertheap();
	image.build_tree();
	cout<<"Enter the output file name"<<endl;
	cin>>filename;
	image.outputFile(filename);
	return 0;
}

