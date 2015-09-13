#ifndef GAME_DATA_H
#define GAME_DATA_H

namespace Keys
{
}

namespace Textures
{
    const std::string overlay = "overlay_polished_R"; 
    const std::string overlayR = "overlay_polished"; 
    const std::string cell = "cell"; 
    const std::string background = "background"; 
    const std::string rotator = "rotator"; 
    const std::string gameOver = "gameOver"; 
    const std::string restart = "RestartButton"; 
    const std::string next = "NextLevelButton"; 
    const std::string levelSelect = "levelSelect"; 
    const std::string medal = "medal"; 
    const std::string levelDescription = "levelDescription"; 
    const std::string lock= "lock"; 
    const std::string checkMark = "checkMark"; 
    
    const std::string menuButton = "menuButton"; 
    const std::string menuWidget = "menuWidget";
    
    //GUI
    const std::string leftSlider = "Slider_Left.png";
    const std::string middleSlider = "Slider_Middle.png";
    const std::string rightSlider = "Slider_Right.png";
    const std::string sliderCursor = "Slider_Cursor.png";
    
    const std::string guiCheckBox= "GUI_CheckBox.png";
    const std::string guiCheckMark = "GUI_CheckMark.png";   
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
    const std::string font = "font";
    const std::string title86 = "subtitle";
    const std::string title118 = "title";
    const std::string subTitle = "gameTitle";
    const std::string smallFont28 = "smallFont28";
    const std::string smallFont38 = "smallFont38";
    const std::string buttonFont = "buttonFont";
    const std::string optionsFont = "optionsFont";
}
#endif