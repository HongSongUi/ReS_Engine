// MngDialog.cpp: 구현 파일
//

#include "pch.h"
#include "ToolTest.h"
#include "MngDialog.h"
#include "afxdialogex.h"

#include "MapDialog.h"

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
	ON_BN_CLICKED(IDC_LoadFbx, &MngDialog::OnBnClickedLoadfbx)
	ON_BN_CLICKED(IDC_ADD, &MngDialog::OnBnClickedAdd)
	ON_WM_PARENTNOTIFY()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// MngDialog 메시지 처리기


void MngDialog::OnBnClickedLoadfbx()
{
	_showFbxLoader = true;
	_showCreateMap = false;

	_parent->HideInfo();
	_parent->ShowInfoBtn();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void MngDialog::OnBnClickedAdd()
{
	_showCreateMap = true;
	_showFbxLoader = false;


	_parent->HideInfo();
	_parent->ShowInfoBtn();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}




int MngDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	

	return 0;
}



void MngDialog::ParentSetter(MapDialog* parent)
{
	_parent = parent;
}

