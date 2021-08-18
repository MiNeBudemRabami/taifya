#include <iostream>
#include <map>

using namespace std;

struct pos
{
	int row;
	int numb;
};

struct lexema
{
	int id;
	pos pos;
	string value;
};

map <int, lexema> buffer;

lexema l_unit = { 0, {0, 0}, ""};

int main()
{
	string unit = "";
	int i = 0;

	for (;;)
	{
		cin >> unit;
		l_unit.value = unit;
		l_unit.id = i;
		int us = unit.size();
		buffer[i] = {i, {0, us}, unit};
	}
}
