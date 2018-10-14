#include <iostream>
#include <string>

int main() {
	using namespace std;
	string DnaPattern;
	cin >> DnaPattern;
	int len = DnaPattern.size();
	string ReversePattern(len, 0);
	for (int i = 0; i < len; i++)
	{
		switch (DnaPattern[i])
		{
		case 'A':
			ReversePattern[len - i - 1] = 'T';
			break;
		case 'T':
			ReversePattern[len - i - 1] = 'A';
			break;
		case 'C':
			ReversePattern[len - i - 1] = 'G';
			break;
		case 'G':
			ReversePattern[len - i - 1] = 'C';
			break;
		default:
			ReversePattern[len - i - 1] = 0;
			break;
		}
	}
	cout << ReversePattern << endl;
}