#include "Aquarium.h"

#include "Milieu.h"
#include "constants.h"

Aquarium::Aquarium( int width, int height, int _delay ) : CImgDisplay(), delay( _delay )
{

   int         screenWidth = screenWidthPX; //screen_width();
   int         screenHeight = screenHeightPX; //screen_height();


   cout << "const Aquarium" << endl;

   flotte = new Milieu( width, height );
   assign( *flotte, "Simulation d'ecosysteme" );

   move( static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2) );

}


Aquarium::~Aquarium( void )
{

   delete flotte;

   cout << "dest Aquarium" << endl;

}


void Aquarium::run( void )
{

   //cout << "running Aquarium" << endl;

   while ( ! is_closed() )
   {


      if ( is_key() ) {
         cout << "You pressed key " << static_cast<unsigned char>( key() );
         cout << " (" << key() << ")" << endl;
         if ( is_keyESC() ) close();
      }


      flotte->step();
      if (flotte->getNbCreatures()==0) 
      {
         cout<<"Every creatures died, simulation is over"<<endl;
         close();
      }


      display( *flotte );
      wait( delay );

   } // while

}
