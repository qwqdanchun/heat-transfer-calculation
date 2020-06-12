
// demoView.cpp: CMydemoView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "demo.h"
#endif

#include "demoDoc.h"
#include "demoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMydemoView

IMPLEMENT_DYNCREATE(CMydemoView, CView)

BEGIN_MESSAGE_MAP(CMydemoView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMydemoView 构造/析构

CMydemoView::CMydemoView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMydemoView::~CMydemoView()
{
}

BOOL CMydemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMydemoView 绘图

void CMydemoView::OnDraw(CDC* pDC)
{
	CMydemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int eagelenth, i, color;
	eagelenth = 50;
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(100, 100);
	pDC->SetViewportExt(100, -100);
	pDC->SetWindowOrg(0, 0);
	pDC->SetViewportOrg(200, 200);
	CBrush* newbrush;
	CBrush* oldbrush;

	for (i = 1; i < 6; i++)
	{
		if (pDoc->T1[i] > pDoc->endtemp)
			color = int(255 * fabs(pDoc->T1[i] - pDoc->endtemp) / (1370 - pDoc->endtemp));
		else
			color = 0;

		newbrush = new CBrush;

		newbrush->CreateSolidBrush(RGB(color, 0, 0));

		oldbrush = pDC->SelectObject(newbrush);

		pDC->Rectangle(i * eagelenth, 0, (i + 1) * eagelenth, eagelenth);

		pDC->SelectObject(oldbrush);
		delete newbrush;
	}
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


void CMydemoView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CPaintDC dc(this);
	OnDraw(&dc); //或自己添加一个绘图程序，但OnDraw 函数中必须有与
				// 绘图程序中同样的绘图程序。
	Invalidate(FALSE);
}



// CMydemoView 打印

BOOL CMydemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMydemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMydemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMydemoView 诊断

#ifdef _DEBUG
void CMydemoView::AssertValid() const
{
	CView::AssertValid();
}

void CMydemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMydemoDoc* CMydemoView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMydemoDoc)));
	return (CMydemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CMydemoView 消息处理程序
