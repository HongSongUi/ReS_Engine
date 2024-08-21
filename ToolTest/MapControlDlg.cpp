// MapControlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ToolTest.h"
#include "MapControlDlg.h"
#include "afxdialogex.h"


// MapControlDlg 대화 상자

IMPLEMENT_DYNAMIC(MapControlDlg, CDialogEx)

MapControlDlg::MapControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MapControl, pParent)
{
	
}

MapControlDlg::~MapControlDlg()
{
}

void MapControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ControlStatus, _controlText);
	DDX_Control(pDX, IDC_ToolStrength, StrengthBar);
	DDX_Control(pDX, IDC_Range, RangeBar);
	DDX_Control(pDX, IDC_StrengthText, StrengthText);
	DDX_Control(pDX, IDC_RangeText, RangeText);
}


BEGIN_MESSAGE_MAP(MapControlDlg, CDialogEx)
	ON_BN_CLICKED(IDC_MapUp, &MapControlDlg::OnBnClickedMapup)
	ON_BN_CLICKED(IDC_MapDown, &MapControlDlg::OnBnClickedMapdown)
	ON_BN_CLICKED(IDC_MapFlat, &MapControlDlg::OnBnClickedMapflat)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ToolStrength, &MapControlDlg::OnNMCustomdrawToolstrength)
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_RangeText, &MapControlDlg::OnEnChangeRangetext)
	ON_EN_CHANGE(IDC_StrengthText, &MapControlDlg::OnEnChangeStrengthtext)
	ON_BN_CLICKED(IDC_CancleCtl, &MapControlDlg::OnBnClickedCanclectl)
END_MESSAGE_MAP()


// MapControlDlg 메시지 처리기




void MapControlDlg::OnBnClickedMapup()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();
	_controlText.SetWindowTextW(L"UP");

	App->_Sample.IsPicking = false;
	App->_Sample.IsMapUp = true;
	App->_Sample.IsMapDown = false;
	App->_Sample.IsMapFlat = false;
}


void MapControlDlg::OnBnClickedMapdown()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();
	_controlText.SetWindowTextW(L"DOWN");
	App->_Sample.IsPicking = false;
	App->_Sample.IsMapUp = false;
	App->_Sample.IsMapDown = true;
	App->_Sample.IsMapFlat = false;
}


void MapControlDlg::OnBnClickedMapflat()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();
	_controlText.SetWindowTextW(L"FLAT");
	App->_Sample.IsPicking = false;
	App->_Sample.IsMapUp = false;
	App->_Sample.IsMapDown = false;
	App->_Sample.IsMapFlat = true;
}


void MapControlDlg::OnNMCustomdrawToolstrength(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


int MapControlDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;


	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void MapControlDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void MapControlDlg::SetSldier()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();
	
	StrengthBar.SetRange(0, 10);
	StrengthBar.SetPos(10);
	StrengthBar.SetTicFreq(1);
	RangeBar.SetRange(0, 30);
	RangeBar.SetPos(10);
	RangeBar.SetTicFreq(5);
	_range = RangeBar.GetPos();
	App->_Sample.SetRange(_range);

	CString pos;
	pos.Format(_T("%d"), _range);
	RangeText.SetWindowTextW(pos);


	_strength = StrengthBar.GetPos();
	CString strengthPos;
	strengthPos.Format(_T("%d"), _strength);
	StrengthText.SetWindowTextW(strengthPos);
	App->_Sample.SetStrength(_strength);
}




void MapControlDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();

	if (IDC_Range == pScrollBar->GetDlgCtrlID())
	{
		_range = RangeBar.GetPos();
		App->_Sample.SetRange(_range);
		CString rangepos;
		rangepos.Format(_T("%d"), _range);
		RangeText.SetWindowTextW(rangepos);
	}
	else if (IDC_ToolStrength == pScrollBar->GetDlgCtrlID())
	{
		_strength = StrengthBar.GetPos();
		CString strengthPos;
		strengthPos.Format(_T("%d"), _strength);
		StrengthText.SetWindowTextW(strengthPos);
		App->_Sample.SetStrength(_strength);
	}
}


void MapControlDlg::OnEnChangeRangetext()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	CString Pos;
	RangeText.GetWindowTextW(Pos);
	int posValue = _ttoi(Pos);

	RangeBar.SetPos(posValue);
	
}


void MapControlDlg::OnEnChangeStrengthtext()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	CString Pos;
	StrengthText.GetWindowTextW(Pos);
	int posValue = _ttoi(Pos);

	StrengthBar.SetPos(posValue);
}


void MapControlDlg::OnBnClickedCanclectl()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();
	_controlText.SetWindowTextW(L" ");
	App->_Sample.IsPicking = false;
	App->_Sample.IsMapUp = false;
	App->_Sample.IsMapDown = false;
	App->_Sample.IsMapFlat = false;
}
