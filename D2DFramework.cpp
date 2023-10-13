#include "D2DFramework.h"

#pragma comment (lib,"d2d1.lib")
// 라이브러리 포함은 cpp에 하기. 라이브러리는 2번 포함하면 안됨

HRESULT D2DFramework::Initialize(HWND hwnd)
{
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, mspD2DFactory.GetAddressOf());

    if (FAILED(hr))
    {
        ShowError(L"Failed To CreateFactory");
        return hr;
    }

    RECT wr;
    GetClientRect(hwnd, &wr);
    hr = mspD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(wr.right - wr.left, wr.bottom - wr.top)),
        mspRenderTarget.GetAddressOf()
    );

    if (FAILED(hr))
    {
        ShowError(L"Failed To Create HWNDRenderTarget");
        return hr;
    }
    // 반대: E_FAIL
    return S_OK;
}

void D2DFramework::Release()
{
    mspRenderTarget.Reset();
    mspD2DFactory.Reset();
}

void D2DFramework::Render()
{
    mspRenderTarget->BeginDraw();
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));
    mspRenderTarget->EndDraw();
}

void D2DFramework::ShowError(LPCWSTR msg, LPCWSTR title)
{
    MessageBox(nullptr, msg, title, MB_OK);
}
