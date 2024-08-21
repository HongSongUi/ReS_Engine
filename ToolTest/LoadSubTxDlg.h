#pragma once


// LoadSubTxDlg 대화 상자

class LoadSubTxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LoadSubTxDlg)

public:
	LoadSubTxDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LoadSubTxDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LoadSubTxt };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoadsubtx();
	afx_msg void OnBnClickedSelectbtn();
	afx_msg void OnLbnSelchangeSubtxlist();
public:
	CStatic _textureName;
	CListBox _textureListBox;

	std::wstring _subTexture;
	std::wstring _Texture;
	W_STR _selectedTextureName;
	afx_msg void OnBnClickedCancle();
};
