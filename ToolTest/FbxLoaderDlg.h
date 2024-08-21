#pragma once

#include <map>
#include <vector>
#include <algorithm>
#include "FbxSceneLoader.h"
// FbxLoaderDlg 대화 상자

class FbxLoaderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FbxLoaderDlg)

public:
	FbxLoaderDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~FbxLoaderDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FbxLoader };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg void OnBnClickedFbxbutton();

	DECLARE_MESSAGE_MAP()
public:
	CString _selectedObjName;
	CStatic _objectNameText;
	CListBox _fbxListBox;
	CStatic _pickState;

	W_STR _fbxFileName;
	W_STR _fbxFilePath;
	W_STR _selectedFbxName;


	bool _mousePicking = false;
public:

	std::wstring GetSplitName(std::wstring path);
	afx_msg void OnBnClickedPicking();
	afx_msg void OnLbnSelchangeFbxlist();
	
	
};
