#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>

#include "functions.h"

using namespace std;
namespace wood_cube {

long long INDEX = 0;
int FOUND = 0;

void show_planch(const planch item)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << '\t' << item[i][j];
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

    out[0][1] = item[0][1];
    out[1][1] = item[1][1];
    out[2][1] = item[2][1];

    out[0][2] = item[0][0];
    out[1][2] = item[1][0];
    out[2][2] = item[2][0];
}

void add_planch(short position, const planch item, box out_matrix)
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
        position -= 32;
    }

    if (position & 16) {
        planch temp_item;
        memcpy(temp_item, working_item, ITEMS_SIZE);
        turn_upside_down(working_item, temp_item);
        memcpy(working_item, temp_item, ITEMS_SIZE);
        position -= 16;
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
    short modify_position;
    for (int i = 0; i < ITEMS; i++) {
        if (in_result(i, result)) continue;

    for (short uturn = 0; uturn < 2; uturn++)
       for (short turn = 0; turn < 2; turn++)
            for (short lvl = 0; lvl < 2; lvl++)
                for (int position = 0; position < 6; position++) {
                    memcpy(new_matrix, current_matrix, MATRIX_SIZE);
        //            cout << '\n' << ++INDEX << " Add planch (" << i <<") position: " << position << endl;
                    modify_position = ((position | (lvl * 64)) | (turn * 32)) | (uturn * 16);
                    ++INDEX;
                    add_planch(modify_position, items[i], new_matrix);

                    if (!(INDEX % 1000000)) {
                        cout << INDEX << endl;
                    }

                    if (check_box(new_matrix)) {
                        successfull temp_result[ITEMS];

                        memcpy(temp_result, result, RESULT_SIZE);
                        temp_result[i].ready = true;
                        temp_result[i].position = modify_position;
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
    for (int i = 0; i < ITEMS; i++) {
        if (!result[i].ready) return false;
    }
}

bool in_result(const short id, const successfull result[ITEMS])
{
        for (int i = 0; i < ITEMS; i++) {
            if (result[i].item == id && result[i].ready) return true;
        }
        return false;
}
}
