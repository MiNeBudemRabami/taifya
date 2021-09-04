#include <iostream>
#include <map>
#include <vector>

using namespace std;

//vector <string> keyword = { "begin", "end" };
//vector <char> operand = { "+", "/" };
//vector <string> variable = { "a", "z" };

struct lexema_struct
{
	int id;
	int row;
	int pos;
	string value;
};

int main()
{
	map <int, lexema_struct> bank;

	lexema_struct unit = { 1, 1, 1, "" }; //id, row, pos, value
	int id = unit.id;
	//char ch = '\0';

	for (;;)
	{
		cin >> unit.value;

		bank[id] = unit;

		id++;
		unit.id == id;
		unit.pos += unit.value.size() + 1;

		if (unit.value == "&")
		{
			break;
		}
	}

	/*
	for (;;)
	{
		ch = cin.get(); 
		pos++;
		if (ch != ' ')
		{
			value.push_back(ch);
		}
		else
		{
			bank[id] = unit;
			value.clear();
		}
		if (ch == '\n')
		{
			pos = 1;
			row++;
		}

		if (ch == '&')
		{
			break;
		}
	}
	*/
}
