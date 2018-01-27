#pragma once
#include "Stdafx.h"
#include "Vehicle.h"
#include "VisibleSimObject.h"




class R_Analyzer: public Vehicle {

public:


    R_Analyzer(int);

    float max_cargo_allowed;
    float curr_cargo;
    float elements[3];
    float total_spot_conciseness;
    int times_fulled;
    static int count;
    static float total_veh_cargo; //All vehicles cargo
    float total_cargo_gathered; //For 1 vehicle only
    void operate();
    void setVehInfoString();


};



