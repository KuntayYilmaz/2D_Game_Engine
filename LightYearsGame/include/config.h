#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG //RELEASE BUILD
	return "assets/";
#else
	return "C:/dev/LightYears/LightYearsGame/assets/";
#endif
}
