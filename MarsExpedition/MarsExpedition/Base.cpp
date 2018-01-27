#include "Stdafx.h"
#include "Base.h"

Base::Base()
{


    elem_max_value[0] = 100;
    elem_max_value[1] = 100;
    elem_max_value[2] = 600;
    Base_cap = elem_max_value[0] + elem_max_value[1] +  elem_max_value[2];
    for (int i=0; i<3; i++)
    {
        elem_value[i] = 0;
        elem_number[i]=i;
        isMax[i] = 1;
    }
    available_parking = true;

}


Base::~Base(){ }




int* Base::elements_ordered()

{



    for (int i=0; i<3; i++)
    {
        for (int j=2; j>0; j--)
        {
            if ( elem_value[j] < elem_value[j-1] )
            {
                int temp = elem_value[j];
                elem_value[j] = elem_value[j-1];
                elem_value[j-1] = temp;

                temp = elem_number[j];
                elem_number[j] = elem_number[j-1];
                elem_number[j-1] = temp;
            }
        }

    }



    return elem_number;

}

void Base::showResources()
{

    for (int i=0; i<3; i++)
    {
        std::cout << "Element " << i << " Value: " << elem_value[i] << std::endl;

    }

}

