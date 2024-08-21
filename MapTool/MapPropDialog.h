#pragma once
#include "afxdialogex.h"


// MapPropDialog 대화 상자

class MapPropDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MapPropDialog)

public:
	MapPropDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MapPropDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MapProp };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
