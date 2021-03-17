#pragma once
#include <vector>

#include "storey.h"

using namespace lab4;
class building
{
	std::vector<storey> storeys;
	

public:
	void add_storey(storey stry);
	std::vector<storey>& get_storey();
};

