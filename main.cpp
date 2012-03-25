/*
 * File:   main.cpp
 * Author: almazko
 *
 * Created on March 8, 2012, 2:00 PM
 */

#include <iostream>
#include <string.h>

#include <functions.h>
#include <tests.h>

using namespace std;
using namespace wood_cube;

extern long long INDEX;

int main(int argc, char *argv[])
{
    if (argc > 1) {
        all_tests();
        return 0;
    }

    box working_matrix;
    successfull result[ITEMS] = {};

    memcpy(working_matrix, matrix, MATRIX_SIZE);
    start(result, working_matrix);

    return 0;
}

