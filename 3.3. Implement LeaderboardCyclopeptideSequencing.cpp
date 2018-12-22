using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3._3__Leaderboard_Cyclopeptide_Sequencing
{
    class Program
    {
        static Dictionary<char, int> AminoacidMass = new Dictionary<char, int>()
        {{'G', 57}, {'A', 71}, {'S', 87}, {'P', 97}, {'V', 99}, {'T', 101}, {'C', 103}, {'I', 113}, {'L', 113}, {'N', 114}, {'D', 115}, {'K', 128},
         { 'Q', 128}, {'E', 129}, {'M', 131}, {'H', 137}, {'F', 147}, {'R', 156}, {'Y', 163}, {'W', 186}};

        static int Mass(string peptide)
        {
            int mass = 0;
            for (int i = 0; i < peptide.Length; i++)
                mass += AminoacidMass[peptide[i]];
            return mass;
        }

        static List<string> Expand(List<string> peptides)
        {
            List<string> newPeptides = new List<string>();

            foreach (var peptide in peptides)
            {
                foreach (var key in AminoacidMass.Keys)
                {
                    newPeptides.Add(peptide + key);
                }
            }
            return newPeptides;
        }

        static string LinearSpectrum(string peptide)
        {
            List<int> Linearspectrum = new List<int>();
            string subpeptide = " ";
            int mass = 0;

            if (peptide.Length == 1)
                return AminoacidMass[peptide[0]].ToString();

            Linearspectrum.Add(0);

            for (int i = 1; i < peptide.Length; i++)
            {
                for (int j = 0; j < peptide.Length; j++)
                {
                    if ((i + j) <= peptide.Length)
                    {
                        subpeptide = peptide.Substring(j, i);
                        Linearspectrum.Add(Mass(subpeptide));
                    }
                }
            }

            Linearspectrum.Add(Mass(peptide));

            Linearspectrum.Sort();
            return string.Join(" ", Linearspectrum);
        }

        static int Score(string peptide, string spectrum)
        {
            List<string> peptideMass = LinearSpectrum(peptide).Split(' ').ToList();
            List<string> spectrumMass = spectrum.Split(' ').ToList();

            int score = 0;

            foreach (var mass in peptideMass)
            {
                if (spectrumMass.Contains(mass))
                {
                    spectrumMass.Remove(mass);
                    score++;
                }
            }

            return score;
        }

        static List<string> Trim(List<string> Leaderboard, string Spectrum, int N)
        {
            Leaderboard.Sort((a, b) => Score(b, Spectrum).CompareTo(Score(a, Spectrum)));
            if (Leaderboard.Count > N)
            {
                int last = N;
                for (int i = N; i < Leaderboard.Count; i++)
                {
                    if (Score(Leaderboard[N - 1], Spectrum) == Score(Leaderboard[i], Spectrum))
                    {
                        last = i;
                    }
                    else break;
                }

                Leaderboard = Leaderboard.Take(last + 1).ToList();
            }

            return Leaderboard;
        }

        static int ParentMass(string spectrum)
        {
            int parentMass = int.Parse(spectrum.Split(' ').Last());
            return parentMass;
        }

        static string LeaderboardCyclopeptideSequencing(string Spectrum, int N)
        {
            List<string> Leaderboard = new List<string>() { "" };
            string LeaderPeptide = "";
            while(Leaderboard.Count() > 0)
            {
                Leaderboard = Expand(Leaderboard);

                List<string> LeaderboardExemple = new List<string>(Leaderboard);
                foreach (var Peptide in LeaderboardExemple)
                {
                    if(Mass(Peptide) == ParentMass(Spectrum))
                    {
                        if(Score(Peptide, Spectrum) > Score(LeaderPeptide, Spectrum))
                        {
                            LeaderPeptide = Peptide;
                        }
                    }
                    else if(Mass(Peptide) > ParentMass(Spectrum))
                    {
                        Leaderboard.Remove(Peptide);
                    }
                }
                Leaderboard = Trim(Leaderboard, Spectrum, N);
            }
            return LeaderPeptide;
        }

        static void Main(string[] args)
        {
            int N = int.Parse(Console.ReadLine());
            string Spectrum = Console.ReadLine();

            string LeaderPeptide = LeaderboardCyclopeptideSequencing(Spectrum, N);

            List<string> Mass = new List<string>();
            foreach (var Peptide in LeaderPeptide)
            {
                Mass.Add(AminoacidMass[Peptide].ToString());
            }

            Console.WriteLine(string.Join("-", Mass));
        }
    }
}