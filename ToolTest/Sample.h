#include "GameCore.h"
#include "HeightMap.h"
#include "JsonHelper.h"
#include "Picking.h"
#include "Character.h"


class ObjectInfoDlg;

class Sample  : public GameCore 
{
	float Distance = 999999.0f;
	float CellDistance;

	int MapSubTextureIndex = 1;



	HeightMap* map;
	Picking MousePicking;
	JsonHelper loader;

	RECT ClientRt;
	RECT PrevClientRt;
	UINT MapWidth;
	UINT MapHeight;
	std::wstring MapTexture;
	std::wstring DefaultTexture = L"000.jpg";
	std::wstring DefaultPath = L"../../data/map/";
	std::wstring DefaultFbxPath = L"../../fbx/";
	std::wstring DefaultFbxShader = L"../_shader/DefaultAni.txt";
	std::wstring SelectedObjStr = L"";

	std::map <W_STR , FbxSceneLoader*> FbxFileFinder;
	std::map <float, Vector3 > InterSectionList;
	std::map< W_STR ,int> SubTextureFinder;
	std::vector<FbxSceneLoader*> FbxFileList;
	std::vector<Picking*> PickingList;
	std::vector<Node*> NodeList;

	Box Objbox;
	Vector3 Min, Max;
	Vector3 ControlRange;
	Vector3 Intersection = {0.0f,0.0f,0.0f};

public:
	bool IsCreatMap = false;
	int ObjID = 0;
	int Range = 0;
	int Strength = 0;
	Object3D* SelectedObject = nullptr;
	ObjectInfoDlg* InfoDlg;
public:

	bool IsChecked = false;
	bool IsPicking = false;
	bool IsMapUp = false;
	bool IsMapDown = false;
	bool IsMapFlat = false;
	bool IsObjectPicking = false;
	bool IsMapSplatting = false;
	UINT SubTextureIndex = 0;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:

	void SetMapSize(UINT mapWidth, UINT mapHeight, float _cellDistance);
	void SetWireFrame(bool isCheck);
	void SetMapTexture(std::wstring mapTexture);
	void CreateMap();
	void InitMap();
	void SetSelectedObj(W_STR obj);
	bool FbxLoader(W_STR fbxFile);
	void SetCharacter(W_STR fbxFileName, Vector3 pos);
	bool IsIntersection();
	void MapUp();
	void MapDown();
	void MapFlatten();
	void SetRange(int range);
	void SetStrength(int strength);
	void SetInfoDlg(ObjectInfoDlg* dlg);
	void SetInfoDlgToData();

	void SetObjectPos(float xPos, float yPos, float zPos);
	void SetObjectScale(float xScale, float yScale, float zScale);
	void SetObjectRotation(float pitch, float yaw, float roll);


	void SetSelectedObjectXPos(float xPos);
	void SetSelectedObjectYPos(float yPos);
	void SetSelectedObjectZPos(float zPos);

	void SetSelectedObjectXScale(float xScale);
	void SetSelectedObjectYScale(float yScale);
	void SetSelectedObjectZScale(float zScale);

	void AddMapSubTexture(W_STR textureName);
	void FindSelectedTextureIndex(W_STR textureName);

	void SaveMap();
};
