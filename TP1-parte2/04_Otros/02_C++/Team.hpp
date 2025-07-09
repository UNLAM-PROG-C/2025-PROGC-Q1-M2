#ifndef TEAM_HPP
#define TEAM_HPP

#include <string>

using namespace std;

class Team 
{
  private:
    string name;
    unsigned int pj = 0, pg = 0, pe = 0, pp = 0, gf = 0, gc = 0;
  
  public:
    Team(const string name_team) 
      : name(name_team) {}

    void reset()
    {
      pj = pg = pe = pp = gf = gc = 0;
    }

    void win()
    {
      this->pj++;
      this->pg++;
    }

    void lose()
    {
      this->pj++;
      this->pp++;
    }

    void draw()
    {
      this->pj++;
      this->pe++;
    }

    void update_score(const int gf, const int gc)
    {
      this->gf += gf;
      this->gc += gc;
    }
    
    string get_name() const 
    {
      return this->name;
    }

    int get_pts() const
    {
      return (this->pg * 2) + this->pe;
    }

    int get_dif() const
    {
      return this->gf - this->gc;
    }

    string get_info() const
    {
      char format[150];
      snprintf(format, sizeof(format), "| %-25s | %5d | %5d | %5d | %5d | %5d | %5d | %5d | %5d", name.c_str(), get_pts(), pj, pg, pe, pp, gf, gc, get_dif());      
      return string(format);
    }
};

#endif // TEAM_HPP
