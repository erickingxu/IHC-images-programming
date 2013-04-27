// voronoiDoc.cpp : CvoronoiDoc 类的实现
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


// CvoronoiDoc 构造/析构

CvoronoiDoc::CvoronoiDoc()
{
	// TODO: 在此添加一次性构造代码

}

CvoronoiDoc::~CvoronoiDoc()
{
}

BOOL CvoronoiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CvoronoiDoc 序列化

void CvoronoiDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		if (img.IsNull())
		{
			AfxMessageBox(_T("No file to be saved!"));
		}
		else{
			
			CString strFilter;
			strFilter="位图文件|*.bmp|JPEG 图像文件|*.jpg|GIF 图像文件|*.gif|PNG 图像文件|*.png||"; 
			CFileDialog dlg(FALSE,NULL,NULL,NULL,strFilter);
			if (IDOK !=dlg.DoModal())
			 return;

			//如果保存时为指定扩展名，则添加一个
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
			//图像保存
			HRESULT hReslt=img.Save(strFileName);
			if (FAILED(hReslt))
			{
				AfxMessageBox(_T("Save File failed!Sorry~"));
			}
		}
	}
	else
	{
		// TODO: 在此添加加载代码
		if (!img.IsNull())
		{
			img.Destroy();
		}
		else
			img.Load(ar.GetFile()->GetFilePath());
	}
}


// CvoronoiDoc 诊断

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


// CvoronoiDoc 命令
