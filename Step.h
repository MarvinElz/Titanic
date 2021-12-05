#ifndef STEP_H
#define STEP_H

#include "Field.h"
#include <vector>
#include <string>
#include <iostream>

class Step{
public:
   Step( Boat* boat, Direction dir ): 
      m_boat(boat),
      m_dir(dir)
      {}

   void exe( Field* );
   void undo( Field* );

   std::string to_string(){
      std::string output = std::to_string(m_boat->nr) + ": ";
      switch( m_dir ){
         case EAST:
            output += ">";
            break;
         case SOUTH:
            output += "v";
            break;
         case WEST:
            output += "<";
            break;
         case NORTH:
            output += "^";
            break;
      }
      return output;
   }

private:
   Boat* m_boat;
   std::vector<Person*> m_rescued_persons;
   Direction m_dir;
};



std::vector<Step> get_possible_steps( Field* );

#endif // STEP_H
