#include "Field.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <eigen3/Eigen/Eigen>

void replace_commas( std::string& line ){
   for( int i = 0; i < line.length(); i++ ){
      if( line[i] == ',' ) line[i] = ' ';
   }
}

// # Person, Nr(A,B,C,...), X, Y
//      P,         A,       0, 1
Person::Person( std::string line ){
   replace_commas( line );
   std::stringstream ss( line );
   char dummy;
   ss >> dummy; // 'P'
   ss >> name;
   int x, y;
   ss >> x;
   ss >> y;
   pos = Eigen::Vector2i(x, y);

   std::cout << "Name:" << name << ", x:" << x << ", y:" << y << std::endl;
}

// # Boat, Nr, Places, X, Y, Orientation
//    B  , 1 ,    1  , 1, 0,     W
Boat::Boat( std::string line ){
   replace_commas( line );
   std::stringstream ss( line );
   char dummy;
   ss >> dummy;
   ss >> nr;
   ss >> size;
   int x, y;
   ss >> x;
   ss >> y;
   pos = Eigen::Vector2i(x, y);
   char orientation;
   ss >> orientation;

   for(int i = 0; i < size; i++){
      persons.push_back(nullptr);
   }

   switch( orientation ){
      case 'N': ori = NORTH; break;
      case 'E': ori = EAST;  break;
      case 'S': ori = SOUTH; break;
      case 'W': ori = WEST;  break;
   }

   std::cout << "Nummer:" << nr << ", Size:" << size <<  ", x:" << x << ", y:" << y << ", Ori:" << ori << std::endl;
}


// Berechnet eindeutigen Wert für den jeweiligen Spielzustand
std::string Field::unique_string(){
   std::string result = "";
   for(int i = 0; i < boats.size(); i++){
      result += std::to_string(boats[i]->pos.x());
      result += std::to_string(boats[i]->pos.y());
      for( int j = 0; j < boats[i]->size; j++ ){
         result += boats[i]->persons[j] ? boats[i]->persons[j]->name : ' ';
      }
   }
   return result;
}

bool Field::valid(){
   bool binary_field[6][6] = {false};

   for( int i = 0; i < persons.size(); i++ ){
      if( !persons[i]->in_boat ){
         binary_field[persons[i]->pos.x()][persons[i]->pos.y()] = true;
      }
   }

   for( int i = 0; i < boats.size(); i++ ){
      Boat* boat = boats[i];
      for( int j = 0; j <= boat->size; j++){
         Eigen::Vector2i pos = boat->pos + j * dir2vec[boat->ori];
         if( pos.x() < 0 || pos.x() >= 6 ) return false;
         if( pos.y() < 0 || pos.y() >= 6 ) return false;
         if( binary_field[pos.x()][pos.y()] ) return false;
         binary_field[pos.x()][pos.y()] = true;
      }
   }
/*
   std::cout << "------" << std::endl;
   for( int y = 0; y < 6; y++ ){
      for( int x = 0; x < 6; x++){
         std::cout << (binary_field[x][y] ? "X" : "O");
      }
      std::cout << std::endl;
   }
   std::cout << "------" << std::endl;
*/
   return true;
}

void Field::draw(){
	char field[6][6]; // = {' '};
   
   memset( field, ' ', 6*6 );
	
	for( int i = 0; i < persons.size(); i++ ){
		if( persons[i]->in_boat ) continue;
		field[persons[i]->pos.x()][persons[i]->pos.y()] = persons[i]->name;
	}
	
	for( int i = 0; i < boats.size(); i++ ){
      Boat* boat = boats[i];
      field[boat->pos.x()][boat->pos.y()] = boat->nr + '0';
      for( int j = 0; j < boat->size; j++){
         Eigen::Vector2i pos = boat->pos + (j+1) * dir2vec[boat->ori];
         if( boat->persons[j] == nullptr ){
			 // Platz leer
			 field[pos.x()][pos.y()] = '0';
		 }else{
			 field[pos.x()][pos.y()] = boat->persons[j]->name;
		 }
      }
   }
   
   std::cout << "------" << std::endl;
   for( int y = 0; y < 6; y++){
      for( int x = 0; x < 6; x++ ){
         std::cout << (char)field[x][y];
      } 
      std::cout << std::endl;
   }
   std::cout << "------" << std::endl;   
}

Field::Field( std::string file_path ){
   std::string line;
   std::ifstream file (file_path);
   if (file.is_open()){
      while ( getline (file,line) ){
         if( line[0] == '#' ) continue;
         if( line[0] == 'B' ){
            boats.push_back( new Boat( line ) );
            continue;
         }
         if( line[0] == 'P' ){
            persons.push_back( new Person( line ) );
            continue;
         }
      }
      file.close();
   }
}
