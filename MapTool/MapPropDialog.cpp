// MapPropDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "MapPropDialog.h"


// MapPropDialog 대화 상자

IMPLEMENT_DYNAMIC(MapPropDialog, CDialogEx)

MapPropDialog::MapPropDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MapProp, pParent)
{

}

MapPropDialog::~MapPropDialog()
{
}

void MapPropDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MapPropDialog, CDialogEx)
END_MESSAGE_MAP()


// MapPropDialog 메시지 처리기
