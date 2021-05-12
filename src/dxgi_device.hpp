#pragma once

#include <dxgi1_2.h>

#include "dxgi_adapter.hpp"

class DXGIDeviceWrapper : public IDXGIDevice {
  public:
	HRESULT STDMETHODCALLTYPE QueryInterface(
	    /* [in] */ REFIID riid,
	    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject) override
	{
		return m_real->QueryInterface(riid, ppvObject);
	}

	ULONG STDMETHODCALLTYPE AddRef(void) override { return m_real->AddRef(); }

	ULONG STDMETHODCALLTYPE Release(void) override
	{
		const auto count = m_real->Release();
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

	HRESULT STDMETHODCALLTYPE GetAdapter(
	    /* [annotation][out] */
	    _COM_Outptr_ IDXGIAdapter **pAdapter) override
	{
		auto adapter = new DXGIAdapterWrapper();

		HRESULT result = m_real->GetAdapter(&adapter->m_real);

		*pAdapter = adapter;
		return result;
	}

	HRESULT STDMETHODCALLTYPE CreateSurface(
	    /* [annotation][in] */
	    _In_ const DXGI_SURFACE_DESC *pDesc,
	    /* [in] */ UINT NumSurfaces,
	    /* [in] */ DXGI_USAGE Usage,
	    /* [annotation][in] */
	    _In_opt_ const DXGI_SHARED_RESOURCE *pSharedResource,
	    /* [annotation][out] */
	    _COM_Outptr_ IDXGISurface **ppSurface) override
	{
		return m_real->CreateSurface(pDesc, NumSurfaces, Usage, pSharedResource, ppSurface);
	}

	HRESULT STDMETHODCALLTYPE QueryResourceResidency(
	    /* [annotation][size_is][in] */
	    _In_reads_(NumResources) IUnknown *const *ppResources,
	    /* [annotation][size_is][out] */
	    _Out_writes_(NumResources) DXGI_RESIDENCY *pResidencyStatus,
	    /* [in] */ UINT NumResources) override
	{
		return m_real->QueryResourceResidency(ppResources, pResidencyStatus, NumResources);
	}

	HRESULT STDMETHODCALLTYPE SetGPUThreadPriority(
	    /* [in] */ INT Priority) override
	{
		return m_real->SetGPUThreadPriority(Priority);
	}

	HRESULT STDMETHODCALLTYPE GetGPUThreadPriority(
	    /* [annotation][retval][out] */
	    _Out_ INT *pPriority) override
	{
		return m_real->GetGPUThreadPriority(pPriority);
	}

	IDXGIDevice *m_real = nullptr;
};
