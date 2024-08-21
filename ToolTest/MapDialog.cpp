// MapDialog.cpp: 구현 파일
//

#include "pch.h"
#include "ToolTest.h"
#include "MapDialog.h"
#include "afxdialogex.h"

// MapDialog 대화 상자

IMPLEMENT_DYNAMIC(MapDialog, CDialogEx)

MapDialog::MapDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MapProp, pParent)
{

}

MapDialog::~MapDialog()
{
}

void MapDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ChildDialog, Child);
	DDX_Control(pDX, IDC_MapInfo, _mapInfo);
	DDX_Control(pDX, IDC_InfoBtn, _showInfo);
}


BEGIN_MESSAGE_MAP(MapDialog, CDialogEx)
	ON_BN_CLICKED(IDC_Manage, &MapDialog::OnBnClickedManage)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_Modify, &MapDialog::OnBnClickedModify)
	ON_BN_CLICKED(IDC_Paint, &MapDialog::OnBnClickedPaint)
	ON_BN_CLICKED(IDC_SaveBtn, &MapDialog::OnBnClickedSavebtn)
END_MESSAGE_MAP()


// MapDialog 메시지 처리기

void MapDialog::OnBnClickedManage()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();

	App->_Sample.IsMapUp = false;
	App->_Sample.IsMapDown = false;
	App->_Sample.IsMapFlat = false;

	GetDlgItem(IDC_ChildDialog)->GetWindowRect(&ChildDialogRect);
	GetDlgItem(IDC_MapInfo)->GetWindowRect(&_infoDlgRect);
	GetDlgItem(IDC_InfoBtn)->GetWindowRect(&_showInfoBtnRect);

	ScreenToClient(ChildDialogRect);
	ScreenToClient(_infoDlgRect);
	ScreenToClient(_showInfoBtnRect);

	_ChildMngDialog.ShowWindow(SW_SHOW);
	_ChildMngDialog.MoveWindow(ChildDialogRect);

	_mapControlDialog.ShowWindow(SW_HIDE);
	_SubTxDialog.ShowWindow(SW_HIDE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

int MapDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	_ChildMngDialog.ParentSetter(this);
	_infoBtnDialog.ParentSetter(this);
	_infoBtnDialog.SelectSetter(&_ChildMngDialog);

	_ChildMngDialog.Create(IDD_MngDialog, this);
	_mapInfoDialog.Create(IDD_Create, this);
	_fbxLoaderDialog.Create(IDD_FbxLoader, this);
	_infoBtnDialog.Create(IDD_InfoBtnDlg, this);
	_mapControlDialog.Create(IDD_MapControl, this);
	_SubTxDialog.Create(IDD_LoadSubTxt, this);
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}

void MapDialog::ShowMapInfo()
{
	_fbxLoaderDialog.ShowWindow(SW_HIDE);
	_SubTxDialog.ShowWindow(SW_HIDE);
	_mapInfoDialog.ShowWindow(SW_SHOW);
	_mapInfoDialog.MoveWindow(_infoDlgRect);
}

void MapDialog::ShowFbxInfo()
{
	_mapInfoDialog.ShowWindow(SW_HIDE);
	_SubTxDialog.ShowWindow(SW_HIDE);
	_fbxLoaderDialog.ShowWindow(SW_SHOW);
	_fbxLoaderDialog.MoveWindow(_infoDlgRect);
}

void MapDialog::ShowInfoBtn()
{
	_infoBtnDialog.ShowWindow(SW_SHOW);
	_infoBtnDialog.MoveWindow(_showInfoBtnRect);
	_infoBtnDialog._isShowInfo = false;
}

void MapDialog::HideInfo()
{
	_fbxLoaderDialog.ShowWindow(SW_HIDE);
	_mapInfoDialog.ShowWindow(SW_HIDE);
	
}


void MapDialog::OnBnClickedModify()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();

	if (App->_Sample.IsCreatMap == false)
	{
		AfxMessageBox(_T("맵을 먼저 생성해주시기 바랍니다!"), MB_ICONSTOP);
		return;
	}

	GetDlgItem(IDC_MapInfo)->GetWindowRect(&_infoDlgRect);

	ScreenToClient(_infoDlgRect);

	_fbxLoaderDialog._mousePicking = false;
	_fbxLoaderDialog.ShowWindow(SW_HIDE);
	_mapInfoDialog.ShowWindow(SW_HIDE);
	_ChildMngDialog.ShowWindow(SW_HIDE);
	_infoBtnDialog.ShowWindow(SW_HIDE);
	_SubTxDialog.ShowWindow(SW_HIDE);

	_mapControlDialog.ShowWindow(SW_SHOW);
	_mapControlDialog.MoveWindow(_infoDlgRect);
	_mapControlDialog.SetSldier();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void MapDialog::OnBnClickedPaint()
{
	GetDlgItem(IDC_MapInfo)->GetWindowRect(&_infoDlgRect);

	ScreenToClient(_infoDlgRect);

	_fbxLoaderDialog._mousePicking = false;
	_fbxLoaderDialog.ShowWindow(SW_HIDE);
	_mapInfoDialog.ShowWindow(SW_HIDE);
	_ChildMngDialog.ShowWindow(SW_HIDE);
	_infoBtnDialog.ShowWindow(SW_HIDE);
	_mapControlDialog.ShowWindow(SW_HIDE);

	_SubTxDialog.ShowWindow(SW_SHOW);
	_SubTxDialog.MoveWindow(_infoDlgRect);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void MapDialog::OnBnClickedSavebtn()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();
	if (App->_Sample.IsCreatMap == false)
	{
		AfxMessageBox(_T("맵을 먼저 생성해주시기 바랍니다!"), MB_ICONSTOP);
		return;
	}
	App->_Sample.SaveMap();
}
