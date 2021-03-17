#pragma once
class input_data
{
public:
	int total_storeys = 3; //N
	int hero_level = 4; //LvL
	int total_rooms = 15; //K
	int rooms_per_storey = 5;//max_K
	int enemy_per_room = 5;
		
	input_data(int total_storeys, int hero_level, int total_rooms, int rooms_per_storey, int enemy_per_room)
	{
		this->total_storeys = total_storeys;
		this->hero_level = hero_level;
		this->total_rooms = total_rooms;
		this->rooms_per_storey = rooms_per_storey;
		this->enemy_per_room = enemy_per_room;
	}
};

