#include "Sample.h"
#include "SoundManager.h"

bool Sample::Init()
{
    SoundMgr.LoadAll(L"../_sound/");
    Test.SetData(GameCore::GetDevice(), GameCore::GetContext(), GameCore::GetClientRect());
    return true;
}

bool Sample::Frame()
{
    Test.Frame();
    return true;
}

bool Sample::Render()
{
    Test.Render();
    //GameCore::GetContext()->RSSetState(DxState::_DefaultRSWireFrame);
    // Test.PreRender();
    //GameCore::GetContext()->PSSetShaderResources(1, 1, &Test.MaskTexture->TextureSRV);
    //  Test.PostRender();
    return true;
}

bool Sample::Release()
{
    Test.Release();
    return true;
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 전역 문자열을 초기화합니다.
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
   // LoadStringW(hInstance, IDC_WINAPI01, szWindowClass, MAX_LOADSTRING);

    Sample  MyWin;
    MyWin.SetWindow(hInstance, L"Megaman", 1024, 768);
    MyWin.Run();

    return 1;
}
