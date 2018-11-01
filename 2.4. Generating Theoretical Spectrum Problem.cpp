#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
	map<char, int> Peptide;
	Peptide['G'] = 57;
	Peptide['A'] = 71;
	Peptide['S'] = 87;
	Peptide['P'] = 97;
	Peptide['V'] = 99;
	Peptide['T'] = 101;
	Peptide['C'] = 103;
	Peptide['I'] = 113;
	Peptide['L'] = 113;
	Peptide['N'] = 114;
	Peptide['D'] = 115;
	Peptide['K'] = 128;
	Peptide['Q'] = 128;
	Peptide['E'] = 129;
	Peptide['M'] = 131;
	Peptide['H'] = 137;
	Peptide['F'] = 147;
	Peptide['R'] = 156;
	Peptide['Y'] = 163;
	Peptide['W'] = 186;
	vector<int> Result;
	Result.push_back(0);
	string sPeptide;
	cin >> sPeptide;
	sPeptide += sPeptide;
	const char * pdSubArray;
	int nMass{ 0 };
	for (size_t i = 1; i < sPeptide.size() / 2; ++i)
	{
		pdSubArray = sPeptide.c_str();
		for (size_t j = 0; j < sPeptide.size() / 2; ++j)
		{
			nMass = 0;
			for (size_t k = 0; k < i; ++k)
			{
				nMass += Peptide[pdSubArray[k]];
			}
			Result.push_back(nMass);
			pdSubArray++;
		}
	}
	nMass = 0;
	for (size_t i = 0; i < sPeptide.size() / 2; ++i)
		nMass += Peptide[sPeptide[i]];
	Result.push_back(nMass);
	sort(Result.begin(), Result.end());
	for (auto it : Result)
		cout << it << " ";
	return 0;
}