#include <iostream>
#include <string>

int main() {
	int count = 0;
	std::string pattern;
	std::cin >> pattern;
	std::string genome;
	std::cin >> genome;
	int gpos = 0;
	int pos = 0;
	while ((gpos = genome.find(pattern, pos)) != std::string::npos)
	{
		count++;
		pos = gpos + 1;
	}

	std::cout << count;
}