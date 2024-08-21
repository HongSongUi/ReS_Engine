#pragma once


// CreateMap 대화 상자

class CreateMap : public CDialogEx
{
	DECLARE_DYNAMIC(CreateMap)

public:
	CreateMap(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CreateMap();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CreateMap };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString _MapWidth;
	CString _MapHeight;
	CString _MapTexture;
	CString _MapCellDis;
	CString _DefaultPath = L"../../data/map/";
	CComboBox _cellCombo;

	std::wstring _Texture;
	int _lCount = 0;
	int _rCount = 0;
	int _mapWidth = 0;
	int _mapHeight = 0;
	int _lNum = 0;
	int _rNum = 0;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedLoadfile();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinmaph(NMHDR* pNMHDR, LRESULT* pResult);
};
