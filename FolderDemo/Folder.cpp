#include "StdAfx.h"
#include "Folder.h"
#include <shlwapi.h>


CFolder::CFolder(void)
{
}


CFolder::~CFolder(void)
{
}

/*判断一个路径是否是已存在的目录*/
BOOL CFolder::IsDirectory(LPCTSTR pstrPath)
{
	if (NULL == pstrPath)
	{
		return FALSE;
	}

	/*去除路径末尾的反斜杠*/
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

	/*判断该路径是否是目录*/
	finder.FindNextFile();
	bRet = finder.IsDirectory();
	finder.Close();
	return bRet;
}

/*复制目录中的所有内容*/
BOOL CFolder::CopyFolder(LPCTSTR pstrSrcFolder, LPCTSTR pstrDstFolder)
{
	if ((NULL == pstrSrcFolder) || (NULL == pstrSrcFolder))
	{
		return FALSE;
	}

	/*检查源目录是否是合法目录*/
	if (!IsDirectory(pstrSrcFolder))
	{
		return FALSE;
	}

	/*把文件名称转换为CString类型，并确认目录的路径末尾为反斜杠*/
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

	/*如果是目录自身复制，直接返回复制成功*/
	if (0 == _tcscmp(strSrcFolder, strDstFolder))
	{
		return TRUE;
	}

	/*如果目的目录不存在,则创建目录*/
	if (!IsDirectory(strDstFolder))
	{
		if (!CreateDirectory(strDstFolder, NULL))
		{
			/*创建目的目录失败*/
			return FALSE;
		}
	}

	/*创建源目录中查找文件的通配符*/
	CString strWildcard(strSrcFolder);
	strWildcard += _T("*.*");

	/*打开文件查找，查看源目录中是否存在匹配的文件*/
	/*调用FindFile后，必须调用FindNextFile才能获得查找文件的信息*/
	CFileFind finder;
	BOOL bWorking = finder.FindFile(strWildcard);

	while (bWorking)
	{
		/*查找下一个文件*/
		bWorking = finder.FindNextFile();

		/*跳过当前目录“.”和上一级目录“..”*/
		if (finder.IsDots())
		{
			continue;
		}

		/*得到当前要复制的源文件的路径*/
		CString strSrcFile = finder.GetFilePath();

		/*得到要复制的目标文件的路径*/
		CString strDstFile(strDstFolder);
		strDstFile += finder.GetFileName();

		/*判断当前文件是否是目录,*/
		/*如果是目录，递归调用复制目录,*/
		/*否则，直接复制文件*/
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

	/*关闭文件查找*/
	finder.Close();

	return TRUE;

} 

/*删除目录及目录中的所有内容*/
BOOL CFolder::DeleteFolder(LPCTSTR pstrFolder)
{
	if ((NULL == pstrFolder))
	{
		return FALSE;
	}

	/*检查输入目录是否是合法目录*/
	if (!IsDirectory(pstrFolder))
	{
		return FALSE;
	}

	/*创建源目录中查找文件的通配符*/
	CString strWildcard(pstrFolder);
	if (strWildcard.Right(1) != _T('\\'))
	{
		strWildcard += _T("\\");
	}
	strWildcard += _T("*.*");

	/*打开文件查找，查看源目录中是否存在匹配的文件*/
	/*调用FindFile后，必须调用FindNextFile才能获得查找文件的信息*/
	CFileFind finder;
	BOOL bWorking = finder.FindFile(strWildcard);

	while (bWorking)
	{
		/*查找下一个文件*/
		bWorking = finder.FindNextFile();

		/*跳过当前目录“.”和上一级目录“..”*/
		if (finder.IsDots())
		{
			continue;
		}

		/*得到当前目录的子文件的路径*/
		CString strSubFile = finder.GetFilePath();

		/*判断当前文件是否是目录,*/
		/*如果是目录，递归调用删除目录,*/
		/*否则，直接删除文件*/
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

	/*关闭文件查找*/
	finder.Close();

	/*删除空目录*/
	return RemoveDirectory(pstrFolder);
}

/*通过调用ShFileOperation来实现整个目录的删除*/
/*只删除单个目录*/
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

	/*确保目录的路径以2个\0结尾*/
	TCHAR tczFolder[MAX_PATH+1];
	ZeroMemory(tczFolder, (MAX_PATH+1)*sizeof(TCHAR));
	_tcscpy(tczFolder, pstrFolder);
	tczFolder[iPathLen] = _T('\0');
	tczFolder[iPathLen+1] = _T('\0');

	SHFILEOPSTRUCT FileOp; 
	ZeroMemory(&FileOp, sizeof(SHFILEOPSTRUCT)); 
	FileOp.fFlags |= FOF_SILENT;		/*不显示进度*/
	FileOp.fFlags |= FOF_NOERRORUI;		/*不报告错误信息*/
	FileOp.fFlags |= FOF_NOCONFIRMATION;/*直接删除，不进行确认*/
	FileOp.hNameMappings = NULL;
	FileOp.hwnd = NULL;
	FileOp.lpszProgressTitle = NULL;
	FileOp.wFunc = FO_DELETE;
	FileOp.pFrom = tczFolder;			/*要删除的目录，必须以2个\0结尾*/
	FileOp.pTo = NULL; 

	/*根据传递的bAllowUndo参数确定是否删除到回收站*/
	if (bAllowUndo)
	{   
		FileOp.fFlags |= FOF_ALLOWUNDO; /*删除到回收站*/
	}  
	else  
	{   
		FileOp.fFlags &= ~FOF_ALLOWUNDO; /*直接删除，不放入回收站*/
	}
	
	/*删除目录*/
	if (0 == SHFileOperation(&FileOp))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


/*通过调用ShFileOperation来实现整个目录的复制*/
/*只复制单个目录*/
/*如果目标目录已存在，将把源目录作为目的目录的子目录*/
/*如果要实现完全覆盖，需要先删除目的目录*/
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

	/*确保源目录的路径以2个\0结尾*/
	TCHAR tczSrcFolder[MAX_PATH+1];
	ZeroMemory(tczSrcFolder, (MAX_PATH+1)*sizeof(TCHAR));
	_tcscpy(tczSrcFolder, pstrSrcFolder);
	tczSrcFolder[iSrcPathLen] = _T('\0');
	tczSrcFolder[iSrcPathLen+1] = _T('\0');

	/*确保目的目录的路径以2个\0结尾*/
	TCHAR tczDstFolder[MAX_PATH+1];
	ZeroMemory(tczDstFolder, (MAX_PATH+1)*sizeof(TCHAR));
	_tcscpy(tczDstFolder, pstrDstFolder);
	tczDstFolder[iDstPathLen] = _T('\0');
	tczDstFolder[iDstPathLen+1] = _T('\0');

	SHFILEOPSTRUCT FileOp; 
	ZeroMemory(&FileOp, sizeof(SHFILEOPSTRUCT)); 
	FileOp.fFlags |= FOF_SILENT;		/*不显示进度*/
	FileOp.fFlags |= FOF_NOERRORUI ;	/*不报告错误信息*/
	FileOp.fFlags |= FOF_NOCONFIRMATION;/*不进行确认*/
	FileOp.hNameMappings = NULL;
	FileOp.hwnd = NULL;
	FileOp.lpszProgressTitle = NULL;
	FileOp.wFunc = FO_COPY;
	FileOp.pFrom = tczSrcFolder;		/*源目录，必须以2个\0结尾*/
	FileOp.pTo = tczDstFolder;			/*目的目录，必须以2个\0结尾*/	

	/*复制目录*/
	if (0 == SHFileOperation(&FileOp))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}