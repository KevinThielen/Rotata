#ifndef GAME_DATA_H
#define GAME_DATA_H

namespace Keys
{
}

namespace Textures
{
    const std::string background = "background"; 

    //Game
    const std::string overlay = "overlay_polished_R"; 
    const std::string overlayR = "overlay_polished"; 
    const std::string cell = "cell"; 
    const std::string rotator = "rotator"; 
    const std::string gameOver = "gameOver"; 

    
    //Menu
    const std::string levelDescription = "levelDescription"; 
    const std::string lock= "lock"; 
    const std::string checkMark = "checkMark"; 
    const std::string menuWidget = "menuWidget";
    const std::string levelSelect = "levelSelect";
    const std::string menuButton = "menuButton";
    
    
    //GUI
    const std::string leftSlider = "leftSlider";
    const std::string middleSlider = "middleSlider";
    const std::string rightSlider = "rightSlider";
    const std::string sliderCursor = "sliderCursor";
    const std::string guiCheckBox= "guiCheckBox";
    const std::string guiCheckMark = "guiCheckMark";   
    const std::string comboBox = "comboBox";
    const std::string comboBoxElement = "comboBoxElement";
    
    
}

namespace Animations
{
}

namespace Audio
{
    const std::string menuHover = "menuHover";
    const std::string menuSelect = "menuSelect";
    const std::string rotationEnd = "rotationEnd";
    const std::string rotatorClick = "rotatorClick";
    const std::string rotation = "rotation";
    const std::string finished = "finished";  
    const std::string bgm = "bgm";  
}

namespace Fonts
{ 
    const std::string font = "font";
    const std::string title86 = "subtitle";
    const std::string title118 = "gameTitle";
    const std::string subTitle = "subtitle";
    const std::string smallFont28 = "smallFont28";
    const std::string smallFont38 = "smallFont38";
    const std::string buttonFont = "buttonFont";
    const std::string optionsFont = "optionsFont";
}
#endif