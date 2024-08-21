// MapControlDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "MapControlDialog.h"


// MapControlDialog 대화 상자

IMPLEMENT_DYNAMIC(MapControlDialog, CDialogEx)

MapControlDialog::MapControlDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MapControl, pParent)
{

}

MapControlDialog::~MapControlDialog()
{
}

void MapControlDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MapControlDialog, CDialogEx)
END_MESSAGE_MAP()


// MapControlDialog 메시지 처리기
