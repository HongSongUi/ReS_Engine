// LoadSubTexture.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "LoadSubTexture.h"


// LoadSubTexture 대화 상자

IMPLEMENT_DYNAMIC(LoadSubTexture, CDialogEx)

LoadSubTexture::LoadSubTexture(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LoadSubTxt, pParent)
{

}

LoadSubTexture::~LoadSubTexture()
{
}

void LoadSubTexture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LoadSubTexture, CDialogEx)
END_MESSAGE_MAP()


// LoadSubTexture 메시지 처리기
