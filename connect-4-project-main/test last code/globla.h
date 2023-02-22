int ii;
typedef struct
{
    char name[100];
    int score;
    int moves;

} winner_players ;
winner_players  *rank;


typedef struct
{

    int score;
    int moves;
    _Bool identifier;
} playerData;
typedef struct
{
    int i;
    int j;
    playerData movingPlayer;
} gameInfo;

playerData player1 = {0,0,0};
playerData player2 = {0,0,1};

int lastMove;
int choose;
int moves;

_Bool inLoadedGame = 0;
_Bool inVsComputer = 0;

_Bool playerIdentifer=0;

char figures[2] = {'x','o'};

