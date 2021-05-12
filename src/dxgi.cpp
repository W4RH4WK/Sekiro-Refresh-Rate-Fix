#include <string>

#define CreateDXGIFactory CreateDXGIFactory_
#define CreateDXGIFactory1 CreateDXGIFactory1_
#define CreateDXGIFactory2 CreateDXGIFactory2_
#include <dxgi1_3.h>
#undef CreateDXGIFactory
#undef CreateDXGIFactory1
#undef CreateDXGIFactory2

#include "dxgi_swap_chain.hpp"
#include "dxgi_factory.hpp"

#define DLLEXPORT __declspec(dllexport)

decltype(&CreateDXGIFactory_) _CreateDXGIFactory;
decltype(&CreateDXGIFactory1_) _CreateDXGIFactory1;
decltype(&CreateDXGIFactory2_) _CreateDXGIFactory2;

struct PfnInit {
	PfnInit()
	{
		std::string systemDir(MAX_PATH, '\0');
		{
			const auto n = GetSystemDirectoryA(systemDir.data(), systemDir.size());
			systemDir.resize(n);
		}

		HMODULE hDll = LoadLibraryA((systemDir + "\\dxgi.dll").c_str());
		if (!hDll) {
			return;
		}

		_CreateDXGIFactory = (decltype(_CreateDXGIFactory))GetProcAddress(hDll, "CreateDXGIFactory");
		_CreateDXGIFactory1 = (decltype(_CreateDXGIFactory1))GetProcAddress(hDll, "CreateDXGIFactory1");
		_CreateDXGIFactory2 = (decltype(_CreateDXGIFactory2))GetProcAddress(hDll, "CreateDXGIFactory2");
	}
} g_pfnInit;


extern "C" {
DLLEXPORT HRESULT WINAPI CreateDXGIFactory2(UINT Flags, REFIID riid, _COM_Outptr_ void **ppFactory)
{
	auto dxgiFactoryWrapper = new DXGIFactoryWrapper();

	HRESULT result = _CreateDXGIFactory2(Flags, riid, (void **)&dxgiFactoryWrapper->m_real);

	*ppFactory = dxgiFactoryWrapper;
	return S_OK;
}

DLLEXPORT HRESULT WINAPI CreateDXGIFactory(REFIID riid, _COM_Outptr_ void **ppFactory)
{
	return CreateDXGIFactory2(0, riid, ppFactory);
}

DLLEXPORT HRESULT WINAPI CreateDXGIFactory1(REFIID riid, _COM_Outptr_ void **ppFactory)
{
	return CreateDXGIFactory2(0, riid, ppFactory);
}
}
