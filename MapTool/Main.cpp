#include "pch.h"
#include "ObjectInfo.h"
#include "Input.h"
#include "Main.h"

bool Main::Init()
{
	ClientRt = GetClientRect();
	PrevClientRt = ClientRt;

	MousePicking.SetWindowData(GetWindowHwnd(), GetClientRect());
	map = new HeightMap;


	DebugCam.CreateViewMatrix(Vector3(0, 10, -10), Vector3(0, 45, 0), Vector3(0, 1, 0));
	DebugCam.CreateProjMatrix(1.0f, 10000.0f, 3.141592 * 0.25f, (float)ClientRt.right / (float)ClientRt.bottom);
	DebugCam.CameraFrustum.CreateFrustum(&DebugCam.ViewMat, &DebugCam.ProjMat);
	return true;
}

bool Main::Frame()
{
	ClientRt = GetClientRect();
	if (PrevClientRt != ClientRt)
	{
		MousePicking.SetWindowData(GetWindowHwnd(), GetClientRect());
		DebugCam.CreateProjMatrix(1.0f, 10000.0f, 3.141592 * 0.25f, (float)ClientRt.right / (float)ClientRt.bottom);
		DebugCam.CameraFrustum.CreateFrustum(&DebugCam.ViewMat, &DebugCam.ProjMat);
		PrevClientRt = ClientRt;
	}

	DebugCam.Frame();
	MousePicking.SetMatrix(nullptr, &DebugCam.ViewMat, &DebugCam.ProjMat);

	if (IsPicking)
	{
		if (IsIntersection())
		{
			SetCharacter(SelectedObjStr, Intersection);
		}
	}
	if (IsMapUp)
	{
		if (IsIntersection())
		{
			MapUp();
		}
	}
	if (IsMapDown)
	{
		if (IsIntersection())
		{
			MapDown();
		}
	}
	if (IsMapFlat)
	{
		if (IsIntersection())
		{
			MapFlatten();
		}
	}
	if (IsObjectPicking)
	{
		if (GameInput.GetKey(VK_LBUTTON) == KEY_PUSH)
		{
			for (auto node : map->SpaceDivisionTree.NodeList)
			{
				for (auto obj : node->ObjectList)
				{
					if (MousePicking.OBBtoRay(&obj->ObjectBox))
					{
						SelectedObject = obj;
						SetInfoDlgToData();
					}
				}
			}
		}
	}
	if (IsMapSplatting)
	{
		if (IsIntersection())
		{
			map->Splatting(Intersection, SubTextureIndex);
		}
	}

	return true;
}

bool Main::Render()
{
	if (map->TextureFile == nullptr || IsChecked == true)
	{
		D3D11Context->RSSetState(DxState::_DefaultRSWireFrame);
	}

	if (map->D3D11Context != nullptr)
	{
		map->SetMatrix(nullptr, &DebugCam.ViewMat, &DebugCam.ProjMat);
		Vector4 lightDir{ 1.0f,1.0f,0.0f,0.0f };
		D3DXVec4Normalize(&lightDir, &lightDir);
		lightDir *= -1.0f;
		Vector4 eyeDir{ DebugCam.LookVec.x , DebugCam.LookVec.y , DebugCam.LookVec.z, 0.5f };
		Vector4 eyePos{ DebugCam.Position.x , DebugCam.Position.y , DebugCam.Position.z , 0.5f };

		map->SetLight(&lightDir, nullptr, &eyeDir, &eyePos);
		map->CheckVisible(DebugCam.CameraFrustum);
	}


	GetContext()->RSSetState(DxState::_DefaultRSSolid);
	return true;
}

bool Main::Release()
{
	if (map != nullptr) {
		map->Release();
		delete map;
		map = nullptr;
	}
	for (auto fbx : FbxFileFinder)
	{
		FbxSceneLoader* data = fbx.second;
		if (data)
		{
			data->Release();
		}
		delete data;
		data = nullptr;
	}
	FbxFileFinder.clear();

	DebugCam.Release();
	return true;
}

void Main::SetMapSize(UINT mapWidth, UINT mapHeight, float cellDistance)
{
	if (map->D3D11Context != nullptr)
	{
		InitMap();
	}

	MapWidth = mapWidth;
	MapHeight = mapHeight;
	CellDistance = cellDistance;
	map->SetMapSize(MapWidth, MapHeight, CellDistance);

}

void Main::SetWireFrame(bool isCheck)
{
	IsChecked = isCheck;
}

void Main::SetMapTexture(std::wstring mapTexture)
{

	MapTexture = mapTexture;
	if (MapTexture == L"")
	{
		MapTexture = DefaultPath + DefaultTexture;
	}
	map->Load(L"DefaultMap.hlsl", MapTexture);

	map->TextureArray[0] = TextureMgr.Load(MapTexture);
}

void Main::CreateMap()
{
	map->SetData(GetDevice(), GetContext(), GetClientRect());
	map->CreateVertex();
	map->CraeteAlphaTexture(1024, 1024);
	IsCreatMap = true;
}

void Main::InitMap()
{
	map->Release();
	delete map;
	map = nullptr;
	map = new HeightMap;
}

void Main::SetSelectedObj(W_STR obj)
{
	SelectedObjStr = obj;
}

bool Main::FbxLoader(W_STR fbxFile)
{
	fbxFile = DefaultFbxPath + fbxFile;
	auto iter = FbxFileFinder.find(fbxFile);
	if (iter == FbxFileFinder.end())
	{
		FbxSceneLoader* fbxLoader = new FbxSceneLoader;
		fbxLoader->Load(GetDevice(), fbxFile);
		FbxFileFinder.insert(std::make_pair(fbxFile, fbxLoader));

		for (int obj = 0; obj < fbxLoader->DrawObjList.size(); obj++)
		{
			FbxEntity* Obj = fbxLoader->DrawObjList[obj];
			Obj->SetData(GetDevice(), GetContext(), GetClientRect());
			Obj->Load(L"../_shader/DefaultAni.txt");
			Obj->CreateVertex();
		}
		return true;
	}
	return false;
}

void Main::SetCharacter(W_STR fbxFileName, Vector3 pos)
{
	std::wstring FileName = DefaultFbxPath + fbxFileName;
	auto iter = FbxFileFinder.find(FileName);

	if (iter != FbxFileFinder.end()) 
	{
		Character* mapObject = new Character;

		mapObject->SetDevice(GetDevice(), GetContext());
		mapObject->SetCharacter(iter->second, pos);
		mapObject->ObjName = fbxFileName + L"_" + std::to_wstring(ObjID);
		mapObject->FbxListID = ObjID++;

		map->SpaceDivisionTree.AddObject(mapObject);
	}

}

bool Main::IsIntersection()
{
	if (GameInput.GetKey(VK_LBUTTON) == KEY_PUSH)
	{
		for (auto node : map->SpaceDivisionTree.DrawNode)
		{
			UINT index = 0;
			UINT faceNum = node->IndexList.size() / 3;
			for (UINT face = 0; face < faceNum; face++)
			{
				UINT i0 = node->IndexList[index + 0];
				UINT i1 = node->IndexList[index + 1];
				UINT i2 = node->IndexList[index + 2];

				Vector3 v0 = map->VertexList[i0].Position;
				Vector3 v1 = map->VertexList[i1].Position;
				Vector3 v2 = map->VertexList[i2].Position;

				if (MousePicking.ChkPick(v0, v1, v2))
				{
					PickingList.push_back(&MousePicking);
				}
				index += 3;
			}
		}
	}
	if (PickingList.size() == 0)
	{
		return false;
	}
	else
	{
		for (int pick = 0; pick < PickingList.size(); pick++)
		{
			if (PickingList[pick]->PickDistance < Distance)
			{
				Distance = PickingList[pick]->PickDistance;
				Intersection = PickingList[pick]->InterSection;
			}
		}
		PickingList.clear();
		Distance = 999999.0f;
		return true;
	}
}

void Main::MapUp()
{
	std::vector<Node*> nodeList;

	Max = Intersection + ControlRange;
	Min = Intersection - ControlRange;
	Objbox.SetBox(Max, Min);
	if (map->SelectVertexList(Objbox, nodeList) > 0)
	{

		for (UINT vertex = 0; vertex < map->VertexList.size(); vertex++)
		{
			Vector3 v0 = map->VertexList[vertex].Position;
			Vector3 v = v0 - Intersection;
			float distance = D3DXVec3Length(&v);
			if (distance <= Range)
			{
				float value = (distance / Range) * 90.0f;
				float dot = cosf(DegreeToRadian(value)) * sinf(DegreeToRadian(Strength));
				map->VertexList[vertex].Position.y += dot * nodeList.size();
				map->ComputeVertexNorm(vertex);
			}

		}
		//map->UpdateVertexList();
		map->MapUpdate(nodeList);
	}
}

void Main::MapDown()
{
	std::vector<Node*> nodeList;

	Max = Intersection + ControlRange;
	Min = Intersection - ControlRange;
	Objbox.SetBox(Max, Min);
	if (map->SelectVertexList(Objbox, nodeList) > 0)
	{

		for (UINT vertex = 0; vertex < map->VertexList.size(); vertex++)
		{
			Vector3 v0 = map->VertexList[vertex].Position;
			Vector3 v = v0 - Intersection;
			float distance = D3DXVec3Length(&v);
			if (distance <= Range)
			{
				float value = (distance / Range) * 90.0f;
				float dot = cosf(DegreeToRadian(value)) * sinf(DegreeToRadian(Strength));
				map->VertexList[vertex].Position.y -= dot * nodeList.size();
				map->ComputeVertexNorm(vertex);
			}

		}
		map->MapUpdate(nodeList);
	}
}

void Main::MapFlatten()
{
	std::vector<Node*> nodeList;

	Max = Intersection + ControlRange;
	Min = Intersection - ControlRange;
	Objbox.SetBox(Max, Min);

	if (map->SelectVertexList(Objbox, nodeList) > 0)
	{
		for (UINT vertex = 0; vertex < map->VertexList.size(); vertex++)
		{
			Vector3 v0 = map->VertexList[vertex].Position;
			Vector3 v = v0 - Intersection;
			float distance = D3DXVec3Length(&v);
			if (distance <= Range)
			{
				float value = (distance / Range) * 90.0f;
				float dot = cosf(DegreeToRadian(value)) * sinf(DegreeToRadian(Strength));
				if (map->VertexList[vertex].Position.y > 0)
				{
					map->VertexList[vertex].Position.y -= dot * nodeList.size();
					if (map->VertexList[vertex].Position.y <= 0)
					{
						map->VertexList[vertex].Position.y = 0;
					}
				}
				else if (map->VertexList[vertex].Position.y < 0)
				{
					map->VertexList[vertex].Position.y += dot * nodeList.size();

					if (map->VertexList[vertex].Position.y >= 0)
					{
						map->VertexList[vertex].Position.y = 0;
					}
				}
				map->ComputeVertexNorm(vertex);
			}
		}
		map->MapUpdate(nodeList);
	}
}

void Main::SetRange(int range)
{
	Range = range;
	ControlRange.x = range;
	ControlRange.y = range;
	ControlRange.z = range;
}

void Main::SetStrength(int strength)
{
	Strength = strength;
}

void Main::SetInfoDlg(ObjectInfo* dlg)
{
	InfoDlg = dlg;
}

void Main::SetInfoDlgToData()
{
	Character* tmp = dynamic_cast<Character*>(SelectedObject);
	float posx = roundf(tmp->Position.x * 100) / 100;
	float posy = roundf(tmp->Position.y * 100) / 100;
	float posz = roundf(tmp->Position.z * 100) / 100;

	float scaleX = tmp->UpdateScaleVec.x;
	float scaleY = tmp->UpdateScaleVec.y;
	float scaleZ = tmp->UpdateScaleVec.z;

	float rotX = tmp->UpdateRotationVal.x;
	float rotY = tmp->UpdateRotationVal.y;
	float rotZ = tmp->UpdateRotationVal.z;

	W_STR xPos = std::to_wstring(posx);
	W_STR yPos = std::to_wstring(posy);
	W_STR zPos = std::to_wstring(posz);

	W_STR xScale = std::to_wstring(scaleX);
	W_STR yScale = std::to_wstring(scaleY);
	W_STR zScale = std::to_wstring(scaleZ);

	W_STR xRot = std::to_wstring(rotX);
	W_STR yRot = std::to_wstring(rotY);
	W_STR zRot = std::to_wstring(rotZ);

//	InfoDlg->SetObjNameText(tmp->ObjName);
//	InfoDlg->SetPosEdit(xPos, yPos, zPos);
//	InfoDlg->SetScaleEdit(xScale, yScale, zScale);
//	InfoDlg->SetRotationEdit(xRot, yRot, zRot);
}

void Main::SetObjectPos(float xPos, float yPos, float zPos)
{

}

void Main::SetObjectScale(float xScale, float yScale, float zScale)
{
}

void Main::SetObjectRotation(float pitch, float yaw, float roll)
{
}

void Main::SetSelectedObjectXPos(float xPos)
{
}

void Main::SetSelectedObjectYPos(float yPos)
{
}

void Main::SetSelectedObjectZPos(float zPos)
{
}

void Main::SetSelectedObjectXScale(float xScale)
{
}

void Main::SetSelectedObjectYScale(float yScale)
{
}

void Main::SetSelectedObjectZScale(float zScale)
{
}

void Main::AddMapSubTexture(W_STR textureName)
{
}

void Main::FindSelectedTextureIndex(W_STR textureName)
{
}

void Main::SaveMap()
{
}
