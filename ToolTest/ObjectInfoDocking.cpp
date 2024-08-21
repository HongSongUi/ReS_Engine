#include "pch.h"
#include "ToolTest.h"
#include "ObjectInfoDocking.h"


IMPLEMENT_DYNAMIC(ObjectInfoDocking, CDockablePane)

ObjectInfoDocking::ObjectInfoDocking()
{

}

ObjectInfoDocking::~ObjectInfoDocking()
{
}

int ObjectInfoDocking::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	BOOL ret = _dialog.Create(IDD_ObjectInfo, this);
	ASSERT(ret);
	_dialog.ShowWindow(SW_SHOW);
	return 0;
}


BEGIN_MESSAGE_MAP(ObjectInfoDocking, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

void ObjectInfoDocking::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	_dialog.MoveWindow(0, 0, cx, cy);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
