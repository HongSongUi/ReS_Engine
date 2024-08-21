#pragma once
#include "afxdialogex.h"


// FbxLoaderDialog 대화 상자

class FbxLoaderDialog : public CDialogEx
{
	DECLARE_DYNAMIC(FbxLoaderDialog)

public:
	FbxLoaderDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~FbxLoaderDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FbxLoader };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
