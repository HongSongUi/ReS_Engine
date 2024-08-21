#pragma once
#include "afxdialogex.h"


// MapInfo 대화 상자

class MapInfo : public CDialogEx
{
	DECLARE_DYNAMIC(MapInfo)

public:
	MapInfo(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MapInfo();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Create };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
