

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip> 
#include "building.h"
#include "helpers.h"
#include "input_data.h"

using namespace std;

void start(int hero_level, building tower);
bool fight_in_the_room(room& room, person& hero);
void storey_display(storey& storey, int current_room_index);
bool movement(person& hero, storey& current_storey, int index_storey, int& current_room_index);
void populate_data_2(building& tower, const input_data data);
int validate_input(string text, int max, int min);
input_data read_input();

int main()
{
	input_data data = read_input();
	helpers::add_to_journal("There were " + to_string(data.total_storeys) + " in this tower!");
	helpers::add_to_journal("There were maximum " + to_string(data.rooms_per_storey) + " rooms for one floor in this tower!");
	helpers::add_to_journal("There were " + to_string(data.total_rooms) + " rooms in this tower!");
	helpers::add_to_journal("There were maximum " + to_string(data.enemy_per_room) + " enemies in one room!");
	helpers::add_to_journal("The hero's level was " + to_string(data.hero_level) + "!");
	srand(time(NULL));
	building tower;

	populate_data_2(tower, data);
	start(data.hero_level, tower);
	string temp;
	helpers::write_to_file();
 
	cin >> temp;
}

input_data read_input()
{
	int hero_level = 4; //LvL
	int total_rooms = 15; //K
	int rooms_per_storey = 5;//max_K
	int enemy_per_room = 5;
	int total_storeys = 3;
	const string floors_text = "Enter the number of floors in the tower from " + to_string(1) + " to " + to_string(15) + ": ";
	const string hero_text = "Enter your hero's level from " + to_string(2) + " to " + to_string(10000) + ": ";

	string storey_room = "Enter the maximum number of rooms on the floor from " + to_string(1) + " to " + to_string(15) + ": ";
	string enemies = "Enter the maximum number of enemies in one room from " + to_string(1) + " to " + to_string(15) + ": ";
	cout << floors_text;
	total_storeys = validate_input(floors_text, 15, 1);
	cout << storey_room;
	rooms_per_storey = validate_input(storey_room, 15, 1);
	int output_total_rooms = total_storeys * rooms_per_storey;
	string rooms_text = "Enter the number of rooms in the tower from " + to_string(total_storeys) + " to " + to_string(output_total_rooms) + ": ";
	cout << rooms_text;
	total_rooms = validate_input(rooms_text, output_total_rooms, total_storeys);
	cout << enemies;
	enemy_per_room = validate_input(enemies, 15, 1);
	cout << hero_text;
	hero_level = validate_input(hero_text, 10000, 2);

	input_data* data = new input_data(total_storeys, hero_level, total_rooms, rooms_per_storey, enemy_per_room);
	
	return *data;
}

void start(int hero_level, building tower)
{
	person hero;
	hero.set_level(hero_level);
	string game_start = "You can see the TOWER with " + to_string(tower.get_storey().size()) + " floors, puppy!";
	cout << game_start << endl;
	helpers::add_to_journal(game_start);
	
	for (int i = 0; i < tower.get_storey().size(); i++)
	{
		string validText = "You are on the " + to_string(i) + " floor! Choose the room for fighting!";
		cout << validText << endl;
		helpers::add_to_journal(validText);
		storey_display(tower.get_storey()[i], -1);
		int current_room_index = helpers::valid_input(validText, 0, tower.get_storey()[i].get_rooms().size());
		helpers::add_to_journal("Player select is: " + std::to_string(current_room_index) + " room.");
		do
		{
			if (!movement(hero, tower.get_storey()[i], i, current_room_index))
			{
				cout << endl << "  (x_x)  ";
				string DEATH = "WASTED!";
				helpers::add_to_journal(DEATH);

				return;
			}

		} while (!tower.get_storey()[i].is_secured());
		string secure_floor = to_string(i) + " floor is secured!";
		cout << endl << secure_floor << endl << endl;
		helpers::add_to_journal(secure_floor);
	}
	cout << endl << "YOU ARE COOLER THAN NARUTO!" << endl;
	cout << endl << "  (>_<)  ";
	string win = "VICTORY!";
	helpers::add_to_journal(win);
}

bool
movement(person& hero, storey& current_storey, int index_storey, int& current_room_index)
{
	bool result = fight_in_the_room(current_storey.get_rooms()[current_room_index], hero);

	if (result == false)
		return result;

	if (current_storey.is_secured())
		return result;

	storey_display(current_storey, current_room_index);

	int max = -2;
	int min = -2;
	current_storey.get_nearest_enemied_room(current_room_index, max, min);
	string text = "You are in the " + to_string(current_room_index) + " room, puppy! Choose the nearest room with enemies: " + to_string(min) + " or " + to_string(max) + "!";
	cout << text << endl;
	current_room_index = helpers::valid_input_or(text, min, max);
	return result;
}

bool fight_in_the_room(room& room, person& hero)
{
	if (room.is_empty())
	{
		string lucky = "You are lucky! There is nobody in this room!";
		cout << lucky << endl;
		helpers::add_to_journal(lucky);
		return true;
	}
	string in_room = "You are in the room with " + to_string(room.get_enemy().size()) + " enemies! Fight!";
	cout << in_room << endl;
	helpers::add_to_journal(in_room);
	for (int i = 0; i < room.get_enemy().size(); ++i)
	{
		if (room.get_enemy()[i].is_dead())
		{
			continue;
		}
		if (room.get_enemy()[i].get_level() < hero.get_level())
		{
			string enemy_level = "Your enemy's level is " + to_string(room.get_enemy()[i].get_level());
			cout << enemy_level << endl;
			helpers::add_to_journal(enemy_level);
			hero.set_level(hero.get_level() + room.get_enemy()[i].get_level());
			room.get_enemy()[i].set_dead();
			string enemy_death = helpers::get_fighting_phrase() + " Now your level is " + to_string(hero.get_level()) + "!";
			cout << enemy_death << endl;
			helpers::add_to_journal(enemy_death);
		}
		else
		{
			string hero_death = "You died a heroic death at the hands of " + to_string(i) + " enemy with " + to_string(room.get_enemy()[i].get_level()) + " level. You will not be forgotten!";
			cout << hero_death << endl;
			helpers::add_to_journal(hero_death);
			return false;
		}
	}
	string secure_room = "The room is secured!";
	cout << secure_room << endl;
	helpers::add_to_journal(secure_room);
	return true;
}



void storey_display(storey& storey, int current_room_index)
{
	for (int i = 0; i < storey.get_rooms().size(); ++i)
	{
		cout << "| " << setw(2) << i << " room ";
	}
	cout << "|" << endl;
	for (int n = 0; n < storey.max_enemy_room(); ++n)
	{
		for (int i = 0; i < storey.get_rooms().size(); ++i)
		{
			cout << "| " << setw(8) << storey.get_rooms()[i].get_enemy_level_by_index(n);
		}
		cout << "|" << endl;
	}
	if (current_room_index != -1)
	{
		for (int i = 0; i < storey.get_rooms().size(); ++i)
		{
			if (i == current_room_index)
			{
				cout << "   (._.)  ";
			}
			else
			{
				cout << "          ";
			}

		}
		cout << " " << endl;
	}
}

void populate_data_2(building& tower, input_data data)
{
	for (int i = 0; i < data.total_storeys; i++) //добавляем этажи в здание
	{
		storey stry;
		tower.add_storey(stry);
	}

	for (int n = 0; n < data.total_storeys; ++n)
	{
		vector<storey>& current_storey = tower.get_storey();
		current_storey[n].add_room_uncoditionnaly();
		data.total_rooms--;
	}

	do
	{
		for (int n = 0; n < data.total_storeys; ++n)
		{
			vector<storey>& current_storey = tower.get_storey();
			if (current_storey[n].add_room(data.rooms_per_storey))
			{
				data.total_rooms--;
			}
		}
	} while (data.total_rooms > 0);

	vector<storey>& storeys = tower.get_storey();
	person wizard;
	wizard.set_level(4);
	for (int n = 0; n < data.total_storeys; ++n)
	{
		vector<room>& rooms = storeys[n].get_rooms();
		unsigned random_room = rand() % rooms.size();
		rooms[random_room].generate_enemies(wizard, data.enemy_per_room);
		do
		{
			int max = -2;
			int min = -2;
			storeys[n].get_nearest_empty_room(random_room, max, min);

			int toRight = rand() % 2;

			if (toRight == 1) {
				rooms[max].generate_enemies(wizard, data.enemy_per_room);
				random_room = max;
			}
			else
			{
				rooms[min].generate_enemies(wizard, data.enemy_per_room);
				random_room = min;
			}


		} while (!storeys[n].is_generated());
	}
}

int validate_input(string text, int max, int min)
{
	int input;
	while (!(cin >> input) || (cin.peek() != '\n') || (input < min) || (input > max))
	{
		cout << text;
		cin.clear();
		cin.ignore(100, '\n');
	}

	return input;
}



