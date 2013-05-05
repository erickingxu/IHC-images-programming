#include <stdio.h>
#include <iostream>
#include <math.h>
#include "stdafx.h"

class Csmoothorsharp{
public:
	//CImage img;
	int PType;
	Csmoothorsharp(int b);
	~Csmoothorsharp();
	void FilterImg(int temp[9],CImage imga);
	//byte* GetRealDataAddress(CImage pImage);
public:
	
	int smoothArr[9]; 
	int sharpArr[9];
	int tempArr[9];
	float cval;
	
};