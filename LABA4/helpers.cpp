#include "helpers.h"

vector<string> fight_phrases;

string helpers::get_fighting_phrase()
{
	
	if (fight_phrases. empty())
	{
		fight_phrases = vector<string>(5);
		fight_phrases[0] = "You broke his head with an ax!";
		fight_phrases[1] = "His heart could not stand your beauty!";
		fight_phrases[2] = "You tripped him, he died of nosebleeds!";
		fight_phrases[3] = "Lucky for you that he was the one who slipped on the banana peel!";
		fight_phrases[4] = "He died from your precise dagger stab right to his heart!";
		
	}
	
	int random = rand() % 5;
	return fight_phrases[random];
}


vector<string>& helpers::get_journal()
{
	static vector<string> journal;
	return journal;
}

void helpers::add_to_journal(string str)
{
	helpers::get_journal().push_back(str);
}

void helpers::write_to_file()
{

	string path_out;
	path_out = "TheGameResults.txt";
	ofstream fout;
	fout.open(path_out);
	if (!fout.is_open())
	{
		cout << "Enable to open a file for output!" << endl;
	}
	for (int i = 0; i < helpers::get_journal().size(); i++)
	{
		fout << helpers::get_journal()[i] << endl;
	}
}