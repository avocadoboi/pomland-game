#pragma once
#include <string>

namespace resource_paths
{

namespace json
{

inline const std::string 
    llamabay_house_aon_guestroom = "room data files/llamabay_house_aon_guestroom.json",
    llamabay_house_aon_livingroom = "room data files/llamabay_house_aon_livingroom.json",
    llamabay_house_aon_hallway = "room data files/llamabay_house_aon_hallway.json",
    llamabay_house_aon_kitchen = "room data files/llamabay_house_aon_kitchen.json",
    llamabay_house_aon_downstairs = "room data files/llamabay_house_aon_downstairs.json",
    llamabay_outside_0 = "room data files/llamabay_outside_0.json";

}

namespace image
{

inline const std::string
    icon = "icon.png",
    sprites = "sprites/sprites.png",
    tileset = "sprites/tileset.png";

}

namespace font
{

inline const std::string main = "chary.ttf";

}

namespace sound
{

inline const std::string 
    voice_aon = "sfx/voice_aon.wav",
    voice_narrator = "sfx/voice_narrator.wav",
    write = "sfx/write.wav";

}

namespace music
{

inline const std::string
    start_menu = "music/start menu.ogg",
    goodbye = "music/goodbye.ogg",
    beach_background_sound = "music/beach background sound.ogg",
    aon = "music/aon.ogg",
    llama_bay = "music/llama bay.ogg";

}

}
