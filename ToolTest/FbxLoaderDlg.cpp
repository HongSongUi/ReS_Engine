// FbxLoaderDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ToolTest.h"
#include "FbxLoaderDlg.h"
#include "afxdialogex.h"


// FbxLoaderDlg 대화 상자

IMPLEMENT_DYNAMIC(FbxLoaderDlg, CDialogEx)

FbxLoaderDlg::FbxLoaderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FbxLoader, pParent)
{

}

FbxLoaderDlg::~FbxLoaderDlg()
{
}

void FbxLoaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FbxList, _fbxListBox);
	DDX_Control(pDX, IDC_ObjectName, _objectNameText);
	DDX_Control(pDX, IDC_PickState, _pickState);
}


BEGIN_MESSAGE_MAP(FbxLoaderDlg, CDialogEx)
	ON_BN_CLICKED(IDC_FbxButton, &FbxLoaderDlg::OnBnClickedFbxbutton)
	ON_BN_CLICKED(IDC_Picking, &FbxLoaderDlg::OnBnClickedPicking)
	ON_LBN_SELCHANGE(IDC_FbxList, &FbxLoaderDlg::OnLbnSelchangeFbxlist)
END_MESSAGE_MAP()


// FbxLoaderDlg 메시지 처리기


void FbxLoaderDlg::OnBnClickedFbxbutton()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();

	if (App->_Sample.IsCreatMap == false)
	{
		AfxMessageBox(_T("맵을 먼저 생성해주시기 바랍니다!"), MB_ICONSTOP);
		return;
	}
	static TCHAR BASED_CODE filter[] = _T("오브젝트 파일(*.fbx)|*FBX;*.fbx | 모든파일(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("*fbx"), _T("object"), OFN_HIDEREADONLY, filter);
	dlg.m_ofn.lpstrInitialDir = _T("C:\\Users\\kgca4109\\source\\repos\\fbx");
	int ret = dlg.DoModal();

	if (ret == IDOK)
	{
		_fbxFileName =  dlg.GetPathName();
		_fbxFileName = GetSplitName(_fbxFileName);
		if (App->_Sample.FbxLoader(_fbxFileName))
		{
			_fbxListBox.AddString(_fbxFileName.c_str());
		}
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

std::wstring FbxLoaderDlg::GetSplitName(std::wstring path)
{
	std::wstring name;
	TCHAR drive[MAX_PATH] = { 0, };
	TCHAR dir[MAX_PATH] = { 0, };
	TCHAR filename[MAX_PATH] = { 0, };
	TCHAR ext[MAX_PATH] = { 0, };
	_tsplitpath_s(path.c_str(), drive, dir, filename, ext);

	name = filename;
	name += ext;

	return name;
}


void FbxLoaderDlg::OnBnClickedPicking()
{
	if (_selectedFbxName == L"")
	{
		AfxMessageBox(_T("선택된 오브젝트가 없습니다!"), MB_ICONSTOP);
		return;
	}

	CToolTestApp* App = (CToolTestApp*)AfxGetApp();
	_mousePicking = !_mousePicking;
	if (_mousePicking)
	{
		_pickState.SetWindowTextW(L"on");
	}
	else
	{
		_pickState.SetWindowTextW(L"off");
	}
	App->_Sample.IsPicking = _mousePicking;
}


void FbxLoaderDlg::OnLbnSelchangeFbxlist()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();

	int index = 0;
	CString fbxName;
	index = _fbxListBox.GetCurSel();
	if (index != LB_ERR)
	{
		_fbxListBox.GetText(index, fbxName);
		_selectedFbxName = fbxName;
		_objectNameText.SetWindowTextW(fbxName);
		App->_Sample.SetSelectedObj(_selectedFbxName);
	}
}


