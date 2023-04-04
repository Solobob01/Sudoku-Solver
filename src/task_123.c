#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./transf_number.h"
#include "./sudoku_checker.h"
#include "./sudoku_solver.h"
#include "./sudoku_write.h"

void task123(char *argv)
{
    //task1
    int i, j;
    unsigned char pixel_ped = 0;

    bmp_fileheader File_header;
    bmp_infoheader Info_header;

    char *strJson, *aux_task1, *aux_bmp;
    char *number_board = strstr(argv, "board");

    //alocare dinamica strJson
    strJson = (char *)calloc(100000, sizeof(char));
    if (strJson == NULL)
    {
        printf("Eroare alocare strJson!\n");
        exit(1);
    }

    //alocare dinamica aux_task1
    aux_task1 = (char *)calloc(100, sizeof(char));
    if (aux_task1 == NULL)
    {
        printf("Eroare alocare aux_task1!\n");
        free(strJson);
        exit(1);
    }

    //alocare dinamica aux_bmp
    aux_bmp = (char *)calloc(100, sizeof(char));
    if (aux_bmp == NULL)
    {
        printf("Eroare alocare aux_bmp!\n");
        free(aux_task1);
        free(strJson);
        exit(1);
    }
    strcpy(aux_task1, "./output_task1_board");
    strcpy(aux_bmp, ".bmp");

    //creaza fisierul primit ca input
    FILE *tmp = fopen(argv, "r");

    if (tmp == NULL)
    {
        printf("Nu exista fisierul de citire!\n");
        free(aux_bmp);
        free(aux_task1);
        free(strJson);
        exit(1);
    }

    //creaza numele fisierului de output pe baza inputului
    strncat(aux_task1, &number_board[5], 1);
    strncat(aux_task1, &number_board[6], 1);
    strcat(aux_task1, aux_bmp);

    //creaza si deschide un fisier de output
    FILE *board_bmp_task1 = fopen(aux_task1, "wb");
    if (board_bmp_task1 == NULL)
    {
        fclose(tmp);
        free(aux_bmp);
        free(aux_task1);
        free(strJson);
        exit(1);
    }

    free(aux_task1);

    //copiaza structura JSON intr-un string
    fread(strJson, 100000, 1, tmp);
    cJSON *board = cJSON_Parse(strJson);

    fclose(tmp);
    free(strJson);

    //file-header(scrie file_header-ul din fisierul json)
    cJSON *file_header = cJSON_GetObjectItem(board, "file_header");

    char *signature = cJSON_GetObjectItem(file_header, "signature")->valuestring;
    int file_size = cJSON_GetObjectItem(file_header, "file_size")->valueint;
    int reserved = cJSON_GetObjectItem(file_header, "reserved")->valueint;
    int offset = cJSON_GetObjectItem(file_header, "offset")->valueint;
    File_header.fileMarker1 = signature[0];
    File_header.fileMarker2 = signature[1];
    File_header.bfSize = file_size;
    File_header.unused1 = reserved;
    File_header.unused2 = reserved;
    File_header.imageDataOffset = offset;

    fwrite(&File_header, sizeof(bmp_fileheader), 1, board_bmp_task1);

    //head-header(scrie head_header-ul din fisierul json)
    cJSON *info_header = cJSON_GetObjectItem(board, "info_header");

    Info_header.biSize = cJSON_GetObjectItem(info_header, "size")->valueint;
    Info_header.width = cJSON_GetObjectItem(info_header, "width")->valueint;
    Info_header.height = cJSON_GetObjectItem(info_header, "height")->valueint;
    Info_header.planes = cJSON_GetObjectItem(info_header, "planes")->valueint;
    Info_header.bitPix = cJSON_GetObjectItem(info_header, "bit_count")->valueint;
    Info_header.biCompression = cJSON_GetObjectItem(info_header, "compression")->valueint;
    Info_header.biSizeImage = cJSON_GetObjectItem(info_header, "image_size")->valueint;
    Info_header.biXPelsPerMeter = cJSON_GetObjectItem(info_header, "x_pixels_per_meter")->valueint;
    Info_header.biYPelsPerMeter = cJSON_GetObjectItem(info_header, "y_pixels_per_meter")->valueint;
    Info_header.biClrUsed = cJSON_GetObjectItem(info_header, "colors_used")->valueint;
    Info_header.biClrImportant = cJSON_GetObjectItem(info_header, "colors_important")->valueint;

    fwrite(&Info_header, sizeof(bmp_infoheader), 1, board_bmp_task1);

    //bitmap(scriem vetctorul bitmap din fisierul json)
    cJSON *bitmap = cJSON_GetObjectItem(board, "bitmap");

    //alocam dinamic o matrice de pixeli
    bmp_pixel **px_task1 = (bmp_pixel **)calloc(Info_header.height * Info_header.width, sizeof(bmp_pixel *));
    if (px_task1 == NULL)
    {
        printf("Alocare px EROARE!\n");
        fclose(board_bmp_task1);
        cJSON_Delete(board);
        exit(1);
    }

    for (int i = 0; i < Info_header.height; i++)
    {
        px_task1[i] = (bmp_pixel *)calloc(Info_header.height, sizeof(bmp_pixel *));
        if (px_task1[i] == NULL)
        {
            printf("Alocare px[%d] EROARE!\n", i);
            for (j = 0; j < i; j++)
            {
                free(px_task1[i]);
            }
            free(px_task1);
            fclose(board_bmp_task1);
            cJSON_Delete(board);
            exit(1);
        }
    }

    //punem valorile din bitmap in matricea pixelilor
    int k = 0;
    for (i = Info_header.height - 1; i >= 0; i--)
        for (j = 0; j < Info_header.width; j++)
        {
            px_task1[i][j].red = cJSON_GetArrayItem(bitmap, k)->valueint;
            k++;
            px_task1[i][j].green = cJSON_GetArrayItem(bitmap, k)->valueint;
            k++;
            px_task1[i][j].blue = cJSON_GetArrayItem(bitmap, k)->valueint;
            k++;
        }

    k = 0;

    //scriem matricea pixelilor in fisierul bitmap
    for (i = 0; i < Info_header.height; i++)
    {
        for (j = 0; j < Info_header.width; j++)
        {
            fwrite(&px_task1[i][j], sizeof(bmp_pixel), 1, board_bmp_task1);
            k += 3;
        }
        fwrite(&pixel_ped, sizeof(unsigned char), 1, board_bmp_task1);
    }

    fclose(board_bmp_task1);

    //task 2

    //creaza numele fisierului de output pe baza inputului

    char *aux_task2;

    //alocare dinamica aux_task2
    aux_task2 = (char *)calloc(100, sizeof(char));
    if (aux_task2 == NULL)
    {
        printf("Eroare alocare aux_task2!\n");
        for (j = 0; j < Info_header.height; j++)
        {
            free(px_task1[i]);
        }
        free(px_task1);
        free(aux_bmp);
        exit(1);
    }

    strcpy(aux_task2, "./output_task2_board");

    strncat(aux_task2, &number_board[5], 1);
    strncat(aux_task2, &number_board[6], 1);
    strcat(aux_task2, aux_bmp);

    FILE *board_bmp_task2 = fopen(aux_task2, "wb");

    fwrite(&File_header, sizeof(File_header), 1, board_bmp_task2);
    fwrite(&Info_header, sizeof(Info_header), 1, board_bmp_task2);

    free(aux_bmp);
    free(aux_task2);

    //aloca dinamic matricea pixelilor pt al doilea task
    bmp_pixel **px_task2 = (bmp_pixel **)malloc(Info_header.height * Info_header.width * sizeof(bmp_pixel *));
    if (px_task2 == NULL)
    {
        printf("Alocare px EROARE!\n");
        exit(1);
    }

    for (int i = 0; i < Info_header.height; i++)
    {
        px_task2[i] = (bmp_pixel *)malloc(Info_header.height * sizeof(bmp_pixel *));
        if (px_task2[i] == NULL)
        {
            printf("Alocare px[%d] EROARE!\n", i);
            for (j = 0; j < Info_header.height; j++)
            {
                free(px_task1[i]);
            }
            free(px_task1);
            for (j = 0; j < i; j++)
            {
                free(px_task2[j]);
            }
            free(px_task2);
            fclose(board_bmp_task2);
            exit(1);
        }
    }

    //aici se iau valorile din matricea pixelilor de la task 1 si se scriu in matricea pixelilor de la task 2
    for (i = 0; i < Info_header.height; i++)
        for (j = 0; j < Info_header.width; j++)
        {
            px_task2[i][j].red = px_task1[i][j].red;
            px_task2[i][j].green = px_task1[i][j].green;
            px_task2[i][j].blue = px_task1[i][j].blue;
        }
    //aici se fac rocada pixelilor care reprezinta o cifra din sudoku
    for (i = 1; i < Info_header.height; i++)
        for (j = 1; j < Info_header.width; j += 8)
        {
            for (k = 0; k < 3; k++)
            {
                bmp_pixel tmp = px_task2[i][j + k];
                px_task2[i][j + k] = px_task2[i][j + 6 - k];
                px_task2[i][j + 6 - k] = tmp;
            }
        }

    //aici se scrie matricea pixelilor in fisier
    k = 0;
    for (i = 0; i < Info_header.height; i++)
    {
        for (j = 0; j < Info_header.width; j++)
        {
            fwrite(&px_task2[i][j], sizeof(px_task2[i][j]), 1, board_bmp_task2);
        }
        fwrite(&pixel_ped, sizeof(pixel_ped), 1, board_bmp_task2);
    }

    for (int i = 0; i < Info_header.height; i++)
        free(px_task1[i]);
    free(px_task1);
    fclose(board_bmp_task2);
    //task 3

    //declar un vector de matrici(fiecare matrice din vector reprezinta o casuta din sudoku)

    int l;
    //aloc vectorul 3D px_task3 care a scop sa memoreze un vector de matrici(fiecare matrice fiind un patratel din sudoku)
    bmp_pixel ***px_task3 = (bmp_pixel ***)calloc(2100, sizeof(bmp_pixel));
    if (px_task3 == NULL)
    {
        printf("Eroare alocare px_task3!\n");
        exit(1);
    }
    for (i = 0; i < 100; i++)
    {
        px_task3[i] = (bmp_pixel **)calloc(500, sizeof(bmp_pixel));
        if (px_task3[i] == NULL)
        {
            printf("Eroare alocare px_task3[%d]!\n", i);
            for (j = 0; j < i; j++)
            {
                free(px_task3[i][j]);
            }
            free(px_task3);
            exit(1);
        }
        for (j = 0; j < 10; j++)
        {
            px_task3[i][j] = (bmp_pixel *)calloc(20, sizeof(bmp_pixel));
            if (px_task3[i][j] == NULL)
            {
                printf("Eroare alocare px_task3[%d][%d]!\n", i, j);
                for (k = 0; k < i; k++)
                {
                    for (l = 0; l < j; l++)
                    {
                        free(px_task3[k][l]);
                    }
                    free(px_task3[k]);
                }
                free(px_task3);
                exit(1);
            }
        }
    }

    //aici completez fiecare matrice cu valoarea respectiva

    int kontor = 0;
    for (i = 1; i < Info_header.height; i += 8)
    {
        for (j = 1; j < Info_header.width; j += 8)
        {
            for (k = 0; k < 7; k++)
            {
                for (l = 0; l < 7; l++)
                {
                    px_task3[kontor][k][l] = px_task2[i + k][j + l];
                }
            }
            kontor++;
        }
    }

    kontor = 0;

    //alocare dinamica sudoku
    int **sudoku = (int **)calloc(20, sizeof(int));
    if (sudoku == NULL)
    {
        printf("Eroare alocare sudoku!\n");
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
            free(sudoku);
            exit(1);
        }
    }

    //transform sudoku.bmp intr-o matrice pe baza functiei transf_number
    for (i = 8; i >= 0; i--)
    {
        for (j = 0; j < 9; j++)
        {
            sudoku[i][j] = transf_number(px_task3[kontor]);
            kontor++;
        }
    }

    //apelez functia sudoku_checker ca sa verific daca este rezolvat corect/sunt introduse date corecte
    int ok_sudoku = sudoku_checker(sudoku);

    //creez fisierul de output
    char *aux_task3;
    aux_task3 = (char *)calloc(50, sizeof(char));
    if (aux_task3 == NULL)
    {
        printf("Eroare alocare aux_task3!\n");
        for (i = 0; i < 9; i++)
        {
            free(sudoku[i]);
        }
        free(sudoku);
    }
    strcpy(aux_task3, "./output_task3_");
    strcat(aux_task3, number_board);
    FILE *board_bmp_task3 = fopen(aux_task3, "w");

    free(aux_task3);

    //in functie de corectitudinea sudokului in fisierul de output scrie json-ul corespunzator
    if (ok_sudoku == 0 || ok_sudoku == 2)
    {
        fprintf(board_bmp_task3, "{\n\t\"input_file\":\t\"%s\",\n", number_board);
        fprintf(board_bmp_task3, "\t\"game_state\":\t\"Loss :(\"\n}\n");
    }
    else
    {
        fprintf(board_bmp_task3, "{\n\t\"input_file\":\t\"%s\",\n", number_board);
        fprintf(board_bmp_task3, "\t\"game_state\":\t\"Win!\"\n}\n");
    }

    //eliberam tot

    for (int i = 0; i < Info_header.height; i++)
        free(px_task2[i]);
    free(px_task2);

    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 10; j++)
        {
            free(px_task3[i][j]);
        }
        free(px_task3[i]);
    }
    free(px_task3);

    for (i = 0; i < 9; i++)
        free(sudoku[i]);
    free(sudoku);

    fclose(board_bmp_task3);
    cJSON_Delete(board);
}