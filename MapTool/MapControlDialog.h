#pragma once
#include "afxdialogex.h"


// MapControlDialog 대화 상자

class MapControlDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MapControlDialog)

public:
	MapControlDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MapControlDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MapControl };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
