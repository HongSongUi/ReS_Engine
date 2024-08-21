#pragma once

#include <iostream>
#include <vector>
// CreateMapPan 대화 상자

class CreateMapPan : public CDialogEx
{
	DECLARE_DYNAMIC(CreateMapPan)

public:
	CreateMapPan(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CreateMapPan();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Create };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CString _mapWidth;
	CString _mapHeight;
	CString _mapCellDistance;

	std::wstring _mapTexture;
	std::wstring _prevMapTexture;
	std::wstring _defaultPath = L"../../data/map/";
	std::wstring _Texture;
	std::wstring _prevTexture;

	CComboBox _cellDisCom;
	CComboBox _mapSizeList;

	CStatic _mapTextureName;

	CStatic _textureImg;

	CImage prevImg;

	CButton Check;

	UINT _mapHeightData;
	UINT _mapWidthData;
	float _mapCellData;

	std::vector<int> _mapSize;
	std::vector<float> _cellDistList;
	bool _isChecked = false;
	bool _setComboList = false;

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedTextureload();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCbnSelchangeMapsize();
	afx_msg void OnCbnSelchangeMapcell();
	afx_msg void OnBnClickedWireframe();
	
public:
	afx_msg void OnBnClickedCreate();
};
