import curses

colonne = 10
righe = 15

isGameOver = False
win = False
esc = False

player = True
GameMode = False

positionX = 0
IndexTetromino = 0


def draw_field(Field, Tetromino, numTetrominoes, score):
    print("\033[H\033[J")

    print("+" + "-" * 8 + "+", end='\n\r')
    for r in range(4):
        print("|", end='')
        for c in range(8):
            if Tetromino[r][(int)(c/2)] == 0:
                print(" ", end='')
            else:
                print(f"\x1B[3{Tetromino[r][(int)(c/2)]}m\u2588\x1B[0m", end='')
        print("|", end='\n\r')
    print("+" + "-" * 8 + "+", end='\n\r')

    print(f" Num: {numTetrominoes[IndexTetromino]}", end='\n\r')
    print(f" Score: {score}", end='\n\r')

    print("+" + "-" * colonne * 2 + "+", end='\n\r')
    for r in range(righe):
        print("|", end='')
        for c in range(colonne*2):
            if Field[r][(int)(c/2)] == 0:
                print(" ", end='')
            elif Field[r][(int)(c/2)] < 8:
                print(f"\x1B[3{Field[r][(int)(c/2)]}m\u2588\x1B[0m", end='')
            else:
                print(f"\x1B[3{Field[r][(int)(c/2)]-7}m\u2593\x1B[0m", end='')
        print("|", end='\n\r')
    print("+" + "-" * colonne * 2 + "+", end='\n\r')

def draw_fields(Field_1, Field_2, Tetromino, numTetrominoes, score_1, score_2):
    print("\033[H\033[J")

    print("+" + "-" * 8 + "+", end='\n\r')
    for r in range(4):
        print("|", end='')
        for c in range(8):
            if Tetromino[r][(int)(c/2)] == 0:
                print(" ", end='')
            else:
                print(f"\x1B[3{Tetromino[r][(int)(c/2)]}m\u2588\x1B[0m", end='')
        print("|", end='\n\r')
    print("+" + "-" * 8 + "+", end='\n\r')

    print(f" Num: {numTetrominoes[IndexTetromino]}", end='\n\r')
    print(f" Score: {score_1}\t      Score 2: {score_2}", end='\n\r')

    print("+" + "-" * colonne * 2 + "+" + "-" * colonne * 2 + "+", end='\n\r')
    for r in range(righe):
        print("|", end='')
        for c in range(colonne*2):
            if Field_1[r][(int)(c/2)] == 0:
                print(" ", end='')
            elif Field_1[r][(int)(c/2)] < 8:
                print(f"\x1B[3{Field_1[r][(int)(c/2)]}m\u2588\x1B[0m", end='')
            else:
                print(f"\x1B[3{Field_1[r][(int)(c/2)]-7}m\u2593\x1B[0m", end='')
        print("|", end='')
        for c in range(colonne*2):
            if Field_2[r][(int)(c/2)] == 0:
                print(" ", end='')
            elif Field_2[r][(int)(c/2)] < 8:
                print(f"\x1B[3{Field_2[r][(int)(c/2)]}m\u2588\x1B[0m", end='')
            else:
                print(f"\x1B[3{Field_2[r][(int)(c/2)]-7}m\u2593\x1B[0m", end='')
        print("|", end='\n\r')
    print("+" + "-" * colonne * 2 + "+" + "-" * colonne * 2 + "+", end='\n\r')

def ISGAMEOVER(Field, numTetrominoes):
    global isGameOver
    global win
    for c in range(colonne):
        if Field[0][c] != 0 and Field[0][c] < 8:
            isGameOver = True
            win = False
            break
    
    sup = 0
    for c in range(7):
        if numTetrominoes[c] == 0:
            sup += 1
    
    if sup == 7:
        isGameOver = True
        win = True

def save_or_not_tetromino(Field, save):
    if save:
        for r in range(righe):
            for c in range(colonne):
                if Field[r][c] > 7:
                    Field[r][c] -= 7
    else:
        for r in range(righe):
            for c in range(colonne):
                if Field[r][c] > 7:
                    Field[r][c] = 0


def delete_line(Field, y):
    for c in range(colonne):
        Field[y][c] = 0
    
    for r in range(y, 0, -1):
        for c in range(colonne):
            Field[r][c] = Field[r-1][c]

def find_complete_lines(Field):
    complete_lines = 0
    for r in range(righe):
        complete_row = 0
        for c in range(colonne):
            complete_row += 1 if Field[r][c] != 0 and Field[r][c] < 8 else 0
        if complete_row == colonne:
            delete_line(Field, r)
            complete_lines += 1
    
    return complete_lines

def reverse_n_lines(Field, n):
    for r in range(righe-n, righe):
        for c in range(colonne):
            if Field[r][c] == 0:
                Field[r][c] = 7
            else:
                Field[r][c] = 0

def find_positionY(Field, Tetromino):
    auy = 0
    collision = False
    for y in range(righe):
        for r in range(3, -1, -1):
            for c in range(4):
                if positionX + c < colonne and y + auy >= 0 and Field[y + auy][positionX + c] < 8 and Field[y + auy][positionX + c] > 0 and Tetromino[r][c] != 0:
                        collision = True
            auy -= 1
        if collision:
            return y - 1
        else:
            auy = 0
    
    return righe - 1

def adjust_positionX(Tetromino):
    out = 0
    for c in range(3, -1, -1):
        z = 0
        for r in range(4):
            if Tetromino[r][c] == 0:
                z += 1
        if z == 4:
            out += 1
    
    return (colonne - 4 + out)

def addTetromino(Field, Tetromino):
    y = 0
    collision = False
    off_the_field = False
    global positionX

    positionY = find_positionY(Field, Tetromino)

    for r in range(3, -1, -1):
        for c in range(4):
            if positionX + c >= colonne and Tetromino[r][c] != 0:
                off_the_field = True
                positionX = adjust_positionX(Tetromino)
            elif positionX < 0:
                off_the_field = True
                positionX = 0
            elif positionX + c < colonne and positionY + y >= 0 and Field[positionY + y][positionX + c] != 0 and Field[positionY + y][positionX + c ] < 8 and Tetromino[r][c] != 0:
                collision = True
        y -= 1
    
    y = 0

    if (not collision) and (not off_the_field):
        save_or_not_tetromino(Field, False)
        for r in range(3, -1, -1):
            for c in range(4):
                if Tetromino[r][c] != 0 and ((positionY + y) * colonne + positionX + c) >= 0 and ((positionY + y) * colonne + positionX + c) < colonne * righe:
                    Field[positionY + y][positionX + c] = Tetromino[r][c] + 7
            y -= 1

def rotateTetromino(Tetromino):
    for r in range(4):
        for c in range(r , 4):
            tmp = Tetromino[r][c]
            Tetromino[r][c] = Tetromino[c][r]
            Tetromino[c][r] = tmp
    
    for r in range(4):
        for c in range(2):
            tmp = Tetromino[r][c]
            Tetromino[r][c] = Tetromino[r][4-1-c]
            Tetromino[r][4-1-c] = tmp

    tmp = 0

    while True:
        for c in range(4):
            if Tetromino[4-1][c] == 0:
                tmp += 1
        
        if tmp == 4:
            tmp = 0
            for r in range(3, -1, -1):
                for c in range(4):
                    Tetromino[r][c] = Tetromino[r-1][c]
            for c in range(4):
                Tetromino[0][c] = 0
        else:
            break

def SCORE(righe):
    if righe == 1:
        return 1
    elif righe == 2:
        return 3
    elif righe == 3:
        return 6
    elif righe == 4:
        return 12
    else:
        return 0

def KeyPressed(c, Field, Tetromino, numTetrominoes):
    global positionX
    global isGameOver
    global IndexTetromino
    global player
    global esc
    if c == ord('a') or c == curses.KEY_LEFT:
        positionX -= 1
    elif c == ord('d') or c == curses.KEY_RIGHT:
        positionX += 1
    elif c == ord('r'):
        if adjust_positionX(Tetromino[IndexTetromino]) == positionX:
            rotateTetromino(Tetromino[IndexTetromino])
            positionX = adjust_positionX(Tetromino[IndexTetromino])
        else:
            rotateTetromino(Tetromino[IndexTetromino])
    elif c == ord('c'):
        IndexCopy = IndexTetromino
        if IndexTetromino == 6:
            IndexTetromino = 0
        else:
            IndexTetromino += 1
        if adjust_positionX(Tetromino[IndexCopy]) == positionX:
            positionX = adjust_positionX(Tetromino[IndexTetromino])
    elif c == ord(' ') and numTetrominoes[IndexTetromino] > 0:
        save_or_not_tetromino(Field, True)
        numTetrominoes[IndexTetromino] -= 1
        if GameMode:
            player = not player
    elif c == ord('q'):
        isGameOver = True
        esc = True

def menu():
    global GameMode
    print(" _  _     ____  ____  ____  ____  __  ____")
    print("( \\/ )___(_  _)(  __)(_  _)(  _ \\(  )/ ___)")
    print(" )  ((___) )(   ) _)   )(   )   / )( \\___ \\")
    print("(_/\\_)    (__) (____) (__) (__\\_)(__)(____/")

    print("Premi 0 per single player e 1 per multi player.")
    sup = int(input("> "))
    GameMode = True if sup == 1 else False

def main():
    menu()
    Field_1 = [0] * righe
    Field_2 = [0] * righe
    for i in range (righe):
        Field_1[i] = [0] * colonne
        Field_2[i] = [0] * colonne

    Tetromino = {
    0: [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [1, 1, 1, 1]], # I
    1: [[0, 0, 0, 0], [0, 0, 0, 0], [2, 2, 0, 0], [2, 2, 0, 0]], # O
    2: [[0, 0, 0, 0], [0, 0, 0, 0], [3, 0, 0, 0], [3, 3, 3, 0]], # J
    3: [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 4, 0], [4, 4, 4, 0]], # L
    4: [[0, 0, 0, 0], [0, 0, 0, 0], [0, 5, 5, 0], [5, 5, 0, 0]], # S
    5: [[0, 0, 0, 0], [0, 0, 0, 0], [0, 6, 0, 0], [6, 6, 6, 0]], # T
    6: [[0, 0, 0, 0], [0, 0, 0, 0], [7, 7, 0, 0], [0, 7, 7, 0]]  # Z
    }

    numTetromino = 20

    numTetrominoes = [numTetromino, numTetromino, numTetromino, numTetromino, numTetromino, numTetromino, numTetromino]
    score_1 = 0
    score_2 = 0

    stdscr = curses.initscr()
    stdscr.keypad(True)
    stdscr.nodelay(True)

    while(not isGameOver):
        c = stdscr.getch()
        if player:
            KeyPressed(c, Field_1, Tetromino, numTetrominoes)
        else:
            KeyPressed(c, Field_2, Tetromino, numTetrominoes)

        ISGAMEOVER(Field_1, numTetrominoes)
        ISGAMEOVER(Field_2, numTetrominoes)
        if GameMode:
            complete_lines = find_complete_lines(Field_1)
            score_1 += SCORE(complete_lines)
            if complete_lines > 2:
                reverse_n_lines(Field_2, complete_lines)
            
            complete_lines = find_complete_lines(Field_2)
            score_2 += SCORE(complete_lines)
            if complete_lines > 2:
                reverse_n_lines(Field_1, complete_lines)
            
            if player:
                addTetromino(Field_1, Tetromino[IndexTetromino])
            else:
                addTetromino(Field_2, Tetromino[IndexTetromino])
            
            draw_fields(Field_1, Field_2, Tetromino[IndexTetromino], numTetrominoes, score_1, score_2)
        else:
            complete_lines = find_complete_lines(Field_1)
            score_1 += SCORE(complete_lines)
            addTetromino(Field_1, Tetromino[IndexTetromino])
            draw_field(Field_1, Tetromino[IndexTetromino], numTetrominoes, score_1)        
        stdscr.nodelay(False)

    if not esc:
        if win:
            if GameMode:
                if score_1 > score_2:
                    print("Player 1 wins!")
                elif score_1 < score_2:
                    print("Player 2 wins!")
                else:
                    print("No winner!")
            else:
                print("You won!")
        else:
            if GameMode:
                j = True
                for i in range(colonne):
                    if Field_1[0][i] != 0:
                        j = False
                if not j:
                    print("Player 1 loses and Player 2 wins!")
                else:
                    print("Player 2 loses and Player 1 wins!")
            else:
                print("you lost!!!")
        stdscr.getch()
        curses.endwin()
    else:
        curses.endwin()
        print("The game was closed.")

if __name__ == "__main__":
    main()
