#pragma once

#include <exception>
#include <iostream>
#include <sstream>
#include <iomanip>

static std::string F2StrFormat(float num, int decimals)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(decimals) << num;
	return static_cast<std::string>(stream.str());
}