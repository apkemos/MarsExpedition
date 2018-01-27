#pragma once
#include "Stdafx.h"
#include "VisibleSimObject.h"

// #include "Map.h" //if i include this i get an error.. WHY?


class Vehicle: public VisibleSimObject {
public:
    Vehicle();

    sf::Vector2i destination;
    int times_damaged;
    int id;
    float _velocity;
    bool damage_state;
    float _accesability;
    int blocks_moved;
    int sprite_x_pos;
    int sprite_y_pos;
    int times_repaired;
    std::string orig_filename;
    enum VehState {Stopped,Moving,Operating,AtBase,Damaged,Destroyed};
    sf::Clock clock;
	 VehState _vehState;

    void update(float elapsedTime);
    float timeElapsed;
    virtual void move(float elapsedTime ,sf::Vector2i destination);
    virtual void operate();

    bool checkDamage();
    void switchState();
    virtual void setVehInfoString();
};



