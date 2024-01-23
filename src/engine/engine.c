#include "../../include/engine.h"
#include "../../include/utils/engine_utils.h"
#include "../../include/gameplay.h"
#include "../../include/sdl_display.h"
#include "../../include/utils/gameplay_utils.h"

void engine()
{
    Game game;
    Sdl_Data *sdl_data;
    init_sdl(&sdl_data);
    load_media(sdl_data);
    bool quit = 0;
    while(!quit)
    {
        frame_events(sdl_data, &quit);
    }
    close_sdl(sdl_data);
    //TODO sync these functions with input from SDL GUI
    //initialize_Game(&game, 3);
    //game.status = IN_PROGRESS;
    //gameplay(&game);
    free_Game(&game);
}