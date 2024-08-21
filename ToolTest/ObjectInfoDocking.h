#pragma once

// DockingViewTest
#include "ObjectInfoDlg.h"
class ObjectInfoDocking : public CDockablePane
{
	DECLARE_DYNAMIC(ObjectInfoDocking)

public:
	ObjectInfoDlg _dialog;

public:
	ObjectInfoDocking();
	virtual ~ObjectInfoDocking();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


