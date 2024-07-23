#pragma once
#include <string>
#include <codecvt>
extern float gGameTimer;
extern float gSecondPerFrame;

#define randstep(fMin,fMax) (fMin+((float)fMax-(float)fMin)*rand()/(float)RAND_MAX)

template<typename T> class Singleton
{
public:
	static T& GetInstance()
	{
		static T Instance;
		return Instance;
	}
};

static std::string WstrToStr(const std::wstring Wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(Wstr);
}

static std::wstring StrToWstr(const std::string str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(str);
}
