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

    cout << " --0--  --1--  --2--\n";
    for (int i = 3; i >= 0; i--) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if ( matrix[i][j][k] < 10) {
                    cout << ' ';
                }
                cout << matrix[i][j][k];
            }
            cout << ' ';
        }
        cout << '\n';
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

void add_planch(short position, const planch item, box out_matrix, short level)
{
    switch (position) {
    case 0:
    case 1:
    case 2:
        out_matrix[level + 2][position][0] += item[0][0];
        out_matrix[level + 2][position][1] += item[0][1];
        out_matrix[level + 2][position][2] += item[0][2];

        out_matrix[level + 1][position][0] += item[1][0];
        out_matrix[level + 1][position][1] += item[1][1];
        out_matrix[level + 1][position][2] += item[1][2];

        out_matrix[level][position][0] += item[2][0];
        out_matrix[level][position][1] += item[2][1];
        out_matrix[level][position][2] += item[2][2];

        break;

    case 3:
    case 4:
    case 5:

        out_matrix[level + 2][0][position - 3] += item[0][0];
        out_matrix[level + 2][1][position - 3] += item[0][1];
        out_matrix[level + 2][2][position - 3] += item[0][2];

        out_matrix[level + 1][0][position - 3] += item[1][0];
        out_matrix[level + 1][1][position - 3] += item[1][1];
        out_matrix[level + 1][2][position - 3] += item[1][2];

        out_matrix[level][0][position - 3] += item[2][0];
        out_matrix[level][1][position - 3] += item[2][1];
        out_matrix[level][2][position - 3] += item[2][2];
        break;
    }
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

bool start(successfull result[ITEMS], box current_matrix)
{

    box new_matrix = {};
    planch working_planch, temp_planch;

    for (int i = 0; i < ITEMS; i++) {
        if (in_result(i, result)) continue;


        for (int position = 0; position < 6; position++){
            for (short level = 0; level < 2; level++) {
                for (short uturn = 0; uturn < 2; uturn++) {
                    if (uturn) {
                        turn_upside_down(items[i], working_planch);
                    } else {
                        memcpy(working_planch, items[i], ITEMS_SIZE);
                    }
                    for (short can_turn = 0; can_turn < 2; can_turn++) {
                        if (can_turn) {
                            turn(working_planch, temp_planch);
                            memcpy(working_planch, temp_planch, ITEMS_SIZE);
                        }

                        ++INDEX;
                        memcpy(new_matrix, current_matrix, MATRIX_SIZE);

                        add_planch(position, working_planch, new_matrix, level);

                        if (check_box(new_matrix)) {
                            successfull temp_result[ITEMS];

                            memcpy(temp_result, result, RESULT_SIZE);
                            temp_result[i].ready = true;
                            temp_result[i].position = position;
                            temp_result[i].item = i;
                            temp_result[i].turn = can_turn;
                            temp_result[i].turn_upside_down = uturn;
                            if (check_result(temp_result)) {
                                FOUND++;
                                show_solution(temp_result, new_matrix, FOUND);
                                return true;
                            }

                            start(temp_result, new_matrix);
                        }
                    }
                }
            }
        }
    }


    return false;
}

void show_result(const successfull result[ITEMS])
{
    for (int i = 0; i < ITEMS; i++) {
        if (!result[i].ready) {
            cout << " - error";
        }

        cout << result[i].item << ") position: " << result[i].position << ", turn:" << result[i].turn << ", turn upside down:" << result[i].turn_upside_down << endl;
    }
}

bool check_result(const successfull result[ITEMS])
{
    for (int i = 0; i < ITEMS; i++) {
        if (!result[i].ready) return false;
    }
    return true;
}

bool in_result(const short id, const successfull result[ITEMS])
{
    for (int i = 0; i < ITEMS; i++) {
        if (result[i].item == id && result[i].ready) return true;
    }
    return false;
}

void show_binary(unsigned dec) {
    for (int t = 128; t > 0; t = t/2) {
        if (t == 8) cout << ' ';
        if (dec & t) {
            cout << '1';
        } else {
            cout << '0';
        }
    }
    cout << endl;
}

void show_solution(const successfull result[ITEMS], const box matrix, int found)
{
    cout << "\nFound Solution (" << found << "):\n";
    show_result(result);
    show_box(matrix);
}

}
