#include <iostream>
#include <map>
#include <string>
static const int nOffer = 4;

using namespace std;
int main()
{
	string sTable = "AAA K AAC N AAG K AAU N ACA T ACC T ACG T ACU T AGA R AGC S AGG R AGU S AUA I AUC I AUG M AUU I CAA Q CAC H CAG Q CAU H CCA P CCC P CCG P CCU P CGA R CGC R CGG R CGU R CUA L CUC L CUG L CUU L GAA E GAC D GAG E GAU D GCA A GCC A GCG A GCU A GGA G GGC G GGG G GGU G GUA V GUC V GUG V GUU V UAA   UAC Y UAG   UAU Y UCA S UCC S UCG S UCU S UGA   UGC C UGG W UGU C UUA L UUC F UUG L UUU F";
	string sRNA;
	string sPeptide{ "" };
	cin >> sRNA;
	for (size_t i = 0; i < sRNA.size(); i += 3)
	{
		string tmp = sRNA.substr(i, 3);
		size_t unCount = sTable.find(tmp);
		sPeptide += sTable[unCount + nOffer];
	}
	cout << sPeptide << endl;
	return 0;
}