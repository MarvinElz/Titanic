#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <vector>
#include <eigen3/Eigen/Eigen>

static Eigen::Vector2i dir2vec[] = {
   Eigen::Vector2i( 1,0 ),
   Eigen::Vector2i( 0,1 ),
   Eigen::Vector2i(-1,0 ),
   Eigen::Vector2i( 0,-1)
};

typedef enum{
   EAST,
   SOUTH,
   WEST,
   NORTH
}Direction;

class Person{
public:
   Person( std::string line );
   
//private:
   char name;
   Eigen::Vector2i pos;
   //int x;
   //int y;
   bool in_boat;
};

class Boat{
public:
   Boat( std::string line );

   bool full(){
      for( int i = 0; i < persons.size(); i++ ){
         if( persons[i] == nullptr ) return false;
      }
      return true;
   }

   void move( Direction dir ){
      pos += dir2vec[dir];
   }


//private:
   int nr;
   Direction ori;    // Orientation
   int size;
   //Eigen::Vector2i pos_init;
   //int x_init;       // Initiale Position x;
   //int y_init;       // Initiale Position y;
   Eigen::Vector2i pos;
   //int x;
   //int y;

   std::vector<Person*> persons;
};

class Field{
public:
   Field( std::string file );

   std::string unique_string();
   
   void draw();

   bool valid();

   bool won(){
      for( int i = 0; i < persons.size(); i++ ){
         if( !persons[i]->in_boat ) return false;
      }
      return true;
   }

//private:
   std::vector<Boat*>   boats;
   std::vector<Person*> persons;
};

#endif // FIELD_H
