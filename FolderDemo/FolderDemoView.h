
// FolderDemoView.h : CFolderDemoView ��Ľӿ�
//

#pragma once

#define BASE_API 0
#define SHELL_FILE_API 1


class CFolderDemoView : public CView
{
protected: // �������л�����
	CFolderDemoView();
	DECLARE_DYNCREATE(CFolderDemoView)

// ����
public:
	CFolderDemoDoc* GetDocument() const;
	int m_iApiMode;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CFolderDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // FolderDemoView.cpp �еĵ��԰汾
inline CFolderDemoDoc* CFolderDemoView::GetDocument() const
   { return reinterpret_cast<CFolderDemoDoc*>(m_pDocument); }
#endif

