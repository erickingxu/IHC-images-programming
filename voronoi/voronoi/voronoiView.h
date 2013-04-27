// voronoiView.h : CvoronoiView 类的接口
//


#pragma once


class triangle
{
public:
	int vv0;
	int vv1;
	int vv2;
};
struct vertex
{
	double x;
	double y;
};

const int maxvertex=50;
const int maxtriangle=100;



class CvoronoiView : public CView
{
protected: // 仅从序列化创建
	CvoronoiView();
	DECLARE_DYNCREATE(CvoronoiView)

// 属性
public:
	CvoronoiDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CvoronoiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

public:
  
	int nver;
	int ntri;
	int nedge;
	// 散点数组
	vertex Vertex[maxvertex];
	//三角形圆心数组
	vertex center[maxtriangle];
	vertex edge[2][maxtriangle];
	triangle Triangle[maxtriangle];
public:
	bool incircle(int xp, int yp, int x1, int y1, int x2, int y2, int x3, int y3, double& xc, double& yc, double& r);
	bool incircle(int inx, int p1, int p2, int p3, double& xc, double& yc, double& r);
public:
	// 生成三角形
	int Triangulate(int nver);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnVoronoiCreatin();
public:
	//afx_msg void OnFileOpen();
public:
	afx_msg void OnVoronoiClear();
public:
	// all triangles include the super triangles' circumcenter
	vertex circlecenter(int x1, int y1, int x2, int y2, int x3, int y3);


	//其他图像功能处理函数
public:
	void CellMembraneContructor(CImage image);
};

#ifndef _DEBUG  // voronoiView.cpp 中的调试版本
inline CvoronoiDoc* CvoronoiView::GetDocument() const
   { return reinterpret_cast<CvoronoiDoc*>(m_pDocument); }
#endif

