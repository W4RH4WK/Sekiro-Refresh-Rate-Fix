#pragma once

#include <dxgi1_2.h>

#include "dxgi_factory.hpp"

class DXGIAdapterWrapper : public IDXGIAdapter {
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
		if (riid == __uuidof(IDXGIFactory)) {
			auto factory = new DXGIFactoryWrapper();

			HRESULT result = m_real->GetParent(riid, (void **)&factory->m_real);

			*ppParent = factory;
			return result;
		}

		return m_real->GetParent(riid, ppParent);
	}

	HRESULT STDMETHODCALLTYPE EnumOutputs(
	    /* [in] */ UINT Output,
	    /* [annotation][out][in] */
	    _COM_Outptr_ IDXGIOutput **ppOutput) override
	{
		return m_real->EnumOutputs(Output, ppOutput);
	}

	HRESULT STDMETHODCALLTYPE GetDesc(
	    /* [annotation][out] */
	    _Out_ DXGI_ADAPTER_DESC *pDesc) override
	{
		return m_real->GetDesc(pDesc);
	}

	HRESULT STDMETHODCALLTYPE CheckInterfaceSupport(
	    /* [annotation][in] */
	    _In_ REFGUID InterfaceName,
	    /* [annotation][out] */
	    _Out_ LARGE_INTEGER *pUMDVersion) override
	{
		return m_real->CheckInterfaceSupport(InterfaceName, pUMDVersion);
	}

	IDXGIAdapter *m_real = nullptr;
};
