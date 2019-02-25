// DeleteFolderDialog.cpp : implementation file
//

#include "stdafx.h"
#include "FolderDemo.h"
#include "DeleteFolderDialog.h"
#include "afxdialogex.h"


// CDeleteFolderDialog dialog

IMPLEMENT_DYNAMIC(CDeleteFolderDialog, CDialog)

CDeleteFolderDialog::CDeleteFolderDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteFolderDialog::IDD, pParent)
	, m_strFolder(_T(""))
{

}

CDeleteFolderDialog::~CDeleteFolderDialog()
{
}

void CDeleteFolderDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, m_strFolder);
}


BEGIN_MESSAGE_MAP(CDeleteFolderDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CDeleteFolderDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CDeleteFolderDialog message handlers


void CDeleteFolderDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	CDialog::OnOK();
}