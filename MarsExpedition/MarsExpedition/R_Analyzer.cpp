#include "Stdafx.h"
#include "Map.h"
#include "R_Analyzer.h"
#include "Base.h"

using namespace std;
int R_Analyzer::count = 0 ;
float R_Analyzer::total_veh_cargo = 0;
R_Analyzer::R_Analyzer(int identification)
    {
        orig_filename = "images/ball.png";
        id = identification;
        for (int i=0; i<3; i++)
        {
            elements[i]=0;
        }


        total_spot_conciseness = 0;
        curr_cargo = 0;
        times_fulled = 0;
        max_cargo_allowed = 500;
        _velocity=300;
        total_cargo_gathered = 0;
        Load("images/ball.png");
        assert(IsLoaded());
        GetSprite().setOrigin( GetSprite().getLocalBounds().width/2, GetSprite().getLocalBounds().height/ 2);
        //GetSprite().setPosition(veh_pos.x, veh_pos.y);
    }





void R_Analyzer::operate(){

    if (Sim::map.map_mining_state == false)
    {
        destination = Map::find_Destination();
        _vehState = Moving;
        return;
    }


    sf::Clock clock;
    float time = clock.restart().asSeconds();
    timeElapsed += time;


    if (timeElapsed >=0.003 )
    {

        timeElapsed = 0;
        total_spot_conciseness = Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][0] + Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][1] + Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][2];
        int* ordered;
        ordered =  Map::base.elements_ordered();
     //   for (int i= 0; i<3; i++) {cout << "Elements Sorted " << ordered[i]<<endl; }

        if ( total_spot_conciseness +curr_cargo > max_cargo_allowed )
        {
                  float Small_Mining;
            //     cout << "MILISAME" << endl;
           //      cout << "total_map_conciseness " << total_spot_conciseness << endl;
           //      cout << "First Element conciseness " << Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[0]] << endl;
                if (  Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[0]] + curr_cargo  > max_cargo_allowed )
                   {
                      // cout << "Mia xara" <<endl;
                       Small_Mining =  max_cargo_allowed - curr_cargo ;
                       elements[ordered[0]] += Small_Mining;
                       curr_cargo += Small_Mining;
                       total_veh_cargo += Small_Mining;
                       total_cargo_gathered += Small_Mining;
                       Small_Mining =0;
                       Sim::map.map_total_conciseness[ordered[0]] -= Small_Mining;
                       Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[0]] -= Small_Mining;
                   }
                else
                {
                    //    cout << "Mia luph" <<endl;
                        elements[ordered[0]] += Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[0]];
                        curr_cargo += Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[0]];
                        total_veh_cargo += Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[0]];
                        total_cargo_gathered += Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[0]];
                        Sim::map.map_total_conciseness[ordered[2]] -=  Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[0]];
                        Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[0]] = 0;
                }



               // cout << "Second Element conciseness " << Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[1]] << endl;
               if (  Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[1]] + curr_cargo  > max_cargo_allowed )

                    {
                   //     cout << "Mia xara2" <<endl;
                       Small_Mining =  max_cargo_allowed - curr_cargo ;
                       elements[ordered[1]] += Small_Mining;
                       curr_cargo += Small_Mining;
                       total_veh_cargo += Small_Mining;
                       total_cargo_gathered += Small_Mining;
                       Small_Mining =0;
                       Sim::map.map_total_conciseness[ordered[1]] -= Small_Mining;
                       Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[1]] -= Small_Mining;

                   }
                else
                {
                    //    cout << "Mia luph2" <<endl;
                        elements[ordered[1]] += Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[1]];

                        curr_cargo += Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[1]];
                        total_veh_cargo += Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[1]];
                        total_cargo_gathered += Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[1]];
                        Sim::map.map_total_conciseness[ordered[2]] -=  Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[1]];
                        Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[1]] = 0;

                }


            //  cout << "Third Element conciseness " << Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[2]] << endl;
                 if (  Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[2]] + curr_cargo  > max_cargo_allowed )
                   {
                   //    cout << "Mia xara3" <<endl;
                       Small_Mining =  max_cargo_allowed - curr_cargo ;
                       elements[ordered[2]] += Small_Mining;
                       curr_cargo += Small_Mining;
                       total_veh_cargo += Small_Mining;
                       total_cargo_gathered += Small_Mining;
                       Small_Mining =0;
                       Sim::map.map_total_conciseness[ordered[2]] -= Small_Mining;
                       Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[2]] -= Small_Mining;
                   }
                else
                {
                  //      cout << "Mia luph3" <<endl;
                        elements[ordered[2]] += Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[2]];
                        curr_cargo += Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[2]];
                        total_veh_cargo += Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[2]];
                        total_cargo_gathered += Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[2]];
                        Sim::map.map_total_conciseness[ordered[2]] -=  Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[2]];
                        Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][ordered[2]] = 0;
                }




        }
        else
        {
            float element_mined[3];
            for (int k=0; k<3; k++)
           {
               element_mined[k] = Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][k] * Sim::map.base.isMax[k];
               elements[k] += element_mined[k];
               curr_cargo += element_mined[k];
               total_veh_cargo += element_mined[k];

               Sim::map.map_total_conciseness[k] -= element_mined[k];
               Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][k] -= element_mined[k];

           }



        }


      //  cout <<  "Curr Cargo " << curr_cargo <<endl;
        destination = Map::find_Destination();
        _vehState = Moving;
        Sim::map.destination_tracker[ veh_pos.x+ veh_pos.y*16] = false;

        total_spot_conciseness = Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][0] + Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][1] + Sim::map.map_conciseness[veh_pos.x + veh_pos.y * 16][2];

        if ( total_spot_conciseness == 0 )
        {
            count++;
          //  cout << "Count "<< count << endl;
            Sim::map.map_mining_state[veh_pos.x + veh_pos.y*16] = true;
        }



        total_spot_conciseness = 0;
        if ( curr_cargo == max_cargo_allowed ) //
        {
            times_fulled++;
             if (Map::base.available_parking == true)
             {
                 cout << "First one " << endl;
                 destination.x =0;
                 destination.y =0;
                 Map::base.available_parking =false;
             }
             else
             {
                 cout << "Alternative " << endl;
                 destination.x = 1;
                 destination.y=0;
             }



            curr_cargo = 0;
        }
    }

}


void  R_Analyzer::setVehInfoString()
{
    Sim::text4.setString(  std::string("      Position Info") + "\n" + "\n"
                         +"Cargo gathered: " + Sim::toString(times_fulled*500 +curr_cargo, 5) + "\n"
                         +"Blocks moved: " + Sim::toString(blocks_moved,5) + "\n"
                         +"Times Damaged: " + Sim::toString(times_damaged,3) + "\n"
                         +"Times Repaired: " + Sim::toString(times_repaired,3) + "\n");

}


