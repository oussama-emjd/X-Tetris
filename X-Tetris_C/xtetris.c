#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

int colonne = 10;
int righe = 15;

void draw_field(int *Field, int *Tetromino, int numTetrominoes, int score)
{
    int r, c;

    printf("\033[H\033[J"); /*cancella lo schermo*/

    /*start - disegna il campo del tetromino*/
    for (r = 0; r <= 4 + 1; ++r)
    {
        for (c = 0; c <= 4 * 2 + 1; ++c)
        {
            if ((r == 0 && c == 0) || (r == 4 + 1 && c == 0) ||
                (r == 0 && c == 4 * 2 + 1) || (r == 4 + 1 && c == 4 * 2 + 1))
                printf("+");
            else if (r == 0 || r == 4 + 1)
                printf("-");
            else if (c == 0 || c == 4 * 2 + 1)
                printf("|");
            else
            {
                if (Tetromino[(r - 1) * 4 + (int)((c - 1) / 2)] == 0)
                    printf(" ");
                else
                    printf("\x1B[3%dm\u2588\x1B[0m", Tetromino[(r - 1) * 4 + (int)((c - 1) / 2)]);
            }
        }
        printf("\n\r");
    }
    /*end - disegna il campo del Tetromino*/

    printf(" Num: %d\n\r", numTetrominoes);
    printf(" Score: %d\n\r", score);

    /*start - disegna il campo di gioco, ovvero la matrice temporania*/
    for (r = 0; r <= righe + 1; ++r)
    {
        for (c = 0; c <= colonne * 2 + 1; ++c)
        {
            if ((r == 0 && c == 0) || (r == righe + 1 && c == 0) ||
                (r == 0 && c == colonne * 2 + 1) || (r == righe + 1 && c == colonne * 2 + 1))
                printf("+");
            else if (r == 0 || r == righe + 1)
                printf("-");
            else if (c == 0 || c == colonne * 2 + 1)
                printf("|");
            else
            {
                if (Field[(r - 1) * colonne + (int)((c - 1) / 2)] == 0)
                    printf(" ");
                else if (Field[(r - 1) * colonne + (int)((c - 1) / 2)] < 8)
                    printf("\x1B[3%dm\u2588\x1B[0m", Field[(r - 1) * colonne + (int)((c - 1) / 2)]);    /*Il carattere \u2588 non è supportato in ANSI C*/
                else
                    printf("\x1B[3%dm\u2593\x1B[0m", Field[(r - 1) * colonne + (int)((c - 1) / 2)] - 7);    /*Il carattere \u2593 non è supportato in ANSI C*/
            }
        }
        printf("\n\r");
    }
    /*end - disegna il campo di gioco*/
}

void draw_fields(int *Field_1, int *Field_2, int *Tetromino, int numTetrominoes, int score_1, int score_2)
{
    int r, c;

    printf("\033[H\033[J"); /*cancella lo schermo*/

    /*start - disegna il campo del Tetromino*/
    for (r = 0; r <= 4 + 1; ++r)
    {
        for (c = 0; c <= 4 * 2 + 1; ++c)
        {
            if ((r == 0 && c == 0) || (r == 4 + 1 && c == 0) || 
                (r == 0 && c == 4 * 2 + 1) || (r == 4 + 1 && c == 4 * 2 + 1))
                printf("+");
            else if (r == 0 || r == 4 + 1)
                printf("-");
            else if (c == 0 || c == 4 * 2 + 1)
                printf("|");
            else
            {
                if (Tetromino[(r - 1) * 4 + (int)((c - 1) / 2)] == 0)
                    printf(" ");
                else
                    printf("\x1B[3%dm\u2588\x1B[0m", Tetromino[(r - 1) * 4 + (int)((c - 1) / 2)]);
            }
        }
        printf("\n\r");
    }
    /*end - disegna il campo del Tetromino*/

    printf(" Num: %d\n\r", numTetrominoes);
    printf(" Score 1: %d\t      Score 2: %d\n\r", score_1, score_2);

    /*start - disegna i due campi di gioco, ovvero le due matrici temporanei di player 1 e player 2*/
    for (r = 0; r <= righe + 1; ++r)
    {
        for (c = 0; c <= (colonne * 4 + 2); ++c)
        {
            if ((r == 0 && c == 0) || (r == righe + 1 && c == 0) ||
                (r == 0 && c == colonne * 2 + 1) || (r == righe + 1 && c == colonne * 2 + 1) ||
                (r == 0 && c == (colonne * 4 + 2)) || (r == righe + 1 && c == (colonne * 4 + 2)))
                printf("+");
            else if (r == 0 || r == righe + 1)
                printf("-");
            else if (c == 0 || c == colonne * 2 + 1 || c == (colonne * 4 + 2))
                printf("|");
            else
            {
                if (c < (colonne * 2 + 1))
                {
                    if (Field_1[(r - 1) * colonne + (int)((c - 1) / 2)] == 0)
                        printf(" ");
                    else if (Field_1[(r - 1) * colonne + (int)((c - 1) / 2)] < 8)
                        printf("\x1B[3%dm\u2588\x1B[0m", Field_1[(r - 1) * colonne + (int)((c - 1) / 2)]);
                    else
                        printf("\x1B[3%dm\u2593\x1B[0m", Field_1[(r - 1) * colonne + (int)((c - 1) / 2)] - 7);
                }
                else
                {
                    if (Field_2[(r - 1) * colonne + (int)((c - 2 - (colonne * 2)) / 2)] == 0)
                        printf(" ");
                    else if (Field_2[(r - 1) * colonne + (int)((c - 2 - (colonne * 2)) / 2)] < 8)
                        printf("\x1B[3%dm\u2588\x1B[0m", Field_2[(r - 1) * colonne + (int)((c - 2 - (colonne * 2)) / 2)]); 
                    else
                        printf("\x1B[3%dm\u2593\x1B[0m", Field_2[(r - 1) * colonne + (int)((c - 2 - (colonne * 2)) / 2)] - 7);
                }
            }
        }
        printf("\n\r");
    }
    /*end - disegna i due campi di gioco*/
}

void ISGAMEOVER(int *Field, int *numTetrominoes, int *win, int *isGameOver)
{
    int c;
    int sup = 0;

    for (c = 0; c < colonne; ++c)   /*controlla se la prima righa della matrice è vuota*/
        if (Field[0 + c] != 0 && Field[0 + c] < 8)
        {
            *isGameOver = 1;         /*se non è vuota allora il gioco è finito*/
            *win = 0;
            break;
        }

    for (c = 0; c < 7; ++c) /*controlla se i tetromini a disposizione sono finiti*/
        if (numTetrominoes[c] == 0)  
            sup++;

    if (sup == 7)
    {
        *isGameOver = 1; /*se i tetromini a disposizione sono fintiti allora anche il gioco è finito*/
        *win = 1;
    }
}

void save_or_not_tetromino(int *Field, int save)
{
    int r, c;

    if (save)
    {
        for(r = 0; r < righe; ++r)
            for (c = 0; c < colonne; ++c)
                if (Field[r * colonne + c] > 7)
                    Field[r * colonne + c] -= 7;
    } else
    {
        for(r = 0; r < righe; ++r)
            for (c = 0; c < colonne; ++c)
                if (Field[r * colonne + c] > 7)
                    Field[r * colonne + c] = 0;
    }
}

void delete_line(int *Field, int y)
{
    int r, c;

    for (c = 0; c < colonne; ++c)   /*cancella dalla matrice la riga y*/
        Field[y * colonne + c] = 0;

    for (r = y; r > 0; --r) /*sposta la matrice a partire dalla riga y in giù*/
        for (c = 0; c < colonne; ++c)
            Field[r * colonne + c] = Field[(r - 1) * colonne + c];
}

int find_complete_lines(int *Field)
{
    int r, c;
    int complete_row;
    int complete_lines = 0;

    for (r = 0; r < righe; ++r)
    {
        complete_row = 0;

        for (c = 0; c < colonne; ++c)
            if (Field[r * colonne + c] != 0 && Field[r * colonne + c] < 8)
                complete_row++;
        if (complete_row == colonne)
        {
            delete_line(Field, r);   /*se trovi una riga completa cancellala*/
            complete_lines++;
        }
    }

    return complete_lines;
}

void reverse_n_lines(int *Field, int n)
{
    int r, c;

    for (r = (righe - n); r < righe; ++r)
    {
        for (c = 0; c < colonne; ++c)
        {
            if (Field[r * colonne + c] == 0)
                Field[r * colonne + c] = 7;
            else
                Field[r * colonne + c] = 0;
        }
    }
}

int find_positionY(int *Field, int *Tetromino, int *positionX)
{
    int r, c;
    int y;
    int auy = 0;
    int collision = 0;

    for (y = 0; y < righe; ++y)
    {
        for (r = 4 - 1; r >= 0; --r)
        {
            for (c = 0; c < 4; ++c)
                if((*positionX + c) < colonne && (y + auy) >= 0 && 
                    Field[(y + auy) * colonne + *positionX + c] < 8 && 
                    Field[(y + auy) * colonne + *positionX + c] > 0 && 
                    Tetromino[r * 4 + c] != 0)
                {
                    collision = 1;
                }
            auy--;
        }
        if (!collision)
            auy = 0;
        else
            return y - 1;   /*quando trovi una collisione restituisci la posizione y precedente*/
    }

    return righe - 1;       /*altrimenti restituisci l'ultima posizione della matrice*/
}

int adjust_positionX (int *Tetromino)
{
    int r, c, z, out = 0;

    for (c = 3; c >= 0; c--)
    {
        z = 0;
        for (r = 0; r < 4; r++)
        {
            if (Tetromino[r * 4 + c] == 0)
                z++;
        }
        if (z == 4)
            out++;
    }

    return (colonne - 4 + out);
}

void addTetromino(int *Field, int *Tetromino, int *positionX)
{
    int r, c;
    int auy = 0;
    int collision = 0;
    int off_the_field = 0;

    int positionY = find_positionY(Field, Tetromino, positionX);

    /*start - cerca se mettendo il tetromino nella posizione X,Y si verifica una collisione oppure il tetromino va fuori campo*/
    for (r = 4 - 1; r >= 0; --r)
    {
        for (c = 0; c < 4; ++c)
        {
            if ((*positionX + c >= colonne) && Tetromino[r * 4 + c] != 0)
            {
                off_the_field = 1;
                *positionX = adjust_positionX (Tetromino);
            }
            else if (*positionX < 0)
            {
                off_the_field = 1;
                *positionX = 0;
            }
            else if (   (*positionX + c) < colonne && (positionY + auy) >= 0 && 
                        Field[(positionY + auy) * colonne + *positionX + c] != 0 &&
                        Field[(positionY + auy) * colonne + *positionX + c] < 8 &&
                        Tetromino[r * 4 + c] != 0)
                    {
                        collision = 1;
                    }
        }
        auy--;
    }
    /*end*/

    auy = 0;

    /*start - se non si verifica nessuna collosione e il tetromino non va fuori campo allora aggiungi il tetromino nella posizione X,Y*/
    if (!collision && !off_the_field)
    {
        save_or_not_tetromino(Field, 0);
        for (r = 4 - 1; r >= 0; --r)
        {
            for (c = 0; c < 4; ++c)
                if (Tetromino[r * 4 + c] != 0 && ((positionY + auy) * colonne + *positionX + c) >= 0 && 
                    ((positionY + auy) * colonne + *positionX + c) < (colonne * righe))
                    Field[(positionY + auy) * colonne + *positionX + c] = Tetromino[r * 4 + c] + 7;
            auy--;
        }
    }
    /*end*/
}

void rotateTetromino(int *Tetromino)
{
    int r, c;
    int temp;

    for (r = 0; r < 4; ++r)
        for (c = r; c < 4; ++c)
        {
            temp = Tetromino[r * 4 + c];
            Tetromino[r * 4 + c] = Tetromino[c * 4 + r];
            Tetromino[c * 4 + r] = temp;
        }

    for (r = 0; r < 4; ++r)
        for (c = 0; c < 4 / 2; ++c)
        {
            int temp = Tetromino[r * 4 + c];
            Tetromino[r * 4 + c] = Tetromino[r * 4 + 4 - 1 - c];
            Tetromino[r * 4 + 4 - 1 - c] = temp;
        }

    temp = 0;

    while (1)
    {
        for (c = 0; c < 4; ++c)
            if (Tetromino[(4 - 1) * 4 + c] == 0)
                temp++;

        if (temp == 4)
        {
            temp = 0;
            for (r = 4 - 1; r > 0; --r)
                for (c = 0; c < 4; ++c)
                    Tetromino[r * 4 + c] = Tetromino[(r - 1) * 4 + c];

            for (c = 0; c < 4; ++c)
                Tetromino[0 + c] = 0;
        }
        else
            break;
    }
}

int SCORE(int righe)
{
    switch (righe)
    {
    case 1: return 1;
    case 2: return 3;
    case 3: return 6;
    case 4: return 12;
    default: return 0;
    }
}

void KeyPressed(char c, int *positionX, int *Field,
                int **Tetromino, int *numTetrominoes, 
                int *IndexTetromino, int *player, int GameMode)
{
    int IndexCopy = *IndexTetromino;
    if (c == 'a' || c == 'A' || c == 68)
        (*positionX)--;
    else if (c == 'd' || c == 'D' || c == 67)
        (*positionX)++;
    else if (c == 'c' || c == 'C')
    {
        (*IndexTetromino == 6) ? *IndexTetromino = 0 : (*IndexTetromino)++;
        if (adjust_positionX(Tetromino[IndexCopy]) == *positionX)
            *positionX = adjust_positionX(Tetromino[*IndexTetromino]);
    }
    else if (c == 'r' || c == 'R')
        if (adjust_positionX(Tetromino[*IndexTetromino]) == *positionX)
        {
            rotateTetromino(Tetromino[*IndexTetromino]);
            *positionX = adjust_positionX(Tetromino[*IndexTetromino]);
        } else
            rotateTetromino(Tetromino[*IndexTetromino]);
    else if (c == ' ' && numTetrominoes[*IndexTetromino] > 0)
    {
        save_or_not_tetromino(Field, 1);
        numTetrominoes[*IndexTetromino]--;
        if (GameMode)
            *player = !(*player);
    }
}

void menu(int *GameMode)
{
    printf(" _  _     ____  ____  ____  ____  __  ____ \n");
    printf("( \\/ )___(_  _)(  __)(_  _)(  _ \\(  )/ ___)\n");
    printf(" )  ((___) )(   ) _)   )(   )   / )( \\___ \\\n");
    printf("(_/\\_)    (__) (____) (__) (__\\_)(__)(____/\n");

    do
    {
        printf("Premi 0 per single player e 1 per multi player.\n");
        printf("> ");
        scanf("%d", GameMode);
    } while (*GameMode != 0 && *GameMode != 1);
}

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR)
    {
        ungetch(ch);
        return 1;
    }
    else
        return 0;
}

int main(void)
{
    int GameMode;
    menu(&GameMode);

    int *Field_1 = (int *)calloc(righe * colonne, sizeof(int)); /*campo originale per player 1*/
    int *Field_2 = (int *)calloc(righe * colonne, sizeof(int)); /*campo originale per player 2*/

    int TetrominoI[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}};
    int TetrominoO[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {2, 2, 0, 0}, {2, 2, 0, 0}};
    int TetrominoJ[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {3, 0, 0, 0}, {3, 3, 3, 0}};
    int TetrominoL[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 4, 0}, {4, 4, 4, 0}};
    int TetrominoS[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 5, 5, 0}, {5, 5, 0, 0}};
    int TetrominoT[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 6, 0, 0}, {6, 6, 6, 0}};
    int TetrominoZ[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {7, 7, 0, 0}, {0, 7, 7, 0}};

    int numTetromino = GameMode ? 40 : 20;

    int *Tetromino[7] = {TetrominoI[0], TetrominoO[0], TetrominoJ[0], TetrominoL[0], TetrominoS[0], TetrominoT[0], TetrominoZ[0]};
    int numTetrominoes[7] = {numTetromino, numTetromino, numTetromino, numTetromino, numTetromino, numTetromino, numTetromino};

    char c;

    int positionX_1 = 0, positionX_2 = 0;
    int score_1 = 0, score_2 = 0;

    int isGameOver = 0;
    int player = 0, win = 0;
    int complete_lines;
    int IndexTetromino = 0;
    int FirstCycle = 1;

    initscr();
    nodelay(stdscr, TRUE);

    while (!isGameOver)
    {
        c = 0x00;

        if (kbhit())
        {
            c = getch();
            if (player)
                KeyPressed(c, &positionX_2, Field_2, Tetromino, numTetrominoes, &IndexTetromino, &player, GameMode);
            else
                KeyPressed(c, &positionX_1, Field_1, Tetromino, numTetrominoes, &IndexTetromino, &player, GameMode);
        }

        if (c != 0x00 || FirstCycle)
        {
            ISGAMEOVER(Field_1, numTetrominoes, &win, &isGameOver);
            ISGAMEOVER(Field_2, numTetrominoes, &win, &isGameOver);

            if (GameMode)
            {
                complete_lines = find_complete_lines(Field_2);
                score_2 += SCORE(complete_lines);
                if (complete_lines > 2)
                    reverse_n_lines(Field_1, complete_lines);

                complete_lines = find_complete_lines(Field_1);
                score_1 += SCORE(complete_lines);
                if (complete_lines > 2)
                    reverse_n_lines(Field_2, complete_lines);

                if (player)
                    addTetromino(Field_2, Tetromino[IndexTetromino], &positionX_2);
                else
                    addTetromino(Field_1, Tetromino[IndexTetromino], &positionX_1);

                draw_fields(Field_1, Field_2, Tetromino[IndexTetromino], numTetrominoes[IndexTetromino], score_1, score_2);
            }
            else
            {
                complete_lines = find_complete_lines(Field_1);
                score_1 += SCORE(complete_lines);

                addTetromino(Field_1, Tetromino[IndexTetromino], &positionX_1);

                draw_field(Field_1, Tetromino[IndexTetromino], numTetrominoes[IndexTetromino], score_1);
            }

            FirstCycle = 0;
        }
    }

    if (win)
    {
        if (GameMode)
        {
            if (score_1 > score_2)
                printf("Player 1 wins!\n");
            else if (score_1 < score_2)
                printf("Player 2 wins!\n");
            else
                printf("No winner!\n");
        }
        else
            printf("You won!\n");
    }
    else
    {
        if (GameMode)
        {
            int i, j = 1;
            for (i = 0; i < colonne; ++i)
                if (Field_1[0 + i] != 0)
                    j = 0;

            if (!j)
                printf("Player 1 loses and Player 2 wins!\n");
            else
                printf("Player 2 loses and Player 1 wins!\n");
        }
        else
            printf("you lost!!!\n");
    }

    nodelay(stdscr, FALSE);
    getch();
    endwin();

    return 0;
}