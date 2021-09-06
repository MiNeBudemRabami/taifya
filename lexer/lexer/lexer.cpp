#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

vector <string> keyword_arr = { "begin", "end" };
vector <char> operand_arr = { "+", "/" };
vector <string> variable_arr = { "a", "z" };

enum lexema_type
{
	def,
	keyword,
	variable,
	constant,
	operand
};

lexema_type get_type(string value)
{
	for_each(keyword_arr.cbegin(), keyword_arr.cend(),
		{})
	
}

struct lexema_struct
{
	int id;
	int row;
	int pos;
	string value;
	lexema_type type;
};

int main()
{
	map <int, lexema_struct> bank;

	lexema_struct lexema = { 1, 1, 1, "",  def}; //id, row, pos, value, type 
	int id = lexema.id;
	//char ch = '\0';
	string unit;

	for (;;)
	{
		cin >> unit;
		
		if (unit == "&")
		{
			break;
		}
		else
		{
			lexema.value = unit;
			get_type(unit);
			bank[id] = lexema;
			id++;
			lexema.id == id;
			lexema.pos += lexema.value.size() + 1;
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
