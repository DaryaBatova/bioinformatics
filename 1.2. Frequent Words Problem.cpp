#include <iostream>
#include <string>
#include <map>

int main() {
	using namespace std;
	string text;
	cin >> text;
	int k;
	cin >> k;
	map<string, int> values;
	int len = 0;
	while (len != (text.size() - k))
	{
		string pattern = text.substr(len++, k);
		if (values.empty())
		{
			values.emplace(pattern, 1);
		}
		else
		{
			auto it = values.find(pattern);
			if (it != values.end())
			{
				it->second += 1;
			}
			else
			{
				values.emplace(pattern, 1);
			}
		}
	}

	auto itMax = values.begin();
	for (auto it = values.begin(); it != values.end(); it++)
	{
		if (itMax->second < it->second)
			itMax = it;
	}
	for (auto it = values.begin(); it != values.end(); it++)
	{
		if (itMax->second == it->second)
		{
			cout << it->first << " ";
		}
	}
	cout << endl;
}