#include "GameCore.h"

bool GameCore::Init()
{
	return true;
}

bool GameCore::Render()
{
	return true;
}

bool GameCore::Release()
{
	return true;
}

bool GameCore::Frame()
{
	return true;
}

bool GameCore::PreProcess()
{
	return true;
}

bool GameCore::PreFrame()
{
	return true;
}

bool GameCore::PostFrame()
{
	return true;
}

bool GameCore::PreRender()
{
	return true;
}

bool GameCore::PostRender()
{
	return true;
}

bool GameCore::PostProcess()
{
	return true;
}

bool GameCore::CoreInit()
{
	GameDevice.SetWindowData(Window.ClientRect, Window.Hwnd);

	ClientRect = Window.ClientRect;
	GameDevice.Init();
	GameWriter.Init();
	IDXGISurface1* BackBuffer = nullptr;
	GameDevice.SwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&BackBuffer);

	TextureMgr.InitMgr(GameDevice.D3D11Device.get(), GameDevice.D3D11Context.get());
	ShaderMgr.InitMgr(GameDevice.D3D11Device.get(), GameDevice.D3D11Context.get());
	GameInput.SetWinHwnd(Window.Hwnd);

	SoundMgr.Init();
	GameTimer.Init();
	GameInput.Init();
	DxState::SetState(GameDevice.D3D11Device.get());
	GameWriter.SetClientRect(ClientRect);
	GameWriter.Set(BackBuffer);

	BackBuffer->Release();
	BackBuffer = nullptr;
	RenderTarget.SetData(GameDevice.D3D11Device.get(), GameDevice.D3D11Context.get(), ClientRect);
	RenderTarget.Load(L"../_shader/DefaultShader.txt", L"../_Texture/StageSelect.png");
	if (RenderTarget.CreateVertex() == false)
	{
		return false;
	}
	RenderTexture.Create(GameDevice.D3D11Device.get(), 2048, 2048);
	Init();
	return true;
}

bool GameCore::CoreFrame()
{
	if (Window.ResizeWindow == true) 
	{
		ReSizeWindow(Window.TotalWidth, Window.TotalHeight);
	}
	UpdateCamString();
	GameTimer.Frame();
	GameInput.Frame();
	SoundMgr.Frame();
	ClearD3D11DeviceContext();
	PreFrame();
	Frame();
	PostFrame();
	return true;
}


bool GameCore::CorePreRender()
{
	GameDevice.PreRender();
	GameDevice.D3D11Context.get()->PSSetSamplers(0, 1, &DxState::_DefaultSS);
	GameDevice.D3D11Context.get()->RSSetState(DxState::_DefaultRSSolid);
	GameDevice.D3D11Context.get()->OMSetBlendState(DxState::_DefaultBS, 0, -1);
	GameDevice.D3D11Context.get()->OMSetDepthStencilState(DxState::_DefaultDepthStencil, 0xff);
	return true;
}

bool GameCore::CorePostRender()
{
	PostRender();
	GameDevice.PostRender();
	return true;
}

bool GameCore::CoreRender()
{
	CorePreRender();
	PreRender();
	//////////////////////////////////////////////
	RenderTexture.OldDepthStencil = GameDevice.DepthStencilView;
	RenderTexture.OldRenderTarget = GameDevice.RenderTargetView;
	RenderTexture.OldViewPort[0] = GameDevice.ViewPort;
	if (RenderTexture.Begin(GetContext())) 
	{
		Render();
		RenderTexture.End(GetContext());
	}
	if (RenderTexture.ShaderResourceView) 
	{
		RenderTarget.Mesh.TextureSRV = RenderTexture.ShaderResourceView;
	}
	//RenderTarget.SetMatrix(nullptr, nullptr, nullptr);
	RenderTarget.Render();

	/// ////////////////////////////////////////////
	GameTimer.Render();
	GameInput.Render();

	CorePostRender();

	return false;
}

bool GameCore::CoreRelease()
{
	Release();

	GameDevice.Release();
	
	GameWriter.Release();
	DxState::Release();
	GameInput.Release();
	GameTimer.Release();
	SoundMgr.Release();
	ShaderMgr.Release();
	TextureMgr.Release();

	RenderTarget.Release();
	RenderTexture.Release();
	return true;
}

bool GameCore::SetWindow(HINSTANCE hInstance, const WCHAR* Title, UINT width, UINT height)
{
	Window.SetWindow(hInstance, Title, width, height);
	return false;
}

bool GameCore::Run()
{
	CoreInit();
	//MSG-> 구조체
	MSG msg = { 0, };
	// 기본 메시지 루프입니다:
	IsGameRun = true;
	while (IsGameRun)
	{
		PreProcess();
		if (!Window.Run()) 
		{
			IsGameRun = false;
		}
		else 
		{
			if (!CoreFrame() || !CoreRender()) 
			{
				IsGameRun = false;
			}
		}
		PostProcess();
	}
	CoreRelease();
	return true;
}

bool GameCore::ToolRun()
{
	if (!CoreFrame() || !CoreRender()) 
	{
		IsGameRun = false;
		return false;
	}
	return true;
}



void GameCore::ClearD3D11DeviceContext()
{
	ID3D11ShaderResourceView* pSRVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ID3D11RenderTargetView* pRTVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ID3D11DepthStencilView* pDSV = NULL;
	ID3D11Buffer* pBuffers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ID3D11SamplerState* pSamplers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	UINT StrideOffset[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	GameDevice.D3D11Context.get()->VSSetShaderResources(0, 16, pSRVs);
	//pd3dDeviceContext->HSSetShaderResources(0, 16, pSRVs);
	//pd3dDeviceContext->DSSetShaderResources(0, 16, pSRVs);
	//pd3dDeviceContext->GSSetShaderResources(0, 16, pSRVs);
	GameDevice.D3D11Context.get()->PSSetShaderResources(0, 16, pSRVs);

}

void GameCore::UpdateCamString()
{
}

void GameCore::SetHwnd(HWND hWnd)
{
	Window.SetWinhWnd(hWnd);
}

void GameCore::ReSizeWindow(UINT width, UINT height)
{
	if (GameDevice.SwapChain == nullptr) 
	{
		return;
	}
	GameWriter.DeleteDxResource();
	ClientRect = Window.GetClientRtSize();


	GameDevice.ResizeWindow(width, height);
	IDXGISurface1* _BackBuffer = nullptr;
	GameWriter.Init();
	GameDevice.SwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&_BackBuffer);

	GameWriter.SetClientRect(ClientRect);
	GameWriter.Set(_BackBuffer);

	DebugCam.CreateProjMatrix(DebugCam.Near, DebugCam.Far, DebugCam.Fov, (float)ClientRect.right / (float)ClientRect.bottom);

	DebugCam.CameraFrustum.CreateFrustum(&DebugCam.ViewMat, &DebugCam.ProjMat);
	_BackBuffer->Release();
	_BackBuffer = nullptr;


	Window.ResizeWindow = false;
}

ID3D11Device* GameCore::GetDevice()
{
	return GameDevice.D3D11Device.get();
}

ID3D11DeviceContext* GameCore::GetContext()
{
	return GameDevice.D3D11Context.get();
}

HWND GameCore::GetWindowHwnd()
{
	return Window.Hwnd;
}

RECT GameCore::GetClientRect()
{
	return ClientRect;
}
