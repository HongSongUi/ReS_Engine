#include "pch.h"
#include "JsonHelper.h"
typedef unsigned long DWORD;


bool JsonHelper::LoadJson(const W_STR& fileName, rapidjson::Document& outDoc)
{
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        return false;
    }
    rapidjson::IStreamWrapper isw(file);
    outDoc.ParseStream(isw);

    if (!outDoc.IsObject())
    {
        return false;
    }
    return true;
}

bool JsonHelper::GetInt(const rapidjson::Value& inObject, const char* inProperty, int& outInt)
{
    auto iter = inObject.FindMember(inProperty);
    if (iter == inObject.MemberEnd())
    {
        return false;
    }
    auto& prop = iter->value;
    if (!prop.IsInt())
    {
        return false;
    }
    outInt = prop.GetInt();
    return true;
}

bool JsonHelper::GetFloat(const rapidjson::Value& inObject, const char* inProperty, float& outFloat)
{
    auto iter = inObject.FindMember(inProperty);
    if (iter == inObject.MemberEnd())
    {
        return false;
    }
    auto& prop = iter->value;
    if (!prop.IsFloat())
    {
        return false;
    }
    outFloat = prop.GetFloat();
    return true;
}

bool JsonHelper::GetWString(const rapidjson::Value& inObject, const char* inProperty, W_STR& outStr)
{
    auto iter = inObject.FindMember(inProperty);
    if (iter == inObject.MemberEnd())
    {
        return false;
    }
    auto& prop = iter->value;
    if (!prop.IsString())
    {
        return false;
    }
    outStr = StrToWstr(prop.GetString());
    return true;
}

bool JsonHelper::GetBool(const rapidjson::Value& inObject, const char* inProperty, bool& outBool)
{
    auto iter = inObject.FindMember(inProperty);
    if (iter == inObject.MemberEnd())
    {
        return false;
    }
    auto& prop = iter->value;
    if (!prop.IsBool())
    {
        return false;
    }
    outBool = prop.GetBool();
    return true;
}

bool JsonHelper::GetVector3(const rapidjson::Value& inObject, const char* inProperty, Vector3& outVector)
{
    auto iter = inObject.FindMember(inProperty);
    if (iter == inObject.MemberEnd())
    {
        return false;
    }

    auto& property = iter->value;
    if (!property.IsArray() || property.Size() != 3)
    {
        return false;
    }

    for (rapidjson::SizeType i = 0; i < 3; i++)
    {
        if (!property[i].IsFloat())
        {
            return false;
        }
    }

    outVector.x = property[0].GetFloat();
    outVector.y = property[1].GetFloat();
    outVector.z = property[2].GetFloat();
    return true;
}

bool JsonHelper::GetQuaternion(const rapidjson::Value& inObject, const char* inProperty, Quaternion& outQuat)
{
    auto itr = inObject.FindMember(inProperty);
    if (itr == inObject.MemberEnd())
    {
        return false;
    }

    auto& property = itr->value;

    for (rapidjson::SizeType i = 0; i < 4; i++)
    {
        if (!property[i].IsFloat())
        {
            return false;
        }
    }

    outQuat.x = property[0].GetFloat();
    outQuat.y = property[1].GetFloat();
    outQuat.z = property[2].GetFloat();
    outQuat.w = property[3].GetFloat();

    return true;
}

void JsonHelper::AddInt(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, int value)
{
    rapidjson::Value v(value);
    inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

void JsonHelper::AddFloat(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, float value)
{
    rapidjson::Value v(value);
    inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

void JsonHelper::AddString(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, const W_STR& value)
{
    rapidjson::Value v;

    v.SetString(WstrToStr(value).c_str(), static_cast<rapidjson::SizeType>(value.length()),
        alloc);
    inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

void JsonHelper::AddBool(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, bool value)
{
    rapidjson::Value v(value);
    inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

void JsonHelper::AddVector3(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, const Vector3& value)
{
    rapidjson::Value v(rapidjson::kArrayType);
    // Push back elements
    v.PushBack(rapidjson::Value(value.x).Move(), alloc);
    v.PushBack(rapidjson::Value(value.y).Move(), alloc);
    v.PushBack(rapidjson::Value(value.z).Move(), alloc);

    // Add array to inObject
    inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

void JsonHelper::AddQuaternion(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, const Quaternion& value)
{
    rapidjson::Value v(rapidjson::kArrayType);
    // Push back elements
    v.PushBack(rapidjson::Value(value.x).Move(), alloc);
    v.PushBack(rapidjson::Value(value.y).Move(), alloc);
    v.PushBack(rapidjson::Value(value.z).Move(), alloc);
    v.PushBack(rapidjson::Value(value.w).Move(), alloc);

    // Add array to inObject
    inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

std::string JsonHelper::MapToJsonFile(const std::vector<Vertex>& mapVertex, const std::vector<unsigned int>& mapIndex)
{
    rapidjson::Document doc;
    doc.SetObject();

    rapidjson::Value vertexArray(rapidjson::kArrayType);
    for (rapidjson::size_t i = 0; i < mapVertex.size(); i++)
    {
        rapidjson::Value vertex(rapidjson::kObjectType);
        vertex.AddMember("PosX", mapVertex[i].Position.x, doc.GetAllocator());
        vertex.AddMember("PosY", mapVertex[i].Position.y, doc.GetAllocator());
        vertex.AddMember("PosZ", mapVertex[i].Position.z, doc.GetAllocator());

        vertex.AddMember("NorX", mapVertex[i].Normal.x, doc.GetAllocator());
        vertex.AddMember("NorY", mapVertex[i].Normal.y, doc.GetAllocator());
        vertex.AddMember("NorZ", mapVertex[i].Normal.z, doc.GetAllocator());

        vertex.AddMember("ColX", mapVertex[i].Color.x, doc.GetAllocator());
        vertex.AddMember("ColY", mapVertex[i].Color.y, doc.GetAllocator());
        vertex.AddMember("ColZ", mapVertex[i].Color.z, doc.GetAllocator());
        vertex.AddMember("ColW", mapVertex[i].Color.w, doc.GetAllocator());

        vertex.AddMember("TexX", mapVertex[i].Texture.x, doc.GetAllocator());
        vertex.AddMember("TexY", mapVertex[i].Texture.y, doc.GetAllocator());

        vertexArray.PushBack(vertex, doc.GetAllocator());
    }
    doc.AddMember("verteies", vertexArray, doc.GetAllocator());

    rapidjson::Value indexArray(rapidjson::kArrayType);

    for (rapidjson::size_t i = 0; i < mapIndex.size(); i++)
    {

        indexArray.PushBack(mapIndex[i], doc.GetAllocator());
    }
    doc.AddMember("indices", indexArray, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);


    return buffer.GetString();
}

bool JsonHelper::SaveMap(const W_STR& fileName, const std::vector<Vertex>& mapVertex, const std::vector<unsigned int>& mapIndex)
{
    std::string jsonString = MapToJsonFile(mapVertex, mapIndex);

    std::ofstream outFile(fileName);
    if (!outFile.is_open())
    {
        return false;
    }
    outFile << jsonString;
    outFile.close();

    return true;
}
