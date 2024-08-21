// InfoButton.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "InfoButton.h"


// InfoButton 대화 상자

IMPLEMENT_DYNAMIC(InfoButton, CDialogEx)

InfoButton::InfoButton(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_InfoBtnDlg, pParent)
{

}

InfoButton::~InfoButton()
{
}

void InfoButton::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InfoButton, CDialogEx)
END_MESSAGE_MAP()


// InfoButton 메시지 처리기
