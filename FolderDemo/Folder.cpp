#include "StdAfx.h"
#include "Folder.h"
#include <shlwapi.h>


CFolder::CFolder(void)
{
}


CFolder::~CFolder(void)
{
}

/*�ж�һ��·���Ƿ����Ѵ��ڵ�Ŀ¼*/
BOOL CFolder::IsDirectory(LPCTSTR pstrPath)
{
	if (NULL == pstrPath)
	{
		return FALSE;
	}

	/*ȥ��·��ĩβ�ķ�б��*/
	CString strPath = pstrPath;
	if (strPath.Right(1) == _T('\\'))
	{
		strPath.Delete(strPath.GetLength()-1);
	}

	CFileFind finder;
	BOOL bRet = finder.FindFile(strPath);
	if (!bRet)
	{
		return FALSE;
	}

	/*�жϸ�·���Ƿ���Ŀ¼*/
	finder.FindNextFile();
	bRet = finder.IsDirectory();
	finder.Close();
	return bRet;
}

/*����Ŀ¼�е���������*/
BOOL CFolder::CopyFolder(LPCTSTR pstrSrcFolder, LPCTSTR pstrDstFolder)
{
	if ((NULL == pstrSrcFolder) || (NULL == pstrSrcFolder))
	{
		return FALSE;
	}

	/*���ԴĿ¼�Ƿ��ǺϷ�Ŀ¼*/
	if (!IsDirectory(pstrSrcFolder))
	{
		return FALSE;
	}

	/*���ļ�����ת��ΪCString���ͣ���ȷ��Ŀ¼��·��ĩβΪ��б��*/
	CString strSrcFolder(pstrSrcFolder);
	if (strSrcFolder.Right(1) != _T('\\'))
	{
		strSrcFolder += _T("\\");
	}
	CString strDstFolder(pstrDstFolder);
	if (strDstFolder.Right(1) != _T("\\"))
	{
		strDstFolder += _T("\\");
	}

	/*�����Ŀ¼�����ƣ�ֱ�ӷ��ظ��Ƴɹ�*/
	if (0 == _tcscmp(strSrcFolder, strDstFolder))
	{
		return TRUE;
	}

	/*���Ŀ��Ŀ¼������,�򴴽�Ŀ¼*/
	if (!IsDirectory(strDstFolder))
	{
		if (!CreateDirectory(strDstFolder, NULL))
		{
			/*����Ŀ��Ŀ¼ʧ��*/
			return FALSE;
		}
	}

	/*����ԴĿ¼�в����ļ���ͨ���*/
	CString strWildcard(strSrcFolder);
	strWildcard += _T("*.*");

	/*���ļ����ң��鿴ԴĿ¼���Ƿ����ƥ����ļ�*/
	/*����FindFile�󣬱������FindNextFile���ܻ�ò����ļ�����Ϣ*/
	CFileFind finder;
	BOOL bWorking = finder.FindFile(strWildcard);

	while (bWorking)
	{
		/*������һ���ļ�*/
		bWorking = finder.FindNextFile();

		/*������ǰĿ¼��.������һ��Ŀ¼��..��*/
		if (finder.IsDots())
		{
			continue;
		}

		/*�õ���ǰҪ���Ƶ�Դ�ļ���·��*/
		CString strSrcFile = finder.GetFilePath();

		/*�õ�Ҫ���Ƶ�Ŀ���ļ���·��*/
		CString strDstFile(strDstFolder);
		strDstFile += finder.GetFileName();

		/*�жϵ�ǰ�ļ��Ƿ���Ŀ¼,*/
		/*�����Ŀ¼���ݹ���ø���Ŀ¼,*/
		/*����ֱ�Ӹ����ļ�*/
		if (finder.IsDirectory())
		{
			if (!CopyFolder(strSrcFile, strDstFile))
			{
				finder.Close();
				return FALSE;
			}
		}
		else
		{
			if (!CopyFile(strSrcFile, strDstFile, FALSE))
			{
				finder.Close();
				return FALSE;
			}
		}

	} /*while (bWorking)*/

	/*�ر��ļ�����*/
	finder.Close();

	return TRUE;

} 

/*ɾ��Ŀ¼��Ŀ¼�е���������*/
BOOL CFolder::DeleteFolder(LPCTSTR pstrFolder)
{
	if ((NULL == pstrFolder))
	{
		return FALSE;
	}

	/*�������Ŀ¼�Ƿ��ǺϷ�Ŀ¼*/
	if (!IsDirectory(pstrFolder))
	{
		return FALSE;
	}

	/*����ԴĿ¼�в����ļ���ͨ���*/
	CString strWildcard(pstrFolder);
	if (strWildcard.Right(1) != _T('\\'))
	{
		strWildcard += _T("\\");
	}
	strWildcard += _T("*.*");

	/*���ļ����ң��鿴ԴĿ¼���Ƿ����ƥ����ļ�*/
	/*����FindFile�󣬱������FindNextFile���ܻ�ò����ļ�����Ϣ*/
	CFileFind finder;
	BOOL bWorking = finder.FindFile(strWildcard);

	while (bWorking)
	{
		/*������һ���ļ�*/
		bWorking = finder.FindNextFile();

		/*������ǰĿ¼��.������һ��Ŀ¼��..��*/
		if (finder.IsDots())
		{
			continue;
		}

		/*�õ���ǰĿ¼�����ļ���·��*/
		CString strSubFile = finder.GetFilePath();

		/*�жϵ�ǰ�ļ��Ƿ���Ŀ¼,*/
		/*�����Ŀ¼���ݹ����ɾ��Ŀ¼,*/
		/*����ֱ��ɾ���ļ�*/
		if (finder.IsDirectory())
		{
			if (!DeleteFolder(strSubFile))
			{
				finder.Close();
				return FALSE;
			}
		}
		else
		{
			if (!DeleteFile(strSubFile))
			{
				finder.Close();
				return FALSE;
			}
		}

	} /*while (bWorking)*/

	/*�ر��ļ�����*/
	finder.Close();

	/*ɾ����Ŀ¼*/
	return RemoveDirectory(pstrFolder);
}

/*ͨ������ShFileOperation��ʵ������Ŀ¼��ɾ��*/
/*ֻɾ������Ŀ¼*/
BOOL CFolder::SHDeleteFolder(LPCTSTR pstrFolder, BOOL bAllowUndo)
{
	if ((NULL == pstrFolder))
	{
		return FALSE;
	}

	int iPathLen = _tcslen(pstrFolder);
	if (iPathLen >= MAX_PATH)
	{
		return FALSE;
	}

	/*ȷ��Ŀ¼��·����2��\0��β*/
	TCHAR tczFolder[MAX_PATH+1];
	ZeroMemory(tczFolder, (MAX_PATH+1)*sizeof(TCHAR));
	_tcscpy(tczFolder, pstrFolder);
	tczFolder[iPathLen] = _T('\0');
	tczFolder[iPathLen+1] = _T('\0');

	SHFILEOPSTRUCT FileOp; 
	ZeroMemory(&FileOp, sizeof(SHFILEOPSTRUCT)); 
	FileOp.fFlags |= FOF_SILENT;		/*����ʾ����*/
	FileOp.fFlags |= FOF_NOERRORUI;		/*�����������Ϣ*/
	FileOp.fFlags |= FOF_NOCONFIRMATION;/*ֱ��ɾ����������ȷ��*/
	FileOp.hNameMappings = NULL;
	FileOp.hwnd = NULL;
	FileOp.lpszProgressTitle = NULL;
	FileOp.wFunc = FO_DELETE;
	FileOp.pFrom = tczFolder;			/*Ҫɾ����Ŀ¼��������2��\0��β*/
	FileOp.pTo = NULL; 

	/*���ݴ��ݵ�bAllowUndo����ȷ���Ƿ�ɾ��������վ*/
	if (bAllowUndo)
	{   
		FileOp.fFlags |= FOF_ALLOWUNDO; /*ɾ��������վ*/
	}  
	else  
	{   
		FileOp.fFlags &= ~FOF_ALLOWUNDO; /*ֱ��ɾ�������������վ*/
	}
	
	/*ɾ��Ŀ¼*/
	if (0 == SHFileOperation(&FileOp))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


/*ͨ������ShFileOperation��ʵ������Ŀ¼�ĸ���*/
/*ֻ���Ƶ���Ŀ¼*/
/*���Ŀ��Ŀ¼�Ѵ��ڣ�����ԴĿ¼��ΪĿ��Ŀ¼����Ŀ¼*/
/*���Ҫʵ����ȫ���ǣ���Ҫ��ɾ��Ŀ��Ŀ¼*/
BOOL CFolder::SHCopyFolder(LPCTSTR pstrSrcFolder, LPCTSTR pstrDstFolder)
{
	if ((NULL == pstrSrcFolder) || (NULL == pstrSrcFolder))
	{
		return FALSE;
	}

	int iSrcPathLen = _tcslen(pstrSrcFolder);
	int iDstPathLen = _tcslen(pstrDstFolder);
	if ((iSrcPathLen >= MAX_PATH) || (iDstPathLen >= MAX_PATH))
	{
		return FALSE;
	}

	/*ȷ��ԴĿ¼��·����2��\0��β*/
	TCHAR tczSrcFolder[MAX_PATH+1];
	ZeroMemory(tczSrcFolder, (MAX_PATH+1)*sizeof(TCHAR));
	_tcscpy(tczSrcFolder, pstrSrcFolder);
	tczSrcFolder[iSrcPathLen] = _T('\0');
	tczSrcFolder[iSrcPathLen+1] = _T('\0');

	/*ȷ��Ŀ��Ŀ¼��·����2��\0��β*/
	TCHAR tczDstFolder[MAX_PATH+1];
	ZeroMemory(tczDstFolder, (MAX_PATH+1)*sizeof(TCHAR));
	_tcscpy(tczDstFolder, pstrDstFolder);
	tczDstFolder[iDstPathLen] = _T('\0');
	tczDstFolder[iDstPathLen+1] = _T('\0');

	SHFILEOPSTRUCT FileOp; 
	ZeroMemory(&FileOp, sizeof(SHFILEOPSTRUCT)); 
	FileOp.fFlags |= FOF_SILENT;		/*����ʾ����*/
	FileOp.fFlags |= FOF_NOERRORUI ;	/*�����������Ϣ*/
	FileOp.fFlags |= FOF_NOCONFIRMATION;/*������ȷ��*/
	FileOp.hNameMappings = NULL;
	FileOp.hwnd = NULL;
	FileOp.lpszProgressTitle = NULL;
	FileOp.wFunc = FO_COPY;
	FileOp.pFrom = tczSrcFolder;		/*ԴĿ¼��������2��\0��β*/
	FileOp.pTo = tczDstFolder;			/*Ŀ��Ŀ¼��������2��\0��β*/	

	/*����Ŀ¼*/
	if (0 == SHFileOperation(&FileOp))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}