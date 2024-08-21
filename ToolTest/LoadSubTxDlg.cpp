// LoadSubTxDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ToolTest.h"
#include "LoadSubTxDlg.h"
#include "afxdialogex.h"


// LoadSubTxDlg 대화 상자

IMPLEMENT_DYNAMIC(LoadSubTxDlg, CDialogEx)

LoadSubTxDlg::LoadSubTxDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LoadSubTxt, pParent)
{

}

LoadSubTxDlg::~LoadSubTxDlg()
{
}

void LoadSubTxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SeletedSubTx, _textureName);
	DDX_Control(pDX, IDC_SubTxList, _textureListBox);
}


BEGIN_MESSAGE_MAP(LoadSubTxDlg, CDialogEx)
	ON_BN_CLICKED(IDC_LoadSubTx, &LoadSubTxDlg::OnBnClickedLoadsubtx)
	ON_BN_CLICKED(IDC_SelectBtn, &LoadSubTxDlg::OnBnClickedSelectbtn)
	ON_LBN_SELCHANGE(IDC_SubTxList, &LoadSubTxDlg::OnLbnSelchangeSubtxlist)
	ON_BN_CLICKED(IDC_Cancle, &LoadSubTxDlg::OnBnClickedCancle)
END_MESSAGE_MAP()


// LoadSubTxDlg 메시지 처리기


void LoadSubTxDlg::OnBnClickedLoadsubtx()
{
	static TCHAR BASED_CODE filter[] = _T("이미지 파일(*.BMP, *GIF, *JPG) | *BMP, *GIF;*JPG;*bmp;*jpg;*gif| 모든파일(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, filter);
	dlg.m_ofn.lpstrInitialDir = _T("C:\\Users\\kgca4109\\source\\repos\\data\\map");
	int ret = dlg.DoModal();
	if (ret == IDOK)
	{
		CToolTestApp* App = (CToolTestApp*)AfxGetApp();

		_Texture = dlg.GetPathName();
		_Texture = TextureMgr.GetSplitName(_Texture);
		_textureListBox.AddString(_Texture.c_str());
		App->_Sample.AddMapSubTexture(_Texture);

	}
	


	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void LoadSubTxDlg::OnBnClickedSelectbtn()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();

	App->_Sample.IsMapSplatting = true;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void LoadSubTxDlg::OnLbnSelchangeSubtxlist()
{
	int index = 0;
	CString textureName;
	index = _textureListBox.GetCurSel();
	if (index != LB_ERR)
	{
		CToolTestApp* App = (CToolTestApp*)AfxGetApp();

		App->_Sample.SubTextureIndex = index;

		_textureListBox.GetText(index, textureName);
		_selectedTextureName = textureName;
		_textureName.SetWindowTextW(textureName);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void LoadSubTxDlg::OnBnClickedCancle()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();

	App->_Sample.IsMapSplatting = false;
}
