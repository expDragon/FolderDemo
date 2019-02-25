// CopyFolderDialog.cpp : implementation file
//

#include "stdafx.h"
#include "FolderDemo.h"
#include "CopyFolderDialog.h"
#include "afxdialogex.h"


// CCopyFolderDialog dialog

IMPLEMENT_DYNAMIC(CCopyFolderDialog, CDialog)

CCopyFolderDialog::CCopyFolderDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCopyFolderDialog::IDD, pParent)
	, m_strSrcFolder(_T(""))
	, m_strDstFolder(_T(""))
{

}

CCopyFolderDialog::~CCopyFolderDialog()
{
}

void CCopyFolderDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_strSrcFolder);
	DDX_Text(pDX, IDC_EDIT4, m_strDstFolder);
}


BEGIN_MESSAGE_MAP(CCopyFolderDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CCopyFolderDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CCopyFolderDialog message handlers

void CCopyFolderDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	CDialog::OnOK();
}