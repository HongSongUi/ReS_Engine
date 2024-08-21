#pragma once


// DockingViewTest
#include "MapDialog.h"
class DockingViewTest : public CDockablePane
{
	DECLARE_DYNAMIC(DockingViewTest)

public:
	MapDialog _dialog;

public:
	DockingViewTest();
	virtual ~DockingViewTest();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


