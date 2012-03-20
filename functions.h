#ifndef FUNCTIONS_H
#define FUNCTIONS_H

namespace wood_cube {
const short matrix[4][3][3] = {0};
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
void add_planch(const short position, const planch item, box out_matrix);

void show_planch(const planch item);
void show_box(const box matrix);
bool start(successfull result[ITEMS], box current_matrix);

bool check_box(const box matrix);
void show_result(const successfull result[ITEMS]);

bool check_result(const successfull result[ITEMS]);
bool in_result(const short id, const successfull result[ITEMS]);
}
#endif // FUNCTIONS_H
