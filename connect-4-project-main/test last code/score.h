/*typedef struct
{
    int score;
    int moves;
    _Bool identifier;
} playerData;
*/
int countHorizontally (int ROW,int COL,char gridarr[ROW][COL],_Bool counted, int i, int j)
{
    int sum = 0;
    if (j-3>=0)
    {
        if ((gridarr[i][j-3] + gridarr[i][j-2] + gridarr[i][j-1] + gridarr[i][j]) == counted * 4 )
        {
            sum++;
        }
    }
    if (j-2>=0 && j+1<COL)
    {
        if ((gridarr[i][j-2] + gridarr[i][j-1] + gridarr[i][j] +  gridarr[i][j+1]) == counted * 4)
        {
            sum++;
        }
    }
    if (j-1>=0 && j+2<COL)
    {
        if ((gridarr[i][j-1] + gridarr[i][j] +  gridarr[i][j+1] + gridarr[i][j+2]) == counted * 4)
        {
            sum++;
        }
    }
    if (j+3<COL)
    {
        if ((gridarr[i][j] +  gridarr[i][j+1] + gridarr[i][j+2] + gridarr[i][j+3]) == counted * 4)
        {
            sum++;
        }
    }
    return sum;
}

//replace the number 9 with the hight variable of the grid
int countVertically(int ROW,int COL,char gridarr[ROW][COL],_Bool counted,int i, int j)
{
    if (i+3<ROW)
    {
        return (gridarr[i][j] + gridarr[i+1][j] + gridarr[i+2][j] + gridarr[i+3][j] == counted * 4);
    }
    else
    {
        return 0;
    }
}

int countDiagonally(int ROW,int COL,char gridarr[ROW][COL],_Bool counted, int i, int j)
{
    int sum = 0;
    //checks the main diagonal
    if (i-3>=0 && j+3<COL)
    {
        if (gridarr[i][j] + gridarr[i-1][j+1] + gridarr[i-2][j+2] + gridarr[i-3][j+3] == counted * 4)
        {
            sum++;
        }
    }
    if (i+1<ROW && i-2>=0 && j-1>=0 && j+2 <COL)
    {
        if (gridarr[i+1][j-1] + gridarr[i][j] + gridarr[i-1][j+1] + gridarr[i-2][j+2] == counted * 4)
        {
            sum++;
        }
    }
    if (i-1>=0 && i+2<ROW && j-2 >=0 && j+1<COL)
    {
        if (gridarr[i+2][j-2] + gridarr[i+1][j-1] + gridarr[i][j] + gridarr[i-1][j+1] == counted * 4)
        {
            sum++;
        }
    }
    if (i+3 < ROW && j-3 >=0)
    {
        if (gridarr[i+3][j-3] + gridarr[i+2][j-2] + gridarr[i+1][j-1] + gridarr[i][j] == counted * 4)
        {
            sum++;
        }
    }
    //checks the other diagonal
    if (i-3>=0 && j-3>=0)
    {
        if (gridarr[i][j] + gridarr[i-1][j-1] + gridarr[i-2][j-2] + gridarr[i-3][j-3] == counted * 4)
        {
            sum++;
        }
    }
    if (i+1<ROW && i-2>=0 && j+1<COL && j-2 >=0)
    {
        if (gridarr[i+1][j+1] + gridarr[i][j] + gridarr[i-1][j-1] + gridarr[i-2][j-2] == counted * 4)
        {
            sum++;
        }
    }
    if (i-1>=0 && i+2<ROW && j+2<COL && j-1>=0)
    {
        if (gridarr[i+2][j+2] + gridarr[i+1][j+1] + gridarr[i][j] + gridarr[i-1][j-1] == counted * 4)
        {
            sum++;
        }
    }
    if (i+3 < ROW && j+3 < COL)
    {
        if (gridarr[i+3][j+3] + gridarr[i+2][j+2] + gridarr[i+1][j+1] + gridarr[i][j] == counted * 4)
        {
            sum++;
        }
    }
    return sum;
}

void updateScore(int ROW,int COL,char gridarr[ROW][COL],playerData *player, int i, int j)
{
    player->score += countHorizontally(ROW,COL,gridarr,player->identifier,i,j) + countVertically(ROW,COL,gridarr,player->identifier,i,j) + countDiagonally(ROW,COL,gridarr,player->identifier,i,j);
}
