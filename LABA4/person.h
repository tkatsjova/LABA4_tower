#pragma once
class person
{
	int power;
	bool _is_dead = false;
public:
	void set_level(int level);
	int get_level();
	bool is_dead();
	void set_dead();
};

