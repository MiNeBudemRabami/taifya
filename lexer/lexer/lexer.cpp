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

int main()
{
	string unit = "";
	int i = 0;

	for (;;)
	{
		cin >> unit;
		buffer[i] = unit;

	}
}
