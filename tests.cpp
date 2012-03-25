
#include "tests.h"
#include "functions.h"

using namespace std;

namespace wood_cube {

    void all_tests() {
        test_turn();
        test_turn_upside_down();
        test_add_planch();
        cout << endl;
    }

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
            cout << "Planches aren't equal" << endl;
            cout << "Expects:" << endl;
            show_planch(expect);

            cout << "Results:" << endl;
            show_planch(result);
            cout << endl;
        } else {
            cout << '.';
        }

    }

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
            cout << "Planches aren't equal" << endl;
            cout << "Expects:" << endl;
            show_planch(expect);

            cout << "Results:" << endl;
            show_planch(result);
            cout << endl;
        } else {
            cout << '.';
        }


    }

    void test_add_planch() {
        planch item = {
            {0, 1, 2},
            {3 ,4, 5},
            {6, 7, 8}
        };
        box actual = {};
        add_planch(5, item, actual, 0);
        box expect = {
            {{0,0,6}, {0,0,7}, {0,0,8}},
            {{0,0,3}, {0,0,4}, {0,0,5}},
            {{0,0,0}, {0,0,1}, {0,0,2}},
            {{0,0,0}, {0,0,0}, {0,0,0}}
        };

        if (memcmp(expect, actual, MATRIX_SIZE)) {
            cout << "Boxes aren't equal" << endl;
            cout << "Expects:" << endl;
            show_box(expect);

            cout << "Actual:" << endl;
            show_box(actual);
            cout << endl;
        } else {
            cout << '.';
        }
    }
}
