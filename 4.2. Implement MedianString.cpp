#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <set>
#include <limits>

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
	for(auto it : kMers)
	{
		if (d >= HammingDistance(it, kMer))
		{
			patterns.insert(it);
		}
	}
	return patterns;
}

int d(string pattern, list<string> DNA)
{
	int result = 0;
	for (auto it = DNA.begin(); it != DNA.end(); it++)
	{
		set<int> D;
		for (int i = 0; i < (*it).size() - pattern.size() + 1; i++)
		{
			D.insert(HammingDistance(pattern, it->substr(i, pattern.size())));
		}
		result += *D.begin();
	}
	return result;
}

string MedianString(list<string> DNA, int k)
{
	size_t distance = -1;
	string Median = "";
	set<string> kMers = CreateKMers(k);
	for (auto it = kMers.begin(); it != kMers.end(); it++)
	{
		if (distance > d((*it), DNA))
		{
			distance = d((*it), DNA);
			Median = *it;
		}
	}
	return Median;
}

int main()
{
	string tmp;
	int k;
	cin >> k;
	
	list<string> Patterns;
	while(cin >> tmp)
	{
		if (tmp == "q")
			break;
		Patterns.push_back(tmp);
	}
	
	string result = MedianString(Patterns, k);
	cout << result << endl;
}