// MngDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "MngDialog.h"


// MngDialog 대화 상자

IMPLEMENT_DYNAMIC(MngDialog, CDialogEx)

MngDialog::MngDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MngDialog, pParent)
{

}

MngDialog::~MngDialog()
{
}

void MngDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MngDialog, CDialogEx)
END_MESSAGE_MAP()


// MngDialog 메시지 처리기
