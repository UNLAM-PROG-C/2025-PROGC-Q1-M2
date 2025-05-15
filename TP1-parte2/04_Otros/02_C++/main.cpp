#include "Tournament.hpp"
#include "TournamentSimulator.hpp"

void run_tournament_simulation(Tournament& tt, void(*simulation)(Tournament&))
{
  tt.reset_tournament();
  cout << "Iniciando simulación..." << endl;
  auto start_time = chrono::high_resolution_clock::now();
  simulation(tt);
  auto end_time = chrono::high_resolution_clock::now();
  chrono::duration<double>  duration = end_time - start_time;
  tt.print_tournament();
  cout << " • Tiempo de ejecución: " << duration.count() << " segundos." << std::endl;
}

int main() 
{
  srand(time(NULL));
  
  const int year = 1992;
  
  const vector<string> names_team = {
    "Boca Juniors", "River Plate", "San Lorenzo",
    "Ferro", "Huracan", "Velez", "Estudiantes (LP)",
    "Belgrano", "Lanus", "Talleres (C)", "Dep Espanol",
    "San Martin (T)", "Dep Mandiyu (C)", "Rosario Central",
    "Independiente", "Racing Club", "Gimnasia (LP)",
    "Platense", "Argentinos", "Newells"
  };
  
  Tournament tt = Tournament(year, names_team);
  
  tt.generate_fixture();

  int option = -1;
  
  do
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Ingrese que simulación quiere ejecutar..." << endl;
    cout << "   (1) - Secuencial " << endl;
    cout << "   (2) - Hilos " << endl;
    cout << "   (3) - Ver resultados " << endl;
    cout << "   (4) - Salir " << endl;
    cout << "--------------------------------------------------" << endl;

    cin >> option;

    if (cin.fail()) 
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Entrada inválida. Intente nuevamente..." << endl;
      continue;
    }

    switch (option)
    {
      case 1:
        run_tournament_simulation(tt, &Tournament_Simulator::run_sequentially);
        break;
        
      case 2:
        run_tournament_simulation(tt, &Tournament_Simulator::run_threads);
        break;

      case 3:
        tt.print_fixtures();
        break;

      case 4:
        cout << "Cerrando programa..." << endl;
        break;
      
      default:
        cout << "Opción inválida. Intente nuevamente..." << endl;
        break;
    }
  } while (option != 4);
}
  
