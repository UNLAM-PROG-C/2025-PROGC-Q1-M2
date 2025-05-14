#ifndef TOURNAMENT_HPP
#define TOURNAMENT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Team.hpp"

using namespace std;

struct Match{
  unsigned int matchday = 0;
  Team* home;
  Team* away;
  int score_home = -1, score_away = -1;

  Match(unsigned int day, Team* h, Team* a)
    : matchday(day), home(h), away(a) {}
};

class Tournament {
  private:
    const int year;

    vector<Team> teams = {};
    vector<vector<Match>> fixture = {};
    friend class Tournament_Simulator;

    void check_odd()
    {
      if (this->teams.size() % 2 != 0) 
      this->teams.push_back(Team("LIBRE"));
    }

    vector<Match> generate_single_round_matchs(int n, vector<int> index, int round)
    {
      vector<Match> matchday;

      for (int i = 0; i < n / 2; ++i) 
      {
        int id_home = index[i], id_away = index[n - 1 - i];

        if (teams[id_home].get_name() != "LIBRE" && teams[id_away].get_name() != "LIBRE")
        {
          if (round % 2 == 0)
            matchday.emplace_back(round + 1, &teams[id_home], &teams[id_away]);
          else
            matchday.emplace_back(round + 1, &teams[id_away], &teams[id_home]);
        }
      }

      return matchday;
    }

    void generate_first_round()
    {
      int n = this->teams.size();
      int all_matchdays = n - 1;

      vector<int> index(n);
      for (int i = 0; i < n; i++) index[i] = i;

      for (int round = 0; round < all_matchdays; ++round) 
      {
        vector<Match> matchday = generate_single_round_matchs(n, index, round);

        fixture.push_back(matchday);

        rotate(index.begin() + 1, index.end() - 1, index.end());
      }
    }

    void generate_second_round()
    {
      int all_matchdays = this->teams.size() - 1;

      for (int round = 0; round < all_matchdays; ++round) 
      {
        vector<Match> matchday;
        for (const Match& match : fixture.at(round)) 
        {
          matchday.emplace_back(round + 1 + all_matchdays, match.away, match.home);
        }
        fixture.push_back(matchday);
      }
    }
    
  public:
    Tournament(int y, vector<string> names_team) : year(y)
    {
      for(const string& name : names_team) 
      {
        teams.emplace_back(name);
      }
    }

    void generate_fixture() 
    {
      check_odd();

      generate_first_round();

      generate_second_round();
    }

    void reset_tournament()
    {
      for(Team& team : teams)
      {
        team.reset();
      }
    }

    vector<const Team*> get_teams_sorted() const
    {
      vector<const Team*> team_to_sort;

      for(const Team& team: teams)
      {
        if(team.get_name() != "LIBRE")
          team_to_sort.push_back(&team);
      }

      sort(team_to_sort.begin(), team_to_sort.end(), [](const Team* first, const Team* other) 
      {
        if(first->get_pts() != other->get_pts())
          return first->get_pts() > other->get_pts();

        return first->get_dif() > other->get_dif();
      });

      return team_to_sort;
    }

    void print_tournament()
    {
      vector<const Team*> teams_sorted = get_teams_sorted();

      printf("------------------------------------------------------------------------------------------------\n");
      printf("%30s %s %d %-30s \n", "", "Posiciones Finales Torneo", year, "");
      printf("------------------------------------------------------------------------------------------------\n");
      printf("#  | %-25s | %5s | %5s | %5s | %5s | %5s | %5s | %5s | %5s \n", "Equipo","Pts", "PJ", "PG", "PE", "PP", "GF", "GC", "DIF");

      for(size_t i=0; i<teams_sorted.size(); i++)
      {
        cout << (i+1) << ((i>8)? " " : "  ") << teams_sorted[i]->get_info() << endl;
      }
      printf("------------------------------------------------------------------------------------------------\n");
    }

    void print_fixtures()
    {
      for(size_t i=0; i<fixture.size() / 2; i++)
      {
        cout << "Fecha N°" << (i+1) << endl;
        for(const Match& match : fixture[i])
        {
          printf("%-25s %-3d - %3d %25s \n", match.home->get_name().c_str(), match.score_home, match.score_away, match.away->get_name().c_str());
        }
        cout << endl;
      }
    }
};

#endif // TOURNAMENT_HPP
