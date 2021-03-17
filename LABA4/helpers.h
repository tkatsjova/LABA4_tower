#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

 class helpers
{
	
public:
	int static valid_input(std::string text, int min, int max)
	{
		int input;
		do
		{
			if ((cin >> input) && input >= min && input <= max)
			{
				return input;
			}
			cout << "Invalid input." << endl;
			cout << text << endl;
		}
		while (true);	
	}

	int static valid_input_or(std::string text, int left, int right)
	{
		int input;
		do
		{
			if ((cin >> input) && (input == left || input == right))
			{
				helpers::add_to_journal(text + " Player select is: " +std::to_string(input));
				return input;
			}
			cout << "Invalid input." << endl;
			cout << text << endl;
		} while (true);
		
	}
	string static get_fighting_phrase();

	static vector<string>& get_journal();
	static void add_to_journal(string str);
	static void write_to_file();
};

