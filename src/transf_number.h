#include "./numbers_default.h"
#include "./bmp_header.h"


//aici in functie de input compara cu pixeli numerelor din numbers_default si returneaza numarul respectiv
int transf_number(bmp_pixel **board_number)
{
    int i, number, j, k;

    //number 1
    int kontor = 1;
    for (i = 0; i < 7; i++)
    {
        k = 0;
        for (j = 0; j < 7; j++)
        {
            if ((board_number[i][j].red != number_1[i][k]) || (board_number[i][j].green != number_1[i][k + 1]) || (board_number[i][j].blue != number_1[i][k + 2]))
            {
                kontor = 0;
                break;
            }
            k += 3;
        }
    }
    if (kontor == 1)
    {
        number = 1;
        goto finish;
    }

    //number 2
    kontor = 1;
    for (i = 0; i < 7; i++)
    {
        k = 0;
        for (j = 0; j < 7; j++)
        {
            if ((board_number[i][j].red != number_2[i][k]) || (board_number[i][j].green != number_2[i][k + 1]) || (board_number[i][j].blue != number_2[i][k + 2]))
            {
                kontor = 0;
                break;
            }
            k += 3;
        }
    }
    if (kontor == 1)
    {
        number = 2;
        goto finish;
    }

    //number 3
    kontor = 1;
    for (i = 0; i < 7; i++)
    {
        k = 0;
        for (j = 0; j < 7; j++)
        {
            if (board_number[i][j].red != number_3[i][k] || board_number[i][j].green != number_3[i][k + 1] || board_number[i][j].blue != number_3[i][k + 2])
            {
                kontor = 0;
                break;
            }
            k += 3;
        }
    }
    if (kontor == 1)
    {
        number = 3;
        goto finish;
    }

    //number 4
    kontor = 1;
    for (i = 0; i < 7; i++)
    {
        k = 0;
        for (j = 0; j < 7; j++)
        {
            if (board_number[i][j].red != number_4[i][k] || board_number[i][j].green != number_4[i][k + 1] || board_number[i][j].blue != number_4[i][k + 2])
            {
                kontor = 0;
                break;
            }
            k += 3;
        }
    }
    if (kontor == 1)
    {
        number = 4;
        goto finish;
    }

    //number 5
    kontor = 1;
    for (i = 0; i < 7; i++)
    {
        k = 0;
        for (j = 0; j < 7; j++)
        {
            if (board_number[i][j].red != number_5[i][k] || board_number[i][j].green != number_5[i][k + 1] || board_number[i][j].blue != number_5[i][k + 2])
            {
                kontor = 0;
                break;
            }
            k += 3;
        }
    }
    if (kontor == 1)
    {
        number = 5;
        goto finish;
    }

    //number 6
    kontor = 1;
    for (i = 0; i < 7; i++)
    {
        k = 0;
        for (j = 0; j < 7; j++)
        {
            if (board_number[i][j].red != number_6[i][k] || board_number[i][j].green != number_6[i][k + 1] || board_number[i][j].blue != number_6[i][k + 2])
            {
                kontor = 0;
                break;
            }
            k += 3;
        }
    }
    if (kontor == 1)
    {
        number = 6;
        goto finish;
    }

    //number 7
    kontor = 1;
    for (i = 0; i < 7; i++)
    {
        k = 0;
        for (j = 0; j < 7; j++)
        {
            if (board_number[i][j].red != number_7[i][k] || board_number[i][j].green != number_7[i][k + 1] || board_number[i][j].blue != number_7[i][k + 2])
            {
                kontor = 0;
                break;
            }
            k += 3;
        }
    }
    if (kontor == 1)
    {
        number = 7;
        goto finish;
    }

    //number 8
    kontor = 1;
    for (i = 0; i < 7; i++)
    {
        k = 0;
        for (j = 0; j < 7; j++)
        {
            if (board_number[i][j].red != number_8[i][k] || board_number[i][j].green != number_8[i][k + 1] || board_number[i][j].blue != number_8[i][k + 2])
            {
                kontor = 0;
                break;
            }
            k += 3;
        }
    }
    if (kontor == 1)
    {
        number = 8;
        goto finish;
    }

    //number 9
    kontor = 1;
    for (i = 0; i < 7; i++)
    {
        k = 0;
        for (j = 0; j < 7; j++)
        {
            if (board_number[i][j].red != number_9[i][k] || board_number[i][j].green != number_9[i][k + 1] || board_number[i][j].blue != number_9[i][k + 2])
            {
                kontor = 0;
                break;
            }
            k += 3;
        }
    }
    if (kontor == 1)
    {
        number = 9;
        goto finish;
    }

    //number 0
    kontor = 1;
    for (i = 0; i < 7; i++)
    {
        k = 0;
        for (j = 0; j < 7; j++)
        {
            if (board_number[i][j].red != number_0[i][k] || board_number[i][j].green != number_0[i][k + 1] || board_number[i][j].blue != number_0[i][k + 2])
            {
                kontor = 0;
                break;
            }
            k += 3;
        }
    }
    if (kontor == 1)
    {
        number = 0;
        goto finish;
    }

    number = -1;

finish:
    return number;
}