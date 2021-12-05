#ifndef SOLVER_H
#define SOLVER_H

#include "Field.h"
#include "Step.h"

#include <map>
#include <vector>

#include <string>

class Solver{
public:
   void solve( Field* );

   void print_result();

   bool solution_found(){ return !result.empty(); }

private:
   void solve_deeper( Field*, std::vector<Step>& );
   std::map<std::string, int> fields;
   std::vector<Step> result;
   //bool result_found = false;
};

#endif // SOLVER_H
