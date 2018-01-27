#include "Stdafx.h"
#include "R_Rescuer.h"
#include "Map.h"
#include "Stdafx.h"
#include "Sim.h"
#include "R_Rescuer.h"
#include "Vehicle.h"



using namespace std;


R_Rescuer::R_Rescuer(int identification)
    {
        orig_filename = "images/rescuer.png";
        id = identification;
        times_saved = 0;
        _velocity=200;
        Load("images/rescuer.png");
        assert(IsLoaded());
        GetSprite().setOrigin( GetSprite().getLocalBounds().width/2, GetSprite().getLocalBounds().height/ 2);

    }


void R_Rescuer::operate()
{
    sf::Clock clock;
    float time = clock.restart().asSeconds();
    timeElapsed += time;


    if (timeElapsed >=0.02 )
    {
        //cout << "HAHAH" <<endl;
        timeElapsed=0;
        Vehicle* veh;
            if ( veh_pos.x!=15 && Sim::map.destroyed_veh_pos[veh_pos.x+1][veh_pos.y]==true  )
            {
                veh = static_cast<Vehicle*>( Sim::getSimObjectManager().Get( Sim::map.destroyed_veh[veh_pos.x +1][veh_pos.y] )) ;
                if (veh->_vehState == Damaged )
                {
                 veh->Load(veh->orig_filename);
                 veh->_vehState = Moving;
                 times_saved++;
                 veh->times_repaired++;
                 cout << "MILISAME" <<endl;
                }

            }

         if ( veh_pos.x!=0 && Sim::map.destroyed_veh_pos[veh_pos.x-1][veh_pos.y]==true  )
            {
             veh = static_cast<Vehicle*>(Sim::getSimObjectManager().Get(Sim::map.destroyed_veh[veh_pos.x +-1][veh_pos.y] ) );
             if (veh->_vehState == Damaged )
                {
                veh->Load(veh->orig_filename);
                veh->_vehState = Moving;
                times_saved++;
                veh->damage_state = false;
                veh->times_repaired++;
                cout << "MILISAME" <<endl;
                }
            }
         if (  veh_pos.y!=11 && Sim::map.destroyed_veh_pos[veh_pos.x][veh_pos.y +1]==true )
        {
             veh = static_cast<Vehicle*>(Sim::getSimObjectManager().Get(Sim::map.destroyed_veh[veh_pos.x +-1][veh_pos.y] ) );
             if (veh->_vehState == Damaged )
                {
                veh->Load(veh->orig_filename);
                veh->_vehState = Moving;
                times_saved++;
                veh->damage_state = false;
                veh->times_repaired++;
                cout << "MILISAME" <<endl;
             }
        }
        if ( veh_pos.y!=0 && Sim::map.destroyed_veh_pos[veh_pos.x][veh_pos.y -1]==true  )
        {
            veh = static_cast<Vehicle*>( Sim::getSimObjectManager().Get(Sim::map.destroyed_veh[veh_pos.x][veh_pos.y-1] ) );
             if (veh->_vehState == Damaged )
                {
                veh->Load(veh->orig_filename);
                veh->_vehState = Moving;
                times_saved++;
                veh->damage_state = false;
                veh->times_repaired++;
                cout << "MILISAME" <<endl;
                }
        }
        Sim::map.destination_tracker[veh_pos.x + veh_pos.y*16] = false;
        destination = Map::find_Destination();
        _vehState = Moving;
    }

}

void  R_Rescuer::setVehInfoString()
{
    Sim::text4.setString(  std::string("      Position Info") + "\n" + "\n"
                         +"Times Fixed A Vehicle: " + Sim::toString(times_saved,5) + "\n"
                         +"Blocks moved: " + Sim::toString(blocks_moved,5) + "\n"
                         +"Times Damaged: " + Sim::toString(times_damaged,3) + "\n"
                         +"Times Repaired: " + Sim::toString(times_repaired,3) + "\n");

}




