#pragma once
#include <string>
#include <Windows.h>
#include <vector>
#include <math.h>
#include <atlconv.h>
#include <atlstr.h>
extern float gGameTimer;
extern float gSecondPerFrame;


#define randf(x) (x*rand()/(float)RAND_MAX)
#define randf2(x,off) (off+x*rand()/(float)RAND_MAX)
#define randstep(fMin,fMax) (fMin+((float)fMax-(float)fMin)*rand()/(float)RAND_MAX)
#define clamp(x,MinX,MaxX) if (x>MaxX) x=MaxX; else if (x<MinX) x=MinX;


template<typename T> class X_Singleton
{
public:
	static T& GetInstance()
	{
		static T Instance;
		return Instance;
	}
};
static std::string UtoM (const std::wstring str) {
	
	USES_CONVERSION;
	std::string strMulti = W2A(str.c_str());
	return strMulti;
}
static std::wstring MtoU(const std::string str) {

	USES_CONVERSION;
	std::wstring strUni = A2W(str.c_str());

	return strUni;
}
