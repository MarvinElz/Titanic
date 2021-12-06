#ifndef STEP_H
#define STEP_H

#include "Field.h"
#include <vector>
#include <string>
#include <iostream>

class Step{
public:

   Step( const Step& step ):
      m_boat( step.m_boat ),
      m_dir( step.m_dir),
      m_rescued_persons( step.m_rescued_persons)
	   {}
      
   Step( Step& step ):
      m_boat( step.m_boat ),
      m_dir( step.m_dir),
      m_rescued_persons( step.m_rescued_persons)
      {}

   Step( Boat* boat, Direction dir, std::vector<Person*> rescued_persons ): 
      m_boat(boat),
      m_dir(dir),
      m_rescued_persons(rescued_persons)
      { /*std::cout << this->to_string() << std::endl;*/ }

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
      
      for( int i = 0; i < m_rescued_persons.size(); i++ ){
		   if( m_rescued_persons[i] == nullptr ) continue;
		   output += " take ";
         output += m_rescued_persons[i]->name;
		}
		
      return output;
   }
   
   int number_of_rescues() const {
		int count = 0;
		for( int i = 0; i < m_rescued_persons.size(); i++ ){
			if( m_rescued_persons[i] != nullptr ) count++;
		}
		return count;
	}

   Boat* m_boat;
private:
   std::vector<Person*> m_rescued_persons;
   Direction m_dir;
};



std::vector<Step> get_possible_steps( Field* );

#endif // STEP_H
