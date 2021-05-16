#pragma once

#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef DXWRAP_EXPORT_LOGGER
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif

#ifdef _DEBUG
#define LOG(message) ::dxwrap::log(__FUNCTION__ + std::string{" "} + std::string{message})
#else
#define LOG(message)
#endif

namespace dxwrap {

DLLEXPORT void log(const std::string &message);

} // namespace dxwrap

#undef DLLEXPORT

static inline std::string to_string(GUID guid)
{
	std::string result(39, '\0');
	sprintf(result.data(), "{%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX}", guid.Data1,
	        guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4],
	        guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	return result;
}
