#include "building.h"

#include <iostream>
#include <vector>


void building::add_storey(storey stry)
{
	storeys.push_back(stry);
}

std::vector<storey>& building::get_storey()
{
	return storeys;
}
