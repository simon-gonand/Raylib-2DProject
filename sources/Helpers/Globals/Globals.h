#pragma once

#include <string>
#include <vector>

#define PTM_RATIO 10.0f

namespace StringHelper
{
	void ParseIntoArray(std::vector<std::string>& OutArray, const std::string& InStr, char Delimiter);
}