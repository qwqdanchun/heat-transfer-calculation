
// demoView.h: CMydemoView 类的接口
//

#pragma once


class CMydemoView : public CView
{
protected: // 仅从序列化创建
	CMydemoView() noexcept;
	DECLARE_DYNCREATE(CMydemoView)

	// 特性
public:
	CMydemoDoc* GetDocument() const;

	// 操作
public:

	// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 实现
public:
	virtual ~CMydemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // demoView.cpp 中的调试版本
inline CMydemoDoc* CMydemoView::GetDocument() const
{
	return reinterpret_cast<CMydemoDoc*>(m_pDocument);
}
#endif

