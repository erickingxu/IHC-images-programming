#include "stdafx.h"
#include "Csmoothorsharp.h"

Csmoothorsharp::Csmoothorsharp( int b){

	
	
	    //img=a;无法完成图像参数的传递？？？？？？？？？？？？？？？？？？？？？？？
    PType=b;

	int aarr[9]={1,2,1,2,4,2,1,2,1};// 高斯模板
	int barr[9] = {-1,-1,-1,-1,9,-1,-1,-1,-1}; // 拉普拉斯模板
	memcpy(smoothArr,aarr,9*sizeof(int));
	memcpy(sharpArr,barr,9*sizeof(int));
		
	if (PType>1)
	{
		AfxMessageBox(_T("Please make sure ptype is:0 or 1!Now,we default it to be 0!"));
		PType=0;
	}
	switch (PType)
	{
	case 0:
		cval=(float)(1.0/16.0);
		memcpy(tempArr,smoothArr,9*sizeof(int));
		break;
	case 1:
		cval=1.0;
		memcpy(tempArr,smoothArr,9*sizeof(int));
		break;

	}
    
	
}

void Csmoothorsharp::FilterImg(int* temp,CImage imga){
	
	int nW=imga.GetWidth()-1;
	int nH=imga.GetHeight()-1;


	byte *pRealData;
	pRealData=(byte*)imga.GetBits();
	int pit=imga.GetPitch();
	int bitCount=imga.GetBPP()/8;

	for (int i=1;i<nH;i++)
	{
		for (int j=1;j<nW;j++)
		{
			int Rval=0,Gval=0,Bval=0,indx=0;
			for ( int row=-1;row<=1;row++)
			{
				for (int col=-1;col<=1;col++)
				{
					 Bval+=((int)(int)(*(pRealData+pit*(i+row)+(j+col)*bitCount))) *temp[indx];
					 Gval=((int)(int)(*(pRealData+pit*(i+row)+(j+col)*bitCount+1)))*temp[indx];
					 Rval=((int)(int)(*(pRealData+pit*(i+row)+(j+col)*bitCount+2)))*temp[indx];
					 indx++;
				}
			}
//template work is over,You need get the center point pixel.
			Rval=(int)(Rval*cval);
			if (Rval>255)
				Rval=255;
			else if(Rval<0)
				Rval=0;

			Gval=(int)(Gval*cval);
			if (Gval>255)
				Gval=255;
			else if(Gval<0)
				Gval=0;

			Bval=(int)(Bval*cval);
			if (Bval>255)
				Bval=255;
			else if (Bval<0)
				Bval=0;

//ok,write the new pixel into the pic.
			*(pRealData+pit*(i-1)+(j-1)*bitCount)=Bval;
			*(pRealData+pit*(i-1)+(j-1)*bitCount+1)=Gval;
			*(pRealData+pit*(i-1)+(j-1)*bitCount+2)=Rval;
		}
	}




//CALL the OnDraw in MFC
	
}
// 
// byte* Csmoothorsharp::GetRealDataAddress(CImage pImage)
// {
// 	byte *Addr=NULL;
// 	if(!pImage.IsNull())
// 	{
// 		if(pImage.GetPitch()<0)
// 		{
// 			//方法1
// 			Addr=(byte *)pImage.GetBits()+pImage.GetPitch()*(pImage.GetHeight()-1);
// 			//方法2
// 			//FirstAdd=(byte *)pImage.GetPixelAddress(0,(pImage.GetHeight()-1));
// 		}
// 
// 		else
// 			Addr=(byte *)pImage.GetBits();
// 	}
// 
// 	return Addr;
// } 