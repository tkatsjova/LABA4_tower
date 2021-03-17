#include "person.h"


	
	void person::set_level(int level)
	{
		power = level;
	}

	int person::get_level()
	{
		return power;
	}

	bool person::is_dead()
	{
		return _is_dead;
	}

	void person::set_dead()
	{
		_is_dead = true;
	}


