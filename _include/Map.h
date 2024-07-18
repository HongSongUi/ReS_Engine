#pragma once
#include "BaseObject.h"
class Map : public BaseObject
{
protected:
    UINT MapWidth;
    UINT MapHeight;
public:
    int _FaceCount;
    int _CellCount;
    float _CellDistance;

public:
    virtual void SetVertexList();
    void SetIndexList();
    void SetMapSize(UINT width, UINT height);
};

