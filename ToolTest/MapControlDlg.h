#pragma once


// MapControlDlg 대화 상자

class MapControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MapControlDlg)

public:
	MapControlDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MapControlDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MapControl };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMapup();
	afx_msg void OnBnClickedMapdown();
	afx_msg void OnBnClickedMapflat();
	afx_msg void OnNMCustomdrawToolstrength(NMHDR* pNMHDR, LRESULT* pResult);
public:

	CStatic _controlText;
	CSliderCtrl StrengthBar;
	CSliderCtrl RangeBar;
	CEdit StrengthText;
	CEdit RangeText;
	
	int _strength;
	int _range;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

public:
	void SetSldier();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeRangetext();
	afx_msg void OnEnChangeStrengthtext();
	afx_msg void OnBnClickedCanclectl();
};
