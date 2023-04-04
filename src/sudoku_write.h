
#include "./number_write.h"

//aceasta functie scrie numarul primit ca input in patratica respectiva
void sudoku_write(bmp_pixel **patrat_sudoku, int numar)
{
    int i, j, k;

    //numar_1
    if (numar == 1)
    {
        for (i = 0; i < 7; i++)
        {
            k = 0;
            for (j = 0; j < 7; j++)
            {
                patrat_sudoku[i][j].red = number_1_w[i][k];
                patrat_sudoku[i][j].green = number_1_w[i][k + 1];
                patrat_sudoku[i][j].blue = number_1_w[i][k + 2];
                k += 3;
            }
        }
    }

    //numar_2
    if (numar == 2)
    {
        for (i = 0; i < 7; i++)
        {
            k = 0;
            for (j = 0; j < 7; j++)
            {
                patrat_sudoku[i][j].red = number_2_w[i][k];
                patrat_sudoku[i][j].green = number_2_w[i][k + 1];
                patrat_sudoku[i][j].blue = number_2_w[i][k + 2];
                k += 3;
            }
        }
    }

    //numar_3
    if (numar == 3)
    {
        for (i = 0; i < 7; i++)
        {
            k = 0;
            for (j = 0; j < 7; j++)
            {
                patrat_sudoku[i][j].red = number_3_w[i][k];
                patrat_sudoku[i][j].green = number_3_w[i][k + 1];
                patrat_sudoku[i][j].blue = number_3_w[i][k + 2];
                k += 3;
            }
        }
    }

    //numar_4
    if (numar == 4)
    {
        for (i = 0; i < 7; i++)
        {
            k = 0;
            for (j = 0; j < 7; j++)
            {
                patrat_sudoku[i][j].red = number_4_w[i][k];
                patrat_sudoku[i][j].green = number_4_w[i][k + 1];
                patrat_sudoku[i][j].blue = number_4_w[i][k + 2];
                k += 3;
            }
        }
    }

    //numar_5
    if (numar == 5)
    {
        for (i = 0; i < 7; i++)
        {
            k = 0;
            for (j = 0; j < 7; j++)
            {
                patrat_sudoku[i][j].red = number_5_w[i][k];
                patrat_sudoku[i][j].green = number_5_w[i][k + 1];
                patrat_sudoku[i][j].blue = number_5_w[i][k + 2];
                k += 3;
            }
        }
    }

    //numar_6
    if (numar == 6)
    {
        for (i = 0; i < 7; i++)
        {
            k = 0;
            for (j = 0; j < 7; j++)
            {
                patrat_sudoku[i][j].red = number_6_w[i][k];
                patrat_sudoku[i][j].green = number_6_w[i][k + 1];
                patrat_sudoku[i][j].blue = number_6_w[i][k + 2];
                k += 3;
            }
        }
    }

    //numar_7
    if (numar == 7)
    {
        for (i = 0; i < 7; i++)
        {
            k = 0;
            for (j = 0; j < 7; j++)
            {
                patrat_sudoku[i][j].red = number_7_w[i][k];
                patrat_sudoku[i][j].green = number_7_w[i][k + 1];
                patrat_sudoku[i][j].blue = number_7_w[i][k + 2];
                k += 3;
            }
        }
    }

    //numar_8
    if (numar == 8)
    {
        for (i = 0; i < 7; i++)
        {
            k = 0;
            for (j = 0; j < 7; j++)
            {
                patrat_sudoku[i][j].red = number_8_w[i][k];
                patrat_sudoku[i][j].green = number_8_w[i][k + 1];
                patrat_sudoku[i][j].blue = number_8_w[i][k + 2];
                k += 3;
            }
        }
    }

    //numar_9
    if (numar == 9)
    {
        for (i = 0; i < 7; i++)
        {
            k = 0;
            for (j = 0; j < 7; j++)
            {
                patrat_sudoku[i][j].red = number_9_w[i][k];
                patrat_sudoku[i][j].green = number_9_w[i][k + 1];
                patrat_sudoku[i][j].blue = number_9_w[i][k + 2];
                k += 3;
            }
        }
    }
    //numar_x
    if (numar == 0)
    {
        for (i = 0; i < 7; i++)
        {
            k = 0;
            for (j = 0; j < 7; j++)
            {
                patrat_sudoku[i][j].red = number_x_w[i][k];
                patrat_sudoku[i][j].green = number_x_w[i][k + 1];
                patrat_sudoku[i][j].blue = number_x_w[i][k + 2];
                k += 3;
            }
        }
    }
}