/*
 * File:   main.cpp
 * Author: almazko
 *
 * Created on March 8, 2012, 2:00 PM
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

const short matrix[4][3][3] = {0};
int INDEX = 0;
int FOUND = 0;
const short PLANCH_LEVEL = 8;
const short BUSY_ITEM = 1;
const short ITEMS = 6;

const short items[ITEMS][3][3] = {
    {
        {0, 0, 1},
        {0 | PLANCH_LEVEL, 0 | PLANCH_LEVEL, 1 | PLANCH_LEVEL},
        {0, 0, 0}
    },
    {
        {0, 1, 0},
        {0 | PLANCH_LEVEL, 1 | PLANCH_LEVEL, 1 | PLANCH_LEVEL},
        {0, 0, 1}
    },
    {
        {0, 1, 0},
        {1 | PLANCH_LEVEL, 1 | PLANCH_LEVEL, 0 | PLANCH_LEVEL},
        {1, 0, 0}
    },
    {
        {1, 0, 0},
        {1 | PLANCH_LEVEL, 0 | PLANCH_LEVEL, 1 | PLANCH_LEVEL},
        {0, 0, 1}
    },
    {
        {0, 1, 0},
        {1 | PLANCH_LEVEL, 1 | PLANCH_LEVEL, 1 | PLANCH_LEVEL},
        {1, 0, 1}
    },
    {
        {1, 1, 0},
        {1 | PLANCH_LEVEL, 1 | PLANCH_LEVEL, 1 | PLANCH_LEVEL},
        {0, 0, 1}
    },

};

struct successfull
{
    bool ready;
    short item;
    short position;

    successfull() : ready(false), item(0), position(0)
    {
    }
};

typedef short planch[3][3];
typedef short box[4][3][3];

const short ALL_ITEMS_SIZE = sizeof (items);
const short ITEMS_SIZE = sizeof (planch);
const short MATRIX_SIZE = sizeof (box);
const short RESULT_SIZE = sizeof (successfull) * 6;

void turn(const planch item, planch out);
void turn_upside_down(const planch item, planch out);
void add_tablet(const short position, const planch item, box out_matrix);

void show_planch(const planch item);
void show_box(const box matrix);
bool start(successfull result[ITEMS], box current_matrix);

bool check_box(const box matrix);
void show_result(const successfull result[ITEMS]);

bool check_result(const successfull result[ITEMS]);
bool in_result(const short id, const successfull result[ITEMS]);

int main()
{
//    short new_item[3][3];
//    short item[3][3];
//
//
//    memcpy(item, items[0], ITEM_SIZE);
//
//    show_tablet_info(item);
//
//    turn_upside_down(item, new_item);
//    memcpy(item, new_item, ITEM_SIZE);
//    cout << endl;
//    show_tablet_info(item);
//
//    turn(item, new_item);
//    memcpy(item, new_item, ITEM_SIZE);
//    cout << endl;
//    show_tablet_info(item);

    show_box(matrix);
    cout << endl;
    box working_matrix;
    successfull result[ITEMS] = {};

    memcpy(working_matrix, matrix, MATRIX_SIZE);
    start(result, working_matrix);

    cout << "\n\nFound: " << FOUND << endl;
    return 0;
}

void show_planch(const planch item)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << item[i][j];
        }
        cout << endl;
    }
}

void show_box(const box matrix)
{
    string info;
    stringstream out;

    for (int i = 3; i >= 0; i--) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if ( matrix[i][j][k] < 10) {
                    cout << ' ';
                }
                cout << matrix[i][j][k];
//                info += out.str();
            }
            cout << " ";
        }
        cout << "\n";
    }

}

void turn_upside_down(const planch item, planch out)
{
    out[0][0] = item[2][0];
    out[0][1] = item[2][1];
    out[0][2] = item[2][2];

    out[1][0] = item[1][0];
    out[1][1] = item[1][1];
    out[1][2] = item[1][2];

    out[2][0] = item[0][0];
    out[2][1] = item[0][1];
    out[2][2] = item[0][2];
}

void turn(const planch item, planch out)
{
    out[0][0] = item[0][2];
    out[1][0] = item[1][2];
    out[2][0] = item[2][2];

    out[0][2] = item[0][0];
    out[1][2] = item[1][0];
    out[2][2] = item[2][0];
}

void add_tablet(short position, const planch item, box out_matrix)
{
    short level = 1;
    planch working_item;
    memcpy(working_item, item, ITEMS_SIZE);


    if (position & 64) {
        level = 2;
        position -= 64;
    }

    if (position & 32) {
        planch temp_item;
        memcpy(temp_item, working_item, ITEMS_SIZE);
        turn(working_item, temp_item);
        memcpy(working_item, temp_item, ITEMS_SIZE);
    }

    if (position & 16) {
        planch temp_item;
        memcpy(temp_item, working_item, ITEMS_SIZE);
        turn_upside_down(working_item, temp_item);
        memcpy(working_item, temp_item, ITEMS_SIZE);
    }


//    show_planch(item);

    switch (position) {
    case 0:
    case 1:
    case 2:
        out_matrix[level + 1][position][0] += working_item[0][0];
        out_matrix[level + 1][position][1] += working_item[0][1];
        out_matrix[level + 1][position][2] += working_item[0][2];

        out_matrix[level][position][0] += working_item[1][0];
        out_matrix[level][position][1] += working_item[1][1];
        out_matrix[level][position][2] += working_item[1][2];

        out_matrix[level - 1][position][0] += working_item[2][0];
        out_matrix[level - 1][position][1] += working_item[2][1];
        out_matrix[level - 1][position][2] += working_item[2][2];

        break;

    case 3:
    case 4:
    case 5:

        out_matrix[level + 1][0][position - 3] += working_item[0][0];
        out_matrix[level + 1][1][position - 3] += working_item[0][1];
        out_matrix[level + 1][2][position - 3] += working_item[0][2];

        out_matrix[level][0][position - 3] += working_item[1][0];
        out_matrix[level][1][position - 3] += working_item[1][1];
        out_matrix[level][2][position - 3] += working_item[1][2];

        out_matrix[level - 1][0][position - 3] += working_item[2][0];
        out_matrix[level - 1][1][position - 3] += working_item[2][1];
        out_matrix[level - 1][2][position - 3] += working_item[2][2];
        break;
    }

//cout << "\nResult box: " << endl;
//show_box(out_matrix);
}

bool check_box(const box matrix)
{
    for (int row = 1; row < 3; row++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (matrix[row][i][j] > BUSY_ITEM + PLANCH_LEVEL) return false;

                if (matrix[row][i][j] < PLANCH_LEVEL && matrix[row][i][j] > BUSY_ITEM) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool start(successfull result[ITEMS_SIZE], box current_matrix)
{
    box new_matrix;
    for (int i = 0; i < ITEMS; i++) {
        if (in_result(i, result)) continue;


        for (short turn = 0; turn < 2; turn++)
            for (short lvl = 0; lvl < 2; lvl++) {
                for (int position = 0; position < 6; position++) {
                    memcpy(new_matrix, current_matrix, MATRIX_SIZE);
        //            cout << '\n' << ++INDEX << " Add planch (" << i <<") position: " << position << endl;
                    add_tablet(position | (lvl * 64), items[i], new_matrix);

                    if (check_box(new_matrix)) {
                        successfull temp_result[ITEMS];

                        memcpy(temp_result, result, RESULT_SIZE);
                        temp_result[i].ready = true;
                        temp_result[i].position = position | (lvl * 64);
                        temp_result[i].item = i;
                        if (check_result(temp_result)) {
                            FOUND++;
                            show_result(temp_result);
                            return true;
                        }

                        start(temp_result, new_matrix);
                    }

                }
            }
    }


    return false;
}

void show_result(const successfull result[ITEMS])
{
    cout << endl;
    for (int i = 0; i < ITEMS; i++) {
        cout << endl << i;
        if (result[i].ready) {
            cout << " - ready";
        } else {
            cout << " - error";
        }

        cout << ", position: " << result[i].position << endl;
    }
}

bool check_result(const successfull result[ITEMS])
{
//    for (int i = 0; i < ITEMS; i++) {
//        if (!result[i].ready) return false;
//    }

    short found = 0;
    for (int i = 0; i < ITEMS; i++) {
        if (result[i].ready) found++;
    }
    return (found > 5) ? true : false;
}

bool in_result(const short id, const successfull result[ITEMS])
{
        for (int i = 0; i < ITEMS; i++) {
            if (result[i].item == id && result[i].ready) return true;
        }
        return false;
}

