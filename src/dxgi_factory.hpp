#pragma once

#include <dxgi1_2.h>

class DXGIFactoryWrapper : public IDXGIFactory2 {
  public:
	HRESULT STDMETHODCALLTYPE QueryInterface(
	    /* [in] */ REFIID riid,
	    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject) override
	{
		return m_real->QueryInterface(riid, ppvObject);
	}

	ULONG STDMETHODCALLTYPE AddRef(void) override { return m_real->AddRef(); }

	ULONG STDMETHODCALLTYPE Release(void) override { return m_real->Release(); }

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

	HRESULT STDMETHODCALLTYPE EnumAdapters(
	    /* [in] */ UINT Adapter,
	    /* [annotation][out] */
	    _COM_Outptr_ IDXGIAdapter **ppAdapter) override
	{
		return m_real->EnumAdapters(Adapter, ppAdapter);
	}

	HRESULT STDMETHODCALLTYPE MakeWindowAssociation(HWND WindowHandle, UINT Flags) override
	{
		return m_real->MakeWindowAssociation(WindowHandle, Flags);
	}

	HRESULT STDMETHODCALLTYPE GetWindowAssociation(
	    /* [annotation][out] */
	    _Out_ HWND *pWindowHandle) override
	{
		return m_real->GetWindowAssociation(pWindowHandle);
	}

	HRESULT STDMETHODCALLTYPE CreateSwapChain(
	    /* [annotation][in] */
	    _In_ IUnknown *pDevice,
	    /* [annotation][in] */
	    _In_ DXGI_SWAP_CHAIN_DESC *pDesc,
	    /* [annotation][out] */
	    _COM_Outptr_ IDXGISwapChain **ppSwapChain) override
	{
		auto dxgiSwapChainWrapper = new DXGISwapChainWrapper();

		HRESULT result = m_real->CreateSwapChain(pDevice, pDesc, (IDXGISwapChain **)&dxgiSwapChainWrapper->m_real);
		*ppSwapChain = static_cast<IDXGISwapChain *>(dxgiSwapChainWrapper);
		return result;
	}

	HRESULT STDMETHODCALLTYPE CreateSoftwareAdapter(
	    /* [in] */ HMODULE Module,
	    /* [annotation][out] */
	    _COM_Outptr_ IDXGIAdapter **ppAdapter) override
	{
		return m_real->CreateSoftwareAdapter(Module, ppAdapter);
	}

	HRESULT STDMETHODCALLTYPE EnumAdapters1(
	    /* [in] */ UINT Adapter,
	    /* [annotation][out] */
	    _COM_Outptr_ IDXGIAdapter1 **ppAdapter) override
	{
		return m_real->EnumAdapters1(Adapter, ppAdapter);
	}

	BOOL STDMETHODCALLTYPE IsCurrent(void) override { return m_real->IsCurrent(); }

	BOOL STDMETHODCALLTYPE IsWindowedStereoEnabled(void) override { return m_real->IsWindowedStereoEnabled(); }

	HRESULT STDMETHODCALLTYPE CreateSwapChainForHwnd(
	    /* [annotation][in] */
	    _In_ IUnknown *pDevice,
	    /* [annotation][in] */
	    _In_ HWND hWnd,
	    /* [annotation][in] */
	    _In_ const DXGI_SWAP_CHAIN_DESC1 *pDesc,
	    /* [annotation][in] */
	    _In_opt_ const DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pFullscreenDesc,
	    /* [annotation][in] */
	    _In_opt_ IDXGIOutput *pRestrictToOutput,
	    /* [annotation][out] */
	    _COM_Outptr_ IDXGISwapChain1 **ppSwapChain) override
	{
		auto dxgiSwapChainWrapper = new DXGISwapChainWrapper();

		HRESULT result = m_real->CreateSwapChainForHwnd(pDevice, hWnd, pDesc, pFullscreenDesc, pRestrictToOutput,
		                                                &dxgiSwapChainWrapper->m_real);
		*ppSwapChain = static_cast<IDXGISwapChain1 *>(dxgiSwapChainWrapper);
		return result;
	}

	HRESULT STDMETHODCALLTYPE CreateSwapChainForCoreWindow(
	    /* [annotation][in] */
	    _In_ IUnknown *pDevice,
	    /* [annotation][in] */
	    _In_ IUnknown *pWindow,
	    /* [annotation][in] */
	    _In_ const DXGI_SWAP_CHAIN_DESC1 *pDesc,
	    /* [annotation][in] */
	    _In_opt_ IDXGIOutput *pRestrictToOutput,
	    /* [annotation][out] */
	    _COM_Outptr_ IDXGISwapChain1 **ppSwapChain) override
	{
		auto dxgiSwapChainWrapper = new DXGISwapChainWrapper();

		HRESULT result = m_real->CreateSwapChainForCoreWindow(pDevice, pWindow, pDesc, pRestrictToOutput,
		                                                      &dxgiSwapChainWrapper->m_real);
		*ppSwapChain = static_cast<IDXGISwapChain1 *>(dxgiSwapChainWrapper);
		return result;
	}

	HRESULT STDMETHODCALLTYPE GetSharedResourceAdapterLuid(
	    /* [annotation] */
	    _In_ HANDLE hResource,
	    /* [annotation] */
	    _Out_ LUID *pLuid) override
	{
		return m_real->GetSharedResourceAdapterLuid(hResource, pLuid);
	}

	HRESULT STDMETHODCALLTYPE RegisterStereoStatusWindow(
	    /* [annotation][in] */
	    _In_ HWND WindowHandle,
	    /* [annotation][in] */
	    _In_ UINT wMsg,
	    /* [annotation][out] */
	    _Out_ DWORD *pdwCookie) override
	{
		return m_real->RegisterStereoStatusWindow(WindowHandle, wMsg, pdwCookie);
	}

	HRESULT STDMETHODCALLTYPE RegisterStereoStatusEvent(
	    /* [annotation][in] */
	    _In_ HANDLE hEvent,
	    /* [annotation][out] */
	    _Out_ DWORD *pdwCookie) override
	{
		return m_real->RegisterStereoStatusEvent(hEvent, pdwCookie);
	}

	void STDMETHODCALLTYPE UnregisterStereoStatus(
	    /* [annotation][in] */
	    _In_ DWORD dwCookie) override
	{
		m_real->UnregisterStereoStatus(dwCookie);
	}

	HRESULT STDMETHODCALLTYPE RegisterOcclusionStatusWindow(
	    /* [annotation][in] */
	    _In_ HWND WindowHandle,
	    /* [annotation][in] */
	    _In_ UINT wMsg,
	    /* [annotation][out] */
	    _Out_ DWORD *pdwCookie) override
	{
		return m_real->RegisterOcclusionStatusWindow(WindowHandle, wMsg, pdwCookie);
	}

	HRESULT STDMETHODCALLTYPE RegisterOcclusionStatusEvent(
	    /* [annotation][in] */
	    _In_ HANDLE hEvent,
	    /* [annotation][out] */
	    _Out_ DWORD *pdwCookie) override
	{
		return m_real->RegisterOcclusionStatusEvent(hEvent, pdwCookie);
	}

	void STDMETHODCALLTYPE UnregisterOcclusionStatus(
	    /* [annotation][in] */
	    _In_ DWORD dwCookie) override
	{
		m_real->UnregisterOcclusionStatus(dwCookie);
	}

	HRESULT STDMETHODCALLTYPE CreateSwapChainForComposition(
	    /* [annotation][in] */
	    _In_ IUnknown *pDevice,
	    /* [annotation][in] */
	    _In_ const DXGI_SWAP_CHAIN_DESC1 *pDesc,
	    /* [annotation][in] */
	    _In_opt_ IDXGIOutput *pRestrictToOutput,
	    /* [annotation][out] */
	    _COM_Outptr_ IDXGISwapChain1 **ppSwapChain) override
	{
		auto dxgiSwapChainWrapper = new DXGISwapChainWrapper();

		HRESULT result =
		    m_real->CreateSwapChainForComposition(pDevice, pDesc, pRestrictToOutput, &dxgiSwapChainWrapper->m_real);
		*ppSwapChain = static_cast<IDXGISwapChain1 *>(dxgiSwapChainWrapper);
		return result;
	}

	IDXGIFactory2 *m_real = nullptr;
};
