#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>

#include "tests.h"
#include "functions.h"

using namespace std;

namespace wood_cube {

    void test_turn_upside_down() {
        planch result;
        planch expect = {
            {1, 2, 3},
            {0 | PLANCH_LEVEL, 1| PLANCH_LEVEL, 1 | PLANCH_LEVEL},
            {4, 5, 6}
        };
        planch item = {
            {4, 5, 6},
            {0 | PLANCH_LEVEL, 1| PLANCH_LEVEL, 1 | PLANCH_LEVEL},
            {1, 2, 3}
        };

        turn_upside_down(item, result);

        if (memcmp(expect, result, ITEMS_SIZE)) {
            cout << "Planch don't equals" << endl;
            cout << "Expects:" << endl;
            show_planch(expect);

            cout << "Results:" << endl;
            show_planch(result);
            cout << endl;
        } else {
            cout << '.';
        }

    }

//    planch test_turn_items[][2] = {

//        {
//            {
//                {0, 0, 0},
//                {1 | PLANCH_LEVEL, 1| PLANCH_LEVEL, 0 | PLANCH_LEVEL},
//                {0, 0, 0}
//            },
//            {
//                {0, 0, 0},
//                {0 | PLANCH_LEVEL, 1| PLANCH_LEVEL, 1 | PLANCH_LEVEL},
//                {0, 0, 0}
//            }
//        },
//        {
//            {
//                {0, 0, 0},
//                {1 | PLANCH_LEVEL, 1| PLANCH_LEVEL, 0 | PLANCH_LEVEL},
//                {0, 0, 5}
//            },
//            {
//                {0, 0, 0},
//                {0 | PLANCH_LEVEL, 1| PLANCH_LEVEL, 1 | PLANCH_LEVEL},
//                {0, 0, 8}
//            }
//        }

//    };

    void test_turn(){
        planch result;
        planch expect = {
            {0, 0, 3},
            {0 | PLANCH_LEVEL, 1| PLANCH_LEVEL, 1 | PLANCH_LEVEL},
            {0, 0, 5}
        };
        planch item = {
            {3, 0, 0},
            {1 | PLANCH_LEVEL, 1| PLANCH_LEVEL, 0 | PLANCH_LEVEL},
            {5, 0, 0}
        };

        turn(item, result);

        if (memcmp(expect, result, ITEMS_SIZE)) {
            cout << "Planch don't equals" << endl;
            cout << "Expects:" << endl;
            show_planch(expect);

            cout << "Results:" << endl;
            show_planch(result);
            cout << endl;
        } else {
            cout << '.';
        }


    }

   void test_add_item() {
       planch item = {
           {0, 0, 1},
           {1 | PLANCH_LEVEL, 1| PLANCH_LEVEL, 0 | PLANCH_LEVEL},
           {0, 1, 0}
       };
       box matrix = {0};
       add_planch(1, item, matrix);
       box expect = {
           {{0,0,0}, {0,0,0}, {0,0,0}},
           {{0,0,0}, {0,1,0}, {0,0,0}},
           {{0,0,0}, {0,0,0}, {0,0,0}}
       };
       show_box(expect);
   }
}
