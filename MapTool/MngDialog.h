#pragma once
#include "afxdialogex.h"


// MngDialog 대화 상자

class MngDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MngDialog)

public:
	MngDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MngDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MngDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
