#pragma once
#undef max
#undef min
#undef DWORD

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <fstream>
#include <vector>
#include "ReSUtility.h"
#include "MathLib.h"
#include "ObjectMesh.h"
class JsonHelper
{
public:
	static bool LoadJson(const W_STR& fileName, rapidjson::Document& outDoc);

	static bool GetInt(const rapidjson::Value& inObject, const char* inProperty, int& outInt);
	static bool GetFloat(const rapidjson::Value& inObject, const char* inProperty, float& outFloat);
	static bool GetWString(const rapidjson::Value& inObject, const char* inProperty, W_STR& outStr);
	static bool GetBool(const rapidjson::Value& inObject, const char* inProperty, bool& outBool);
	static bool GetVector3(const rapidjson::Value& inObject, const char* inProperty, Vector3& outVector);
	static bool GetQuaternion(const rapidjson::Value& inObject, const char* inProperty, Quaternion& outQuat);
public:
	static void AddInt(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, int value);
	static void AddFloat(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, float value);
	static void AddString(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, const W_STR& value);
	static void AddBool(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, bool value);
	static void AddVector3(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, const Vector3& value);
	static void AddQuaternion(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, const Quaternion& value);

	static std::string MapToJsonFile(const std::vector<Vertex>& mapVertex, const std::vector<unsigned int>& mapIndex);
	static bool SaveMap(const W_STR& fileName, const std::vector<Vertex>& mapVertex, const std::vector<unsigned int>& mapIndex);
};

