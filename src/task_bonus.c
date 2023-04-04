#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void task_bonus(char *argv)
{
    bmp_fileheader File_header;
    bmp_infoheader Info_header;
    int i, j;
    unsigned char pixel_ped = 0;

    //deschidem fisierul primit ca input

    FILE *board_bmp_task_bonus = fopen(argv, "rb");
    if (board_bmp_task_bonus == NULL)
    {
        printf("Nu exista fisierul!\n");
        exit(1);
    }

    //citim datele default pentru bmp primite din fisierul input
    fread(&File_header, sizeof(bmp_fileheader), 1, board_bmp_task_bonus);
    fread(&Info_header, sizeof(bmp_infoheader), 1, board_bmp_task_bonus);

    //alocam dinamic nume_output si il si creez pe baza inputului
    char *nume_output;
    nume_output = (char *)calloc(100, sizeof(char));
    if (nume_output == NULL)
    {
        printf("Eroare alocare nume_output!\n");
        exit(1);
    }
    strcpy(nume_output, "./output_bonus_board");

    //alocam dinamic aux_bmp
    char *aux_bmp;
    aux_bmp = (char *)calloc(60, sizeof(char));
    if (aux_bmp == NULL)
    {
        printf("Eroare alocare aux_bmp!\n");
        free(nume_output);
        exit(1);
    }
    strcpy(aux_bmp, ".bmp");
    char *number_board = strstr(argv, "board");

    strncat(nume_output, &number_board[5], 1);
    strncat(nume_output, &number_board[6], 1);
    strcat(nume_output, aux_bmp);

    printf("%s\n", nume_output);

    //creez fisierul de output
    FILE *output = fopen(nume_output, "wb");
    if (output == NULL)
    {
        printf("alocare output eroare!\n");
        exit(1);
    }

    //scriem datele default primite din fisierul din input
    fwrite(&File_header, sizeof(File_header), 1, output);
    fwrite(&Info_header, sizeof(Info_header), 1, output);

    free(nume_output);
    free(aux_bmp);


    //aloc dinamic matricea de pixel in care citesc pixeli din fisierul de input
    bmp_pixel **pixel = (bmp_pixel **)calloc(300, sizeof(bmp_pixel));
    if (pixel == NULL)
    {
        printf("Eroare alocare pixel!\n");
        exit(1);
    }
    for (i = 0; i < 80; i++)
    {
        pixel[i] = (bmp_pixel *)calloc(8000, sizeof(*pixel));
        if (pixel[i] == NULL)
        {
            printf("Eroare alocare pixel[%d]!\n", i);
            for (j = 0; j < i; j++)
            {
                free(pixel[j]);
            }
            free(pixel);
            exit(1);
        }
    }

    for (i = 0; i < Info_header.height; i++)
    {
        for (j = 0; j < Info_header.width; j++)
        {
            fread(&pixel[i][j], sizeof(bmp_pixel), 1, board_bmp_task_bonus);
        }
        fseek(board_bmp_task_bonus, 1, SEEK_CUR);
    }

    int kontor, l, k;

    //aloc vectorul 3D px_task_bonus care a scop sa memoreze un vector de matrici(fiecare matrice fiind un patratel din sudoku)
    bmp_pixel ***px_task_bonus = (bmp_pixel ***)calloc(2100, sizeof(bmp_pixel));
    if (px_task_bonus == NULL)
    {
        printf("Eroare alocare px_task_bonus!\n");
        for (i = 0; i < 80; i++)
            free(pixel[i]);
        free(pixel);
        exit(1);
    }
    for (i = 0; i < 100; i++)
    {
        px_task_bonus[i] = (bmp_pixel **)calloc(500, sizeof(bmp_pixel));
        if (px_task_bonus[i] == NULL)
        {
            printf("Eroare alocare px_task_bonus[%d]!\n", i);
            for (j = 0; j < i; j++)
            {
                free(px_task_bonus[i][j]);
            }
            for (i = 0; i < 80; i++)
            {
                free(pixel[i]);
            }
            free(pixel);
            free(px_task_bonus);
            exit(1);
        }
        for (j = 0; j < 10; j++)
        {
            px_task_bonus[i][j] = (bmp_pixel *)calloc(20, sizeof(bmp_pixel));
            if (px_task_bonus[i][j] == NULL)
            {
                printf("Eroare alocare px_task4[%d][%d]!\n", i, j);
                for (k = 0; k < i; k++)
                {
                    for (l = 0; l < j; l++)
                    {
                        free(px_task_bonus[k][l]);
                    }
                    free(px_task_bonus[k]);
                }
                for (i = 0; i < 80; i++)
                {
                    free(pixel[i]);
                }
                free(pixel);
                free(px_task_bonus);
                exit(1);
            }
        }
    }

    kontor = 0;

    //copiez din matricea pixel in pe pozitia respectiva din px_task_bonus
    for (i = 1; i < Info_header.height; i += 8)
    {
        for (j = 1; j < Info_header.width; j += 8)
        {
            for (k = 0; k < 7; k++)
            {
                for (l = 0; l < 7; l++)
                {
                    px_task_bonus[kontor][k][l] = pixel[i + k][j + l];
                }
            }
            kontor++;
        }
    }

    //aloc dinamic matricea sudoku
    int **sudoku = (int **)calloc(20, sizeof(int));
    if (sudoku == NULL)
    {
        printf("Eroare alocare sudoku!\n");
        for (i = 0; i < 100; i++)
        {
            for (j = 0; j < 10; j++)
            {
                free(px_task_bonus[i][j]);
            }
            free(px_task_bonus[i]);
        }
        free(px_task_bonus);
        for (i = 0; i < 80; i++)
        {
            free(pixel[i]);
        }
        free(pixel);
        exit(1);
    }
    for (i = 0; i < 9; i++)
    {
        sudoku[i] = (int *)calloc(20, sizeof(int));
        if (sudoku[i] == NULL)
        {
            printf("Eroare alocare sudoku[%d]!\n", i);
            for (j = 0; j < i; j++)
            {
                free(sudoku[j]);
            }
            for (i = 0; i < 100; i++)
            {
                for (j = 0; j < 10; j++)
                {
                    free(px_task_bonus[i][j]);
                }
                free(px_task_bonus[i]);
            }
            free(px_task_bonus);
            for (i = 0; i < 80; i++)
            {
                free(pixel[i]);
            }
            free(pixel);
            free(sudoku);
            exit(1);
        }
    }

    //aloc dinamic matricea copia-sudoku
    int **copie_sudoku = (int **)calloc(20, sizeof(int));
    if (copie_sudoku == NULL)
    {
        printf("Eroare alocare copie_sudoku!\n");
        for (i = 0; i < 9; i++)
        {
            free(sudoku[i]);
        }
        free(sudoku);
        for (i = 0; i < 100; i++)
        {
            for (j = 0; j < 10; j++)
            {
                free(px_task_bonus[i][j]);
            }
            free(px_task_bonus[i]);
        }
        free(px_task_bonus);
        for (i = 0; i < 80; i++)
        {
            free(pixel[i]);
        }
        free(pixel);
        exit(1);
    }
    for (i = 0; i < 9; i++)
    {
        copie_sudoku[i] = (int *)calloc(20, sizeof(int));
        if (copie_sudoku[i] == NULL)
        {
            printf("Eroare alocare copie_sudoku[%d]!\n", i);
            for (j = 0; j < i; j++)
            {
                free(copie_sudoku[j]);
            }
            for (i = 0; i < 9; i++)
            {
                free(sudoku[i]);
            }
            free(sudoku);
            for (i = 0; i < 100; i++)
            {
                for (j = 0; j < 10; j++)
                {
                    free(px_task_bonus[i][j]);
                }
                free(px_task_bonus[i]);
            }
            free(px_task_bonus);
            for (i = 0; i < 80; i++)
            {
                free(pixel[i]);
            }
            free(pixel);
            free(copie_sudoku);
            exit(1);
        }
    }

    //aloc dinamic matricea_white_space
    int *matrix_white_space = (int *)calloc(100, sizeof(int));
    if (matrix_white_space == NULL)
    {
        printf("Eroare alocare matrix_white_space!\n");
        for (i = 0; i < 9; i++)
        {
            free(sudoku[i]);
        }
        free(sudoku);
        for (i = 0; i < 100; i++)
        {
            for (j = 0; j < 10; j++)
            {
                free(px_task_bonus[i][j]);
            }
            free(px_task_bonus[i]);
        }
        free(px_task_bonus);
        for (i = 0; i < 80; i++)
        {
            free(pixel[i]);
        }
        free(pixel);
        for (i = 0; i < 9; i++)
        {
            free(copie_sudoku[i]);
        }
        free(matrix_white_space);
    }

    int count_white_space = 0;

    //creez pe baza functiei transf_number matricea care reprezinta sudokul
    kontor = 0;
    for (i = 8; i >= 0; i--)
    {
        for (j = 0; j < 9; j++)
        {
            sudoku[i][j] = transf_number(px_task_bonus[kontor]);
            kontor++;
        }
    }

    //copiez sudoku
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            copie_sudoku[i][j] = sudoku[i][j];
        }
    }

    //aici tin minte pozitiile casutelor goale din sudoku
    kontor = 0;
    for (i = 8; i >= 0; i--)
    {
        for (j = 0; j < 9; j++)
        {
            if (sudoku[i][j] == -1)
            {
                matrix_white_space[count_white_space] = kontor;
                count_white_space++;
            }
            kontor++;
        }
    }

    kontor = 0;

    //rezolv matricea sudoku
    solveSuduko(sudoku, 0, 0);

    //cu ajutorul sudoku_write scriu fiecare pixel in casuta respectiva
    int ok_sudoku = 1;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (sudoku[i][j] == 0)
            {
                ok_sudoku = 0;
            }
        }
    }

    if (ok_sudoku == 0)
    {
        for (i = 0; i < 81; i++)
        {
            sudoku_write(px_task_bonus[i], 0);
        }
    }
    else
    {
        kontor = 0;
        for (i = 8; i >= 0; i--)
        {
            for (j = 0; j < 9; j++)
            {
                if (copie_sudoku[i][j] == -1)
                {
                    sudoku_write(px_task_bonus[matrix_white_space[kontor]], sudoku[i][j]);
                    kontor++;
                }
            }
        }
    }

    //aici transfer vectorul de pixeli din px_task4 in pixel
    kontor = 0;
    for (i = 1; i < Info_header.height; i += 8)
    {
        for (j = 1; j < Info_header.width; j += 8)
        {
            for (k = 0; k < 7; k++)
            {
                for (l = 0; l < 7; l++)
                {
                    pixel[i + k][j + l] = px_task_bonus[kontor][k][l];
                }
            }
            kontor++;
        }
    }

    //scriu fisierul
    for (i = 0; i < Info_header.height; i++)
    {
        for (j = 0; j < Info_header.width; j++)
        {
            fwrite(&pixel[i][j], sizeof(bmp_pixel), 1, output);
        }
        fwrite(&pixel_ped, sizeof(unsigned char), 1, output);
    }

    //eliberez toata memoria alocata dinamic
    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 10; j++)
        {
            free(px_task_bonus[i][j]);
        }
        free(px_task_bonus[i]);
    }
    free(px_task_bonus);

    for (i = 0; i < 9; i++)
    {
        free(sudoku[i]);
    }
    free(sudoku);
    for (i = 0; i < 80; i++)
    {
        free(pixel[i]);
    }
    free(pixel);
    for (i = 0; i < 9; i++)
    {
        free(copie_sudoku[i]);
    }
    free(copie_sudoku);
    free(matrix_white_space);

    fclose(output);
    fclose(board_bmp_task_bonus);
}