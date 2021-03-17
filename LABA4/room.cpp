#include "room.h"




#include <string>
#include <vector>

using namespace std;


void room::add_person(int enemy_per_room)
{
	
	int random_result = rand() % (enemy_per_room + 1);
	for (int i = 0; i < random_result; ++i)
	{
		int random_power = rand() % (10000 + 1);
		person enemy;
		enemy.set_level(random_power);
		enemies.push_back(enemy);
	}
}

std::vector<person>& room::get_enemy()
{
	return enemies;
}

string room::get_enemy_level_by_index(int index)
{
		if (index>=enemies.size() || enemies[index].is_dead())
		{
			return "";
		}
		return to_string(enemies[index].get_level());
}

bool room::is_empty()
{
	for (int i = 0; i <enemies.size(); ++i)
	{
		if (!enemies[i].is_dead())
		{
			return false;
		}
	}
	return true;
}

void room::generate_enemies(person &wizard, int enemies_per_room)
{
	if (generated_with_enemies)
		return;
	
	unsigned enemies_amount = rand() % enemies_per_room +1;
	
	for (int i = 0; i < enemies_amount; ++i)
	{
		person enemy;		
		unsigned wizard_level_from = (wizard.get_level() / 7);
		unsigned enemy_power = wizard_level_from + rand() % wizard.get_level()/2;
		if (enemy_power <= 0)
			enemy_power = 1;

		if (enemy_power >= 10000)
			enemy_power = 10000;
		enemy.set_level(enemy_power);
		wizard.set_level(wizard.get_level() + enemy_power);
		enemies.push_back(enemy);

	}
	generated_with_enemies = true;
}

bool room::is_generated_with_enemies()
{
	return generated_with_enemies;
}

