#include "Vehicle.h"
#include "Stdafx.h"
#include "Map.h"


using namespace std;

Vehicle::Vehicle() : times_repaired(0)
 {
    _vehState = Stopped;
    blocks_moved=0;
    destination = Map::find_Destination();
    damage_state = false;
    //srand(destination.x); //Must only seed once
    _accesability = 0.98;//rand()%11/10.0;
    timeElapsed = 0;
    times_damaged=0;
    cout << "Accesability" << _accesability << endl;
 }

void Vehicle::move(float elapsedTime, sf::Vector2i destination ) {

         static long int i=0;
         static long int c=0;

         veh_pos.x = sprite_x_pos / 64;
         veh_pos.y = sprite_y_pos / 64;
         bool x_compl= false;
         bool y_compl= false;


         int dir = 0;
         float y_move=0;
         float x_move= _velocity*elapsedTime;

        if ( sprite_x_pos < destination.x*64 + 32){ dir=1;}
        else dir = -1;


        if (  sprite_x_pos == destination.x*64 + 32)
            {

                x_move =0;
                y_move= elapsedTime*_velocity;
                x_compl= true;
            }
        if ( x_compl == true ) {
            if ( sprite_y_pos < destination.y*64+ 32 )      dir =1;
            else if (sprite_y_pos > destination.y*64+ 32 ) dir = -1;
            else y_compl=true;
        }
        Sim::map.position_tracker[veh_pos.x + veh_pos.y *16] = id;
        i++;
    //    c++;
       GetSprite().move(x_move*dir, y_move*dir);

        if ( y_move ==0 && sprite_y_pos!= veh_pos.y*64 +32 )  { sprite_y_pos = veh_pos.y*64 +32;} //Fixed glitch that made sprite_y_pos take +1 after calling operating()
        if ( x_move ==0 && sprite_x_pos!= veh_pos.x*64 +42 ) {sprite_x_pos = veh_pos.x*64 +32;}
        // std::cout << "Sprite pos x  " << sprite_x_pos << "   " << "Sprite pos y  " << sprite_y_pos << std::endl;
         //   std::cout << "Veh pos x  " << veh_pos.x*64 +32 << "   " << "Veh pos y  " << veh_pos.y*64 +32 << std::endl;
      //  if (sprite_y_pos == veh_pos.y*64 +32 ) {i++; cout<< "True in y " << i<< endl; }
   //     else i=0;
     //  cout<< "Fag " << i<< endl;

        if ( (sprite_x_pos == veh_pos.x*64 + 32 )&& (sprite_y_pos == veh_pos.y*64 + 32  ) && i>400 ) //Benei polles fores epeidh h metavolh tou sprite_x_pos einai polu mikri
                        {
                            i=0;
                            blocks_moved++;

           //                cout<< "Time that showed the pos " << blocks_moved<< endl;

                        if ( checkDamage() )
                            {
                               // cout<< "STOP" << endl;

                            Load("images/ball_destroyed.png");
                            damage_state = true;
                            times_damaged++;
                            Sim::map.total_damages++;
                            _vehState=Damaged;
                            Sim::map.destroyed_veh_pos[veh_pos.x][veh_pos.y] = true;
                            Sim::map.destroyed_veh[veh_pos.x][veh_pos.y] = id;

                            return;

                            }
                        }
        sprite_x_pos =  static_cast<int>(GetSprite().getPosition().x);
        sprite_y_pos = static_cast<int>(GetSprite().getPosition().y);

    //    if ( c == 30000){ c=0; Sim::map.showMapInfo(); }
        //cout << "den paizei na paei edw" << endl;



    if ( x_compl && y_compl ) {
        i=0;
         _vehState = Operating;
         sprite_x_pos = veh_pos.x*64 +32;
         sprite_y_pos = veh_pos.y*64 +32;
        if ( (destination .x == 0 && destination.y == 0) || (destination .x == 1 && destination.y == 0) )
            _vehState = AtBase;
    }


   // delete &destination;
}

void Vehicle::operate(){}

void Vehicle::update(float elapsedTime) {

switch ( _vehState )
    {

        case Stopped:
            {

            sf::Clock clock;
            float time = clock.restart().asSeconds();


              timeElapsed += time;
           // cout << timeElapsed << endl;
                if (timeElapsed >= 0.01)
                {
                    timeElapsed = 0;
                    _vehState = Moving;
                    return;
                }
           // cout<<i << endl;
         //    std::cout << "Sprite pos x  " << sprite_x_pos << "   " << "Sprite pos y  " << sprite_y_pos << std::endl;
//            std::cout << "Veh pos x  " << veh_pos.x*64 +32 << "   " << "Veh pos y  " << veh_pos.y*64 +32 << std::endl;

            break;
            }
        case Moving:
            {
                move( elapsedTime, destination );
                break;
            }
        case Operating:
            {
                operate();
                break;
            }
        case AtBase:
            {
                 clock.restart().asSeconds();
                float deltaTime = clock.restart().asSeconds();

                timeElapsed+= deltaTime;
              //  cout << "Time Delta " << timeElapsed << endl;
                if (timeElapsed > 0.02)
                {
                cout << "At Base" <<endl;
   //             cout << "I am quite sure it's not " <<  static_cast<R_Analyzer*>(this)->Palladium_cargo <<endl;
                Map::base.elem_value[0] += static_cast<R_Analyzer*>(this)->elements[0];
                Map::base.elem_value[1] += static_cast<R_Analyzer*>(this)->elements[1];
                Map::base.elem_value[2] += static_cast<R_Analyzer*>(this)->elements[2];

                static_cast<R_Analyzer*>(this)->elements[0] = 0;
                static_cast<R_Analyzer*>(this)->elements[1] = 0;
                static_cast<R_Analyzer*>(this)->elements[2] = 0;

                int all_gathered=0;
                for (int k=0; k<3; k++)
                {
                    if (Map::base.elem_value[k] >= Map::base.elem_max_value[k])
                    {
                        Map::base.isMax[k] = 0;
                        all_gathered++;
                    }
                }
         //       Map::base.showResources();
                destination = Map::find_Destination();
                _vehState = Moving;
                if ( all_gathered == 3  )
                {
                    cout << Sim::map.base.Base_cap << endl;
                    Sim::_isFinished = true;
                    Sim::_simState = Sim::Finished ;
                }
                Map::base.available_parking = true;

                    _vehState = Moving;
                    timeElapsed =0;
                }
                break;
            }

        case Damaged:
            {

                clock.restart().asSeconds();
                float deltaTime = clock.restart().asSeconds();

                timeElapsed+= deltaTime;
            //    cout << "Time Delta " << timeElapsed << endl;
                if (timeElapsed > 0.01)
                {
                    Sim::map.total_veh_destroyed++;
                    _vehState = Destroyed;
                    timeElapsed =0;
                }
                break;
            }
         case Destroyed:
            {

                if (Sim::map.total_veh_destroyed == Sim::map.total_veh)
                {
                    Sim::_simState = Sim::Finished;
                }
                sf::Rect<int> r1(0,0,0,0);
                GetSprite().setTextureRect( r1 );
                break;
            }


         }

    }



bool Vehicle::checkDamage()
        {
            float damage_propability = Sim::map.map_access_danger[veh_pos.x + veh_pos.y*16]*(1-_accesability);
            float event = rand()%101/100.0;
         //    cout << "Damage Propabilty" << damage_propability << endl;
     //       cout << "Event Propabilty" << event << endl;

            if ( event < damage_propability )
            {
                return true;
            }
            else
            {
                return false;
            }
        }

void Vehicle::switchState()
{
    if (_vehState == Damaged)
        {
            Load(orig_filename);
            _vehState = Moving;
        }
    else
        {
            Load("images/ball_destroyed.png");
            std::cout<< "ALAXE" <<std::endl;
            _vehState = Damaged;
    //         sprite_x_pos = veh_pos.x*64 +32;
     //        sprite_y_pos = veh_pos.y*64 +32;
             GetSprite().setPosition(sprite_x_pos, sprite_y_pos);
        }


}


void Vehicle::setVehInfoString() { }
