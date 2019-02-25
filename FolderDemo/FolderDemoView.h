
// FolderDemoView.h : CFolderDemoView 类的接口
//

#pragma once

#define BASE_API 0
#define SHELL_FILE_API 1


class CFolderDemoView : public CView
{
protected: // 仅从序列化创建
	CFolderDemoView();
	DECLARE_DYNCREATE(CFolderDemoView)

// 特性
public:
	CFolderDemoDoc* GetDocument() const;
	int m_iApiMode;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CFolderDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCopyFolder();
	afx_msg void OnDeleteFolder();
	afx_msg void OnBaseApi();
	afx_msg void OnShellFile();
	afx_msg void OnUpdateBaseApi(CCmdUI *pCmdUI);
	afx_msg void OnUpdateShellFile(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // FolderDemoView.cpp 中的调试版本
inline CFolderDemoDoc* CFolderDemoView::GetDocument() const
   { return reinterpret_cast<CFolderDemoDoc*>(m_pDocument); }
#endif

