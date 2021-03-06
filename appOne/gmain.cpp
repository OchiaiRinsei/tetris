#define _EX
#ifdef _EX
#include"libOne.h"
const int INIT = 0;
const int PLAY = 1;
const int OVER = 2;
int GameState = INIT;
float Size = 50;
const int ROWS = 20;
const int COLS = 12;
float Satu = 255;
float Value = 255;
float Alpha = 255;
int FallFlag = 0;
int Point = 0;
struct COLOR Color[9] = {
    COLOR(0,Satu,Value,Alpha),
    COLOR(30,Satu,Value,Alpha),
    COLOR(60,Satu,Value,Alpha),
    COLOR(120,Satu,Value,Alpha),
    COLOR(180,Satu,Value,Alpha),
    COLOR(240,Satu,Value,Alpha),
    COLOR(300,Satu,Value,Alpha),
    COLOR(200,44,88,Alpha),
    COLOR(0,0,20,Alpha),
};
const int WALL = 7;
const int BACK = 8;
int Stage[ROWS][COLS];
int X, Y, R;
int Px[4], Py[4];
int PtnNo = 0;
int Ptn[7][3][2] = {
    //????????...0
    -1,0,   1,0,  2,0,
    //??
    //??????....1
    -1,-1, -1,0,  1,0,
    //  ?@??
    //??????....2
    -1,0,   1,-1, 1,0,
    //????
    //?@????....3
    -1,0,   0,1,  1,1,
    //?@????
    //????  ....4
     1,0,   0,1, -1,1,
     //?@??
     //??????....5
     -1,0,   0,-1, 1,0,
     //????
     //????......6
      1,0,   0,1,  1,1,
};
int LoopCnt = 0;
void init() {
    for (int y = 0; y < ROWS; y++) {
        Stage[y][0] = WALL;
        Stage[y][COLS-1] = WALL;
        for (int x = 1; x < COLS-1; x++) {
            Stage[y][x] = BACK;
            if (y == ROWS - 1) {
                Stage[y][x] = WALL;
            }
        }
    }
    X = 5;
    Y = 1;
    R = 0;
    PtnNo = random() % 7;
    GameState = PLAY;
}
void drawStage() {
    colorMode(HSV);
    angleMode(DEGREES);
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            int no = Stage[y][x];
            fill(Color[no]);
            rect(Size * x, Size * y, Size, Size);
        }
    }
}
void setPosition() {
    Px[0] = X;
    Py[0] = Y;
    int r = R % 4;
    for (int i = 0; i < 3; i++) {
        int x = Ptn[PtnNo][i][0];
        int y = Ptn[PtnNo][i][1];
        for (int j = 0; j < r; j++) {
            int w = x;
            x = y;
            y = -w;
        }
        Px[i + 1] = X + x;
        Py[i + 1] = Y + y;
    }
}
void setPtn() {
    setPosition();
    for (int i = 0; i < 4; i++) {
        int x = Px[i];
        int y = Py[i];
        Stage[y][x] = PtnNo;
    }
}
void delPtn() {
    setPosition();
    for (int i = 0; i < 4; i++) {
        int x = Px[i];
        int y = Py[i];
        Stage[y][x] = BACK;
    }
}
int collision() {
    setPosition();
    int flag = 0;
    for (int i = 0; i < 4; i++) {
        int x = Px[i];
        int y = Py[i];
        if (Stage[y][x] != BACK) {
            flag = 1;
        }
    }
    return flag;
}
void complete() {
    for (int y = 1; y < ROWS - 1; y++) {
        int flag = 1;
        for (int x = 1; x < COLS - 1; x++) {
            if (Stage[y][x] == BACK) {
                flag = 0;
            }
        }
        if (flag) {
            for (int upy = y - 1; upy > 0; upy--) {
                for (int x = 1; x < COLS - 1; x++) {
                    Stage[upy+1][x] = Stage[upy][x];
                }
            }
            Point++;
        }
    }

}
void play() {
    //Stage[Y][X] = BACK;
    delPtn();
    int dy = 0, dx = 0,dr=0;
    int DPp = 0;
    if ((++LoopCnt %= 10) == 0)dy = 1;
    if (isTrigger(KEY_D))dx = 1;
    if (isTrigger(KEY_A))dx = -1;
    if (isTrigger(KEY_SPACE))dr = 1;
    if (isTrigger(KEY_S))FallFlag = 1;
    if (FallFlag)dy = 1;
    Y += dy;
    X += dx;
    R += dr;
    //if (State[Y][X] != BACK){
    if (collision()) {
        Y -= dy;
        X -= dx;
        R -= dr;
        FallFlag = 0;
        if (dy == 1 && dx == 0 && dr == 0) {
            //Stage[Y][X] = PtnNo;
            setPtn();
            complete();
            //?V?????u???b?N
            Y = 1;
            X = 5;
            R = 0;
            PtnNo=random() % 7;
            if (collision()) {
                GameState = OVER;
            }
        }
    }
    //Stage[Y][X] = PtnNo;
    setPtn();
    clear(0);
    drawStage();
}
void over() {
    clear(0);
    drawStage();
    textSize(Size);
    fill(0, 0, 255);
    text("?l????", Size * 2, Size);
    text((let)"???_?@= "+Point, Size * 6, Size);
    if (isTrigger(KEY_C)) {
        GameState = INIT;
    }
}
void gmain() {
    window(Size * COLS, Size * ROWS);
    while (notQuit) {
        if (GameState == INIT)init();
        else if (GameState == PLAY)play();
        else if (GameState == OVER)over();

    }
}
#endif



#ifdef _SAMPLE2
#include"libOne.h"
//?O???ϐ?------------------------------------------------------------
//?V?[?P???X
const int INIT = 0;
const int PLAY = 1;
const int OVER = 2;
int GameState = INIT;
//?F?f?[?^
float Satu = 200;
float Value = 255;
float Alpha = 255;
struct COLOR Color[9] = {
    COLOR(0,Satu,Value,Alpha),
    COLOR(30,Satu,Value,Alpha),
    COLOR(60,Satu,Value,Alpha),
    COLOR(120,Satu,Value,Alpha),
    COLOR(180,Satu,Value,Alpha),
    COLOR(220,Satu,Value,Alpha),
    COLOR(300,Satu,Value,Alpha),
    COLOR(200,44,88,Alpha),
    COLOR(0,0,20,Alpha),
};
//?ǂƔw?i?̐F?ԍ?
const int WALL = 7;
const int BACK = 8;
//?X?e?[?W?i?F?ԍ????L???????j
const int ROWS = 20;
const int COLS = 12;
int Stage[ROWS][COLS];
float Size = 50;
//??u???b?N?ʒu?Ɖ??]??
int X, Y, R;
//?u???b?N?p?^?[???̈ʒu
int Px[4], Py[4];
//?u???b?N?ړ?????
int FallFlag = 0;
int LoopCnt = 0;
//?u???b?N?p?^?[???ԍ?  ?? ???F?ԍ? ??
int PtnNo;
//?u???b?N?p?^?[???I?t?Z?b?g
int PtnOffsets[7][3][2] = {
    //????????...0
    -1,0,   1,0,  2,0,
    //??
    //??????....1
    -1,-1, -1,0,  1,0,
    //  ?@??
    //??????....2
    -1,0,   1,-1, 1,0,
    //????
    //?@????....3
    -1,0,   0,1,  1,1,
    //?@????
    //????  ....4
     1,0,   0,1, -1,1,
    //?@??
    //??????....5
    -1,0,   0,-1, 1,0,
    //????
    //????......6
     1,0,   0,1,  1,1,
};

//?֐?----------------------------------------------------------------
void setPtnPosition();

void init() {
    //?ǂƔw?i?̐F?ԍ???Stage2?????z???ɃZ?b?g
    for (int y = 0; y < ROWS; y++) {
        Stage[y][0] = Stage[y][COLS - 1] = WALL;
        for (int x = 1; x < COLS-1; x++) {
            Stage[y][x] = BACK;
            if (y == ROWS - 1) {
                Stage[y][x] = WALL;
            }
        }
    }
    //?u???b?N?????l
    X = 5;
    Y = 1;
    R = 0;
    PtnNo = random() % 7;
    setPtnPosition();
    //???̃V?[?P???X
    GameState = PLAY;
}

void drawStage() {
    angleMode(DEGREES);
    colorMode(HSV);
    strokeWeight(20);
    rectMode(CENTER);
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            int no = Stage[y][x];
            stroke(Color[no]);
            fill(0, 0, 100);
            rect(Size/2+Size * x, Size/2+Size * y, Size/2, Size/2);
        }
    }
}
void setPtnPosition() {
    //??u???b?N?ʒu
    Px[0] = X;
    Py[0] = Y;
    //???]??
    int r = R % 4;
    for (int i = 0; i < 3; i++) {
        //???݂̃u???b?N?p?^?[???̃I?t?Z?b?g?l???擾
        int ofsX = PtnOffsets[PtnNo][i][0];
        int ofsY = PtnOffsets[PtnNo][i][1];
        //???]???ɉ????ĂX?O?x?????]??????
        for (int j = 0; j < r; j++) {
            int w = ofsX;
            ofsX = -ofsY;
            ofsY = w;
        }
        //?ʒu????
        Px[i + 1] = X + ofsX;
        Py[i + 1] = Y + ofsY;
    }
}
void setPtnNoToStage() {
    setPtnPosition();
    for (int i = 0; i < 4; i++) {
        int x = Px[i];
        int y = Py[i];
        Stage[y][x] = PtnNo;
    }
}
void delPtnNoFromStage() {
    for (int i = 0; i < 4; i++) {
        int x = Px[i];
        int y = Py[i];
        Stage[y][x] = BACK;
    }
}
int collision() {
    setPtnPosition();
    int flag = 0;
    for (int i = 0; i < 4; i++) {
        int x = Px[i];
        int y = Py[i];
        if (Stage[y][x] != BACK) {
            flag = 1;
        }
    }
    return flag;
}
void complete() {
    for (int y = 1; y < ROWS - 1; y++) {
        int flag = 1;
        for (int x = 1; x < COLS - 1; x++) {
            if (Stage[y][x] == BACK) {
                flag = 0;
            }
        }
        if (flag) {
            //?????????̂ŃX???C?h
            for (int upy = y - 1; upy >= 0; upy--) {
                for (int x = 1; x < COLS - 1; x++) {
                    Stage[upy + 1][x] = Stage[upy][x];
                }
            }
        }
    }
}
void play() {
    //???݂̃p?^?[???ԍ??i?F?ԍ??j???X?e?[?W????????
    delPtnNoFromStage();
    //?ړ??A???]
    int dy = 0, dx = 0, dr = 0;;
    if ((++LoopCnt %= 15) == 0)dy = 1;
    if (isTrigger(KEY_D))dx = 1;
    if (isTrigger(KEY_A))dx = -1;
    if (isTrigger(KEY_W))dr = 1;
    if (isTrigger(KEY_S))FallFlag = 1;
    if (FallFlag)dy = 1;
    Y += dy;
    X += dx;
    R += dr;
    if (collision()) {
        //???̈ʒu?A???]?ɖ߂?
        Y -= dy;
        X -= dx;
        R -= dr;
        FallFlag = 0;
        if (dy == 1 && dx == 0 && dr == 0) {
            //?ς??点??
            setPtnNoToStage();
            //?s?????????Ă??????X???C?h??????
            complete();
            //?V?????u???b?N?a??
            X = 5;
            Y = 1;
            R = 0;
            PtnNo = random() % 7;
            if (collision()) {
                GameState = OVER;
            }
        }
    }
    //?p?^?[???ԍ??i?F?ԍ??j???X?e?[?W?ɃZ?b?g
    setPtnNoToStage();

    //?`??
    clear(0);
    drawStage();
}

void over() {
    clear(0);
    drawStage();
    //?Q?[???I?[?o?[?e?L?X?g
    fill(0, 0, 255);
    textSize(Size);
    text("?f???????n??????", (width - Size * 8) / 2, Size);
    if (isTrigger(KEY_SPACE)) {
        GameState = INIT;
    }
}

void gmain() {
    window(Size * COLS, Size * ROWS);
    while (notQuit) {
        if      (GameState == INIT)init();
        else if (GameState == PLAY)play();
        else if (GameState == OVER)over();
    }
}


#endif

#ifdef _SAMPLE1
#include"libOne.h"
//?O???ϐ?------------------------------------------------------------
//?V?[?P???X
const int INIT = 0;
const int PLAY = 1;
const int OVER = 2;
int GameState = INIT;
//?F?f?[?^
float Satu = 200;
float Value = 255;
float Alpha = 255;
struct COLOR Color[9] = {
    COLOR(0,Satu,Value,Alpha),
    COLOR(30,Satu,Value,Alpha),
    COLOR(60,Satu,Value,Alpha),
    COLOR(120,Satu,Value,Alpha),
    COLOR(180,Satu,Value,Alpha),
    COLOR(220,Satu,Value,Alpha),
    COLOR(300,Satu,Value,Alpha),
    COLOR(200,44,88,Alpha),
    COLOR(0,0,20,Alpha),
};
//?ǂƔw?i?̐F?ԍ?
const int WALL = 7;
const int BACK = 8;
//?X?e?[?W?i?F?ԍ????L???????j
const int ROWS = 20;
const int COLS = 12;
int Stage[ROWS][COLS];
float Size = 50;
//??u???b?N?ʒu?Ɖ??]??
int R;
//?u???b?N?p?^?[???̈ʒu
int Px[4], Py[4];
//?u???b?N?ړ?????
int FallFlag = 0;
int LoopCnt = 0;
//?u???b?N?p?^?[???ԍ?  ?? ???F?ԍ? ??
int PtnNo;
//?u???b?N?p?^?[???I?t?Z?b?g
int PtnOffsets[7][3][2] = {
    //????????...0
    -1,0,   1,0,  2,0,
    //??
    //??????....1
    -1,-1, -1,0,  1,0,
    //  ?@??
    //??????....2
    -1,0,   1,-1, 1,0,
    //????
    //?@????....3
    -1,0,   0,1,  1,1,
    //?@????
    //????  ....4
     1,0,   0,1, -1,1,
     //?@??
     //??????....5
     -1,0,   0,-1, 1,0,
     //????
     //????......6
      1,0,   0,1,  1,1,
};

//?֐?----------------------------------------------------------------
void init() {
    //?ǂƔw?i?̐F?ԍ???Stage2?????z???ɃZ?b?g
    for (int y = 0; y < ROWS; y++) {
        Stage[y][0] = Stage[y][COLS - 1] = WALL;
        for (int x = 1; x < COLS - 1; x++) {
            Stage[y][x] = BACK;
            if (y == ROWS - 1) {
                Stage[y][x] = WALL;
            }
        }
    }
    //?u???b?N?????l?i?͂??߂͂S?Ƃ??????ł悢?j
    for (int i = 0; i < 4; i++) {
        Px[i] = 5;
        Py[i] = 1;
    }
    R = 0;
    PtnNo = random() % 7;
    //???̃V?[?P???X
    GameState = PLAY;
}

void drawStage() {
    angleMode(DEGREES);
    colorMode(HSV);
    strokeWeight(20);
    rectMode(CENTER);
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            int no = Stage[y][x];
            stroke(Color[no]);
            fill(0, 0, 180);
            rect(Size / 2 + Size * x, Size / 2 + Size * y, Size / 2, Size / 2);
        }
    }
}
void setPtnPosition() {
    //???]??
    int r = R % 4;
    for (int i = 0; i < 3; i++) {
        //???݂̃u???b?N?p?^?[???̃I?t?Z?b?g?l???擾
        int ofsX = PtnOffsets[PtnNo][i][0];
        int ofsY = PtnOffsets[PtnNo][i][1];
        //???]???ɉ????ĂX?O?x?????]??????
        for (int j = 0; j < r && PtnNo != 6; j++) {
            int w = ofsX;
            ofsX = -ofsY;
            ofsY = w;
        }
        //?ʒu????
        Px[i + 1] = Px[0] + ofsX;
        Py[i + 1] = Py[0] + ofsY;
    }
}
void setPtnNoToStage() {
    setPtnPosition();
    for (int i = 0; i < 4; i++) {
        int x = Px[i];
        int y = Py[i];
        Stage[y][x] = PtnNo;
    }
}
void delPtnNoFromStage() {
    for (int i = 0; i < 4; i++) {
        int x = Px[i];
        int y = Py[i];
        Stage[y][x] = BACK;
    }
}
int collision() {
    setPtnPosition();
    int flag = 0;
    for (int i = 0; i < 4; i++) {
        int x = Px[i];
        int y = Py[i];
        if (Stage[y][x] != BACK) {
            flag = 1;
        }
    }
    return flag;
}
void complete() {
    for (int y = 1; y < ROWS - 1; y++) {
        //y?s????????????
        int flag = 1;
        for (int x = 1; x < COLS - 1; x++) {
            if (Stage[y][x] == BACK) {
                flag = 0;
            }
        }
        if (flag) {
            //?????????̂ŃX???C?h
            for (int upy = y - 1; upy >= 0; upy--) {
                for (int x = 1; x < COLS - 1; x++) {
                    Stage[upy + 1][x] = Stage[upy][x];
                }
            }
        }
    }
}
void play() {
    //???݂̃p?^?[???ԍ??i?F?ԍ??j???X?e?[?W????????
    delPtnNoFromStage();
    //?ړ??A???]
    int dy = 0, dx = 0, dr = 0;;
    if ((++LoopCnt %= 15) == 0)dy = 1;
    if (isTrigger(KEY_D))dx = 1;
    if (isTrigger(KEY_A))dx = -1;
    if (isTrigger(KEY_W))dr = 1;
    if (isTrigger(KEY_S))FallFlag = 1;
    if (FallFlag)dy = 1;
    Px[0] += dx;
    Py[0] += dy;
    R += dr;
    if (collision()) {
        //???̈ʒu?A???]?ɖ߂?
        Px[0] -= dx;
        Py[0] -= dy;
        R -= dr;
        FallFlag = 0;
        if (dy == 1 && dx == 0 && dr == 0) {
            //?ς??点??
            setPtnNoToStage();
            //?s?????????Ă??????X???C?h??????
            complete();
            //?V?????u???b?N?a??
            Px[0] = 5;
            Py[0] = 1;
            R = 0;
            PtnNo = random() % 7;
            if (collision()) {
                GameState = OVER;
            }
        }
    }
    //?p?^?[???ԍ??i?F?ԍ??j???X?e?[?W?ɃZ?b?g
    setPtnNoToStage();

    //?`??
    clear(0);
    drawStage();
}

void over() {
    clear(0);
    drawStage();
    //?Q?[???I?[?o?[?e?L?X?g
    for (int x = 1; x < COLS - 1; x++)Stage[0][x] = BACK;
    fill(0, 0, 255);
    textSize(Size);
    text("?f???????n??????", (width - Size * 8) / 2, Size);
    if (isTrigger(KEY_SPACE)) {
        GameState = INIT;
    }
}

void gmain() {
    window(Size * COLS, Size * ROWS, full);
    ShowCursor(false);
    while (notQuit) {
        if (GameState == INIT)init();
        else if (GameState == PLAY)play();
        else if (GameState == OVER)over();
    }
    ShowCursor(true);
}
#endif
