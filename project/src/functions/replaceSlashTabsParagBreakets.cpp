/*
 * replaceSlashTabsParagBreakets.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: name
 */

#include "../inc/main.h"


void changeIdInJsonFromOldToNew(string &json, int newId) {
	string begin = json;
	string end = json;
	int task_begin = begin.find("\"task\":");
	begin.erase(task_begin + 8, begin.size() - 1);

	string breakets = json;

	breakets.erase(0, breakets.find("\"task\":") + 9);

	breakets.erase(breakets.find(","), breakets.size() - 1);

	int breaket_pos = breakets.find("\"");
	bool is_breakets = false;
	if (breaket_pos > -1)
		is_breakets = true;

	int task_end = end.find(",", task_begin + 8);
	end.erase(0, task_end);

/*if (is_breakets == false)
		json = begin + to_string(newId) + end;
	else*/
		json = begin + "\"" + to_string(newId) + "\"" + end;


	l12("copyTask:\n\n" + json);
	//fix for itatests
	task_begin = json.find("\"task\":\"\"");
	if (task_begin > -1)
	{
		json.erase(task_begin + 8, 1);
	}
}


string replaceSlashTabsParagBreakets (string input)
{
	string output = "";
	bool first_slash = false;
	//bool second_slash = false;
	bool tab = false;
	bool paragraph = false;

	for (int i = 1; i < input.size() - 2; i++)
	{
		char curent = input[i];
		if (curent == '\\')
		{
			if ( !first_slash )
				first_slash = true;
			else
			{
				output += curent;
			}
		}
		else
			if ( curent == '\"')
			{
				if ( first_slash )
				{
					output += "\"";
					first_slash = false;
				}
				else
				{
					output += curent;
				}
			}
			else
				if ( curent == 't')
				{
					if ( first_slash)
					{
						output += "\t";
						first_slash = false;
					}
					else
					{
						output += curent;
					}
				}
				else
					if ( curent == 'n')
					{
						if ( first_slash)
						{
							output += '\n';
							first_slash = false;
						}
						else
						{
							output += curent;
						}
					}
					else
					{
						output += curent;
						first_slash = false;
					}

	}
	return output;

}


/*
string replaceSlashTabsParagBreakets (string input)
{
	string output = "";
	bool first_slash = false;
	bool second_slash = false;
	bool tab = false;
	bool paragraph = false;

	for (int i = 0; i < input.size(); i++)
	{
		char curent = input[i];
		if (curent == '\\')
		{
			if ( !first_slash )
				first_slash = true;
			else
				if (second_slash)
				{
					output += curent;
					first_slash = second_slash = false;
				}
				else
					second_slash = true;
		}
		else
			if ( curent == '\"')
			{
				if ( second_slash)
				{
					output += "\"";
					second_slash = first_slash = false;
				}
				else
				{
					output += curent;
					first_slash = second_slash = false;
				}
			}
			else
				if ( curent == 't')
				{
					if ( second_slash)
					{
						output += "\t";
						second_slash = first_slash = false;
					}
					else
					{
						output += curent;
						first_slash = second_slash = false;
					}
				}
				else
					if ( curent == 'n')
					{
						if ( second_slash)
						{
							output += '\n';
							second_slash = first_slash = false;
						}
						else
						{
							output += curent;
							first_slash = second_slash = false;
						}
					}
					else
					{
						output += curent;
						first_slash = second_slash = false;
					}

	}
	return output;

}
 */
