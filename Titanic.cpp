// Programm zum Lösen von Titanic-Rätseln
// Level werden als Datei eingeladen

#include "Field.h"
#include "Solver.h"

#include <iostream>

void print_usage(){
   std::cout << "Usage:" << std::endl;
   std::cout << "   ./Titanic level_datei.txt" << std::endl;
}

int main( int argc, char** argv ){
   if( argc < 2 ){
      std::cout << "Bitte Level-Datei mit angeben." << std::endl;
      print_usage();
      return 1;
   }

   //std::cout << "Öffne Datei:" << argv[1] << std::endl; 
   Field field( argv[1] );
   //std::cout << field.unique_string() << std::endl;

   Solver solver;
   solver.solve( &field );

   if( solver.solution_found() ){
      std::cout << "Lösung gefunden." << std::endl;
   }

   solver.print_result();
}
