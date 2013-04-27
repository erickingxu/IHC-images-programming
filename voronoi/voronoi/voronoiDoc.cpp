// voronoiDoc.cpp : CvoronoiDoc ���ʵ��
//

#include "stdafx.h"
#include "voronoi.h"

#include "voronoiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvoronoiDoc

IMPLEMENT_DYNCREATE(CvoronoiDoc, CDocument)

BEGIN_MESSAGE_MAP(CvoronoiDoc, CDocument)
END_MESSAGE_MAP()


// CvoronoiDoc ����/����

CvoronoiDoc::CvoronoiDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CvoronoiDoc::~CvoronoiDoc()
{
}

BOOL CvoronoiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CvoronoiDoc ���л�

void CvoronoiDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
		if (img.IsNull())
		{
			AfxMessageBox(_T("No file to be saved!"));
		}
		else{
			
			CString strFilter;
			strFilter="λͼ�ļ�|*.bmp|JPEG ͼ���ļ�|*.jpg|GIF ͼ���ļ�|*.gif|PNG ͼ���ļ�|*.png||"; 
			CFileDialog dlg(FALSE,NULL,NULL,NULL,strFilter);
			if (IDOK !=dlg.DoModal())
			 return;

			//�������ʱΪָ����չ���������һ��
			CString strFileName;
			CString strExtension;

			strFileName=dlg.m_ofn.lpstrFile;
			if (dlg.m_ofn.nFileExtension!=0)
			{
				switch (dlg.m_ofn.nFilterIndex)
				{
				case 1:
					strExtension="BMP";
					break;
				case 2:
					strExtension="JPG";
					break;
				case 3:
					strExtension="GIF";
					break;
				case 4:
					strExtension="PNG";
					break;
				default:

					break;
				}
			strFileName =strFileName+_T(".")+strExtension;
			}
			//ͼ�񱣴�
			HRESULT hReslt=img.Save(strFileName);
			if (FAILED(hReslt))
			{
				AfxMessageBox(_T("Save File failed!Sorry~"));
			}
		}
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
		if (!img.IsNull())
		{
			img.Destroy();
		}
		else
			img.Load(ar.GetFile()->GetFilePath());
	}
}


// CvoronoiDoc ���

#ifdef _DEBUG
void CvoronoiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CvoronoiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CvoronoiDoc ����
