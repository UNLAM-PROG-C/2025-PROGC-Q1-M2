#ifndef TOURNAMENT_SIMULATOR_HPP
#define TOURNAMENT_SIMULATOR_HPP

#include <vector>
#include <thread>

#include "Tournament.hpp"

class Tournament_Simulator{
  private:
    static void simulation_match(Match& match)
    {
      this_thread::sleep_for(chrono::milliseconds(125));

      match.score_home = match.score_away = 0;

      for(int i = 0; i<5; i++)
      {
        double prob = (rand() % 100);

        if(prob < 35)
          match.score_home += 1;
        else if(prob > 75)
          match.score_away += 1;
      }
    }
  
    static void process_matchday(const Tournament& tournament, int matchday)
    {
      for(const Match& match : tournament.fixture[matchday])
      {
        apply_result(match.home, match.away, match.score_home - match.score_away);
        match.home->update_score(match.score_home, match.score_away);
        match.away->update_score(match.score_away, match.score_home);
      }
    }
  
    static void apply_result(Team* home, Team* away, int result)
    {
      if(result > 0)
      {
        home->win();
        away->lose();
      }
      else if(result < 0)
      {
        home->lose();
        away->win();
      }
      else
      {
        home->draw();
        away->draw();
      }
    }
  
  public:
    static void run_threads(Tournament& tournament)
    {
      vector<thread> ths;

      for(size_t i = 0; i < tournament.fixture.size() / 2; i++)
      {
        for(Match& match : tournament.fixture[i])
        {
          ths.emplace_back(simulation_match, ref(match));
        }

        for (thread& th : ths)
        {
          if (th.joinable())
            th.join();
        }

        ths.clear();

        process_matchday(tournament, i);
      }
    }
  
    static void run_sequentially(Tournament& tournament)
    {
      vector<thread> ths;

      for(size_t i = 0; i < tournament.fixture.size() / 2; i++)
      {
        for(Match& match : tournament.fixture[i])
        {
          simulation_match(match);
        }

        process_matchday(tournament, i);
      }
    }
  };

#endif // TOURNAMENT_SIMULATOR_HPP
