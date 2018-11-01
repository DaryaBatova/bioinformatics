#include <iostream>
#include <list>
#include <set>
#include <string>
using namespace std;
static const string sTable = "AAA K AAC N AAG K AAU N ACA T ACC T ACG T ACU T AGA R AGC S AGG R AGU S AUA I AUC I AUG M AUU I CAA Q CAC H CAG Q CAU H CCA P CCC P CCG P CCU P CGA R CGC R CGG R CGU R CUA L CUC L CUG L CUU L GAA E GAC D GAG E GAU D GCA A GCC A GCG A GCU A GGA G GGC G GGG G GGU G GUA V GUC V GUG V GUU V UAA   UAC Y UAG   UAU Y UCA S UCC S UCG S UCU S UGA   UGC C UGG W UGU C UUA L UUC F UUG L UUU F";
const int nOffer = 4;
const int nSizeDNA = 3;

string reverse1(const string & sText)
{
	int len = sText.size();
	string ReversePattern(len, 0);
	for (int i = 0; i < len; i++)
	{
		switch (sText[i])
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
	return ReversePattern;
}

string reverse2(string sText)
{
	for (int i = 0; i < sText.size(); i++)
	{
		if (sText[i] == 'T')
			sText[i] = 'U';
	}
	return sText;
}

string DNAtoPeptide(string sDNA, int start, int finish)
{
	string sPeptide;
	for (size_t i = start; i < finish; i += 3)
	{
		string tmp = sDNA.substr(i, 3);
		int unCount = sTable.find(tmp);
		sPeptide += sTable[unCount + nOffer];
	}
	return sPeptide;
}

list<string> FindPeptide(const string& sPeptide, const string& sExistPeptide, const string& sText, int m)
{
	list<string> lFoundDNA;
	int nFoundIndex = 0;
	int len = sPeptide.size();
	while ((nFoundIndex = sExistPeptide.find(sPeptide, nFoundIndex)) != string::npos)
	{
		lFoundDNA.emplace_back(sText.substr((nFoundIndex*nSizeDNA + m), len*nSizeDNA));
		nFoundIndex += 1;
	}
	return lFoundDNA;
}

int main() {
	string sText;
	string sPeptide;
	cin >> sText;
	cin >> sPeptide;
	string sText2 = reverse2(sText);
	int len = sText2.size();
	string sPeptideFromText1 = DNAtoPeptide(sText2, 0, len);
	string sPeptideFromText2 = DNAtoPeptide(sText2, 1, len - 2);
	string sPeptideFromText3 = DNAtoPeptide(sText2, 2, len - 1);

	list<string> sResult1 = FindPeptide(sPeptide, sPeptideFromText1, sText, 0);
	list<string> sResult2 = FindPeptide(sPeptide, sPeptideFromText2, sText, 1);
	list<string> sResult3 = FindPeptide(sPeptide, sPeptideFromText3, sText, 2);

	for (auto it : sResult1)
	{
		cout << it << endl;
	}

	for (auto it : sResult2)
	{
		cout << it << endl;
	}
	for (auto it : sResult3)
	{
		cout << it << endl;
	}

	sText2 = reverse1(sText);
	string sPeptideFromText4 = DNAtoPeptide(reverse2(sText2), 0, len);
	string sPeptideFromText5 = DNAtoPeptide(reverse2(sText2), 1, len - 2);
	string sPeptideFromText6 = DNAtoPeptide(reverse2(sText2), 2, len - 1);
	list<string> sResult4 = FindPeptide(sPeptide, sPeptideFromText4, sText2, 0);
	list<string> sResult5 = FindPeptide(sPeptide, sPeptideFromText5, sText2, 1);
	list<string> sResult6 = FindPeptide(sPeptide, sPeptideFromText6, sText2, 2);

	for (auto it : sResult4)
	{
		it = reverse1(it);
		cout << it << endl;
	}

	for (auto it : sResult5)
	{
		it = reverse1(it);
		cout << it << endl;
	}
	for (auto it : sResult6)
	{
		it = reverse1(it);
		cout << it << endl;
	}
	return 0;
}
