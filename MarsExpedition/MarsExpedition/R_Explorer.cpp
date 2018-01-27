#include "Stdafx.h"
#include "R_Explorer.h"
#include "Map.h"




using namespace std;



R_Explorer::R_Explorer(int identification)
    {
        orig_filename = "images/explorer.png";
        id = identification;

        _velocity=500;
        flags=0;

        Load("images/explorer.png");
        assert(IsLoaded());
        GetSprite().setOrigin( GetSprite().getLocalBounds().width/2, GetSprite().getLocalBounds().height/ 2);

    }





void R_Explorer::operate(){
    static int i=0;
    i++;

    sf::Clock clock;
    float time = clock.restart().asSeconds();
    timeElapsed += time;




    if (Sim::map.map_flag_state[veh_pos.x + veh_pos.y*16]==true)
    {
        i=0;
        _vehState = Moving;
         destination = Map::find_Destination();
         Sim::map.destination_tracker[ veh_pos.x+ veh_pos.y*16] = false;
    }
    else
    {
        if (timeElapsed >=0.02 ) //Time the sprite will be idle for operation
        {
            timeElapsed=0;
            if ( Sim::map.map_access_danger[veh_pos.x + veh_pos.y*16] >0.6)
                {
                cout<<"DANGER" << endl;
                flags++;
                Sim::map.total_flags ++;
                Sim::map.map_flag_state[veh_pos.x + veh_pos.y*16]=true;
                sf::Vertex* quad = &Sim::map.m_vertices[(veh_pos.x + veh_pos.y * 16) * 4];

                quad[0].texCoords = sf::Vector2f(2 * 64 ,0 * 64);
                quad[1].texCoords = sf::Vector2f(( 2+ 1) * 64, 0* 64);   //I am just changing the texture of the quad with the tile i want from the spritesheet i dont need to touch its position (it's already been defined)
                quad[2].texCoords = sf::Vector2f((2 + 1) * 64, (0 + 1) *64);
                quad[3].texCoords = sf::Vector2f(2 * 64, (0 + 1) * 64);
                 }
            destination = Map::find_Destination();
            _vehState = Moving;
             Sim::map.destination_tracker[ veh_pos.x+ veh_pos.y*16] = false;                                          //KANONIKA THA ALLAZW TO TILE TOU LEVEL
        }
    }
}


void  R_Explorer::setVehInfoString()
{
    Sim::text4.setString(  std::string("      Position Info") + "\n" + "\n"
                         +"Flags Setted Up: " + Sim::toString(flags,3) + "\n"
                         +"Blocks moved: " + Sim::toString(blocks_moved,5) + "\n"
                         +"Times Damaged: " + Sim::toString(times_damaged,3) + "\n"
                         +"Times Repaired: " + Sim::toString(times_repaired,3) + "\n");

}






