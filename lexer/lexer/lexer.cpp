#include <iostream>
#include <map>
#include <vector>
using namespace std;

enum lexema_type {keyword,operand,variable,constant};

vector <string> keyword = { "begin", "end" };
vector <char> operand = { "+", "/" };
vector <string> variable = { "a", "z" };

lexema_type get_type(lexema)
{
}

struct lexema
{
	int id;
	int row;
	int pos;
	string value;
};

map <int, lexema> buffer;

lexema l_unit = { 0, 0, 0, ""};

int main()
{
	char unit = '\0';
	int i = 0;

	for (;;)
	{
		unit = cin.get();
		l_unit.value = unit;
		l_unit.id = i;
		buffer[i] = {i, {0, us}, unit};
	}
}
