#pragma once
#include <string>
#include <vector>

#include "person.h"

class room
{
	bool generated_with_enemies = false;
	std::vector<person> enemies;
public:
	void add_person(int enemy_per_room);
	std::vector<person>& get_enemy();
	std::string get_enemy_level_by_index(int index);
	bool is_empty();
	void generate_enemies(person &wizard, int enemies_per_room);
	bool is_generated_with_enemies();
};

