// MapInfo.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "MapInfo.h"


// MapInfo 대화 상자

IMPLEMENT_DYNAMIC(MapInfo, CDialogEx)

MapInfo::MapInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Create, pParent)
{

}

MapInfo::~MapInfo()
{
}

void MapInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MapInfo, CDialogEx)
END_MESSAGE_MAP()


// MapInfo 메시지 처리기
