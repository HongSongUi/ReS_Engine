#pragma once
#include "X_BaseObject.h"
class Line : public X_BaseObject
{
public:
	void SetVertexList()override;
	void SetIndexList() override;
	bool Render()override;

};

