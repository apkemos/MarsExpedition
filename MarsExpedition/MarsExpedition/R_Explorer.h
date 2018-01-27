#pragma once
#include "Stdafx.h"
#include "Vehicle.h"
#include "VisibleSimObject.h"



class R_Explorer: public Vehicle {

public:

     int flags;
     R_Explorer(int);

     void operate();
     void setVehInfoString();
};
