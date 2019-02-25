#pragma once
class CFolder
{
public:
	CFolder(void);
	virtual ~CFolder(void);

public:

	/*判断一个路径是否是已存在的目录*/
	static BOOL IsDirectory(LPCTSTR pstrPath);

	/*复制目录中的所有内容*/
	static BOOL CopyFolder(LPCTSTR pstrSrcFolder, LPCTSTR pstrDstFolder);

	/*删除目录及目录中的所有内容*/
	static BOOL DeleteFolder(LPCTSTR pstrFolder);

	/*通过调用ShFileOperation来实现整个目录的删除*/
	static BOOL SHDeleteFolder(LPCTSTR pstrFolder, BOOL bAllowUndo);

	/*通过调用ShFileOperation来实现整个目录的复制*/
	static BOOL SHCopyFolder(LPCTSTR pstrSrcFolder, LPCTSTR pstrDstFolder);
};

