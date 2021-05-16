#define DXWRAP_EXPORT_LOGGER
#include "logger.hpp"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>

namespace dxwrap {

using namespace std::chrono;

void log(const std::string &message)
{
	static std::ofstream logfile("dxwrap.log");

	OutputDebugStringA(("dxwrap: " + message).c_str());

	const auto now = system_clock::to_time_t(system_clock::now());
	logfile << std::put_time(std::localtime(&now), "%Y-%m-%d %X") << " " << message << std::endl;
}

} // namespace dxwrap
