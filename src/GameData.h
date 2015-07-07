#ifndef GAME_DATA_H
#define GAME_DATA_H
#include "../../Playground/include/GameData.h"


namespace Keys
{
}

namespace Textures
{
    const std::string overlay = "overlay_polished_R.png"; 
    const std::string overlayR = "overlay_polished.png"; 
    const std::string cell = "cell_polished.png"; 
    const std::string background = "Background.png"; 
    const std::string rotator = "rotator_polished.png"; 
    const std::string gameOver = "GameOver.png"; 
    const std::string restart = "RestartButton.png"; 
    const std::string next = "NextLevelButton.png"; 
    const std::string levelSelect = "LevelSelect.png"; 
    const std::string medal = "medal.png"; 
    const std::string levelDescription = "levelDescription.png"; 
    const std::string lock= "lock.png"; 
    const std::string checkMark = "checkMark.png"; 
    
    const std::string menuButton = "MenuButton.png"; 
    const std::string menuWidget = "MenuWidget.png"; 
}

namespace Animations
{
}

namespace Audio
{
    const std::string menuHover = "MenuSelect.wav";
    const std::string menuSelect = "MenuChoice.wav";
    const std::string rotationEnd = "RotatorClick.wav";
    const std::string rotatorClick = "RotationEnd.wav";
    const std::string rotation = "Rotation.wav";
    const std::string finished = "GameFinished.wav";
    
}

namespace Fonts
{
    const std::string font = "font.ttf";
    const std::string title = "Action_Man_Shaded.ttf";
    const std::string subTitle = "SubTitle.ttf";
    const std::string smallFont = "smallFont.ttf";
    const std::string buttonFont = "2font.ttf";
    const std::string optionsFont = "optionsFont.ttf";

}
#endif