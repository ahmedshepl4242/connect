void playComputerMode(int ROW,int COL,char gridarr[ROW][COL],int *moves,_Bool *identify, gameInfo undoList[])
{
    int enteredColumn;
    //clear console and update it with previous action
    system("cls");
    print(ROW, COL,gridarr);

    //decide which player is about to play
    *identify = ((*moves)%2);

    if (*identify==0) {
       printf("\n\tplayer %d your turn now :\n\t",*identify+1);
   while(1)
    {
        int check_char;
        beging:

         check_char=scanf("%d",&enteredColumn);
         if(check_char!=1){
         gets(&enteredColumn);

          printf("enter valid columns between 0:%d:\n",COL);


         }

         else if(!(enteredColumn>=0&&enteredColumn<=COL)){
            printf("enter valid columns between 0:%d:\n",COL);
            goto beging;

         }
         else{

            break;
         }


    }
    }

    else {
        srand(time(0));
        enteredColumn = (rand()%COL)+1;
        if (gridarr[0][enteredColumn-1]!='-') {
            int i = 0;
            while (gridarr[0][(i+enteredColumn-1)%COL]!='-') i++;
            enteredColumn = ((i+enteredColumn-1)%COL) +1;
        }
    }

    if (enteredColumn==0)
    {
        chooseMenu(ROW,COL,gridarr,enteredColumn,undoList);
        return;
    }

    while(gridarr[0][enteredColumn-1]!='-')
    {
        printf("column  is full \n please enter another column:\n");

        while(1)
        {
            int check_char;
        newstart:

         check_char=scanf("%d",&enteredColumn);
         if(check_char!=1){
         gets(&enteredColumn);

          printf("enter valid columns \n");

         }

         else if(!(enteredColumn>0&&enteredColumn<=COL)){
            printf("enter valid columns \n");
            goto newstart;
         }
         else{

            break;
         }
    }
    }

    putDisk(ROW, COL,gridarr,enteredColumn-1,identify,moves,undoList);
    int *lastMovePlayed = &lastMove;
    *lastMovePlayed = *moves;
}

void undoComputerMode (int ROW, int COL, char gridarr[ROW][COL],int *move, gameInfo undoList[]) {
    gridarr[(undoList[*move-1]).i][(undoList[*move-1]).j] = '-';
    gridarr[(undoList[*move-2]).i][(undoList[*move-2]).j] = '-';
    playerData *movedPlayer;

    movedPlayer = &player1;
    (*movedPlayer).moves = undoList[(*move)-2].movingPlayer.moves;
    (*movedPlayer).score = undoList[(*move)-2].movingPlayer.score;

    movedPlayer = &player2;
    (*movedPlayer).moves = undoList[(*move)-1].movingPlayer.moves;
    (*movedPlayer).score = undoList[(*move)-1].movingPlayer.score;

    *move=*move - 2;
}

void redoComputerMode (int ROW, int COL, char gridarr[ROW][COL],int *move, gameInfo undoList[]) {
    gridarr[undoList[*move].i][undoList[*move].j] = undoList[*move].movingPlayer.identifier;
    gridarr[undoList[*move+1].i][undoList[*move+1].j] = undoList[*move+1].movingPlayer.identifier;
    playerData *movedPlayer;

    movedPlayer = &player1;
    (*movedPlayer).moves = undoList[*move+2].movingPlayer.moves;
    (*movedPlayer).score = undoList[*move+2].movingPlayer.score;

    movedPlayer = &player2;
    (*movedPlayer).moves = undoList[*move+3].movingPlayer.moves;
    (*movedPlayer).score = undoList[*move+3].movingPlayer.score;

    *move = *move + 2;
}

void new_game_vs_computer(int ROW,int COL,char gridarr[ROW][COL],gameInfo undoList[])
{
    lastMove=0;
    moves=0;
    original_grid(ROW, COL,gridarr);
    player1.moves = 0;
    player1.score = 0;
    player2.moves = 0;
    player2.score = 0;
    start_time = clock();
    playComputerMode(ROW,COL,gridarr,&moves,&playerIdentifer,undoList);                     //here
}
void load_player_computer_mode(int ROW,int COL,char gridarr[ROW][COL], gameInfo undoList[], int high_score)
{

    while(1)
    {

        if((player1.moves+player2.moves)==(COL*ROW))
        {
            system("cls");
            print(ROW, COL,gridarr);
            printf("game end\n");
            //deleted xx = 1 and replaced first parameter with 1 instead of xx
            top_rank(1,player1.score,player2.score,high_score);
            printf("    1->main.\n");
            printf("    2->exit.\n");
            while(1)
        {
            int check_char;
        beging:

         check_char=scanf("%d",&choose);
         if(check_char!=1){
         gets(&choose);

          printf("enter valid columns between 1:2:\n");

         }

         else if(!(choose>0&&choose<=2)){
            printf("enter valid columns between 1:2:\n");
            goto beging;

         }
         else{

            break;
         }
    }

            if(choose==1)
            {
                main_manu(ROW,COL,gridarr);
                return;
            }
            else if(choose==2)
            {
                return;
            }
        }
        playComputerMode(ROW,COL,gridarr,&moves,&playerIdentifer,undoList);
    }

}
