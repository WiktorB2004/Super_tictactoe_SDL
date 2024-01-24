#include "../../include/engine.h"
#include "../../include/utils/engine_utils.h"
#include "../../include/gameplay.h"
#include "../../include/sdl_display.h"
#include "../../include/utils/gameplay_utils.h"

void engine()
{
    Game game;
    Sdl_Data *sdl_data;
    initialize_Game(&game);
    init_sdl(&sdl_data);
    sdl_data->game = &game;
    load_media(sdl_data);
    bool quit = 0;
    while (!quit)
    {
        frame_events(sdl_data, &quit);
    }
    close_sdl(sdl_data);
    free_Game(&game);
}