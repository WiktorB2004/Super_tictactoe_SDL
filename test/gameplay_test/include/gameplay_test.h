#pragma once
#include "unity.h"
#include "../include/gameplay_test.h"
#include "../../include/utils/gameplay_utils.h"

void setUp(void);
void tearDown(void);

// Test case for initialize_Board function
void test_initialize_Board(void);

// Test case for initialize_Game function
void test_initialize_Game(void);

// Test case for free_Game function
void test_free_Game(void);

// Test case for check_board_horizontally function
void test_check_board_horizontally(void);

// Test case for check_board_vertically function
void test_check_board_vertically(void);

// Test case for check_board_diagonally function
void test_check_board_diagonally(void);

// Test case for modify_board function
void test_modify_board(void);

// Test case for check_board function
void test_check_board(void);

// Test case for check_game function
void test_check_game(void);

// Test case for gameplay function - integration test
void test_gameplay(void);