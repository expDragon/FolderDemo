
// FolderDemoView.cpp : CFolderDemoView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "FolderDemo.h"
#endif

#include "FolderDemoDoc.h"
#include "FolderDemoView.h"
#include "Folder.h"
#include "CopyFolderDialog.h"
#include "DeleteFolderDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFolderDemoView

IMPLEMENT_DYNCREATE(CFolderDemoView, CView)

BEGIN_MESSAGE_MAP(CFolderDemoView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_COPY_FOLDER, &CFolderDemoView::OnCopyFolder)
	ON_COMMAND(ID_DELETE_FOLDER, &CFolderDemoView::OnDeleteFolder)
	ON_COMMAND(ID_BASE_API, &CFolderDemoView::OnBaseApi)
	ON_COMMAND(ID_SHELL_FILE, &CFolderDemoView::OnShellFile)
	ON_UPDATE_COMMAND_UI(ID_BASE_API, &CFolderDemoView::OnUpdateBaseApi)
	ON_UPDATE_COMMAND_UI(ID_SHELL_FILE, &CFolderDemoView::OnUpdateShellFile)
END_MESSAGE_MAP()

// CFolderDemoView 构造/析构

CFolderDemoView::CFolderDemoView()
	: m_iApiMode(BASE_API)
{
	// TODO: 在此处添加构造代码

}

CFolderDemoView::~CFolderDemoView()
{
}

BOOL CFolderDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CFolderDemoView 绘制

void CFolderDemoView::OnDraw(CDC* /*pDC*/)
{
	CFolderDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CFolderDemoView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFolderDemoView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFolderDemoView 诊断

#ifdef _DEBUG
void CFolderDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CFolderDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFolderDemoDoc* CFolderDemoView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFolderDemoDoc)));
	return (CFolderDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CFolderDemoView 消息处理程序


void CFolderDemoView::OnCopyFolder()
{
	// TODO: Add your command handler code here
	CString strAppFile(_T(""));
	GetModuleFileName(NULL,strAppFile.GetBuffer(MAX_PATH), MAX_PATH);
	strAppFile.ReleaseBuffer();
	int iSplitIdx = strAppFile.ReverseFind(_T('\\'));
	CString strAppFolder = strAppFile.Left(iSplitIdx + 1);

	CCopyFolderDialog dlg;
	dlg.m_strSrcFolder = strAppFolder + _T("Src");
	dlg.m_strDstFolder = strAppFolder + _T("Dst");

	
	
	if (IDOK != dlg.DoModal())
	{
		return;
	}

	CString strPrompt(_T(""));
	BOOL bRet = FALSE;

	if (BASE_API == m_iApiMode)
	{
		bRet = CFolder::CopyFolder(dlg.m_strSrcFolder, dlg.m_strDstFolder);
	}
	else
	{
		bRet = CFolder::SHCopyFolder(dlg.m_strSrcFolder, dlg.m_strDstFolder);
	}

	if (bRet)
	{
		strPrompt.Format(_T("复制目录“%s”至“%s”成功！"), dlg.m_strSrcFolder, dlg.m_strDstFolder);
		AfxMessageBox(strPrompt);
	}
	else
	{
		strPrompt.Format(_T("复制目录“%s”至“%s”失败！"), dlg.m_strSrcFolder, dlg.m_strDstFolder);
		AfxMessageBox(strPrompt);
	}

}


void CFolderDemoView::OnDeleteFolder()
{
	// TODO: Add your command handler code here
	CString strAppFile(_T(""));
	GetModuleFileName(NULL,strAppFile.GetBuffer(MAX_PATH), MAX_PATH);
	strAppFile.ReleaseBuffer();
	int iSplitIdx = strAppFile.ReverseFind(_T('\\'));
	CString strAppFolder = strAppFile.Left(iSplitIdx + 1);

	CDeleteFolderDialog dlg;
	dlg.m_strFolder = strAppFolder + _T("Dst");

	if (IDOK != dlg.DoModal())
	{
		return;
	}

	CString strPrompt(_T(""));
	BOOL bRet = FALSE;
	if (BASE_API == m_iApiMode)
	{
		bRet = CFolder::DeleteFolder(dlg.m_strFolder);
	}
	else
	{
		bRet = CFolder::SHDeleteFolder(dlg.m_strFolder, FALSE);
	}

	if (bRet)
	{
		strPrompt.Format(_T("删除目录“%s”成功！"), dlg.m_strFolder);
		AfxMessageBox(strPrompt);
	}
	else
	{
		strPrompt.Format(_T("删除目录“%s”失败！"), dlg.m_strFolder);
		AfxMessageBox(strPrompt);
	}
}


void CFolderDemoView::OnBaseApi()
{
	// TODO: Add your command handler code here
	m_iApiMode = BASE_API;
}


void CFolderDemoView::OnShellFile()
{
	// TODO: Add your command handler code here
	m_iApiMode = SHELL_FILE_API;
}


void CFolderDemoView::OnUpdateBaseApi(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (BASE_API == m_iApiMode)
	{
		pCmdUI->SetCheck(BST_CHECKED);
	}
	else
	{
		pCmdUI->SetCheck(BST_UNCHECKED);
	}
}


void CFolderDemoView::OnUpdateShellFile(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (SHELL_FILE_API == m_iApiMode)
	{
		pCmdUI->SetCheck(BST_CHECKED);
	}
	else
	{
		pCmdUI->SetCheck(BST_UNCHECKED);
	}
}
