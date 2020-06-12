
// demoDoc.h: CMydemoDoc 类的接口
//


#pragma once


class CMydemoDoc : public CDocument
{
protected: // 仅从序列化创建
	CMydemoDoc() noexcept;
	DECLARE_DYNCREATE(CMydemoDoc)

	// 特性
public:

	// 操作
public:
	float T1[7], T2[7];
	float lamda, s_h, ru;
	float delta_t, delta_x;
	float endtemp;

	// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// 实现
public:
	virtual ~CMydemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnCalStart();
};
