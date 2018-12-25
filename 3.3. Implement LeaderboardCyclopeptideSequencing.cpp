#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

static map<char, int> PeptideMap = { {'G', 57}, {'A', 71}, {'S', 87}, {'P', 97}, {'V', 99}, {'T', 101}, {'C', 103}, {'I', 113}, {'L', 113}, {'N', 114}, {'D', 115}, {'K', 128}, {'Q', 128}, {'E', 129}, {'M', 131}, {'H', 137}, {'F', 147}, {'R', 156},  {'Y', 163}, {'W', 186} };

int MassOfPeptide(const string& Peptide)
{
    int mass = 0;
    for (auto it : Peptide)
    {
        mass += PeptideMap[it];
    }
    return mass;
}

multiset<int> LinearSpectrum(const string& Peptide)
{
    multiset<int> Result;
    Result.insert(0);
    const char * pszSubArray;
    int nMass{ 0 };
    for (size_t i = 1; i < Peptide.size(); ++i)
    {
        pszSubArray = Peptide.c_str();
        for (size_t j = 0; j < Peptide.size() - i + 1; ++j)
        {
            nMass = 0;
            for (size_t k = 0; k < i; ++k)
            {
                nMass += PeptideMap[pszSubArray[k]];
            }
            Result.insert(nMass);
            pszSubArray++;
        }
    }
    nMass = 0;
    for (size_t i = 0; i < Peptide.size(); ++i)
        nMass += PeptideMap[Peptide[i]];
    Result.insert(nMass);
    return Result;
}

set<string> Expand(const set<string>& LeaderBoard)
{
    set<string> NewLeaderBoard;
    for (const auto& itLeadBoard : LeaderBoard)
    {
        for (const auto& itPeptideMap : PeptideMap)
        {
            NewLeaderBoard.insert(itLeadBoard + itPeptideMap.first);
        }
    }
    return NewLeaderBoard;
}

int Score(const string& sPeptide, const multiset<int>& Spectrum)
{
    int nScore{ 0 };
    multiset<int> LinSpectr = LinearSpectrum(sPeptide);
    vector<int> Result(LinSpectr.size() + Spectrum.size(), 0);
    auto it = set_intersection(LinSpectr.begin(), LinSpectr.end(), Spectrum.begin(), Spectrum.end(), Result.begin());
    Result.resize(it - Result.begin());
    return Result.size();
}

set<string> Trim(set<string>& LeaderBoard, const multiset<int>& Spectrum, int N)
{
    vector<pair<int, string>> LeaderBoardVector;
    for (const auto& it : LeaderBoard)
    {
        LeaderBoardVector.emplace_back(Score(it, Spectrum), it);
    }
    sort(LeaderBoardVector.begin(), LeaderBoardVector.end(), [](std::pair<int, string> a, std::pair<int, string> b) -> decltype(a.first > b.first)
    {
        return a.first > b.first;
    });
    set<string> NewLeaderBoard;
    size_t i = 0;
    while (i < N || (i >= N && LeaderBoardVector[i].first == LeaderBoardVector[N].first))
    {
        NewLeaderBoard.insert(LeaderBoardVector[i++].second);
    }
    return NewLeaderBoard;
}

string LeaderboardCyclopeptideSequencing(const multiset<int>& Spectrum, int N)
{
    set<string> LeaderBoard;
    string LeaderPeptide{ "" };
    LeaderBoard.insert(LeaderPeptide);
    while (!LeaderBoard.empty())
    {
        LeaderBoard = Expand(LeaderBoard);
        set<string> LeaderBoardCopy = LeaderBoard;
        for (const auto& it : LeaderBoardCopy)
        {
            auto itMax = --(Spectrum.end()); //элемент, обратный первому
            if (MassOfPeptide(it) == *itMax)
            {
                if (Score(it, Spectrum) > Score(LeaderPeptide, Spectrum))
                {
                    LeaderPeptide = it;
                }
            }
            else if (MassOfPeptide(it) > *itMax)
                LeaderBoard.erase(it);
        }
        if (!LeaderBoard.empty())
            LeaderBoard = Trim(LeaderBoard, Spectrum, N);
    }
    return LeaderPeptide;
}

void OutputResult(const string& LeaderPeptide)
{
    
    for (auto itChar = LeaderPeptide.begin(); itChar != LeaderPeptide.end(); itChar++)
    {
        cout << PeptideMap[*itChar];
        if (itChar != (LeaderPeptide.end() - 1))
            cout << "-";
    }

    cout << endl;
}

int main()
{
    
    int N{ 0 };
    cin >> N;
    int tmp{ 0 };
    multiset<int> Spectrum;
    while (cin >> tmp)
    {
        Spectrum.insert(tmp);
    }
    string LeaderPeptide = LeaderboardCyclopeptideSequencing(Spectrum, N);
    OutputResult(LeaderPeptide);
}