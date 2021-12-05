#include "Solver.h"
#include "Step.h"

#include <thread>
#include <unistd.h>

#include <iostream>

static bool stop = false;

static void print_progress(){
   while( !stop ){
      std::cout << ".";
      std::cout.flush();
      usleep(1000000);
   }
   std::cout << std::endl;
}

void Solver::print_result(){
   std::cout << result.size() << " Schritte:" << std::endl;
   for( int i = 0; i < result.size(); i++ ){
      std::cout << result[i].to_string() << std::endl;
   }
}

void Solver::solve( Field* field ){
   std::vector<Step> steps;
   stop = false;
   std::thread solve_thread( print_progress );

   solve_deeper( field, steps );
   stop = true;
   solve_thread.join();
}

void Solver::solve_deeper( Field* field, std::vector<Step>& steps ){
   // Gibt es für die aktuelle Situation einen Pfad, der schneller ist?
   // Dann springe hier aus der Suche raus.
   if(   fields.find(field->unique_string()) != fields.end() 
      && fields[ field->unique_string() ] <= steps.size() ){
      //std::cout << "Faster route already found." << std::endl;
      return;
   }

   fields[ field->unique_string() ] = steps.size();

   if( field->won() ){
      result = steps;
      //std::cout << "Lösung gefunden." << std::endl;
      return;
   }

   // Berechne alle möglichen Steps
   std::vector<Step> possible_steps = get_possible_steps( field );
 
   // Wenn Spiel gewonnen, Spielstand ausgeben und return;
   if( possible_steps.empty() ){
      //std::cout << "No possible steps." << std::endl;
      return;
   }

   //std::cout << "Possible_Steps: " << possible_steps.size() << std::endl;

   for( int i = 0; i < possible_steps.size(); i++){
      // Führe den jeweiligen Step aus
      possible_steps[i].exe( field );
      steps.push_back( possible_steps[i] );
      
      // Suche weiter
      solve_deeper( field, steps );

      // Setze den letzten Step zurück
      possible_steps[i].undo( field );
      steps.pop_back( );
   }
}

