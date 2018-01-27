#include "Stdafx.h"
#include "Sim.h"
#include "Flag.h"


Flag::Flag() {
    std::cout<< "Flag created" << std::endl;
    Load("images/flag.png");
    assert(IsLoaded());
    GetSprite().setOrigin( GetSprite().getLocalBounds().width/2, GetSprite().getLocalBounds().height/ 2);
    GetSprite().setPosition(veh_pos.x*Sim::TileSize, veh_pos.y*Sim::TileSize);

}


Flag::~Flag() {
}
