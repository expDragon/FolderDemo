#pragma once
class CFolder
{
public:
	CFolder(void);
	virtual ~CFolder(void);

public:

	/*�ж�һ��·���Ƿ����Ѵ��ڵ�Ŀ¼*/
	static BOOL IsDirectory(LPCTSTR pstrPath);

	/*����Ŀ¼�е���������*/
	static BOOL CopyFolder(LPCTSTR pstrSrcFolder, LPCTSTR pstrDstFolder);

	/*ɾ��Ŀ¼��Ŀ¼�е���������*/
	static BOOL DeleteFolder(LPCTSTR pstrFolder);

	/*ͨ������ShFileOperation��ʵ������Ŀ¼��ɾ��*/
	static BOOL SHDeleteFolder(LPCTSTR pstrFolder, BOOL bAllowUndo);

	/*ͨ������ShFileOperation��ʵ������Ŀ¼�ĸ���*/
	static BOOL SHCopyFolder(LPCTSTR pstrSrcFolder, LPCTSTR pstrDstFolder);
};

