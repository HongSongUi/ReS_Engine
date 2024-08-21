// ObjectInfoDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ToolTest.h"
#include "ObjectInfoDlg.h"
#include "afxdialogex.h"


// ObjectInfoDlg 대화 상자

IMPLEMENT_DYNAMIC(ObjectInfoDlg, CDialogEx)

ObjectInfoDlg::ObjectInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ObjectInfo, pParent)
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();
	App->_Sample.SetInfoDlg(this);
}

ObjectInfoDlg::~ObjectInfoDlg()
{
}

void ObjectInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ObjectPicking, _objectPickingText);
	DDX_Control(pDX, IDC_SeletcObjName, _selectedObjText);
	DDX_Control(pDX, IDC_XPos, _objectXPos);
	DDX_Control(pDX, IDC_YPos, _objectYPos);
	DDX_Control(pDX, IDC_ZPos, _objectZPos);
	DDX_Control(pDX, IDC_XScale, _xScale);
	DDX_Control(pDX, IDC_YScale, _yScale);
	DDX_Control(pDX, IDC_ZScale, _zScale);
	DDX_Control(pDX, IDC_XRot, _xRotText);
	DDX_Control(pDX, IDC_YRot, _yRotText);
	DDX_Control(pDX, IDC_ZRot, _zRotText);
}


BEGIN_MESSAGE_MAP(ObjectInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ObjectPickingBtn, &ObjectInfoDlg::OnBnClickedObjectpickingbtn)
	ON_BN_CLICKED(IDC_PosBtn, &ObjectInfoDlg::OnBnClickedPosbtn)
	ON_BN_CLICKED(IDC_ScaleBtn, &ObjectInfoDlg::OnBnClickedScalebtn)
	ON_BN_CLICKED(IDC_RotBtn, &ObjectInfoDlg::OnBnClickedRotbtn)
	ON_EN_CHANGE(IDC_XPos, &ObjectInfoDlg::OnEnChangeXpos)
	ON_EN_CHANGE(IDC_YPos, &ObjectInfoDlg::OnEnChangeYpos)
	ON_EN_CHANGE(IDC_ZPos, &ObjectInfoDlg::OnEnChangeZpos)
	ON_EN_CHANGE(IDC_XScale, &ObjectInfoDlg::OnEnChangeXscale)
	ON_EN_CHANGE(IDC_YScale, &ObjectInfoDlg::OnEnChangeYscale)
	ON_EN_CHANGE(IDC_ZScale, &ObjectInfoDlg::OnEnChangeZscale)
	ON_EN_CHANGE(IDC_XRot, &ObjectInfoDlg::OnEnChangeXrot)
	ON_EN_CHANGE(IDC_YRot, &ObjectInfoDlg::OnEnChangeYrot)
	ON_EN_CHANGE(IDC_ZRot, &ObjectInfoDlg::OnEnChangeZrot)
END_MESSAGE_MAP()


// ObjectInfoDlg 메시지 처리기


void ObjectInfoDlg::OnBnClickedObjectpickingbtn()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();

	_objPicking = !_objPicking;
	App->_Sample.IsObjectPicking = _objPicking;
	App->_Sample.SetInfoDlg(this);
	if (_objPicking)
	{
		_objectPickingText.SetWindowTextW(L"On");
	}
	else
	{
		_objectPickingText.SetWindowTextW(L"Off");
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void ObjectInfoDlg::SetObjNameText(W_STR objName)
{
	_selectedObjText.SetWindowTextW(objName.c_str());
}



void ObjectInfoDlg::OnBnClickedPosbtn()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();



	App->_Sample.SetObjectPos(_Posx, _Posy, _Posz);
}


void ObjectInfoDlg::OnBnClickedScalebtn()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();
	_xScale.GetWindowTextW(xScale);
	_yScale.GetWindowTextW(yScale);
	_zScale.GetWindowTextW(zScale);
	float x = _ttof(xScale);
	float y = _ttof(yScale);
	float z = _ttof(zScale);

	App->_Sample.SetObjectScale(x, y, z);
}
void ObjectInfoDlg::OnBnClickedRotbtn()
{
	CToolTestApp* App = (CToolTestApp*)AfxGetApp();
	_xRotText.GetWindowTextW(_pitchText);
	_yRotText.GetWindowTextW(_yawText);
	_zRotText.GetWindowTextW(_rollText);
	float x = _ttof(_pitchText);
	float y = _ttof(_yawText);
	float z = _ttof(_rollText);


	App->_Sample.SetObjectRotation(x, y, z);
}

void ObjectInfoDlg::SetPosEdit(W_STR xPos, W_STR yPos, W_STR zPos)
{
	_objectXPos.SetWindowTextW(xPos.c_str());
	_objectYPos.SetWindowTextW(yPos.c_str());
	_objectZPos.SetWindowTextW(zPos.c_str());

}

void ObjectInfoDlg::SetScaleEdit(W_STR xScale, W_STR yScale, W_STR zScale)
{
	_xScale.SetWindowTextW(xScale.c_str());
	_yScale.SetWindowTextW(yScale.c_str());
	_zScale.SetWindowTextW(zScale.c_str());
}

void ObjectInfoDlg::SetRotationEdit(W_STR pitch, W_STR yaw, W_STR roll)
{
	_xRotText.SetWindowTextW(pitch.c_str());
	_yRotText.SetWindowTextW(yaw.c_str());
	_zRotText.SetWindowTextW(roll.c_str());
}


void ObjectInfoDlg::OnEnChangeXpos()
{
	_objectXPos.GetWindowTextW(xPos);
	//_objectYPos.GetWindowTextW(yPos);
	//_objectZPos.GetWindowTextW(zPos);
	_Posx = _ttof(xPos);

	//float y = _ttof(yPos);
	//float z = _ttof(zPos);
	//App->_Sample.SetSelectedObjectXPos(x);
	
}


void ObjectInfoDlg::OnEnChangeYpos()
{
	_objectYPos.GetWindowTextW(yPos);
	_Posy = _ttof(yPos);
	//App->_Sample.SetSelectedObjectYPos(y);
}


void ObjectInfoDlg::OnEnChangeZpos()
{
	_objectZPos.GetWindowTextW(zPos);
	_Posz = _ttof(zPos);
//	App->_Sample.SetSelectedObjectZPos(z);
}


void ObjectInfoDlg::OnEnChangeXscale()
{

	_xScale.GetWindowTextW(xScale);
	_Scalex = _ttof(xScale);

	//App->_Sample.SetSelectedObjectXScale(x);
}


void ObjectInfoDlg::OnEnChangeYscale()
{
	
	_yScale.GetWindowTextW(yScale);
	_Scaley = _ttof(yScale);

	//App->_Sample.SetSelectedObjectYScale(y);
}


void ObjectInfoDlg::OnEnChangeZscale()
{

	_zScale.GetWindowTextW(zScale);
	_Scalez = _ttof(zScale);
	//App->_Sample.SetSelectedObjectZScale(z);
}


void ObjectInfoDlg::OnEnChangeXrot()
{

}


void ObjectInfoDlg::OnEnChangeYrot()
{

}


void ObjectInfoDlg::OnEnChangeZrot()
{
	
}
