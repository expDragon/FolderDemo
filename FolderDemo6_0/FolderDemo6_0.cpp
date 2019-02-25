// FolderDemo6_0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FolderDemo6_0.h"
#include "../FolderDemo/Folder.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	CString strAppFile(_T(""));
	GetModuleFileName(NULL,strAppFile.GetBuffer(MAX_PATH), MAX_PATH);
	strAppFile.ReleaseBuffer();
	int iSplitIdx = strAppFile.ReverseFind(_T('\\'));
	CString strAppFolder = strAppFile.Left(iSplitIdx + 1);

	CString strSrcFolder = strAppFolder + _T("Src");
	CString strDstFolder = strAppFolder + _T("Dst");

	cout<<"CFolder::CopyFolder"<<endl;
	if (CFolder::CopyFolder(strSrcFolder, strDstFolder))
	{
		cout<<"复制目录“"<<(const char*)strSrcFolder<<"”至“"<<(const char*)strDstFolder<<"”成功！"<<endl;
	}
	else
	{
		cout<<"复制目录“"<<(const char*)strSrcFolder<<"”至“"<<(const char*)strDstFolder<<"”失败！"<<endl;
	}
	cout<<endl;


	system("pause");
	
	cout<<"CFolder::DeleteFolder"<<endl;
	if (CFolder::DeleteFolder(strDstFolder))
	{
		cout<<"删除目录“"<<(const char*)strDstFolder<<"”成功！"<<endl;
	}
	else
	{
		cout<<"删除目录“"<<(const char*)strDstFolder<<"”失败！"<<endl;
	}
	cout<<endl;
	
	system("pause");

	cout<<"CFolder::SHCopyFolder"<<endl;
	if (CFolder::SHCopyFolder(strSrcFolder, strDstFolder))
	{
		cout<<"复制目录“"<<(const char*)strSrcFolder<<"”至“"<<(const char*)strDstFolder<<"”成功！"<<endl;
	}
	else
	{
		cout<<"复制目录“"<<(const char*)strSrcFolder<<"”至“"<<(const char*)strDstFolder<<"”失败！"<<endl;
	}
	cout<<endl;

	system("pause");

	cout<<"CFolder::SHDeleteFolder"<<endl;
	if (CFolder::SHDeleteFolder(strDstFolder, FALSE))
	{
		cout<<"删除目录“"<<(const char*)strDstFolder<<"”成功！"<<endl;
	}
	else
	{
		cout<<"删除目录“"<<(const char*)strDstFolder<<"”失败！"<<endl;
	}
	cout<<endl;

	return 0;
}


