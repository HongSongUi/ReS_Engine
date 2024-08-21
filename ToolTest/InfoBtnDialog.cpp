// InfoBtnDialog.cpp: 구현 파일
//

#include "pch.h"
#include "ToolTest.h"
#include "InfoBtnDialog.h"
#include "afxdialogex.h"
#include "MapDialog.h"

// InfoBtnDialog 대화 상자

IMPLEMENT_DYNAMIC(InfoBtnDialog, CDialogEx)

InfoBtnDialog::InfoBtnDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_InfoBtnDlg, pParent)
{

}

InfoBtnDialog::~InfoBtnDialog()
{
}

void InfoBtnDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void InfoBtnDialog::ParentSetter(MapDialog* parent)
{
	_parent = parent;
}

void InfoBtnDialog::SelectSetter(MngDialog* select)
{
	_selectShowDlg = select;
}


BEGIN_MESSAGE_MAP(InfoBtnDialog, CDialogEx)
	ON_BN_CLICKED(IDC_ShowInfoBtn, &InfoBtnDialog::OnBnClickedShowinfobtn)
END_MESSAGE_MAP()


// InfoBtnDialog 메시지 처리기


void InfoBtnDialog::OnBnClickedShowinfobtn()
{
	_isShowInfo = !_isShowInfo;
	if (_isShowInfo) {
		if (_selectShowDlg->_showCreateMap)
		{
			_parent->ShowMapInfo();
		}
		else if (_selectShowDlg->_showFbxLoader)
		{
			_parent->ShowFbxInfo();
		}
	}
	else
	{
		_parent->HideInfo();
	}
	

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
