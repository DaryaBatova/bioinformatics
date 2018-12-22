#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <map>
#include <set>

using namespace std;
const static string AlphaBet = "ATCG";

int HammingDistance(string pattern1, string pattern2)
{
	if (pattern1.length() != pattern2.length())
		return -1;
	int error_count = 0;
	for (int i = 0; i < pattern1.length(); i++)
		if (pattern1[i] != pattern2[i])
			error_count++;
	return error_count;
}



void GenerateKmers(set<string> & words, int length, string currentStr = "")
{
	if (length == 0)
	{
		words.insert(currentStr);
		return;
	}
	for (auto it = AlphaBet.begin(); it != AlphaBet.end(); it++)
	{
		GenerateKmers(words, length - 1, currentStr + (*it));
	}
}



set<string> CreateKMers(int length)
{
	set<string> kMers{};
	GenerateKmers(kMers, length);
	return kMers;
}


set<string> GetAllKDMotifs(const string& kMer, int d)
{
	set<string> patterns;
	auto kMers = CreateKMers(kMer.size());
	for(auto it = kMers.begin(); it != kMers.end(); it++)
	{
		if (d >= HammingDistance(*it, kMer))
		{
			patterns.insert(*it);
		}
	}
	return patterns;
}

set<string> MotifEnumeration(list<string> & Dna, int k, int d)
{
	set<string> result;
	
	for (auto DnaIt = Dna.begin(); DnaIt != Dna.end(); DnaIt++)
	{
		string tmp = *DnaIt;
		for (size_t i = 0; i < tmp.size() - k + 1; i++)
		{
			string kMer = tmp.substr(i, k);
			auto kMerDna = GetAllKDMotifs(kMer, d);
			for (auto it = kMerDna.begin(); it != kMerDna.end(); it++)
			{
				int size = 0;
				for (auto DnaIt1 = Dna.begin(); DnaIt1 != Dna.end(); DnaIt1++)
				{
					for (int j = 0; j < DnaIt->size() - k + 1; j++)
					{
						if (d >= HammingDistance(DnaIt1->substr(j, k), (*it)))
						{
							size++;
							break;
						}

					}
				}
				if (size == Dna.size())
				{
					result.insert(*it);
				}
				
			}
		}
	}
	return result;
}


int main()
{
	string tmp;
	int k, d;
	std::cin >> k;
	std::cin >> d;
	list<string> Patterns;
	while(cin >> tmp)
	{
		if (tmp == "q")
			break;
		Patterns.push_back(tmp);
	}
	set<string> result = MotifEnumeration(Patterns, k, d);
	for (auto it = result.begin(); it != result.end(); it++)
	{
		std::cout << (*it) << " ";
	}
}