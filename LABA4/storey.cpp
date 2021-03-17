#include "storey.h"
#include <vector>
#include <cstdlib>
#include <iostream>


void lab4::storey::add_room(room room)
{
	this->rooms.push_back(room);
}

bool lab4::storey::add_room(unsigned max_rooms)
{
	if (this->rooms.size() >= max_rooms)
	{
		return false;
	}

	int random_result = rand() % 2;
	if (random_result == 1)
	{
		room new_room;
		this->rooms.push_back(new_room);
		return true;
	}
	return false;
}

void lab4::storey::add_room_uncoditionnaly()
{
	room new_room;
	rooms.push_back(new_room);
}

std::vector<room>& lab4::storey::get_rooms()
{
	return rooms;
}

int lab4::storey::max_enemy_room()
{
	int max_enemies = 0;
	for (int i = 0; i < rooms.size(); ++i)
	{
		if (rooms[i].get_enemy().size() > max_enemies)
		{
			max_enemies = rooms[i].get_enemy().size();
		}
	}
	return max_enemies;
}

bool lab4::storey::is_secured()
{

	for (int i = 0; i < rooms.size(); i++)
	{
		if (!rooms[i].is_empty())
			return false;
	}
	return true;
}

void lab4::storey::get_nearest_enemied_room(int current, int& max, int& min)
{
	if (rooms.size() == 1)
	{
		max = 0;
		min = 0;
		return;
	}
	max = rooms.size() - 1;
	min = 0;
	int i = current;
	do
	{
		i++;
		if (i >= rooms.size())
		{
			i = 0;
		}

	} while (rooms[i].is_empty());
	max = i;
	i = current;
	do
	{
		i--;
		if (i < 0)
		{
			i = rooms.size() - 1;
		}

	} while (rooms[i].is_empty());
	min = i;

}

bool lab4::storey::is_generated()
{
	for (int i = 0; i < rooms.size(); i++)
	{
		if (!rooms[i].is_generated_with_enemies())
			return false;
	}
	return true;
}

void lab4::storey::get_nearest_empty_room(int current, int& max, int& min)

{

	if (rooms.size() == 1)
	{
		max = 0;
		min = 0;
		return;
	}
	max = rooms.size() - 1;
	min = 0;
	int i = current;
	do
	{
		i++;
		if (i >= rooms.size())
		{
			i = 0;
		}

	} while (rooms[i].is_generated_with_enemies());
	max = i;
	i = current;
	do
	{
		i--;
		if (i < 0)
		{
			i = rooms.size() - 1;
		}

	} while (rooms[i].is_generated_with_enemies());
	min = i;

}


