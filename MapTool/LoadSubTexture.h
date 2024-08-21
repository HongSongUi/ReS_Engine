#pragma once
#include "afxdialogex.h"


// LoadSubTexture 대화 상자

class LoadSubTexture : public CDialogEx
{
	DECLARE_DYNAMIC(LoadSubTexture)

public:
	LoadSubTexture(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LoadSubTexture();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LoadSubTxt };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
