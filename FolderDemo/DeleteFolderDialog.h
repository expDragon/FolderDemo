#pragma once


// CDeleteFolderDialog dialog

class CDeleteFolderDialog : public CDialog
{
	DECLARE_DYNAMIC(CDeleteFolderDialog)

public:
	CDeleteFolderDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDeleteFolderDialog();

// Dialog Data
	enum { IDD = IDD_DELETE_FOLDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_strFolder;
};
