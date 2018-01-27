#pragma once
#include "Stdafx.h"
#include "Vehicle.h"
#include "VisibleSimObject.h"


class R_Rescuer: public Vehicle {

public:
    R_Rescuer(int);
    int times_saved;
    void operate();
    void setVehInfoString();

};
