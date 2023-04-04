int sudoku_checker(int **sudoku)
{
    int i, j, l, output = 1;

    //verificare pe linii
    for (i = 0; i < 9; i++)
        for (j = 0; j < 8; j++)
        {
            if (sudoku[i][j] == 0)
            {
                output = 0;
                goto finish;
            }
            if (sudoku[i][j] == -1)
            {
                output = 2;
            }
            for (l = j + 1; l < 9; l++)
            {
                if (sudoku[i][j] == sudoku[i][l] && sudoku[i][j] != -1)
                {
                    output = 0;
                    goto finish;
                }
            }
        }
    //verifica pe coloane
    for (i = 0; i < 9; i++)
        for (j = 0; j < 8; j++)
        {
            if (sudoku[i][j] == 0)
            {
                output = 0;
                goto finish;
            }
            if (sudoku[i][j] == -1)
            {
                output = 2;
            }
            for (l = j + 1; l < 9; l++)
            {
                if (sudoku[j][i] == sudoku[l][i] && sudoku[i][j] != -1)
                {
                    output = 0;
                    goto finish;
                }
            }
        }
finish:
    return output;
}