#include <iostream>
#include <string>
#include <map>
#include <vector>
#include<list>

using namespace std;

vector<char> Aminos = { 'G','A','S','P','V','T','C','I','L','N','D','K','Q','E','M','H','F','R','Y','W' };

map<char, int> Masses{ { 'G', 57 },{ 'A', 71 },{ 'S', 87 },{ 'P', 97 },{ 'V', 99 },
{ 'T', 101 },{ 'C', 103 },{ 'I', 113 },{ 'L', 113 },{ 'N', 114 },
{ 'D', 115 },{ 'K', 128 },{ 'Q', 128 },{ 'E', 129 },{ 'M', 131 },
{ 'H', 137 },{ 'F', 147 },{ 'R', 156 },{ 'Y', 163 },{ 'W', 186 } };

int Mass(string Peptide) 
{
	int mass = 0;
	for (int i = 0; i < Peptide.length(); i++) {
		mass += Masses[Peptide[i]];
	}
	return mass;
}

vector<string> Expand(vector<string> Peptides)
{
	vector<string> nPeptides;
	for (int i = 0; i < Peptides.size(); i++) {

		for (int j = 0; j < Masses.size(); j++) {

			nPeptides.push_back(Peptides[i] + Aminos[j]);
		}
	}

	return nPeptides;
}

int  PeptidesCount(string Peptide) {
	int res = 0;
	for (int i = 1; i <= Peptide.length(); i++) {
		res += i;
	}
	return res;
}

string LinearSpectrum(string Peptide)
{
	string res = "";
	list<string> subPeptides;
	string tmp;
	int weight = 0;
	for (int i = 1; i < Peptide.length(); i++) {

		for (int j = 0; j < Peptide.length(); j++) {

			if (Peptide.length() - j >= i) {

				subPeptides.push_back(Peptide.substr(j, i));
			}
		}
	}

	subPeptides.push_back(Peptide);
	res += to_string(weight);
	res += " ";

	for (int i = 0; i < PeptidesCount(Peptide); i++) {

		tmp = subPeptides.front();
		subPeptides.pop_front();

		for (int j = 0; j < tmp.length(); j++) {

			weight += Masses.at(tmp[j]);
		}
		res += to_string(weight);
		res += " ";
		weight = 0;
	}
	return res;

}

int SubPeptidesCount(string Peptide) {
	return Peptide.length()*(Peptide.length() - 1);
}
string CycloSpectrum(string Peptide)
{
	string res = "";
	list<string> subPeptides;
	list<int> weightSubPeptides;
	string tmp;
	int weight = 0;

	for (int i = 1; i < Peptide.length(); i++) {

		for (int j = 0; j < Peptide.length(); j++) {

			if (Peptide.length() - j >= i) {

				subPeptides.push_back(Peptide.substr(j, i));
			}
			else {

				tmp = Peptide.substr(j,Peptide.length() - j) + Peptide.substr(0, i - (Peptide.length() - j));
				subPeptides.push_back(tmp);
			}
		}
	}
	subPeptides.push_back(Peptide);
	weightSubPeptides.push_back(weight);
	for (int i = 0; i < SubPeptidesCount(Peptide) + 1; i++) {
		tmp = subPeptides.front();
		subPeptides.pop_front();
		for (int j = 0; j < tmp.length(); j++) {
			weight += Masses.at(tmp[j]);
		}
		weightSubPeptides.push_back(weight);

		weight = 0;
	}
	weightSubPeptides.sort();
	
	for (auto it = weightSubPeptides.begin(); it != weightSubPeptides.end(); it++) {

		res += to_string(*it);
		res += " ";
	}

	return res;

}


vector<string> Remove(vector<string> Peptides, string Peptide)
{
	vector<string> res;
	int j = 0;

	for (int i = 0; i < Peptides.size(); i++) {

		if (Peptides[i] != Peptide) {
			res.push_back(Peptides[i]);

		}
	}
	return res;
}
vector<string> StrToVector(string str)
{
	vector<string> res;

	while (str != "") {

		res.push_back(str.substr(0, str.find(" ")));
		str.erase(0, str.find(" ") + 1);

	}
	return res;
}


bool IsConsistent(string Peptide, string Spectrum)
{
	bool flag = false;
	vector<string> specMass = StrToVector(Spectrum + " ");
	vector<string> peptideMass = StrToVector(LinearSpectrum(Peptide));

	for (int i = 0; i < peptideMass.size(); i++) {

		for (int j = 0; j < specMass.size(); j++) {

			if (specMass[j] == peptideMass[i]) {
				flag = true;
			}

		}
		if (!flag) return false;

		flag = false;
	}

	return true;
}
int main()
{

	string spectrum;
	getline(cin, spectrum);
	int ParentMass = stoi(spectrum.substr(spectrum.find_last_of(' ') + 1, spectrum.length() - 1));
	vector<string> Peptides = { "" };
	vector<string> AllPeptides;

	spectrum += " ";

	while (Peptides.size() > 0)
	{
		Peptides = Expand(Peptides);
		vector<string> copyAllPeptides = Peptides;

		for (int i = 0; i < copyAllPeptides.size(); i++) {

			string peptide = copyAllPeptides[i];

			if (Mass(peptide) == ParentMass) {

				string t = CycloSpectrum(peptide);

				if (CycloSpectrum(peptide) == (spectrum)) {

					AllPeptides.push_back(peptide);
				}
				Peptides = Remove(Peptides, peptide);
			}
			else if (!IsConsistent(peptide, spectrum))
			{
				Peptides = Remove(Peptides, peptide);
			}

		}
	}

	string res;

	for (int i = 0; i < AllPeptides.size(); i++) {

		string tmp;

		for (int j = 0; j < AllPeptides[i].length(); j++) {

			tmp += to_string(Masses[AllPeptides[i][j]]);
			tmp += "-";

		}
		tmp = tmp.substr(0, tmp.length() - 1);

		if (res.find(tmp) > res.length() || res.find(tmp) < 0) {

			res += tmp;
			res += " ";
		}
	}

	res = res.substr(0, res.length() - 1);
	cout << res;

	return 0;
}