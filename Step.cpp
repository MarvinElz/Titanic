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
            
            std::vector<std::vector<Person*>> rescued_persons_in_place( boat->size );
            
            for( int m = 0; m < boat->size; m++ ){
               std::vector<Person*> rescued_persons;
               if( boat->persons[m] != nullptr ){
                  // Place already taken
                  rescued_persons.push_back( nullptr );
                  rescued_persons_in_place[m] = rescued_persons;
                  continue;
               }
      
               // Position of free space in boat in global coordinates
               Eigen::Vector2i pos = boat->pos + (1+m) * dir2vec[boat->ori];
               for( int d = 0; d < 4; d++ ){
                  for( int k = 0; k < field->persons.size(); k++ ){
                     if( !field->persons[k]->in_boat && field->persons[k]->pos == pos + dir2vec[d] ){
                        rescued_persons.push_back( field->persons[k] );
                     }
                  }
               }
               if( rescued_persons.empty() ){
                  rescued_persons.push_back( nullptr );
               }
               rescued_persons_in_place[m] = rescued_persons;
            }
            
            for( int m1 = 0; m1 < rescued_persons_in_place[0].size(); m1++ ){
               std::vector<Person*> rescued_persons(boat->size);
               rescued_persons[0] = rescued_persons_in_place[0][m1];
               if( rescued_persons_in_place.size() > 1 ){
                  for( int m2 = 0; m2 < rescued_persons_in_place[1].size(); m2++ ){
                     rescued_persons[1] = rescued_persons_in_place[1][m2];
                     steps.push_back( Step(boat, (Direction)j, rescued_persons ) );
                  }
               }else{
                  steps.push_back( Step(boat, (Direction)j, rescued_persons ) ); 
               }
            }            
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

   for(int i = 0; i < m_rescued_persons.size(); i++){
      if( m_rescued_persons[i] == nullptr ) continue;
      m_rescued_persons[i]->in_boat = true;
      if( m_boat->persons[i] ){
         std::cout << "FEHLER: Platz im Boat ist schon besetzt." << std::endl;
      }
      m_boat->persons[i] = m_rescued_persons[i];
   }
}


void Step::undo( Field* field ){
   m_boat->move( (Direction)((m_dir+2)%4) );
   for(int i = 0; i < m_rescued_persons.size(); i++){
      if( m_rescued_persons[i] == nullptr ) continue;
      m_rescued_persons[i]->in_boat = false;
      m_boat->persons[i] = nullptr;
   }
}
