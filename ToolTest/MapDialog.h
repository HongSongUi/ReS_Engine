#pragma once


// MapDialog 대화 상자

#include "MngDialog.h"
#include "CreateMapPan.h"
#include "FbxLoaderDlg.h"
#include "InfoBtnDialog.h"
#include "MapControlDlg.h"
#include "LoadSubTxDlg.h"

class MapDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MapDialog)
public:
	MapDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MapDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MapProp };
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	MngDialog		_ChildMngDialog;
	CreateMapPan	_mapInfoDialog;
	FbxLoaderDlg	_fbxLoaderDialog;
	InfoBtnDialog	_infoBtnDialog;
	MapControlDlg	_mapControlDialog;
	LoadSubTxDlg	_SubTxDialog;

	CStatic Child;
	CRect ChildDialogRect;
	CRect _showInfoBtnRect;
	CRect _infoDlgRect;

	CStatic _showInfo;
	CStatic CreateInfo;
	CStatic _mapInfo;

	afx_msg void OnBnClickedManage();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:

	bool _isShowDlg = false;


	void ShowMapInfo();
	void ShowFbxInfo();
	void ShowInfoBtn();
	void HideInfo();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedPaint();
	afx_msg void OnBnClickedSavebtn();
};
