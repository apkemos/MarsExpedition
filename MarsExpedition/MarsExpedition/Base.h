#pragma once
#include "Stdafx.h"
#include "VisibleSimObject.h"


class Base {

public:
    Base();
    ~Base();
    int Base_cap;
    float elem_value[3];
    int elem_number[3];

    int* elements_ordered();
    bool available_parking;
    void showResources();

    float elem_max_value[3];
    int isMax[3]; // 0 for full 1 for not full
};
