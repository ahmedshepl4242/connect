void updateUndoList (int ROW,int COL,char gridarr[ROW][COL],playerData playerMoved, int i, int j, int moveNumber,gameInfo undoList[])
{
    undoList[moveNumber].i = i;
    undoList[moveNumber].j = j;
    undoList[moveNumber+2].movingPlayer = playerMoved;
}

void undo (int ROW, int COL, char gridarr[ROW][COL],int *move, gameInfo undoList[])
{
    gridarr[(undoList[*move-1]).i][(undoList[*move-1]).j] = '-';
    playerData *movedPlayer;
    if (undoList[*move-1].movingPlayer.identifier == player1.identifier)
    {
        movedPlayer = &player1;
        (*movedPlayer).moves = undoList[(*move)-1].movingPlayer.moves;
        (*movedPlayer).score = undoList[(*move)-1].movingPlayer.score;
    }
    else if (undoList[*move-1].movingPlayer.identifier == player2.identifier)
    {
        movedPlayer = &player2;
        (*movedPlayer).moves = undoList[(*move)-1].movingPlayer.moves;
        (*movedPlayer).score = undoList[(*move)-1].movingPlayer.score;
    }
    *move=*move - 1;
}

void redo (int ROW,int COL,char gridarr[ROW][COL],int *move, gameInfo undoList[])
{
    gridarr[undoList[*move].i][undoList[*move].j] = undoList[*move].movingPlayer.identifier;
    playerData *movedPlayer;
    if (undoList[*move].movingPlayer.identifier == player1.identifier)
    {
        movedPlayer = &player1;
        (*movedPlayer).moves = undoList[*move+2].movingPlayer.moves;
        (*movedPlayer).score = undoList[*move+2].movingPlayer.score;
    }
    else if (undoList[*move].movingPlayer.identifier == player2.identifier)
    {
        movedPlayer = &player2;
        (*movedPlayer).moves = undoList[*move+2].movingPlayer.moves;
        (*movedPlayer).score = undoList[*move+2].movingPlayer.score;
    }
    *move = *move + 1;
}
