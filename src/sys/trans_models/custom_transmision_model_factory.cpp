/************************************************************************
 ** This file is part of the network simulator Shawn.                  **
 ** Copyright (C) 2004-2007 by the SwarmNet (www.swarmnet.de) project  **
 ** Shawn is free software; you can redistribute it and/or modify it   **
 ** under the terms of the BSD License. Refer to the shawn-licence.txt **
 ** file in the root of the Shawn source tree for further details.     **
 ************************************************************************/

#include "sys/transm_models/custom_transmission_model.h"
#include "sys/transm_models/custom_transmission_model_factory.h"
#include "sys/transm_models/transmission_model_keeper.h"
#include "sys/simulation/simulation_controller.h"
#include "sys/simulation/simulation_environment.h"

namespace shawn
{

   CustomTransmissionModelFactory::
   CustomTransmissionModelFactory()
   {}
   // ----------------------------------------------------------------------
   CustomTransmissionModelFactory::
   ~CustomTransmissionModelFactory()
   {}
   // ----------------------------------------------------------------------
   std::string
   CustomTransmissionModelFactory::
   name( void )
      const throw()
   {
      return std::string("custom");
   }
   // ----------------------------------------------------------------------
   std::string
   CustomTransmissionModelFactory::
   description( void )
      const throw()
   {
      return std::string("A CustomTransmissionModel (\"custom\") delivers every message without loss."
          "If $immediate_delivery is set to true, messages will be delivered immediately, otherwise "
          "they will be delivered at the beginning of a new simulation round, just before Processor::work() "
          "is called.");
   }
   // ----------------------------------------------------------------------
   TransmissionModel*
   CustomTransmissionModelFactory::
   create( const SimulationController& sc)
      throw()
   {
       bool immediate_delivery = sc.environment().optional_bool_param("immediate_delivery", false);
       return new CustomTransmissionModel(immediate_delivery);
   }

}

/*-----------------------------------------------------------------------
 * Source  $Source: /cvs/shawn/shawn/sys/transm_models/custom_transmission_model_factory.cpp,v $
 * Version $Revision: 38 $
 * Date    $Date: 2007-06-08 14:30:12 +0200 (Fri, 08 Jun 2007) $
 *-----------------------------------------------------------------------
 * $Log: custom_transmission_model_factory.cpp,v $
 *-----------------------------------------------------------------------*/
