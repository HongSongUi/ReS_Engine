// CreateMap.cpp: 구현 파일
//

#include "pch.h"
#include "ToolTest.h"
#include "CreateMap.h"
#include "afxdialogex.h"
#include "TextureManager.h"
#include <cmath>
// CreateMap 대화 상자

IMPLEMENT_DYNAMIC(CreateMap, CDialogEx)

CreateMap::CreateMap(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CreateMap, pParent)
	, _MapWidth(_T(""))
	, _MapHeight(_T(""))
	, _MapTexture(_T(""))
	, _MapCellDis(_T(""))
{

}

CreateMap::~CreateMap()
{
}

void CreateMap::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MapWidth, _MapWidth);
	DDX_Text(pDX, IDC_MapHeight, _MapHeight);
	DDX_Text(pDX, IDC_TextureName, _MapTexture);

	DDX_Control(pDX, IDC_CellCombo, _cellCombo);
}


BEGIN_MESSAGE_MAP(CreateMap, CDialogEx)
	ON_BN_CLICKED(IDOK, &CreateMap::OnBnClickedOk)

	ON_BN_CLICKED(IDC_LoadFile, &CreateMap::OnBnClickedLoadfile)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SpinMapW, &CreateMap::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINMapH, &CreateMap::OnDeltaposSpinmaph)
END_MESSAGE_MAP()


// CreateMap 메시지 처리기


BOOL CreateMap::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	_MapWidth = L"";
	_MapHeight = L"";
	_MapCellDis = L"1";
	_MapTexture = L"";
	_cellCombo.AddString(L"1");
	_cellCombo.AddString(L"2");
	_cellCombo.AddString(L"4");
	_cellCombo.AddString(L"8");
	_cellCombo.AddString(L"16");
	_cellCombo.AddString(L"32");
	_cellCombo.SetCurSel(0);
	UpdateData(FALSE);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CreateMap::OnBnClickedOk()
{
	UpdateData(TRUE);
	_cellCombo.GetLBText(_cellCombo.GetCurSel(), _MapCellDis);
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();
	UINT MapW = _ttoi(_MapWidth);
	UINT MapH = _ttoi(_MapHeight);
	UINT CellDis = _ttoi(_MapCellDis);
	std::wstring Texture = _MapTexture;

	if (AfxMessageBox(_T("맵을 설정하시겠습니까?"), MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{
		if (_MapWidth == "" || _MapHeight == "" ||_MapTexture=="") {
			AfxMessageBox(_T("비어있는 칸이 있습니다."), MB_ICONSTOP);
		}
		else {
			_MapTexture = _DefaultPath + _MapTexture;
			App->_Sample.SetMapSize(MapW, MapH, CellDis);
			App->_Sample.SetMapTexture(_MapTexture.operator LPCWSTR());
			App->_Sample.CreateMap();
			CDialogEx::OnOK();
		}
	}
	else {
		AfxMessageBox(_T("취소"));
		CDialogEx::OnOK();

	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
}

void CreateMap::OnBnClickedLoadfile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static TCHAR BASED_CODE filter[] = _T("이미지 파일(*.BMP, *GIF, *JPG) | *BMP, *GIF;*JPG;*bmp;*jpg;*gif| 모든파일(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, filter);
	dlg.DoModal();
	_Texture = dlg.GetPathName();
	_Texture = TextureMgr.GetSplitName(_Texture);
	SetDlgItemText(IDC_TextureName, _Texture.c_str());
	
}

void CreateMap::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	if (pNMUpDown->iDelta < 0) {
		_lCount++;
	}
	else {
		_lCount--;
	}
	_mapWidth = pow(2,_lCount);
	
	SetDlgItemInt(IDC_MapWidth, _mapWidth);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CreateMap::OnDeltaposSpinmaph(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	if (pNMUpDown->iDelta < 0) {
		_rCount++;
	}
	else {
		_rCount--;
	}
	_mapHeight = pow(2, _rCount);
	SetDlgItemInt(IDC_MapHeight, _mapHeight);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
