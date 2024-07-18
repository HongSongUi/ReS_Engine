#pragma once
#include "X_BaseObject.h"
class X_Map : public X_BaseObject
{
//
//추후 변경 : TestLib-> Create SpaceDivision 에 있는 TestMap 내용 올리기
//
protected:
    UINT _MapWidth;
    UINT _MapHeight;
public:
    int _FaceCount;
    int _CellCount;
    float _CellDistance;

public:
    virtual void SetVertexList();
    void SetIndexList();
    void SetMapSize(UINT width, UINT height);
};

