// CreateMap.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "CreateMap.h"


// CreateMap 대화 상자

IMPLEMENT_DYNAMIC(CreateMap, CDialogEx)

CreateMap::CreateMap(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CreateMap, pParent)
{

}

CreateMap::~CreateMap()
{
}

void CreateMap::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CreateMap, CDialogEx)
END_MESSAGE_MAP()


// CreateMap 메시지 처리기
