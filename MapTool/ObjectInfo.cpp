// ObjectInfo.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "ObjectInfo.h"


// ObjectInfo 대화 상자

IMPLEMENT_DYNAMIC(ObjectInfo, CDialogEx)

ObjectInfo::ObjectInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ObjectInfo, pParent)
{

}

ObjectInfo::~ObjectInfo()
{
}

void ObjectInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ObjectInfo, CDialogEx)
END_MESSAGE_MAP()


// ObjectInfo 메시지 처리기
