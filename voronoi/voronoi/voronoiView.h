// voronoiView.h : CvoronoiView ��Ľӿ�
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
protected: // �������л�����
	CvoronoiView();
	DECLARE_DYNCREATE(CvoronoiView)

// ����
public:
	CvoronoiDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CvoronoiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

public:
  
	int nver;
	int ntri;
	int nedge;
	// ɢ������
	vertex Vertex[maxvertex];
	//������Բ������
	vertex center[maxtriangle];
	vertex edge[2][maxtriangle];
	triangle Triangle[maxtriangle];
public:
	bool incircle(int xp, int yp, int x1, int y1, int x2, int y2, int x3, int y3, double& xc, double& yc, double& r);
	bool incircle(int inx, int p1, int p2, int p3, double& xc, double& yc, double& r);
public:
	// ����������
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


	//����ͼ���ܴ�����
public:
	void CellMembraneContructor(CImage image);
};

#ifndef _DEBUG  // voronoiView.cpp �еĵ��԰汾
inline CvoronoiDoc* CvoronoiView::GetDocument() const
   { return reinterpret_cast<CvoronoiDoc*>(m_pDocument); }
#endif

