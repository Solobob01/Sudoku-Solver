int numar_sigur(int **sudoku, int linie, int coloana, int numar)
{
    int i, j;
    //checker pt linie
    for (j = 0; j < 9; j++)
    {
        if (sudoku[linie][j] == numar)
        {
            return 0;
        }
    }

    //checker pt coloana
    for (i = 0; i < 9; i++)
    {
        if (sudoku[i][coloana] == numar)
            return 0;
    }
    //checker pt patrat
    int start_linie = linie - linie % 3;
    int start_coloana = coloana - coloana % 3;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (sudoku[start_linie + i][start_coloana + j] == numar)
                return 0;
        }
    }
    return 1;
}

int solveSuduko(int **sudoku, int linie, int coloana)
{
    int k;
    //daca s-a ajuns la sfarsit atunci returneaza 1
    if (linie == 8 && coloana == 9)
    {
        return 1;
    }

    //daca s-a ajuns la capatul liniei atunci trece pe o linie noua la inceput
    if (coloana == 9)
    {
        linie++;
        coloana = 0;
    }
    //daca este un numar pe patratica atunci el incerca sa rezolve de la urmatoarea patratica
    if (sudoku[linie][coloana] > 0)
    {
        return solveSuduko(sudoku, linie, coloana + 1);
    }

    //verifica daca se poate pune un numar in patratica goala
    for (k = 1; k < 10; k++)
    {
        if (numar_sigur(sudoku, linie, coloana, k) == 1)
        {
            //daca da atunci acesta trece acel numar in patratica
            sudoku[linie][coloana] = k;
            //daca tot sudokul este rezolvat sau s-a ajuns la sfarsit returneaza 1
            if (solveSuduko(sudoku, linie, coloana + 1) == 1)
            {
                return 1;
            }
        }
        sudoku[linie][coloana] = 0;
    }
    return 0;
}