#include <string>

#define D3D11CreateDevice D3D11CreateDevice_
#define D3D11CreateDeviceAndSwapChain D3D11CreateDeviceAndSwapChain_
#include <d3d11.h>
#undef D3D11CreateDevice
#undef D3D11CreateDeviceAndSwapChain

#include "dxgi_swap_chain.hpp"

#include "d3d11_device.hpp"

#define DLLEXPORT __declspec(dllexport)

decltype(&D3D11CreateDevice_) _D3D11CreateDevice;
decltype(&D3D11CreateDeviceAndSwapChain_) _D3D11CreateDeviceAndSwapChain;

struct PfnInit {
	PfnInit()
	{
		std::string systemDir(MAX_PATH, '\0');
		{
			const auto n = GetSystemDirectoryA(systemDir.data(), systemDir.size());
			systemDir.resize(n);
		}

		HMODULE hDll = LoadLibraryA((systemDir + "\\d3d11.dll").c_str());
		if (!hDll) {
			return;
		}

		_D3D11CreateDevice = (decltype(_D3D11CreateDevice))GetProcAddress(hDll, "D3D11CreateDevice");
		_D3D11CreateDeviceAndSwapChain =
		    (decltype(_D3D11CreateDeviceAndSwapChain))GetProcAddress(hDll, "D3D11CreateDeviceAndSwapChain");
	}
} g_pfnInit;

extern "C" {
DLLEXPORT HRESULT WINAPI D3D11CreateDevice(IDXGIAdapter *pAdapter, D3D_DRIVER_TYPE DriverType, HMODULE Software,
                                           UINT Flags, const D3D_FEATURE_LEVEL *pFeatureLevels, UINT FeatureLevels,
                                           UINT SDKVersion, ID3D11Device **ppDevice, D3D_FEATURE_LEVEL *pFeatureLevel,
                                           ID3D11DeviceContext **ppImmediateContext)
{
	auto device = new D3D11DeviceWrapper();

	HRESULT result = _D3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels,
	                                    SDKVersion, &device->m_real, pFeatureLevel, ppImmediateContext);

	*ppDevice = static_cast<ID3D11Device *>(device);
	return result;
}

DLLEXPORT HRESULT WINAPI D3D11CreateDeviceAndSwapChain(IDXGIAdapter *pAdapter, D3D_DRIVER_TYPE DriverType,
                                                       HMODULE Software, UINT Flags,
                                                       const D3D_FEATURE_LEVEL *pFeatureLevels, UINT FeatureLevels,
                                                       UINT SDKVersion, const DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
                                                       IDXGISwapChain **ppSwapChain, ID3D11Device **ppDevice,
                                                       D3D_FEATURE_LEVEL *pFeatureLevel,
                                                       ID3D11DeviceContext **ppImmediateContext)
{
	auto swapChain = new DXGISwapChainWrapper();
	auto device = new D3D11DeviceWrapper();

	HRESULT result = _D3D11CreateDeviceAndSwapChain(
	    pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc,
	    (IDXGISwapChain **)&swapChain->m_real, &device->m_real, pFeatureLevel, ppImmediateContext);

	*ppSwapChain = static_cast<IDXGISwapChain *>(swapChain);
	*ppDevice = static_cast<ID3D11Device *>(device);
	return result;
}
}
