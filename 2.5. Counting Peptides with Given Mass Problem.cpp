#include <iostream>
#include <string>
#include <unordered_map>
static int Masses[18] = { 57, 71, 87, 97, 99, 101, 103, 113, 114, 115, 128, 129, 131, 137, 147, 156, 163, 186 };
using namespace std;

int main()
{
	int m;
	cin >> m;
	unordered_map<int, uint64_t> number = { { 0, 1 } };
	for (int i = 57; i <= m; i++)
	{
		number[i] = 0;
		for (int j = 0; j < 18; j++)
		{
			if (number.find(i - Masses[j]) != number.end())
			{
				number[i] += number[i - Masses[j]];
			}
		}
	}
	cout << number[m] << endl;
	return 0;
}