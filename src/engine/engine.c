#include "../../include/engine.h"
#include "../../include/utils/engine_utils.h"
#include "../../include/gameplay.h"
#include "../../include/utils/gameplay_utils.h"

void engine()
{
    Game game;
    initialize_Game(&game, 3);
    game.status = IN_PROGRESS;
    gameplay(&game);
    free_Game(&game);
}