#include "XMLHelper.h"

namespace XMLHelper {
	float GetFloatAttribute(rapidxml::xml_node<>* Node, const char* AttributeName)
	{
		if (!Node)
			return 0.0f;

		rapidxml::xml_attribute<>* Attribute = Node->first_attribute(AttributeName);
		if (!Attribute)
			return 0.0f;

		return (float)atof(Attribute->value());
	}
	int GetIntAttribute(rapidxml::xml_node<>* Node, const char* AttributeName)
	{
		if (!Node)
			return 0.0f;

		rapidxml::xml_attribute<>* Attribute = Node->first_attribute(AttributeName);
		if (!Attribute)
			return 0.0f;

		return atoi(Attribute->value());
	}
}