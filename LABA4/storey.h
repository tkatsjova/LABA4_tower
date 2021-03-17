#pragma once
#include <vector>

#include "room.h"



namespace lab4
{	class storey
	{
	std::vector<room> rooms;
	public:
		std::vector<room>& get_rooms();
		void add_room(room room);
		bool add_room(unsigned max_rooms);
		int max_enemy_room();
		bool is_secured();
		void get_nearest_enemied_room(int current, int& max, int& min);
		bool is_generated();
		void get_nearest_empty_room(int current, int& max, int& min);
		void add_room_uncoditionnaly();
		};
	

}