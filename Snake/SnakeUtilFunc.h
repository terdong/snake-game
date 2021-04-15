enum {
    BLACK,
    D_BLUE,
    D_GREEN,
    D_SKYBLUE,
    D_RED,
    D_VIOLET,
    D_YELLOW,
    GRAY,
    D_GRAY,
    BLUE,
    GREEN,
    SKYBLUE,
    RED,
    VIOLET,
    YELLOW,
    WHITE,
};

int SetScreenBuf(int width, int height);
int SetWindowSize(int width, int height);
void SetCursor(bool bVisible);
int GetBufferSizeX();
int GetBufferSizeY();
void SetColor(int color , int bgcolor );
void setPos(int x, int y);
COORD getPos();