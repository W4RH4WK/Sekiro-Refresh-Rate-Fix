#pragma once

#include <d3d11.h>

#include "dxgi_device.hpp"

class D3D11DeviceWrapper : public ID3D11Device {
  public:
	HRESULT STDMETHODCALLTYPE QueryInterface(
	    /* [in] */ REFIID riid,
	    /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject) override
	{
		if (riid == __uuidof(IDXGIDevice)) {
			auto device = new DXGIDeviceWrapper();

			HRESULT result = m_real->QueryInterface(riid, (void **)&device->m_real);

			*ppvObject = device;
			return result;
		}

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

	HRESULT STDMETHODCALLTYPE CreateBuffer(
	    /* [annotation] */
	    _In_ const D3D11_BUFFER_DESC *pDesc,
	    /* [annotation] */
	    _In_opt_ const D3D11_SUBRESOURCE_DATA *pInitialData,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11Buffer **ppBuffer) override
	{
		return m_real->CreateBuffer(pDesc, pInitialData, ppBuffer);
	}

	HRESULT STDMETHODCALLTYPE CreateTexture1D(
	    /* [annotation] */
	    _In_ const D3D11_TEXTURE1D_DESC *pDesc,
	    /* [annotation] */
	    _In_reads_opt_(_Inexpressible_(pDesc->MipLevels * pDesc->ArraySize)) const D3D11_SUBRESOURCE_DATA *pInitialData,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11Texture1D **ppTexture1D) override
	{
		return m_real->CreateTexture1D(pDesc, pInitialData, ppTexture1D);
	}

	HRESULT STDMETHODCALLTYPE CreateTexture2D(
	    /* [annotation] */
	    _In_ const D3D11_TEXTURE2D_DESC *pDesc,
	    /* [annotation] */
	    _In_reads_opt_(_Inexpressible_(pDesc->MipLevels * pDesc->ArraySize)) const D3D11_SUBRESOURCE_DATA *pInitialData,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11Texture2D **ppTexture2D) override
	{
		return m_real->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
	}

	HRESULT STDMETHODCALLTYPE CreateTexture3D(
	    /* [annotation] */
	    _In_ const D3D11_TEXTURE3D_DESC *pDesc,
	    /* [annotation] */
	    _In_reads_opt_(_Inexpressible_(pDesc->MipLevels)) const D3D11_SUBRESOURCE_DATA *pInitialData,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11Texture3D **ppTexture3D) override
	{
		return m_real->CreateTexture3D(pDesc, pInitialData, ppTexture3D);
	}

	HRESULT STDMETHODCALLTYPE CreateShaderResourceView(
	    /* [annotation] */
	    _In_ ID3D11Resource *pResource,
	    /* [annotation] */
	    _In_opt_ const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11ShaderResourceView **ppSRView) override
	{
		return m_real->CreateShaderResourceView(pResource, pDesc, ppSRView);
	}

	HRESULT STDMETHODCALLTYPE CreateUnorderedAccessView(
	    /* [annotation] */
	    _In_ ID3D11Resource *pResource,
	    /* [annotation] */
	    _In_opt_ const D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11UnorderedAccessView **ppUAView) override
	{
		return m_real->CreateUnorderedAccessView(pResource, pDesc, ppUAView);
	}

	HRESULT STDMETHODCALLTYPE CreateRenderTargetView(
	    /* [annotation] */
	    _In_ ID3D11Resource *pResource,
	    /* [annotation] */
	    _In_opt_ const D3D11_RENDER_TARGET_VIEW_DESC *pDesc,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11RenderTargetView **ppRTView) override
	{
		return m_real->CreateRenderTargetView(pResource, pDesc, ppRTView);
	}

	HRESULT STDMETHODCALLTYPE CreateDepthStencilView(
	    /* [annotation] */
	    _In_ ID3D11Resource *pResource,
	    /* [annotation] */
	    _In_opt_ const D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11DepthStencilView **ppDepthStencilView) override
	{
		return m_real->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
	}

	HRESULT STDMETHODCALLTYPE CreateInputLayout(
	    /* [annotation] */
	    _In_reads_(NumElements) const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,
	    /* [annotation] */
	    _In_range_(0, D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT) UINT NumElements,
	    /* [annotation] */
	    _In_reads_(BytecodeLength) const void *pShaderBytecodeWithInputSignature,
	    /* [annotation] */
	    _In_ SIZE_T BytecodeLength,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11InputLayout **ppInputLayout) override
	{
		return m_real->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature,
		                                 BytecodeLength, ppInputLayout);
	}

	HRESULT STDMETHODCALLTYPE CreateVertexShader(
	    /* [annotation] */
	    _In_reads_(BytecodeLength) const void *pShaderBytecode,
	    /* [annotation] */
	    _In_ SIZE_T BytecodeLength,
	    /* [annotation] */
	    _In_opt_ ID3D11ClassLinkage *pClassLinkage,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11VertexShader **ppVertexShader) override
	{
		return m_real->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
	}

	HRESULT STDMETHODCALLTYPE CreateGeometryShader(
	    /* [annotation] */
	    _In_reads_(BytecodeLength) const void *pShaderBytecode,
	    /* [annotation] */
	    _In_ SIZE_T BytecodeLength,
	    /* [annotation] */
	    _In_opt_ ID3D11ClassLinkage *pClassLinkage,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11GeometryShader **ppGeometryShader) override
	{
		return m_real->CreateGeometryShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppGeometryShader);
	}

	HRESULT STDMETHODCALLTYPE CreateGeometryShaderWithStreamOutput(
	    /* [annotation] */
	    _In_reads_(BytecodeLength) const void *pShaderBytecode,
	    /* [annotation] */
	    _In_ SIZE_T BytecodeLength,
	    /* [annotation] */
	    _In_reads_opt_(NumEntries) const D3D11_SO_DECLARATION_ENTRY *pSODeclaration,
	    /* [annotation] */
	    _In_range_(0, D3D11_SO_STREAM_COUNT *D3D11_SO_OUTPUT_COMPONENT_COUNT) UINT NumEntries,
	    /* [annotation] */
	    _In_reads_opt_(NumStrides) const UINT *pBufferStrides,
	    /* [annotation] */
	    _In_range_(0, D3D11_SO_BUFFER_SLOT_COUNT) UINT NumStrides,
	    /* [annotation] */
	    _In_ UINT RasterizedStream,
	    /* [annotation] */
	    _In_opt_ ID3D11ClassLinkage *pClassLinkage,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11GeometryShader **ppGeometryShader) override
	{
		return m_real->CreateGeometryShaderWithStreamOutput(pShaderBytecode, BytecodeLength, pSODeclaration, NumEntries,
		                                                    pBufferStrides, NumStrides, RasterizedStream, pClassLinkage,
		                                                    ppGeometryShader);
	}

	HRESULT STDMETHODCALLTYPE CreatePixelShader(
	    /* [annotation] */
	    _In_reads_(BytecodeLength) const void *pShaderBytecode,
	    /* [annotation] */
	    _In_ SIZE_T BytecodeLength,
	    /* [annotation] */
	    _In_opt_ ID3D11ClassLinkage *pClassLinkage,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11PixelShader **ppPixelShader) override
	{
		return m_real->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
	}

	HRESULT STDMETHODCALLTYPE CreateHullShader(
	    /* [annotation] */
	    _In_reads_(BytecodeLength) const void *pShaderBytecode,
	    /* [annotation] */
	    _In_ SIZE_T BytecodeLength,
	    /* [annotation] */
	    _In_opt_ ID3D11ClassLinkage *pClassLinkage,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11HullShader **ppHullShader) override
	{
		return m_real->CreateHullShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppHullShader);
	}

	HRESULT STDMETHODCALLTYPE CreateDomainShader(
	    /* [annotation] */
	    _In_reads_(BytecodeLength) const void *pShaderBytecode,
	    /* [annotation] */
	    _In_ SIZE_T BytecodeLength,
	    /* [annotation] */
	    _In_opt_ ID3D11ClassLinkage *pClassLinkage,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11DomainShader **ppDomainShader) override
	{
		return m_real->CreateDomainShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppDomainShader);
	}

	HRESULT STDMETHODCALLTYPE CreateComputeShader(
	    /* [annotation] */
	    _In_reads_(BytecodeLength) const void *pShaderBytecode,
	    /* [annotation] */
	    _In_ SIZE_T BytecodeLength,
	    /* [annotation] */
	    _In_opt_ ID3D11ClassLinkage *pClassLinkage,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11ComputeShader **ppComputeShader) override
	{
		return m_real->CreateComputeShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader);
	}

	HRESULT STDMETHODCALLTYPE CreateClassLinkage(
	    /* [annotation] */
	    _COM_Outptr_ ID3D11ClassLinkage **ppLinkage) override
	{
		return m_real->CreateClassLinkage(ppLinkage);
	}

	HRESULT STDMETHODCALLTYPE CreateBlendState(
	    /* [annotation] */
	    _In_ const D3D11_BLEND_DESC *pBlendStateDesc,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11BlendState **ppBlendState) override
	{
		return m_real->CreateBlendState(pBlendStateDesc, ppBlendState);
	}

	HRESULT STDMETHODCALLTYPE CreateDepthStencilState(
	    /* [annotation] */
	    _In_ const D3D11_DEPTH_STENCIL_DESC *pDepthStencilDesc,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11DepthStencilState **ppDepthStencilState) override
	{
		return m_real->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState);
	}

	HRESULT STDMETHODCALLTYPE CreateRasterizerState(
	    /* [annotation] */
	    _In_ const D3D11_RASTERIZER_DESC *pRasterizerDesc,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11RasterizerState **ppRasterizerState) override
	{
		return m_real->CreateRasterizerState(pRasterizerDesc, ppRasterizerState);
	}

	HRESULT STDMETHODCALLTYPE CreateSamplerState(
	    /* [annotation] */
	    _In_ const D3D11_SAMPLER_DESC *pSamplerDesc,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11SamplerState **ppSamplerState) override
	{
		return m_real->CreateSamplerState(pSamplerDesc, ppSamplerState);
	}

	HRESULT STDMETHODCALLTYPE CreateQuery(
	    /* [annotation] */
	    _In_ const D3D11_QUERY_DESC *pQueryDesc,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11Query **ppQuery) override
	{
		return m_real->CreateQuery(pQueryDesc, ppQuery);
	}

	HRESULT STDMETHODCALLTYPE CreatePredicate(
	    /* [annotation] */
	    _In_ const D3D11_QUERY_DESC *pPredicateDesc,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11Predicate **ppPredicate) override
	{
		return m_real->CreatePredicate(pPredicateDesc, ppPredicate);
	}

	HRESULT STDMETHODCALLTYPE CreateCounter(
	    /* [annotation] */
	    _In_ const D3D11_COUNTER_DESC *pCounterDesc,
	    /* [annotation] */
	    _COM_Outptr_opt_ ID3D11Counter **ppCounter) override
	{
		return m_real->CreateCounter(pCounterDesc, ppCounter);
	}

	HRESULT STDMETHODCALLTYPE CreateDeferredContext(UINT ContextFlags,
	                                                /* [annotation] */
	                                                _COM_Outptr_opt_ ID3D11DeviceContext **ppDeferredContext) override
	{
		return m_real->CreateDeferredContext(ContextFlags, ppDeferredContext);
	}

	HRESULT STDMETHODCALLTYPE OpenSharedResource(
	    /* [annotation] */
	    _In_ HANDLE hResource,
	    /* [annotation] */
	    _In_ REFIID ReturnedInterface,
	    /* [annotation] */
	    _COM_Outptr_opt_ void **ppResource) override
	{
		return m_real->OpenSharedResource(hResource, ReturnedInterface, ppResource);
	}

	HRESULT STDMETHODCALLTYPE CheckFormatSupport(
	    /* [annotation] */
	    _In_ DXGI_FORMAT Format,
	    /* [annotation] */
	    _Out_ UINT *pFormatSupport) override
	{
		return m_real->CheckFormatSupport(Format, pFormatSupport);
	}

	HRESULT STDMETHODCALLTYPE CheckMultisampleQualityLevels(
	    /* [annotation] */
	    _In_ DXGI_FORMAT Format,
	    /* [annotation] */
	    _In_ UINT SampleCount,
	    /* [annotation] */
	    _Out_ UINT *pNumQualityLevels) override
	{
		return m_real->CheckMultisampleQualityLevels(Format, SampleCount, pNumQualityLevels);
	}

	void STDMETHODCALLTYPE CheckCounterInfo(
	    /* [annotation] */
	    _Out_ D3D11_COUNTER_INFO *pCounterInfo) override
	{
		m_real->CheckCounterInfo(pCounterInfo);
	}

	HRESULT STDMETHODCALLTYPE CheckCounter(
	    /* [annotation] */
	    _In_ const D3D11_COUNTER_DESC *pDesc,
	    /* [annotation] */
	    _Out_ D3D11_COUNTER_TYPE *pType,
	    /* [annotation] */
	    _Out_ UINT *pActiveCounters,
	    /* [annotation] */
	    _Out_writes_opt_(*pNameLength) LPSTR szName,
	    /* [annotation] */
	    _Inout_opt_ UINT *pNameLength,
	    /* [annotation] */
	    _Out_writes_opt_(*pUnitsLength) LPSTR szUnits,
	    /* [annotation] */
	    _Inout_opt_ UINT *pUnitsLength,
	    /* [annotation] */
	    _Out_writes_opt_(*pDescriptionLength) LPSTR szDescription,
	    /* [annotation] */
	    _Inout_opt_ UINT *pDescriptionLength) override
	{
		return m_real->CheckCounter(pDesc, pType, pActiveCounters, szName, pNameLength, szUnits, pUnitsLength,
		                            szDescription, pDescriptionLength);
	}

	HRESULT STDMETHODCALLTYPE CheckFeatureSupport(D3D11_FEATURE Feature,
	                                              /* [annotation] */
	                                              _Out_writes_bytes_(FeatureSupportDataSize) void *pFeatureSupportData,
	                                              UINT FeatureSupportDataSize) override
	{
		return m_real->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
	}

	HRESULT STDMETHODCALLTYPE GetPrivateData(
	    /* [annotation] */
	    _In_ REFGUID guid,
	    /* [annotation] */
	    _Inout_ UINT *pDataSize,
	    /* [annotation] */
	    _Out_writes_bytes_opt_(*pDataSize) void *pData) override
	{
		return m_real->GetPrivateData(guid, pDataSize, pData);
	}

	HRESULT STDMETHODCALLTYPE SetPrivateData(
	    /* [annotation] */
	    _In_ REFGUID guid,
	    /* [annotation] */
	    _In_ UINT DataSize,
	    /* [annotation] */
	    _In_reads_bytes_opt_(DataSize) const void *pData) override
	{
		return m_real->SetPrivateData(guid, DataSize, pData);
	}

	HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(
	    /* [annotation] */
	    _In_ REFGUID guid,
	    /* [annotation] */
	    _In_opt_ const IUnknown *pData) override
	{
		return m_real->SetPrivateDataInterface(guid, pData);
	}

	D3D_FEATURE_LEVEL STDMETHODCALLTYPE GetFeatureLevel(void) override { return m_real->GetFeatureLevel(); }

	UINT STDMETHODCALLTYPE GetCreationFlags(void) override { return m_real->GetCreationFlags(); }

	HRESULT STDMETHODCALLTYPE GetDeviceRemovedReason(void) override { return m_real->GetDeviceRemovedReason(); }

	void STDMETHODCALLTYPE GetImmediateContext(
	    /* [annotation] */
	    _Outptr_ ID3D11DeviceContext **ppImmediateContext) override
	{
		m_real->GetImmediateContext(ppImmediateContext);
	}

	HRESULT STDMETHODCALLTYPE SetExceptionMode(UINT RaiseFlags) override
	{
		return m_real->SetExceptionMode(RaiseFlags);
	}

	UINT STDMETHODCALLTYPE GetExceptionMode(void) override { return m_real->GetExceptionMode(); }

	ID3D11Device *m_real = nullptr;
};
