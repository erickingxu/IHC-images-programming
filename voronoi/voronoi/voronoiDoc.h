// voronoiDoc.h : CvoronoiDoc ��Ľӿ�
//


#pragma once


class CvoronoiDoc : public CDocument
{
protected: // �������л�����
	CvoronoiDoc();
	DECLARE_DYNCREATE(CvoronoiDoc)

// ����
public:
  CImage img;
// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CvoronoiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


