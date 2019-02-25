#pragma once


// CCopyFolderDialog dialog

class CCopyFolderDialog : public CDialog
{
	DECLARE_DYNAMIC(CCopyFolderDialog)

public:
	CCopyFolderDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCopyFolderDialog();

// Dialog Data
	enum { IDD = IDD_COPY_FOLDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_strSrcFolder;
	CString m_strDstFolder;
};
