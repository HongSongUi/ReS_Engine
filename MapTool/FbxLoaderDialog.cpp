// FbxLoaderDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "FbxLoaderDialog.h"


// FbxLoaderDialog 대화 상자

IMPLEMENT_DYNAMIC(FbxLoaderDialog, CDialogEx)

FbxLoaderDialog::FbxLoaderDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FbxLoader, pParent)
{

}

FbxLoaderDialog::~FbxLoaderDialog()
{
}

void FbxLoaderDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FbxLoaderDialog, CDialogEx)
END_MESSAGE_MAP()


// FbxLoaderDialog 메시지 처리기
