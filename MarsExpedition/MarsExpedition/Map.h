#pragma once
#include "Stdafx.h"
#include "Vehicle.h"
#include "SimObjectManager.h"
#include "Sim.h"
#include "Base.h"

class Map : public sf::Drawable, public sf::Transformable
{
public:
    Map();
    Map(int num_of_Analyzers, int num_of_Explorers, int num_of_Rescuers);
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height); //this must be the contructor

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    float map_conciseness[16*12][3];
    float map_total_conciseness[3];
    float map_access_danger[16*12];
    float map_avg_vent;
    bool map_flag_state[16*12];
    bool destination_tracker[16*12];
    bool map_mining_state [16*12];
    int position_tracker[16*12];
    bool destroyed_veh_pos[16][12];
    int destroyed_veh[16][12];
    void map_info_init();
    void vehicle_positions_init(int veh_number);
    int total_veh_destroyed;
    static Base base;

    int num_of_Analyzers;
    int num_of_Explorers;
    int num_of_Rescuers;
    int total_veh;
    int total_flags;
    int total_damages;
    void showMapInfo();

    static sf::Vector2i find_Destination();


private:

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const ;


};



