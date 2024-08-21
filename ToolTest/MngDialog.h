#pragma once


// MngDialog 대화 상자
#include "CreateMapPan.h"
#include "FbxLoaderDlg.h"

class MapDialog;

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
	
public:
	afx_msg void OnBnClickedLoadfbx();
	afx_msg void OnBnClickedAdd();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:
	bool _showFbxLoader = false;
	bool _showCreateMap = false;
	bool _showSubTxDlg = false;
	bool _selectChange = false;

public:
	CreateMapPan _createMapPan;
	FbxLoaderDlg _fbxLoaderPan;
	MapDialog* _parent;
	
public:

	void ParentSetter(MapDialog* parent);

};
