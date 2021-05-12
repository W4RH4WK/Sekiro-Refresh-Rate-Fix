#pragma once

#include <fstream>

#include <dxgi1_2.h>

class DXGISwapChainWrapper : public IDXGISwapChain1 {
  public:
	DXGISwapChainWrapper() { std::ofstream("dxwrap_swap_chain.log", std::ios_base::app) << "created\n"; }

	HRESULT STDMETHODCALLTYPE QueryInterface(
	    /* [in] */ REFIID riid,
	    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject) override
	{
		return m_real->QueryInterface(riid, ppvObject);
	}

	ULONG STDMETHODCALLTYPE AddRef(void) override { return m_real->AddRef(); }

	ULONG STDMETHODCALLTYPE Release(void) override
	{
		auto count = m_real->Release();
		if (count == 0) {
			delete this;
		}
		return count;
	}

	HRESULT STDMETHODCALLTYPE SetPrivateData(
	    /* [annotation][in] */
	    _In_ REFGUID Name,
	    /* [in] */ UINT DataSize,
	    /* [annotation][in] */
	    _In_reads_bytes_(DataSize) const void *pData) override
	{
		return m_real->SetPrivateData(Name, DataSize, pData);
	}

	HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(
	    /* [annotation][in] */
	    _In_ REFGUID Name,
	    /* [annotation][in] */
	    _In_opt_ const IUnknown *pUnknown) override
	{
		return m_real->SetPrivateDataInterface(Name, pUnknown);
	}

	HRESULT STDMETHODCALLTYPE GetPrivateData(
	    /* [annotation][in] */
	    _In_ REFGUID Name,
	    /* [annotation][out][in] */
	    _Inout_ UINT *pDataSize,
	    /* [annotation][out] */
	    _Out_writes_bytes_(*pDataSize) void *pData) override
	{
		return m_real->GetPrivateData(Name, pDataSize, pData);
	}

	HRESULT STDMETHODCALLTYPE GetParent(
	    /* [annotation][in] */
	    _In_ REFIID riid,
	    /* [annotation][retval][out] */
	    _COM_Outptr_ void **ppParent) override
	{
		return m_real->GetParent(riid, ppParent);
	}

	HRESULT STDMETHODCALLTYPE GetDevice(
	    /* [annotation][in] */
	    _In_ REFIID riid,
	    /* [annotation][retval][out] */
	    _COM_Outptr_ void **ppDevice) override
	{
		return m_real->GetDevice(riid, ppDevice);
	}

	HRESULT STDMETHODCALLTYPE Present(
	    /* [in] */ UINT SyncInterval,
	    /* [in] */ UINT Flags) override
	{
		return m_real->Present(SyncInterval, Flags);
	}

	HRESULT STDMETHODCALLTYPE GetBuffer(
	    /* [in] */ UINT Buffer,
	    /* [annotation][in] */
	    _In_ REFIID riid,
	    /* [annotation][out][in] */
	    _COM_Outptr_ void **ppSurface) override
	{
		return m_real->GetBuffer(Buffer, riid, ppSurface);
	}

	HRESULT STDMETHODCALLTYPE SetFullscreenState(
	    /* [in] */ BOOL Fullscreen,
	    /* [annotation][in] */
	    _In_opt_ IDXGIOutput *pTarget) override
	{
		return m_real->SetFullscreenState(Fullscreen, pTarget);
	}

	HRESULT STDMETHODCALLTYPE GetFullscreenState(
	    /* [annotation][out] */
	    _Out_opt_ BOOL *pFullscreen,
	    /* [annotation][out] */
	    _COM_Outptr_opt_result_maybenull_ IDXGIOutput **ppTarget) override
	{
		return m_real->GetFullscreenState(pFullscreen, ppTarget);
	}

	HRESULT STDMETHODCALLTYPE GetDesc(
	    /* [annotation][out] */
	    _Out_ DXGI_SWAP_CHAIN_DESC *pDesc) override
	{
		return m_real->GetDesc(pDesc);
	}

	HRESULT STDMETHODCALLTYPE ResizeBuffers(
	    /* [in] */ UINT BufferCount,
	    /* [in] */ UINT Width,
	    /* [in] */ UINT Height,
	    /* [in] */ DXGI_FORMAT NewFormat,
	    /* [in] */ UINT SwapChainFlags) override
	{
		return m_real->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
	}

	HRESULT STDMETHODCALLTYPE ResizeTarget(
	    /* [annotation][in] */
	    _In_ const DXGI_MODE_DESC *pNewTargetParameters) override
	{
		// Do not change monitor refresh rate.
		DXGI_MODE_DESC param = *pNewTargetParameters;
		param.RefreshRate = DXGI_RATIONAL{0, 0};

		return m_real->ResizeTarget(&param);
	}

	HRESULT STDMETHODCALLTYPE GetContainingOutput(
	    /* [annotation][out] */
	    _COM_Outptr_ IDXGIOutput **ppOutput) override
	{
		return m_real->GetContainingOutput(ppOutput);
	}

	HRESULT STDMETHODCALLTYPE GetFrameStatistics(
	    /* [annotation][out] */
	    _Out_ DXGI_FRAME_STATISTICS *pStats) override
	{
		return m_real->GetFrameStatistics(pStats);
	}

	HRESULT STDMETHODCALLTYPE GetLastPresentCount(
	    /* [annotation][out] */
	    _Out_ UINT *pLastPresentCount) override
	{
		return m_real->GetLastPresentCount(pLastPresentCount);
	}

	HRESULT STDMETHODCALLTYPE GetDesc1(
	    /* [annotation][out] */
	    _Out_ DXGI_SWAP_CHAIN_DESC1 *pDesc) override
	{
		return m_real->GetDesc1(pDesc);
	}

	HRESULT STDMETHODCALLTYPE GetFullscreenDesc(
	    /* [annotation][out] */
	    _Out_ DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pDesc) override
	{
		return m_real->GetFullscreenDesc(pDesc);
	}

	HRESULT STDMETHODCALLTYPE GetHwnd(
	    /* [annotation][out] */
	    _Out_ HWND *pHwnd) override
	{
		return m_real->GetHwnd(pHwnd);
	}

	HRESULT STDMETHODCALLTYPE GetCoreWindow(
	    /* [annotation][in] */
	    _In_ REFIID refiid,
	    /* [annotation][out] */
	    _COM_Outptr_ void **ppUnk) override
	{
		return m_real->GetCoreWindow(refiid, ppUnk);
	}

	HRESULT STDMETHODCALLTYPE Present1(
	    /* [in] */ UINT SyncInterval,
	    /* [in] */ UINT PresentFlags,
	    /* [annotation][in] */
	    _In_ const DXGI_PRESENT_PARAMETERS *pPresentParameters) override
	{
		return m_real->Present1(SyncInterval, PresentFlags, pPresentParameters);
	}

	BOOL STDMETHODCALLTYPE IsTemporaryMonoSupported(void) override { return m_real->IsTemporaryMonoSupported(); }

	HRESULT STDMETHODCALLTYPE GetRestrictToOutput(
	    /* [annotation][out] */
	    _Out_ IDXGIOutput **ppRestrictToOutput) override
	{
		return m_real->GetRestrictToOutput(ppRestrictToOutput);
	}

	HRESULT STDMETHODCALLTYPE SetBackgroundColor(
	    /* [annotation][in] */
	    _In_ const DXGI_RGBA *pColor) override
	{
		return m_real->SetBackgroundColor(pColor);
	}

	HRESULT STDMETHODCALLTYPE GetBackgroundColor(
	    /* [annotation][out] */
	    _Out_ DXGI_RGBA *pColor) override
	{
		return m_real->GetBackgroundColor(pColor);
	}

	HRESULT STDMETHODCALLTYPE SetRotation(
	    /* [annotation][in] */
	    _In_ DXGI_MODE_ROTATION Rotation) override
	{
		return m_real->SetRotation(Rotation);
	}

	HRESULT STDMETHODCALLTYPE GetRotation(
	    /* [annotation][out] */
	    _Out_ DXGI_MODE_ROTATION *pRotation) override
	{
		return m_real->GetRotation(pRotation);
	}

	IDXGISwapChain1 *m_real = nullptr;
};
