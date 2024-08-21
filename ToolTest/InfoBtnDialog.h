#pragma once


// InfoBtnDialog 대화 상자

class MapDialog;
class MngDialog;

class InfoBtnDialog : public CDialogEx
{
	DECLARE_DYNAMIC(InfoBtnDialog)

public:
	InfoBtnDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~InfoBtnDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_InfoBtnDlg };
#endif



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedShowinfobtn();

public:
	void ParentSetter(MapDialog* parent);
	void SelectSetter(MngDialog* select);

public:
	MapDialog* _parent;
	MngDialog* _selectShowDlg;

	bool _isShowInfo = false;
	bool _isSelectChange = false;
	
};
