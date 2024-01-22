#include "unity.h"
#include "include/gameplay_test.h"

// Define setUp and tearDown functions
void setUp(void)
{
    // setup code
}

void tearDown(void)
{
    // teardown code
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_initialize_Board);
    RUN_TEST(test_initialize_Game);
    RUN_TEST(test_free_Game);
    RUN_TEST(test_check_board_horizontally);
    RUN_TEST(test_check_board_vertically);
    RUN_TEST(test_check_board_diagonally);
    RUN_TEST(test_modify_board);
    RUN_TEST(test_check_board);
    // RUN_TEST(test_check_game); - need to implement draw checking logic
    RUN_TEST(test_gameplay);

    return UNITY_END();
}