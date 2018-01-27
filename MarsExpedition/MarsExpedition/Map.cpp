#include "Map.h"
#include "Stdafx.h"
#include "SimObjectManager.h"




Base Map::base;
Map::Map(){}

Map::Map(int num_of_Analyzers, int num_of_Explorers, int num_of_Rescuers) {
      this->num_of_Analyzers = num_of_Analyzers;
      this->num_of_Explorers = num_of_Explorers;
      this->num_of_Rescuers = num_of_Rescuers;

      total_veh = num_of_Analyzers + num_of_Explorers + num_of_Rescuers;
      total_flags=0;
      total_damages = 0;

} //Why cant it be declared like :veh_count(2) ??


//Map::
using namespace std;


    bool Map::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {

        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i + j * width];
             //   cout << (tileNumber) << endl;
                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }


    void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
       // cout << m_vertices[1].position.x << endl;;
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

void Map::map_info_init() {
//map_info will make a a compiler error when is static? why?
    srand(time(NULL));
    for (int i=0; i<16; i++)
        for (int j=0; j<12; j++)
            {
               for (int k=0; k<3; k++)
               {
                   map_conciseness[i+ j*16][k] = rand()%1001/10.0; //float number between 0-100
                   map_total_conciseness[k] += map_conciseness[i+j*16][k];
               }


                map_access_danger[i+ j*16] = rand()%10/10.0; //Access Danger
                map_avg_vent += map_access_danger[i + j*16];

                map_mining_state[i+ j*16] = false;
                Sim::map.map_flag_state[i+ j*16] = false; // Flag state;

                destination_tracker[i+ j*16] = false;

                destroyed_veh_pos[i][j] = false;
                destroyed_veh[i][j] = -1;


            }
            map_avg_vent /= (Sim::num_of_x_tiles * Sim::num_of_y_tiles )  -2;

            map_access_danger[0] = 0;
            map_access_danger[1] = 0;

            destination_tracker[0] = true;
            destination_tracker[1] = true;

            for (int k=0; k<3; k++)
               {
                   map_conciseness[0][k] = 0;
                   map_conciseness[1][k] = 0;
               }

                //  Map::showMapInfo();


}

void Map::vehicle_positions_init(int veh_num) {
 srand(time(NULL));
 for (int i=0; i<veh_num; i++) {
        Vehicle* veh = static_cast <Vehicle*> (Sim::getSimObjectManager().Get(i) );
        int xrand= rand()%16;
        int yrand= rand()%12;
   //     int xOffSet  = veh->GetSprite().getLocalBounds().width;
    //    int yOffSet = veh->GetSprite().getLocalBounds().height;
      veh->GetSprite().setPosition(xrand*Sim::TileSize + Sim::TileSize/2  ,yrand*Sim::TileSize + Sim::TileSize/2); //Must also do the destinatio_tracker true for initialization

      veh->sprite_x_pos =  static_cast<int>(veh->GetSprite().getPosition().x);
      veh->sprite_y_pos = static_cast<int>(veh->GetSprite().getPosition().y);
  //  cout <<"The starting coords are.." <<endl << xrand<<"  " << yrand << endl;
   //  cout <<"The starting bounds are.." <<endl << veh->sprite_x_pos <<"  " << veh->sprite_y_pos << endl;
 }
}


sf::Vector2i Map::find_Destination(){
    int xrand;
    int yrand;

    xrand= rand()%Sim::num_of_x_tiles;
    yrand= rand()%Sim::num_of_y_tiles;

    srand(time(NULL)-xrand);
    sf::Vector2i destination;



   // cout << xrand << " " << yrand <<endl;
    while( (xrand ==0 && yrand == 0) || (xrand ==1 && yrand ==0) || Sim::map.destination_tracker[ xrand + yrand*16] == true
           || Sim::map.map_flag_state[ xrand + yrand*16] == true || Sim::map.map_mining_state[ xrand + yrand*16] == true  )
    {
        cout << "KOLISE " << endl;
        xrand= rand()%16;
        yrand= rand()%12;
    }
    Sim::map.destination_tracker[ xrand + yrand*16] = true;

    destination.x = xrand;
    destination.y = yrand;


 // cout<< "Destination:  " << destination.x << "  "<<destination.y << endl;

    return destination;
}






 void Map::showMapInfo()
{

for (int j=0; j<12; j++)
        for (int i=0; i<16; i++)
           // for (int k=0; k<3; k++) cout<< map_conciseness[j+ i*16][k] <<endl; */
           {
            // cout <<i <<endl;
             if ( map_mining_state[i+j*16] == false)
             cout <<    ". ";
             else cout << "K " ;

             if ( i%15 == 0 && i!=0  )
                   // cout << true << endl;
                    cout << endl;

           }
    cout <<endl;

}
