
// demoDoc.cpp: CMydemoDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "demo.h"
#endif

#include "demoDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMydemoDoc

IMPLEMENT_DYNCREATE(CMydemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CMydemoDoc, CDocument)
	ON_COMMAND(ID_CAL_START, &CMydemoDoc::OnCalStart)
END_MESSAGE_MAP()


// CMydemoDoc 构造/析构

CMydemoDoc::CMydemoDoc() noexcept
{
	// TODO: 在此添加一次性构造代码
	int i;
	int j;
	T1[0][0] = 300;
	T1[6][0] = 300;
	T1[0][6] = 300;
	T1[6][6] = 300;

	for (i = 1; i < 6; i++)
		for (j = 1; j < 6; j++)
			T1[i][j] = 1370;
	for (i = 0; i < 7; i++)
	{
		T1[i][0] = 300;
		T1[i][6] = 300;
	}
	for (j = 0; j < 7; j++)
	{
		T1[0][j] = 300;
		T1[6][j] = 300;
	}

	lamda = 52;
	s_h = 600;
	ru = 7200;
	delta_x = 0.01;
	endtemp = 750;
}

CMydemoDoc::~CMydemoDoc()
{
}

BOOL CMydemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMydemoDoc 序列化

void CMydemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMydemoDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMydemoDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMydemoDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMydemoDoc 诊断

#ifdef _DEBUG
void CMydemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMydemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMydemoDoc 命令


void CMydemoDoc::OnCalStart()
{
	// TODO: 在此添加命令处理程序代码
	int i, j;
	int endflag;
	float themprop;
	long k;
	double delay;
	endflag = 0;
	delta_t = 0.01 * s_h * ru * delta_x * delta_x / (2 * lamda);
	themprop = lamda * delta_t / (s_h * ru * delta_x * delta_x);
	while (endflag == 0)
	{
		for (i = 1; i < 6; i++)
			for (j = 1; j < 6; j++)
				T2[i][j] = themprop * (T1[i - 1][j] + T1[i + 1][j] + T1[i][j - 1] + T1[i][j + 1] + (1 / themprop - 4) * T1[i][j]);

		UpdateAllViews(NULL);
		for (i = 1; i < 6; i++)
		{
			for (j = 1; j < 6; j++)
			{
				endflag = 1;
				if (T2[i][j] >= 750)
				{
					endflag = 0;
					break;
				}

			}
			if (j != 6) break;
		}

		for (i = 1; i < 6; i++)
			for (j = 1; j < 6; j++)
				T1[i][j] = T2[i][j];
		delay = 0.0;
		for (k = 1; k < 30000000; k++)
			delay = delay * i;
	}
	return;
}
