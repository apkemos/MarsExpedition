#include "Stdafx.h"
#include "Sim.h"
#include "MainMenu.h"
#include "SplashScreen.h"



using namespace std;


Sim::SimState Sim::_simState = Uninitialized;
SimObjectManager Sim::_simObjectManager;
sf::RenderWindow Sim::_mainWindow;
Map Sim::map(4,3,4) ;
int Sim::TileSize;
int Sim::num_of_x_tiles;
int Sim::num_of_y_tiles;
int Sim::MAP_HEIGHT;
int Sim::MAP_WIDTH;
bool Sim::_isFinished = false;
sf::Text Sim::text1; // Position Info
sf::Text Sim::text2; // Total Vehicle Info
sf::Text Sim::text3; // Map Info
sf::Text Sim::text4; // Single Vehicle's Info
sf::Text Sim::text5; // Base's Info
sf::Text Sim::text6; //Finished Message
sf::Font Sim::font;

int Sim::level[(SCREEN_WIDTH/64)*(SCREEN_HEIGHT/64)];
//SimObjectManager Sim::_simObjectManager;

void Sim::Start(void){

    if(_simState != Uninitialized)
		return;

    _mainWindow.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),"Mars Expedition");

    _simState= Sim::ShowingSplash;


    _mainWindow.setKeyRepeatEnabled(false);
    while(!IsExiting())
	{
		SimLoop();
	}

	_mainWindow.close();
}

bool Sim::IsExiting()
{
	if(_simState == Sim::Exiting)
		return true;
	else
		return false;
}


sf::RenderWindow& Sim::getWindow()
{
	return _mainWindow;
}

const sf::Event& Sim::GetInput()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	return currentEvent;
}

const SimObjectManager& Sim::getSimObjectManager()
{
	return _simObjectManager;
}

void Sim::SimLoop() {
    sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);

    static pair<bool,Vehicle*> hit_veh;
    static bool hit_base = false;
    switch(_simState)
	{
		case Sim::ShowingMenu:
			{
				ShowMenu();
				break;
			}
		case Sim::ShowingSplash:
			{
				ShowSplashScreen();
				break;
			}
        case Sim::Paused:
            {
                if(currentEvent.type == sf::Event::KeyPressed)
                    {
                        _simObjectManager.clock.restart();

						if(currentEvent.key.code == sf::Keyboard::Escape) _simState = ShowingMenu;

                        if(currentEvent.key.code == sf::Keyboard::Tab)
                        {
                            cout << "Simulation Resumed" << endl;
                            _simState = Simulating;
                        }
                        sf::Vector2i localPosition = sf::Mouse::getPosition(_mainWindow);
                        int x_pos = localPosition.x / TileSize;
                        int y_pos = localPosition.y / TileSize;
                        if(currentEvent.key.code == sf::Keyboard::Q)
                        {
                             map.total_veh++;
                            _simObjectManager.Add(map.total_veh , new R_Analyzer(map.total_veh) );
                            _simObjectManager.Get(map.total_veh)->GetSprite().setPosition( x_pos*TileSize + TileSize/2 , y_pos*TileSize + TileSize/2);

                        }
                         if(currentEvent.key.code == sf::Keyboard::W)
                        {
                            map.total_veh++;
                            _simObjectManager.Add(map.total_veh , new R_Explorer(map.total_veh) );
                            _simObjectManager.Get(map.total_veh)->GetSprite().setPosition( x_pos*TileSize + TileSize/2 , y_pos*TileSize + TileSize/2);
                            map.total_veh++;
                        }
                         if(currentEvent.key.code == sf::Keyboard::E)
                        {
                            map.total_veh++;
                            _simObjectManager.Add(map.total_veh, new R_Rescuer(map.total_veh) );
                            _simObjectManager.Get(map.total_veh)->GetSprite().setPosition( x_pos*TileSize + TileSize/2 , y_pos*TileSize + TileSize/2);

                        }
                         if(currentEvent.key.code == sf::Keyboard::T)
                         {
                             int tile_pos_x;
                             int tile_pos_y;
                             cout << "Give position coordinates" << endl;
                             cin >> tile_pos_x;
                             cin >> tile_pos_y;
                             float new_map_conciseness[3];
                             cout << "Give new conciseness for the position " <<endl;
                             for (int k=0; k<3; k++)
                             {
                                 cin >> new_map_conciseness[k];
                                 Sim::map.map_conciseness[tile_pos_x + tile_pos_y*num_of_x_tiles][k] = new_map_conciseness[k];
                             }
                         }
                         if(currentEvent.key.code == sf::Keyboard::F)
                         {
                             cout << "Hover the mouse over the vehicle you want to change" << endl;
                             SwitchVehState(currentEvent , localPosition.x , localPosition.y);

                         }

                    }
                else if(currentEvent.type == sf::Event::MouseButtonPressed)
                {
                    hit_veh = HandleVehClickEvent(currentEvent);
                    if (hit_veh.first ==false)
                        hit_base = HandleClickEvent(currentEvent);

                }
                if (hit_base)
                    setBaseString();

                DrawAndDisplay();
                break;
            }
		case Sim::Simulating:
			{


                _simObjectManager.UpdateAll();


             if(currentEvent.type == sf::Event::MouseButtonPressed)
                {
                   hit_veh = HandleVehClickEvent(currentEvent);
                   if (hit_veh.first==false)
                        hit_base = HandleClickEvent(currentEvent);

                }
                else if(currentEvent.type == sf::Event::Closed) _simState = Sim::Exiting;

				else if(currentEvent.type == sf::Event::KeyPressed)
                    {

						if(currentEvent.key.code == sf::Keyboard::Escape) _simState = ShowingMenu;
                        else if(currentEvent.key.code == sf::Keyboard::Tab)
                        {
                            cout << "Simulation Paused" << endl;
                            _simState = Paused;
                        }
                        else if(currentEvent.key.code == sf::Keyboard::F)
                         {
                             sf::Vector2i localPosition = sf::Mouse::getPosition(_mainWindow);
                             cout << "Hover the mouse over the vehicle you want to change" << endl;
                             SwitchVehState(currentEvent , localPosition.x , localPosition.y);

                         }

                    }
                text2.setString(std::string("     Total Vehicles Info") + "\n" + "\n"
                                +"Total Flags : " + toString(map.total_flags,3) + "\n"
                                +"Total Damages: " + toString(map.total_damages,3) + "\n"
                                +"Total Cargo Mined: " + toString(R_Analyzer::total_veh_cargo,5));

                text3.setString(std::string("     Terrain Info") + "\n" + "\n"
                                +"Total Palladium : " + toString(map.map_total_conciseness[0],5) + "\n"
                                +"Total Iridium: " + toString(map.map_total_conciseness[1],5) + "\n"
                                +"Total Platinum: " + toString(map.map_total_conciseness[2],5) + "\n"
                                +"Average Ventourousness: " + toString(map.map_avg_vent,3) );
                if (hit_veh.first == true)
                {
                    hit_veh.second->setVehInfoString();
                }
                else
                {
                    text4.setString("");
                }

                if (hit_base == true)
                {
                    setBaseString();
                }

                DrawAndDisplay();

				break;
			}
        case Finished:
            {
               // cout << "WHY?" << endl;
                if (_isFinished)
                    {
                        text6.setString("Simulation Succesfuly Ended!");
                    }
                else
                    {
                        for(int i=0; i<map.total_veh; i++)
                            {
                                sf::Rect<int> r1(0,0,0,0);
                                _simObjectManager.Get(i)->GetSprite().setTextureRect( r1 );
                            }
                        text6.setString("Simulation Failed!");
                    }
                if(currentEvent.type == sf::Event::MouseButtonPressed)
                {
                    hit_veh = HandleVehClickEvent(currentEvent);
                    if (hit_veh.first ==false)
                        hit_base = HandleClickEvent(currentEvent);

                }
                if (hit_base)
                    setBaseString();

                DrawAndDisplay();
                break;
            }

        }
}

void Sim::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_simState = Sim::ShowingMenu;
}

void Sim::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
		case MainMenu::Exit:
			_simState = Exiting;
			break;
		case MainMenu::Play:
			_simState = Simulating;
			break;
	}
}


template <typename T>
std::string Sim::toString(T value,int n)
{
	std::ostringstream os ;
    os <<std::setprecision(n)<<value;
	//os << value ;
	return os.str() ;
}

bool Sim::HandleClickEvent(sf::Event& currentEvent)
{
            bool hit_base=false;
            if (currentEvent.mouseButton.x < MAP_WIDTH && currentEvent.mouseButton.y < MAP_HEIGHT)
            {
                int tile_pos_x = currentEvent.mouseButton.x / TileSize;
                int tile_pos_y = currentEvent.mouseButton.y / TileSize;
                if (currentEvent.mouseButton.x < TileSize*2 && currentEvent.mouseButton.y < TileSize)
                {
                                    hit_base = true;
                }

                else
                {
                    text1.setColor(sf::Color::Red);
                    text1.setString( std::string("      Position Info( " ) +toString(tile_pos_x,2) + "," + toString(tile_pos_y,3) + " )" + "\n" + "\n" //std::string because comp needs to know that + is between strings and not char pointers
                                    +
                                    +"Palladium: " + toString(map.map_conciseness[ tile_pos_x + tile_pos_y*num_of_x_tiles][0],4) + "\n"
                                    +"Iridium: " + toString(map.map_conciseness[ tile_pos_x + tile_pos_y*num_of_x_tiles][1],4) + "\n"
                                    +"Platinum: " + toString(map.map_conciseness[ tile_pos_x + tile_pos_y*num_of_x_tiles][2],4) + "\n"
                                    +"Access Danger: " + toString(map.map_access_danger[ tile_pos_x + tile_pos_y*num_of_x_tiles], 2 ) );
                }
            }

    return hit_base;


}

pair<bool,Vehicle*> Sim::HandleVehClickEvent(sf::Event& currentEvent)
{
        bool hit = false;
        Vehicle* correct_veh;
        for (int i=0; i<map.total_veh; i++)
        {
            Vehicle *veh = static_cast<Vehicle*>(_simObjectManager.Get(i));
            sf::Rect<float> rect = veh->GetSprite().getGlobalBounds();
            if (rect.contains(currentEvent.mouseButton.x  , currentEvent.mouseButton.y ))
                {
                    hit = true;
                    veh->setVehInfoString();
                    correct_veh = veh;
                }
        }
        pair <bool,Vehicle*>  p(hit,  correct_veh) ;
    return p;
}

void Sim::SwitchVehState(sf::Event& currentEvent,int mouse_x_pos , int mouse_y_pos)
{
    for (int i=0; i<map.total_veh; i++)
        {
            Vehicle *veh = static_cast<Vehicle*>(_simObjectManager.Get(i));
            sf::Rect<float> rect = veh->GetSprite().getGlobalBounds();
            if (rect.contains(mouse_x_pos  , mouse_y_pos ) )
                {
                    veh->switchState();
                    return;
                }
        }
}

void Sim::setTextParameters(sf::Text &text, sf::Font &font , int x_pos , int y_pos ,int charSize, sf::Color color, sf::Text::Style style)
{
    cout<<charSize<<endl;
    text.setFont(font);
    text.setPosition(x_pos, y_pos);
    text.setCharacterSize(charSize);
    text.setColor(color);
    text.setStyle(style);
}

void Sim::Map_Initialization()
{
        font.loadFromFile("fonts/RockoFLF.ttf");

    level[0] = 4;
    level[1] = 4;


    TileSize = 64;
    MAP_WIDTH = 1024;
    MAP_HEIGHT = 768;
    num_of_x_tiles = MAP_WIDTH / TileSize;
    num_of_y_tiles = MAP_HEIGHT / TileSize;

    for( int i=0; i< map.num_of_Analyzers; i++)
        {
            _simObjectManager.Add(i,new R_Analyzer(i));
        }


    for( int i=map.num_of_Analyzers; i< map.num_of_Analyzers + map.num_of_Explorers; i++)
       {
           _simObjectManager.Add(i,new R_Explorer(i));
        }
    for( int i=map.num_of_Analyzers + map.num_of_Explorers; i< map.total_veh; i++)
        {
           _simObjectManager.Add(i,new R_Rescuer(i));
        }




    cout << "Map objects " << map.total_veh << endl;

     if (!map.load("images/spritesheet.png", sf::Vector2u(TileSize, TileSize), level, num_of_x_tiles, num_of_y_tiles)){
            cout<<"Couldnt Load Map"<< endl;
            return;
            }
    map.map_info_init();
    map.vehicle_positions_init(map.total_veh);

   Sim::setTextParameters(text1,font,MAP_WIDTH+5,10,20,sf::Color::Red,sf::Text::Bold);

   Sim::setTextParameters(text2,font,MAP_WIDTH+5,MAP_HEIGHT/2+50 ,15,sf::Color::Cyan,sf::Text::Bold);

   Sim::setTextParameters(text3,font,MAP_WIDTH+5, MAP_HEIGHT/2+210,15,sf::Color::White,sf::Text::Bold);

   Sim::setTextParameters(text4,font,MAP_WIDTH+5, 210,20,sf::Color::Magenta,sf::Text::Bold);

   Sim::setTextParameters(text5,font,MAP_WIDTH+5,10,20,sf::Color::Yellow,sf::Text::Bold);

   Sim::setTextParameters(text6,font,40,MAP_HEIGHT/2 -200,60,sf::Color::Black,sf::Text::Bold);

}

void Sim::DrawAndDisplay()
{
        _mainWindow.clear(sf::Color(0,0,0));
        _mainWindow.draw(map);
        _simObjectManager.DrawAll(_mainWindow);
        _mainWindow.draw(text1);
        _mainWindow.draw(text2);
        _mainWindow.draw(text3);
        _mainWindow.draw(text4);
        _mainWindow.draw(text5);
        _mainWindow.draw(text6);
        _mainWindow.display();
}


void Sim::setBaseString()
{
     text1.setColor(sf::Color::Yellow);
     text1.setString( std::string("      Base Info   ") + "( Max )" + + "\n" + "\n" //std::string because comp needs to know that + is between strings and not char pointers
                    +"Palladium: " + toString(map.base.elem_value[0],5) + "  ( " + toString(map.base.elem_max_value[0],5) + " )"  + "\n"
                    +"Iridium: " + toString(map.base.elem_value[1],5) + "   ( " + toString(map.base.elem_max_value[1],5) + " ) " +"\n"
                    +"Platinum: " + toString(map.base.elem_value[2],5) + "  ( " + toString(map.base.elem_max_value[2],5) + " ) " + "\n");
}
