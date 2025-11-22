#pragma once

#include "../../../external/rapidxml-1.13/rapidxml.hpp"

namespace XMLHelper {
	float GetFloatAttribute(rapidxml::xml_node<>* Node, const char* AttributeName);
	int GetIntAttribute(rapidxml::xml_node<>* Node, const char* AttributeName);
}