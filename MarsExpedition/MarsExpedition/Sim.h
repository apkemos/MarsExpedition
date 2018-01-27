#pragma once
#include "Stdafx.h"
#include "Map.h"
#include "R_Analyzer.h"
#include "R_Explorer.h"
#include "R_Rescuer.h"
#include "SimObjectManager.h"

class SimObjectManager;
class Map;

class Sim
{
public:
    static void Start();
    static sf::RenderWindow& getWindow();
    const static sf::Event& GetInput();
    const static SimObjectManager& getSimObjectManager();
    const static int SCREEN_WIDTH = 1280;
	const static int SCREEN_HEIGHT = 768;

    static Map map;
    static int level[(SCREEN_WIDTH/64)* (SCREEN_HEIGHT/64)];

    enum SimState { Uninitialized, ShowingSplash, Paused,
					ShowingMenu, Simulating,Finished,Exiting };

	static SimState _simState;
    static int TileSize;
    static int num_of_x_tiles;
    static int num_of_y_tiles;
    static int MAP_WIDTH;
    static int MAP_HEIGHT;
    static void Map_Initialization();
    static bool _isFinished;
    static sf::Text text1;
    static sf::Text text2;
    static sf::Text text3;
    static sf::Text text4;
    static sf::Text text5;    static sf::Text text6;
    static sf::Font font;

  //  static std::string string;
    template <typename T> static std::string toString(T,int);
private:

	static bool IsExiting();
	static void SimLoop();
    static bool HandleClickEvent(sf::Event &event);
    static std::pair < bool, Vehicle*> HandleVehClickEvent(sf::Event &event);
    static void HandlePausedEvent();
	static void ShowSplashScreen();
	static void ShowMenu();
    static void setTextParameters(sf::Text &text, sf::Font &font , int x_pos , int y_pos ,int charSize, sf::Color color, sf::Text::Style style);
	static sf::RenderWindow _mainWindow;
    static void DrawAndDisplay();
    static void setBaseString();
	static SimObjectManager _simObjectManager;
	static void SwitchVehState(sf::Event& currentEvent,int mouse_x_pos , int mouse_y_pos);


};


