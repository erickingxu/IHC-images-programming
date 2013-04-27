// voronoiView.cpp : CvoronoiView 类的实现
//

#include "stdafx.h"
#include "voronoi.h"

#include "voronoiDoc.h"
#include "voronoiView.h"
#include <iostream>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// CvoronoiView

IMPLEMENT_DYNCREATE(CvoronoiView, CView)

BEGIN_MESSAGE_MAP(CvoronoiView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    
	//view中要响应的函数
	//ON_COMMAND(ID_FILE_OPEN ,CvoronoiView::OnFileOpen )
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_Voronoi_Creatin,CvoronoiView::OnVoronoiCreatin)
	ON_COMMAND(ID_Voronoi_Clear,CvoronoiView::OnVoronoiClear)

END_MESSAGE_MAP()

// CvoronoiView 构造/析构

CvoronoiView::CvoronoiView()
{
	// TODO: 在此处添加构造代码
	nver=0;
	ntri=0;
	nedge=0;
	

}

CvoronoiView::~CvoronoiView()
{
}

BOOL CvoronoiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

////打开文件
//void CvoronoiView::OnFileOpen(){
//	MessageBox("Openfile is ok!");
//	//CString strFilter;
//	//CSimpleArray<GUID> aguidFileTypes;
//	//HRESULT hResult;
//
//	////获取CImage支持的图像文件 的 过滤字符串
//	//hResult=m_image->getex
//}
//


// CvoronoiView 绘制

void CvoronoiView::OnDraw(CDC* pDC)
{
	CvoronoiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
    if (!pDoc->img.IsNull())
    {
		pDoc->img.Draw(pDC->m_hDC,0,0);
    }

	// TODO: 在此处为本机数据添加绘制代码
	int i,j;
	CPen *oldpen;
	CPen *newpen2=new CPen;
	newpen2->CreatePen(PS_DASH,1,RGB(255,0,0));
	CPen *newpen=new CPen;
	newpen->CreatePen(PS_SOLID,2,RGB(255,255,255));
	oldpen=pDC->SelectObject(newpen2);
	for(i=0;i<nedge;i++)
	{
		pDC->MoveTo(edge[0][i].x,edge[0][i].y);//连接分割线
		pDC->LineTo(edge[1][i].x,edge[1][i].y);
	}
	i=0;
	for(i=0;i<ntri;i++)
	{
		if (Triangle[i].vv0 >=nver|| Triangle[i].vv1>= nver|| Triangle[i].vv2 >= nver) //将super三角形去掉
		{
			Triangle[i].vv0 = Triangle[ntri-1].vv0;
			Triangle[i].vv1 = Triangle[ntri-1].vv1;
			Triangle[i].vv2 = Triangle[ntri-1].vv2;
			i = i - 1;
			ntri = ntri - 1;
		}
	}
	i=0;
	newpen2=pDC->SelectObject(newpen2);
	for(i=0;i<nver;i++)
	{
		pDC->Ellipse(Vertex[i].x,Vertex[i].y,Vertex[i].x+5,Vertex[i].y+5);
	}

	//Draw Delaunay triangulation
	i=0;
	newpen2=pDC->SelectObject(newpen);
	for(i=0;i<ntri;i++)
	{
		pDC->MoveTo(Vertex[Triangle[i].vv0].x,Vertex[Triangle[i].vv0].y);//连接所有输入点组成的三角形
		pDC->LineTo(Vertex[Triangle[i].vv1].x,Vertex[Triangle[i].vv1].y);
		pDC->MoveTo(Vertex[Triangle[i].vv0].x,Vertex[Triangle[i].vv0].y);
		pDC->LineTo(Vertex[Triangle[i].vv2].x,Vertex[Triangle[i].vv2].y);
		pDC->MoveTo(Vertex[Triangle[i].vv1].x,Vertex[Triangle[i].vv1].y);
		pDC->LineTo(Vertex[Triangle[i].vv2].x,Vertex[Triangle[i].vv2].y);
	}

	pDC->SelectObject(oldpen);
}


void CvoronoiView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	Vertex[nver].x=point.x;
	Vertex[nver].y=point.y;
	nver++;
	CClientDC dc(this);
	CPen *oldpen;
	CPen *newpen=new CPen;
	newpen->CreatePen(PS_SOLID,3,RGB(255,0,0));
	oldpen=dc.SelectObject(newpen);
	//dc.SetPixel(point,RGB(255,1,1));
	dc.SelectObject(oldpen);
	dc.Ellipse(point.x,point.y,point.x+2,point.y+2);
	CView::OnLButtonDown(nFlags, point);
}

//操作菜单函数
void CvoronoiView::OnVoronoiCreatin(){

	//接口，可以在这里完成 待分割点的输入工作

	if(nver<2)
	{
		MessageBox(_T("please input some points first!!"));
		//cout<<"input the points number: ";
		nver=3;
		Vertex[0].x=20;
		Vertex[0].y=20;
		Vertex[1].x=80;
		Vertex[1].y=20;
		Vertex[2].x=50;
		Vertex[2].y=100;
			/*for (int i=0;i<nver;i++)
		{
			cout<<"第"<<i+1<<"个点的横坐标为： ";
			cin>>Vertex[i].x;
			cout<<endl;
			cout<<"第"<<i+1<<"个点的纵坐标为： ";
				cin>>Vertex[i].y;
			cout<<endl;
		}*/
	}
	ntri=Triangulate(nver);//返回所有可能的三角形（含super点）

	Invalidate(true);
}


// CvoronoiView 打印

BOOL CvoronoiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CvoronoiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CvoronoiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CvoronoiView 诊断

#ifdef _DEBUG
void CvoronoiView::AssertValid() const
{
	CView::AssertValid();
}

void CvoronoiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CvoronoiDoc* CvoronoiView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvoronoiDoc)));
	return (CvoronoiDoc*)m_pDocument;
}
#endif //_DEBUG


// CvoronoiView 消息处理程序
bool CvoronoiView::incircle(int xp, int yp, int x1, int y1, int x2, int y2, int x3, int y3, double& xc, double& yc, double& r)
{
	//Return TRUE if the point (xp,yp) lies inside the circumcircle
	//made up by points (x1,y1) (x2,y2) (x3,y3)
	//The circumcircle centre is returned in (xc,yc) and the radius r
	//NOTE: A point on the edge is inside the circumcircle

	double m1=0.0;
	double m2=0.0;
	double mx1=0.0;
	double mx2=0.0;
	double my1=0.0;
	double my2=0.0;
	double dx=0.0;
	double dy=0.0;
	double rsqr=0.0;
	double drsqr=0.0;

	bool InCircle = false;

	if ((abs(y1 - y2)<1)&&(abs(y2 - y3)<1) )
	{
		MessageBox( _T("INCIRCUM - F - Points are coincident !!"));
		return false;
	}


	if (abs(y2 - y1) <5)
	{
		m2 = -(x3 - x2) /(double) (y3 - y2);
		mx2 = (x2 + x3) / 2.0;
		my2 = (y2 + y3) / 2.0;
		xc = (x2 + x1) / 2.0;
		yc = m2 * (xc - mx2) + my2;
	}
	else if (abs(y3 - y2) < 5 )
	{
		m1 = -(x2 - x1) / (double)(y2 - y1);
		mx1 = (x1 + x2) / 2.0;
		my1 = (y1 + y2) / 2.0;
		xc = (x3 + x2) / 2.0;
		yc = m1 * (xc - mx1) + my1;
	}
	else
	{
		m1=-(double)((x2-x1)/(double)(y2-y1));
		m2=-(double)((x3-x2)/(double)(y3-y2));
		mx1=(double)(x1+x2)/2.0;
		mx2=(double)(x2+x3)/2.0;
		my1=(double)(y1+y2)/2.0;
		my2=(double)(y2+y3)/2.0;
		xc=(double)((m1*mx1-m2*mx2+my2-my1)/(m1-m2));
		yc=(double)(m1*(xc-mx1)+my1);

	}

	dx = x2- xc;
	dy = y2-yc;
	rsqr = dx * dx + dy * dy;
	r = sqrt(rsqr);
	dx = xp - xc;
	dy = yp - yc;
	drsqr = dx * dx + dy * dy;

	if (drsqr <= rsqr )
		return true;
	else 
		return false;
}
bool CvoronoiView::incircle(int inx, int p1, int p2, int p3, double& xc, double& yc, double& r)
{
	int xp=Vertex[inx].x;
	int yp=Vertex[inx].y;
	int x1=Vertex[p1].x;
	int y1=Vertex[p1].y;
	int x2=Vertex[p2].x;
	int y2=Vertex[p2].y;
	int x3=Vertex[p3].x;
	int y3=Vertex[p3].y;

	double m1=0.0;
	double m2=0.0;
	double mx1=0.0;
	double mx2=0.0;
	double my1=0.0;
	double my2=0.0;
	double dx=0.0;
	double dy=0.0;
	double rsqr=0.0;
	double drsqr=0.0;

	bool InCircle = false;

	if ((abs(y1 - y2)<0.01)&&(abs(y2 - y3)<0.01) )
	{
		MessageBox( _T("INCIRCUM - F - Points are coincident !!"));
		return false;
	}


	if (abs(y2 - y1) <0.01 )
	{
		m2 = -(x3 - x2) /(double) (y3 - y2);
		mx2 = (x2 + x3) / 2.0;
		my2 = (y2 + y3) / 2.0;
		xc = (x2 + x1) / 2.0;
		yc = m2 * (xc - mx2) + my2;
	}
	else if (abs(y3 - y2) < 0.01 )
	{
		m1 = -(x2 - x1) / (double)(y2 - y1);
		mx1 = (x1 + x2) / 2.0;
		my1 = (y1 + y2) / 2.0;
		xc = (x3 + x2) / 2.0;
		yc = m1 * (xc - mx1) + my1;
	}
	else
	{
		m1=-((x2-x1)/(double)(y2-y1));
		m2=-((x3-x2)/(double)(y3-y2));
		mx1=(x1+x2)/2.0;
		mx2=(x2+x3)/2.0;
		my1=(y1+y2)/2.0;
		my2=(y2+y3)/2.0;
		xc=(m1*mx1-m2*mx2+my2-my1)/(m1-m2);
		yc=m1*(xc-mx1)+my1;

	}

	dx = x2- xc;
	dy = y2 - yc;
	rsqr = dx * dx + dy * dy;
	r = sqrt(rsqr);
	dx = xp - xc;
	dy = yp - yc;
	drsqr = dx * dx + dy * dy;

	if (drsqr <= rsqr )
		InCircle =true;

	return InCircle;
}

// 生成三角形
int CvoronoiView::Triangulate(int nver)
{
	bool Complete[maxtriangle];
	int Edges[2][ maxtriangle * 3];
	int Nedge;
	int ntri;
	int nedge;//temp edge of center
	vertex edge[2][maxtriangle];
	//For Super Triangle
	int xmin,xmax,ymin,ymax,xmid,ymid;
	double dx,dy,dmax;

	//General Variables
	int i,j,k;
	int temp;
	double xc=0.0,yc=0.0,r=0.0;
	bool inc=false;//点是否在内部
	for(i=0;i<2;i++)
	{	for(j=0;j<maxtriangle * 3;j++)
	Edges[i][j]=-1;
	}

	//Find the maximum and minimum vertex bounds.
	//This is to allow calculation of the bounding triangle
	xmin = Vertex[0].x;
	ymin = Vertex[0].y;
	xmax = xmin;
	ymax = ymin;
	for (i=1;i<nver;i++)
	{
		if (Vertex[i].x < xmin)  xmin = Vertex[i].x;
		if (Vertex[i].x > xmax ) xmax = Vertex[i].x;
		if (Vertex[i].y < ymin)  ymin = Vertex[i].y;
		if (Vertex[i].y > ymax)  ymax = Vertex[i].y;
	}

	dx = xmax - xmin;
	dy = ymax - ymin;
	if (dx > dy)
		dmax = dx;
	else
		dmax = dy;

	xmid = (xmax + xmin) / 2;
	ymid = (ymax + ymin) / 2;

	/*sort vertext*/
	temp=nver;
	for(i=0;i<nver-1;i++)
	{
		for(j=i+1;j<nver;j++)
		{
			if(Vertex[j].x<Vertex[i].x)  //冒泡法，将点的x坐标小的点放到Vertex[]的前面
			{
				Vertex[temp].x=Vertex[i].x;
				Vertex[temp].y=Vertex[i].y;
				Vertex[i].x=Vertex[j].x;
				Vertex[i].y=Vertex[j].y;
				Vertex[j].x=Vertex[temp].x;
				Vertex[j].y=Vertex[temp].y;
			}

		}
	}

	/*Set up the supertriangle
	'This is a triangle which encompasses all the sample points.
	'The supertriangle coordinates are added to the end of the
	'vertex list. The supertriangle is the first triangle in
	'the triangle list.*/

	Vertex[nver].x = xmid - 2*dmax;
	Vertex[nver].y = ymid - dmax;
	Vertex[nver + 1].x = xmid;
	Vertex[nver + 1].y = ymid + 2*dmax;
	Vertex[nver + 2].x = xmid + 2* dmax;
	Vertex[nver + 2].y = ymid - dmax;
	//nver=nver+3;

    //将第n个三角形的三个顶点在Vertex[]中的对应位置设置好
	Triangle[0].vv0 = nver ;
	Triangle[0].vv1 = nver + 1;
	Triangle[0].vv2 = nver + 2;
	Complete[0] = false;
	ntri=1;
	//Include each point one at a time into the existing mesh
	for( i = 0;i<nver;i++)//将所有的点(包括super三角形的点一起)组成的三角形都生成出来，然后一一付到Triangle[]数组中。
	{
		Nedge = 0;
		//'Set up the edge buffer.
		//'If the point (Vertex(i).x,Vertex(i).y) lies inside the circumcircle then the
		//'three edges of that triangle are added to the edge buffer.
		for(j = 0;j<ntri;j++)
		{
			if(!Complete[j])
			{
				inc=incircle(Vertex[i].x, Vertex[i].y, Vertex[Triangle[j].vv0].x,Vertex[Triangle[j].vv0].y, Vertex[Triangle[j].vv1].x, Vertex[Triangle[j].vv1].y, Vertex[Triangle[j].vv2].x, Vertex[Triangle[j].vv2].y, xc, yc, r);
				//inc=incircle(i, Triangle[j].vv0,Triangle[j].vv1,Triangle[j].vv2, xc, yc, r);
				if(xc+r<Vertex[i].x) //点Vertex[i]在外接圆外部，则三角是ok
					Complete[j]=true;
				if (inc)
				{                                          //把三角形的三个点在定点数组中的位置，赋给Edges[][]数组，0是起点，1为终点。
					Edges[0][ Nedge + 0] = Triangle[j].vv0;//第一次，5号点给Edges[0][0]
					Edges[1][ Nedge + 0] = Triangle[j].vv1;
					Edges[0][ Nedge + 1] = Triangle[j].vv1;
					Edges[1][ Nedge + 1] = Triangle[j].vv2;
					Edges[0][ Nedge + 2] = Triangle[j].vv2;
					Edges[1][ Nedge + 2] = Triangle[j].vv0;
					Nedge = Nedge + 3;
					Triangle[j].vv0 = Triangle[ntri-1].vv0;//如果输入点在三角形里，则这个三角形不合Dlaunary三角形规则，将计算下个三角形
					Triangle[j].vv1 = Triangle[ntri-1].vv1;
					Triangle[j].vv2 = Triangle[ntri-1].vv2;
					Complete[j] = Complete[ntri-1];
					j = j - 1;
					ntri = ntri - 1;
				}

			}
		}

		/*'Tag multiple edges
		'Note: if all triangles are specified anticlockwise then all
		'interior edges are opposite pointing in direction.*/
		for (j = 0; j< Nedge-1;j ++)
		{	
			for( k = j + 1;k< Nedge;k++)
			{
				if(Edges[0][j]==Edges[1][k]&&Edges[1][j]==Edges[0][k])//如果第j个起始边的起点==它对应终点的下个点（类似a->b,b->a），则边的顶点值为-1
				{
					Edges[0][j] = -1;
					Edges[1][j] = -1;
					Edges[0][k] = -1;
					Edges[1][k] = -1;
				}
				if(Edges[0][j]==Edges[0][k]&&Edges[1][j]==Edges[1][k])
				{
					Edges[0][j] = -1;
					Edges[1][j] = -1;
					Edges[0][k] = -1;
					Edges[1][k] = -1;
				}
			}
		}



		/*'Form new triangles for the current point
		'Skipping over any tagged edges.
		'All edges are arranged in clockwise order.*/
		for(j = 0;j< Nedge;j++)
		{
			if ( Edges[0][j] >= 0 && Edges[1][j] >= 0)//跳过不存在的边，将对应的边给对应的三角形
			{

				Triangle[ntri].vv0 = Edges[0][j];
				Triangle[ntri].vv1 = Edges[1][j];
				Triangle[ntri].vv2 = i;//将先前输入的点（即上面用来判断的Vertex[i]）赋给三角形第三个顶点，前2个点还是原来的三角形
                                       //这样就可以得到所有重新点组成的三角形，在做条件判断    
				Complete[ntri] = false;
				ntri = ntri + 1;
			}
		}
	}//所有点三角形生成结束


	// all triangles include the super triangles' circumcenter
	for(j=0;j<ntri;j++)  //计算出所有三角形重心
	{
		center[j]=circlecenter(Vertex[Triangle[j].vv0].x,Vertex[Triangle[j].vv0].y, Vertex[Triangle[j].vv1].x, Vertex[Triangle[j].vv1].y, Vertex[Triangle[j].vv2].x, Vertex[Triangle[j].vv2].y);
	}
	nedge=0;
	for(i=0;i<ntri-1;i++)
	{
		for(j=i+1;j<ntri;j++)
		{
			if(Triangle[i].vv0 >=nver|| Triangle[i].vv1>= nver|| Triangle[i].vv2 >= nver)//只要三角形数组中的顶点有一个比输入点数大
			{
				if(Triangle[j].vv0 >=nver|| Triangle[j].vv1>= nver|| Triangle[j].vv2 >= nver)//i的下个顺时针三角形任意一顶点大于输入点数
					continue; //即不遇到由真实点（出去super的三个顶点外的所有点的vv都是<nver输入点数的）三角形，就跳出到下个循环，即不运行下面的代码！！！！！continue！！！！！！


				if(Triangle[i].vv0==Triangle[j].vv0||Triangle[i].vv0==Triangle[j].vv1||Triangle[i].vv0==Triangle[j].vv2)
				{	
					if(Triangle[i].vv1==Triangle[j].vv0||Triangle[i].vv1==Triangle[j].vv1||Triangle[i].vv1==Triangle[j].vv2||Triangle[i].vv2==Triangle[j].vv0||Triangle[i].vv2==Triangle[j].vv1||Triangle[i].vv2==Triangle[j].vv2)

					{
						edge[0][nedge]=center[i];
						edge[1][nedge]=center[j];                 //找到含有用点的邻接三角形（判断至少一条边相同），将两个重心保存好，用连线来分割输入点
						nedge++;
					}
				}
				if(Triangle[i].vv1==Triangle[j].vv0||Triangle[i].vv1==Triangle[j].vv1||Triangle[i].vv1==Triangle[j].vv2)
				{
					if(Triangle[i].vv0==Triangle[j].vv0||Triangle[i].vv0==Triangle[j].vv1||Triangle[i].vv0==Triangle[j].vv2||Triangle[i].vv2==Triangle[j].vv0||Triangle[i].vv2==Triangle[j].vv1||Triangle[i].vv2==Triangle[j].vv2)

					{
						edge[0][nedge]=center[i];              //找到含有用点的邻接三角形（判断至少一条边相同），将两个重心保存好，用连线来分割输入点
						edge[1][nedge]=center[j];
						nedge++;
					}
				}

			}
			else//当三角形的顶点都是输入的点（不含有super三角形中的点）
			{
				if(Triangle[i].vv0==Triangle[j].vv0||Triangle[i].vv0==Triangle[j].vv1||Triangle[i].vv0==Triangle[j].vv2)
				{	
					if(Triangle[i].vv1==Triangle[j].vv0||Triangle[i].vv1==Triangle[j].vv1||Triangle[i].vv1==Triangle[j].vv2||Triangle[i].vv2==Triangle[j].vv0||Triangle[i].vv2==Triangle[j].vv1||Triangle[i].vv2==Triangle[j].vv2)

					{
						edge[0][nedge]=center[i];         //找到含有用点的邻接三角形（判断至少一条边相同），将两个重心保存好，用连线来分割输入点
						edge[1][nedge]=center[j];
						nedge++;
					}
				}
				if(Triangle[i].vv1==Triangle[j].vv0||Triangle[i].vv1==Triangle[j].vv1||Triangle[i].vv1==Triangle[j].vv2)
				{
					if(Triangle[i].vv0==Triangle[j].vv0||Triangle[i].vv0==Triangle[j].vv1||Triangle[i].vv0==Triangle[j].vv2||Triangle[i].vv2==Triangle[j].vv0||Triangle[i].vv2==Triangle[j].vv1||Triangle[i].vv2==Triangle[j].vv2)

					{
						edge[0][nedge]=center[i];
						edge[1][nedge]=center[j];         //找到含有用点的邻接三角形（判断至少一条边相同），将两个重心保存好，用连线来分割输入点
						nedge++;
					}
				}
			}
		}
	}
	this->nedge=nedge;//用来分割输入点的边界
	for(i=0;i<2;i++)
	{
		for(j=0;j<nedge;j++)
			this->edge[i][j]=edge[i][j];
	}
	/*'Remove triangles with supertriangle vertices
	'These are triangles which have a vertex number greater than NVERT*/

	/*for(i=0;i<ntri;i++)
	{
	if (Triangle[i].vv0 >=nver|| Triangle[i].vv1>= nver|| Triangle[i].vv2 >= nver)
	{
	Triangle[i].vv0 = Triangle[ntri-1].vv0;
	Triangle[i].vv1 = Triangle[ntri-1].vv1;
	Triangle[i].vv2 = Triangle[ntri-1].vv2;
	i = i - 1;
	ntri = ntri - 1;
	}
	}*/


	return ntri;
}



void CvoronoiView::OnVoronoiClear(){
	nver=0;
	ntri=0;
	nedge=0;
	Invalidate(true);
}


//求重心函数
vertex CvoronoiView::circlecenter(int x1, int y1, int x2, int y2, int x3, int y3)
{
	double xc,yc;

	double m1=0.0;
	double m2=0.0;
	double mx1=0.0;
	double mx2=0.0;
	double my1=0.0;
	double my2=0.0;

	if ((abs(y1 - y2)<1)&&(abs(y2 - y3)<1))
	{
		MessageBox( _T("INCIRCUM - F - Points are coincident !!"));
		exit(0);
	}

	if (abs(y2 - y1) <5)
	{
		m2 = -(x3 - x2) /(double) (y3 - y2);
		mx2 = (x2 + x3) / 2.0;
		my2 = (y2 + y3) / 2.0;
		xc = (x2 + x1) / 2.0;
		yc = m2 * (xc - mx2) + my2;
	}
	else if (abs(y3 - y2) < 5 )
	{
		m1 = -(x2 - x1) / (double)(y2 - y1);
		mx1 = (x1 + x2) / 2.0;
		my1 = (y1 + y2) / 2.0;
		xc = (x3 + x2) / 2.0;
		yc = m1 * (xc - mx1) + my1;
	}
	else
	{
		m1=-(double)((x2-x1)/(double)(y2-y1));
		m2=-(double)((x3-x2)/(double)(y3-y2));
		mx1=(double)(x1+x2)/2.0;
		mx2=(double)(x2+x3)/2.0;
		my1=(double)(y1+y2)/2.0;
		my2=(double)(y2+y3)/2.0;
		xc=(double)((m1*mx1-m2*mx2+my2-my1)/(m1-m2));
		yc=(double)(m1*(xc-mx1)+my1);

	}
	vertex temp;
	temp.x=xc;
	temp.y=yc;
	return temp;
}

//细胞膜重构函数
void CvoronoiView::CellMembraneContructor(CImage image){

}