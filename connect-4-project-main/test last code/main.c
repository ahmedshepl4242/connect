#include "global.h"
#include <stdio.h>
FILE *rank_file;
#include <sys/types.h>
#include "top_rank.h"
#include <stdlib.h>
#include <time.h>
time_t start_time;
#include "parseXML.h"
#include "load_save.h"
#include "score.h"
#include "vs_computer.h"
#include "undo.h"


void chooseMenu ( int ROW,int COL,char gridarr[ROW][COL],int enteredColumn,gameInfo undoList[])
{
    char  usrx;
     printMenu();
     fscanf(stdin," ");
     scanf("%c",&usrx);
     while((usrx!='u')&&(usrx!='r')&&(usrx!='s')&&(usrx!='x')){
        printf("---->enter valid charachter\n");
           scanf("%c",&usrx);
     }

    if ( usrx== 'u')
    {

        if (!inLoadedGame) {
          if (moves>0)
            {
                if (inVsComputer) {
                    undoComputerMode(ROW,COL,gridarr,&moves,undoList);
                }
                else {
                    undo(ROW,COL,gridarr,&moves,undoList);
                }
            }
        }
        else {
            if (moves>1) {
                if (inVsComputer) {
                    undoComputerMode(ROW,COL,gridarr,&moves,undoList);
                }
                else {
                    undo(ROW,COL,gridarr,&moves,undoList);
                }
            }
        }
    }
    else if ( usrx == 'r')
    {
        if (moves<lastMove)
        {
            redo(ROW,COL,gridarr,&moves,undoList);
        }
    }


    else if(usrx == 's')
    {

        save_game(ROW,COL,gridarr,player1,player2,undoList);
    }
    else if( usrx == 'x')
    {
        main_manu(ROW,COL,gridarr);
    }

}
void printMenu()
{
    printf("to undo press u\n");
    printf("to redo press r\n");
    printf("to save press s\n");
    printf("to exit prss x\n");
}


void display_time()
{

    int minutes;
    int timer;
    timer=(clock()-start_time)/1000;

    if(timer>59)
    {
        minutes=timer/60;
        timer=timer%60;
    }

    printf("\n\t%02d:%02d\n",minutes,timer);
}


void addMoves(playerData *player)
{
    (player->moves)++;
}


void original_grid(int ROW,int COL, char gridarr[ROW][COL])
{
    int j,i;
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            gridarr[i][j]='-';
        }
    }
}


void print(int ROW,int COL,char gridarr[ROW][COL])
{
    int j,i;
    for(i=1; i<=COL; i++)
    {

        printf("\t%d",i);
    }
    printf("\n" );


    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            if(gridarr[i][j]=='-')
            {
                if(i==0&&j==0)
                {
                    printf("\t%c\t",gridarr[i][j]);
                }
                else
                {
                    printf("%c\t",gridarr[i][j]);
                }
            }

            else
            {
                if(i==0&&j==0)
                {
                    if (gridarr[i][j]==0) {
                       printf("\033[0;31m");
                    }
                    else {
                        printf("\033[0;34m");
                    }
                    printf("\t%c\t",figures[(int)gridarr[i][j]]);
                    printf("\033[0m");
                }
                else
                {
                    if (gridarr[i][j]==0) {
                       printf("\033[0;31m");
                    }
                    else {
                        printf("\033[0;34m");
                    }
                    printf("%c\t",figures[(int)gridarr[i][j]]);
                    printf("\033[0m");
                }
            }
        }
        printf("\n\n\t" );
    }
    printf("Score of \033[0;31mplayer 1\033[0m:%d\n",player1.score);
    printf("\tmoves of \033[0;31mplayer 1\033[0m:%d\n",player1.moves);
    printf("\t-------------------------------------------\n");
    printf("\tScore of \033[0;34mplayer 2\033[0m:%d\n",player2.score);
    printf("\tmoves of \033[0;34mplayer 2\033[0m:%d\n",player2.moves);
    display_time();
}


void putDisk(int ROW,int COL,char gridarr[ROW][COL],int j,_Bool *identify,int *moves, gameInfo undoList[])
{
    int i = ROW -1;
    while(1)
    {
        if(gridarr[i][j]=='-')
        {
            if(*identify==0)
            {
                gridarr[i][j]=0;
                updateScore(ROW, COL,gridarr,&player1,i,j);
                addMoves(&player1);
                updateUndoList( ROW, COL,gridarr,player1,i,j,*moves,undoList);
                (*moves)++;
                break;
            }

            else if(*identify==1)
            {
                gridarr[i][j]=1;
                updateScore(ROW, COL,gridarr,&player2,i,j);
                addMoves(&player2);
                updateUndoList(ROW, COL,gridarr,player2,i,j,*moves,undoList);
                (*moves)++;
                break;
            }
        }
        else
        {
            i--;
        }
    }
}

void play(int ROW,int COL,char gridarr[ROW][COL],int *moves,_Bool *identify, gameInfo undoList[])
{
    int check_char;
    int enteredColumn;
    //clear console and update it with previous action
    system("cls");
    print(ROW, COL,gridarr);

    //decide which player is about to play
    *identify = ((*moves)%2);

    printf("\n\tplayer %d your turn now :\n\t",*identify+1);
   while(1)
    {
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
void new_game(int ROW,int COL,char gridarr[ROW][COL],gameInfo undoList[])
{
    lastMove=0;
    moves=0;
    original_grid(ROW, COL,gridarr);
    player1.moves = 0;
    player1.score = 0;
    player2.moves = 0;
    player2.score = 0;
    start_time = clock();

    play(ROW,COL,gridarr,&moves,&playerIdentifer,undoList);
}
void load_player(int ROW,int COL,char gridarr[ROW][COL], gameInfo undoList[], int high_score)
{
int check_char;
    while(1)
    {

        if((player1.moves+player2.moves)==(COL*ROW) && !(inVsComputer))
        {
            system("cls");
            print(ROW, COL,gridarr);
            printf("    game end\n");
            top_rank(1,player1.score,player2.score, high_score);

            top_rank(0,player1.score,player2.score,high_score);

            printf("    1->main.\n");
            printf("    2->exit.\n");
              while(1)
        {
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
        play(ROW,COL,gridarr,&moves,&playerIdentifer,undoList);
    }

}
void main_manu(int ROW,int COL,char gridarr[ROW][COL], int high_score)
{
    int return_value;
    gameInfo undoList[ROW*COL+2];
    //initializing undo list
    undoList[0].i=0;
    undoList[0].j=0;
    undoList[0].movingPlayer.identifier=0;
    undoList[0].movingPlayer.moves=0;
    undoList[0].movingPlayer.score=0;
    undoList[1].i=0;
    undoList[1].j=0;
    undoList[1].movingPlayer.identifier=1;
    undoList[1].movingPlayer.moves=0;
    undoList[1].movingPlayer.score=0;

    int choose_manu;

    printf("-------------------------MAIN MANU--------------------------\n");
    printf("    1->start a new game.\n");
    printf("    2->load a game last games.\n");
    printf("    3->Top players.\n");
    printf("    4->Quit\n");
    fscanf(stdin, " ");
    scanf("%d",&choose_manu);
    int check_char;
    while((choose_manu!=1)&&(choose_manu!=2)&&(choose_manu!=3)&&(choose_manu!=4))
    {

        printf("please enter number between 1:4\n");
              while(1)
    {
        beging:

         check_char=scanf("%d",&choose_manu);
         if(check_char!=1){
         gets(&choose_manu);

          printf("--->enter number between 1:4 :\n");


         }

         else if(!(choose_manu>0&&choose_manu<=4)){
            printf("---->enter  number between 1:4\n",COL);
            goto beging;

         }
         else{

            break;
         }
    }
    }

    if(choose_manu==1)
    {
        inLoadedGame = 0;
        //choosing mood
        char choose_mode;
        printf("\t----->enter 1 for human vs human mode\n");
        printf("\t----->enter 2 for human vs computer mode\n");
        fscanf(stdin, " ");
        scanf("%d",&choose_mode);
        while((choose_mode!=1)&&(choose_mode!=2))
    {

        printf("please enter number between 1:2\n");
              while(1)
    {
        restart:

         check_char=scanf("%d",&choose_mode);
         if(check_char!=1){
         gets(&choose_mode);

          printf("--->enter number between 1:2 :\n");


         }

         else if(!(choose_mode>0&&choose_mode<=4)){
            printf("---->enter  number between 1:2\n");
            goto restart;

         }
         else{

            break;
         }


    }


    }
        if (choose_mode==1) {
            inVsComputer = 0;
            new_game(ROW,COL,gridarr,undoList);
            load_player(ROW,COL,gridarr,undoList, high_score);
        }
        else {
            inVsComputer = 1;
            new_game_vs_computer(ROW,COL,gridarr,undoList);
            load_player_computer_mode(ROW,COL,gridarr,undoList,high_score);
        }
    }

    if(choose_manu==2)
    {


        return_value=load_game(ROW,COL,gridarr,undoList);
       if(return_value==0){
        if (inVsComputer) {
            load_player_computer_mode(ROW,COL,gridarr,undoList, high_score);
        }
        else {
            load_player(ROW,COL,gridarr,undoList, high_score);
        }


        return;
         }
        if(return_value==1){

             main_manu(ROW,COL,gridarr,high_score);
            return;
        }


    }
    if(choose_manu==3)
    {

       top_rank(0,player1.score,player2.score,high_score);
        printf("    1->main.\n");
        printf("    2->exit.\n");
        scanf("%d",&choose);

        while((choose!=1)&&(choose!=2))
    {

        printf("please enter number between 1:2\n");

              while(1)
    {
        start:

         check_char=scanf("%d",&choose);
         if(check_char!=1){
         gets(&choose);

          printf("--->enter number between 1:2 :\n");


         }

         else if(!(choose>0&&choose<=2)){
            printf("---->enter  number between 1:2\n");
            goto start;

         }
         else{

            break;
         }


    }


    }

         if(choose==1)
            {
                main_manu(ROW,COL,gridarr,high_score);
                return;
            }
            else if(choose==2)
            {
                return;
            }


    }
    if(choose_manu==4)
    {
        exit(0);
    }

  return;


}
int main()
{

    int ROW=9,COL=7,highScores=10;
    char gridArr[ROW][COL];
    char configFilePath[1000] = "configure.xml";

    for (int i=0; i<3; i++) {
        _Bool recieved = readParametars(&COL,&ROW,&highScores,configFilePath);
        if (recieved) break;
        else {
            printf("Configuration file is corrupted or doesn't exist, please enter a path for a valid file\n");
            gets(configFilePath);
        }
    }

    lastMove=0;
    moves=0;
    original_grid(ROW,COL,gridArr);

    main_manu(ROW,COL,gridArr,highScores);

    return 0;
}
