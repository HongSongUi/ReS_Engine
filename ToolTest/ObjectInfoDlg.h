#pragma once


// ObjectInfoDlg 대화 상자

class ObjectInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ObjectInfoDlg)

public:
	ObjectInfoDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ObjectInfoDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ObjectInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedObjectpickingbtn();
public:
	bool _objPicking = false;
	CStatic _objectPickingText;
	CStatic _selectedObjText;

	void SetObjNameText(W_STR objName);

	CEdit _objectXPos;
	CEdit _objectYPos;
	CEdit _objectZPos;

	CEdit _xScale;
	CEdit _yScale;
	CEdit _zScale;

	CEdit _xRotText;
	CEdit _yRotText;
	CEdit _zRotText;

	CString xPos;
	CString yPos;
	CString zPos;

	CString xScale;
	CString yScale;
	CString zScale;
	
	CString _pitchText;
	CString _yawText;
	CString _rollText;

	float _Posx;
	float _Posy;
	float _Posz;

	float _Scalex;
	float _Scaley;
	float _Scalez;
	
	float _pitch;
	float _yaw;
	float _roll;

public:
	afx_msg void OnBnClickedPosbtn();
	afx_msg void OnBnClickedScalebtn();
	afx_msg void OnBnClickedRotbtn();
	afx_msg void OnEnChangeXpos();
	afx_msg void OnEnChangeYpos();
	afx_msg void OnEnChangeZpos();
	void SetPosEdit(W_STR xPos, W_STR yPos, W_STR zPos);
	void SetScaleEdit(W_STR xScale, W_STR yScale, W_STR zScale);
	void SetRotationEdit(W_STR pitch, W_STR yaw, W_STR roll);
	afx_msg void OnEnChangeXscale();
	afx_msg void OnEnChangeYscale();
	afx_msg void OnEnChangeZscale();
	afx_msg void OnEnChangeXrot();
	afx_msg void OnEnChangeYrot();
	afx_msg void OnEnChangeZrot();

};
