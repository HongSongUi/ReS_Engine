// CreateMapPan.cpp: 구현 파일
//

#include "pch.h"
#include "ToolTest.h"
#include "CreateMapPan.h"
#include "afxdialogex.h"
#include <atlimage.h>
#include <string>

// CreateMapPan 대화 상자



IMPLEMENT_DYNAMIC(CreateMapPan, CDialogEx)

CreateMapPan::CreateMapPan(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Create, pParent)
{
	_mapSize.reserve(8);
	_cellDistList.reserve(2);
}

CreateMapPan::~CreateMapPan()
{
}

void CreateMapPan::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MapCell, _cellDisCom);
	DDX_Control(pDX, IDC_TextureFileName, _mapTextureName);
	DDX_Control(pDX, IDC_TexImg, _textureImg);
	DDX_Control(pDX, IDC_MapSize, _mapSizeList);
	DDX_Control(pDX, IDC_WireFrame, Check);
}


BEGIN_MESSAGE_MAP(CreateMapPan, CDialogEx)
	ON_BN_CLICKED(IDC_TextureLoad, &CreateMapPan::OnBnClickedTextureload)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_MapSize, &CreateMapPan::OnCbnSelchangeMapsize)
	ON_CBN_SELCHANGE(IDC_MapCell, &CreateMapPan::OnCbnSelchangeMapcell)

	ON_BN_CLICKED(IDC_WireFrame, &CreateMapPan::OnBnClickedWireframe)
	ON_BN_CLICKED(ID_Create, &CreateMapPan::OnBnClickedCreate)
END_MESSAGE_MAP()


// CreateMapPan 메시지 처리기


BOOL CreateMapPan::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return 0;
}

void CreateMapPan::OnBnClickedTextureload()
{
	static TCHAR BASED_CODE filter[] = _T("이미지 파일(*.BMP, *GIF, *JPG) | *BMP, *GIF;*JPG;*bmp;*jpg;*gif| 모든파일(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, filter);
	dlg.m_ofn.lpstrInitialDir = _T("C:\\Users\\kgca4109\\source\\repos\\data\\map");
	dlg.DoModal();
	_Texture = dlg.GetPathName();
	_Texture = TextureMgr.GetSplitName(_Texture);

	if (_Texture == L"image")
	{
		_Texture = L"No Image";
	}
	
	SetDlgItemText(IDC_TextureFileName, _Texture.c_str());
	
	_mapTexture = _defaultPath + _Texture;
	
	CImage img;
	
	HRESULT hr = img.Load(_mapTexture.c_str());
	CRect ImgRect;
	GetDlgItem(IDC_TexImg)->GetWindowRect(&ImgRect);
	ScreenToClient(ImgRect);
	CDC* dc;
	dc = _textureImg.GetDC();
	dc->SetStretchBltMode(COLORONCOLOR);

	if (hr == S_OK) 
	{
		_prevTexture = _Texture;
		_prevMapTexture = _mapTexture;
		img.StretchBlt(dc->m_hDC, 0, 0, ImgRect.Width(), ImgRect.Height(), SRCCOPY);
	}
	else 
	{
		if (_prevMapTexture != L"")
		{
			SetDlgItemText(IDC_TextureFileName, _prevTexture.c_str());
			hr = img.Load(_prevMapTexture.c_str());
			img.StretchBlt(dc->m_hDC, 0, 0, ImgRect.Width(), ImgRect.Height(), SRCCOPY);
			_mapTexture = _defaultPath + _prevMapTexture;
		}
	}
	ReleaseDC(dc);
}

int CreateMapPan::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;


	
	
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	
	return 0;
}


void CreateMapPan::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == true&& _setComboList == false)
	{
		for (int cell = 0; cell < 2; cell++) 
		{
			int cellDis = pow(2, cell);
			std::wstring dis = std::to_wstring(cellDis);
			_cellDisCom.AddString(dis.c_str());
			_cellDistList.push_back(cellDis);
		}
		for (int height = 0;  height < 8; height++)
		{
			int mapSz = pow(2, height);
			_mapSize.push_back(mapSz);
			std::wstring he = std::to_wstring(mapSz);
			he += L" ";
			he += L"X";
			he += L" ";
			he += std::to_wstring(mapSz);
			_mapSizeList.AddString(he.c_str());
		}

		_mapSizeList.SetCurSel(4);
		_cellDisCom.SetCurSel(0);

		int mapIndex = _mapSizeList.GetCurSel();
		int cellIndex = _cellDisCom.GetCurSel();

		_mapHeightData = _mapSize[mapIndex];
		_mapWidthData = _mapSize[mapIndex];
		_mapCellData = _cellDistList[cellIndex];

		_setComboList = true;
	}

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}





void CreateMapPan::OnCbnSelchangeMapsize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = _mapSizeList.GetCurSel();

	_mapHeightData = _mapSize[index];
	_mapWidthData = _mapSize[index];
}


void CreateMapPan::OnCbnSelchangeMapcell()
{

	int index = _cellDisCom.GetCurSel();

	_mapCellData = _cellDistList[index];

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CreateMapPan::OnBnClickedWireframe()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	_isChecked = Check.GetCheck();
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();
	App->_Sample.SetWireFrame(_isChecked);
}



void CreateMapPan::OnBnClickedCreate()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();
	App->_Sample.SetMapSize(_mapWidthData, _mapHeightData, _mapCellData);
	App->_Sample.SetMapTexture(_mapTexture);
	App->_Sample.CreateMap();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
