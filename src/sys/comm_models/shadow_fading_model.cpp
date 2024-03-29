#include "sys/comm_models/shadow_fading_model.h"
#include "sys/node.h"
#include "sys/world.h"
#include "sys/simulation/simulation_controller.h"

#include <cassert>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>




using namespace std;

namespace shawn
{

   ShadowFadingModel::
   ShadowFadingModel()
      : initialized_ ( false ),
        range_       ( 1.0 ),
        has_range_   ( false )
   {}
   // ----------------------------------------------------------------------
   ShadowFadingModel::
   ~ShadowFadingModel()
   {}
   // ----------------------------------------------------------------------
   void
   ShadowFadingModel::
   init( void )
      throw()
   {
      CommunicationModel::init();
      initialized_ = true;
   }
   // ----------------------------------------------------------------------
   void
   ShadowFadingModel::
   set_transmission_range( double tr )
      throw()
   {
      assert( !initialized_ );
      range_ = tr;
      has_range_ = true;
      cout << "ShadowFadeModel: Transmission range set to ["<< range_ <<"]" << endl;
   }
   double
   ShadowFadingModel::
   transmission_range( void )
      const throw()
   {
      return range_;
   }
   // ----------------------------------------------------------------------
   bool
   ShadowFadingModel::
   can_communicate_bidi( const Node& u,
                         const Node& v )
      const throw()
   {
	   return true;
   }
   // ----------------------------------------------------------------------
   bool
   ShadowFadingModel::
   can_communicate_uni( const Node& u,
                        const Node& v )
      const throw()
   {
   	   const shawn::SimulationEnvironment& se = world().simulation_controller().environment();
   	   double PX = 0;
   	   double x = euclidean_distance( u.real_position(), v.real_position() );
   	   double Range = range_ * u.transmission_range();
   	   double beta = se.required_double_param( "beta" );
   	   if ( beta > 10 ) { beta = 10; }
   	   else if (beta < 1 ) { beta = 1; }
   	   double r_ratio = se.required_double_param( "r_ratio" );
   	   if ( r_ratio > 100 ) { r_ratio = 100; }
   	   else if ( r_ratio < 0 ) { r_ratio = 0; }
   	   double R = Range * r_ratio / 100;
   	   int r_error = se.required_int_param( "r_error" );
   	   if ( r_error > 100 ) { r_error = 100; }
   	   else if ( r_error < 0 ) { r_error = 0; }
   	   R = R + R * (double)( rand() % r_error ) / 100;
   	   if ( x < R )
   	   {
   		   PX =  1 - ( pow( x / R, 2 * beta ) / 2 );
   	   }
   	   else if (x >= R)
   	   {
   		   PX = pow( ( ( 2 * R - x ) / R ), 2 * beta ) / 2;
   	   }
   	   else if ( x > Range )
   	   {
   		   return false;
   	   }
   	   return ( rand() % 100 <= PX * 100 );
   }
   // ----------------------------------------------------------------------
   bool
   ShadowFadingModel::
   exists_communication_upper_bound( void )
      const throw()
   {
      return true;
   }
   // ----------------------------------------------------------------------
   double
   ShadowFadingModel::
   communication_upper_bound( void )
      const throw()
   {
      return range_;
   }
   // ----------------------------------------------------------------------
   bool
   ShadowFadingModel::
   is_status_available_on_construction( void )
      const throw()
   {
      return true;
   }
   // ----------------------------------------------------------------------
   void 
   ShadowFadingModel::
   set_size_hint(double size_hint)
   throw()
   {
        if(has_range_) 
            return;
        has_range_ = true;
        range_ = size_hint;
        cout << "ShadowFadingModel: Using size hint ["<< range_ <<"] as comm range" << endl;
   }

}
