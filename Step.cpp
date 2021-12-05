#include "Step.h"

std::vector<Step> get_possible_steps( Field* field ){
   std::vector<Step> steps;
   
   for( int i = 0; i < field->boats.size(); i++ ){
      Boat* boat = field->boats[i];
      if( boat->full() ) continue;

      for( int j = 0; j < 4; j++ ){
         // Move boat in every direction
         boat->move( (Direction)j );
         
         // Test for collision
         if( field->valid() ){
            // Test ok? -> insert into steps
            steps.push_back( Step(boat, (Direction)j) );
         }         

         // Move boat back
         boat->move( (Direction)((j+2)%4) );
      }
   }

   return steps;
}


void Step::exe( Field* field ){
   m_boat->move( m_dir );
   // Test for possible rescues

   for( int i = 0; i <= m_boat->persons.size(); i++ ){
      if( m_boat->persons[i] != nullptr ) continue;
      Eigen::Vector2i pos = m_boat->pos + (1+i) * dir2vec[m_boat->ori];
      for( int j = 0; j < 4; j++ ){
         for( int k = 0; k < field->persons.size(); k++ ){
            if( field->persons[k]->pos == pos + dir2vec[j] && !field->persons[k]->in_boat ){
               field->persons[k]->in_boat = true;
               m_rescued_persons.push_back( field->persons[k] );
               m_boat->persons[i] = field->persons[k];
               return; 
            }
         }
      }
   }
}


void Step::undo( Field* field ){
   m_boat->move( (Direction)((m_dir+2)%4) );
   for(int i = 0; i < m_rescued_persons.size(); i++){
      m_rescued_persons[i]->in_boat = false;
      for( int j = 0; j < m_boat->persons.size(); j++ ){
         if( m_boat->persons[j] == m_rescued_persons[i] ){
            m_boat->persons[j] = nullptr;
            return;
         }
      }
   }
}
