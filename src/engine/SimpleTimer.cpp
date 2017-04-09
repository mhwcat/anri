#include <chrono>
#include <engine/SimpleTimer.h>
#include <engine/DebugPrint.h>

SimpleTimer::SimpleTimer()
{
	// Initialize begin value to prevent counting delta using undefined value
	begin = std::chrono::steady_clock::now();
}

void SimpleTimer::start()
{
	begin = std::chrono::steady_clock::now();
}


long SimpleTimer::getMillisecondsSinceStart()
{
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

long SimpleTimer::getMicrosecondsSinceStart()
{
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	return std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
}