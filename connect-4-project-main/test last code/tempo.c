/*

void save_game(int ROW,int COL,char gridarr[ROW][COL],playerData player1,playerData  player2,gameInfo undoList[]);
int load_game(int ROW,int COL,char gridarr[ROW][COL],gameInfo undoList[]);


int load_game(int ROW,int COL,char gridarr[ROW][COL],gameInfo undoList[])
{
    int check_char;
    typedef struct
{
0
    char gridArr[ROW][COL];

    int score1;
    int moves1;
    int score2;
    int moves2;

} storeGrid;
storeGrid *save_games;

storeGrid grid;

    _Bool playerIdentifer=0;
    int i,j,return_value=0,number_game;
    long int  x,size;


    FILE*address_file;
    address_file=fopen("st.bin","rb");
    fseek(address_file,0,SEEK_END);
    size=ftell(address_file);
    size=(size)/(sizeof(storeGrid));
    printf("%ld",size);


    printf("    ->Enter place that your stored in it :\n");
    printf("    ->GAME NUMBER ONE .\n");
    printf("    ->GAME NUMBER TWO .\n");
    printf("    ->GAME NUMBER THREE .\n");
    scanf("%d",&number_game);

   if(number_game>size){

    printf("    this game not existed \n");
    return_value=1;
    return return_value;
   }

    while((number_game!=3)&&(number_game!=1)&&(number_game!=2))
    {
        printf("--->number between 1:3 :\n");



         while(1)
    {
        beging:

         check_char=scanf("%d",&number_game);
         if(check_char!=1){
         gets(&number_game);

          printf("--->enter number between 1:3 :\n");


         }

         else if(!(number_game>0&&number_game<=3)){
            printf("---->enter  number between 1:3\n",COL);
            goto beging;

         }
         else{

            break;
         }


    }



    }

    for(i=1; i<=3; i++)
    {

        if(i==number_game)
        {
            x =sizeof(storeGrid)*(number_game-1);
            fseek(address_file,x,SEEK_SET);
            fread(&grid, sizeof(storeGrid), 1, address_file);
        }
    }


    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            gridarr[i][j]=grid.gridArr[i][j];
        }
    }
    player1.score=grid.score1;
    player1.moves=grid.moves1;

    player2.score=grid.score2;
    player2.moves=grid.moves2;



     if (grid.moves1<=grid.moves2) {
        moves = 0;
        lastMove = 0;
        inLoadedGame = 0;
    }

     else {
        moves = 1;
        lastMove = 1;
        inLoadedGame = 1;
    }


    undoList[0].movingPlayer = player1;
    undoList[1].movingPlayer = player2;
    undoList[2].movingPlayer = player1;


    fclose(address_file);

    system("cls");


    return return_value;
}


void save_game(int ROW,int COL,char gridarr[ROW][COL],playerData player1,playerData  player2,gameInfo undoList[])
{
     typedef struct
{

    char gridArr[ROW][COL];

    int score1;
    int moves1;
    int score2;
    int moves2;

} storeGrid;
storeGrid *save_games;

storeGrid grid;

    int i,j,chooseSaveOR;
    long int size;

    FILE *address_file;




    address_file=fopen("st.bin","ab");

    if(address_file==NULL)
    {

        printf("not find file");

    }

    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            grid.gridArr[i][j]=gridarr[i][j];
        }
    }
    grid.score1= player1.score;
    grid.moves1=player1.moves;
    grid.score2=player2.score;
    grid.moves2= player2.moves;

    fwrite(&grid, sizeof(storeGrid), 1, address_file);
    fclose(address_file);
    address_file=fopen("st.bin","rb ");
    fseek(address_file,0,SEEK_END);
    size=ftell(address_file);
    size=(size)/(sizeof(storeGrid));
    fclose(address_file);
    if(size>3){

       /* printf("the storage of the game is FULL\n");
        printf("IF YOU WANT TO DELETE THE FIRST GAME AND STORE YOUR GAME  PRESS 1\n");
        printf("IF NOT PRESS  2\n");


        scanf("%d",&chooseSaveOR);

         /* if(chooseSaveOR==1){
                  save_games=malloc(sizeof(storeGrid)*3);
                   fseek(address_file,-3*sizeof(storeGrid),SEEK_END);
                     fread(save_games,sizeof(storeGrid),3,address_file);
                      fclose(address_file);

                       address_file=fopen("st.bin","wb");
                       fwrite(save_games, sizeof(storeGrid),3, address_file);
                       fclose(address_file);
                       free(save_games);*/
/*
                      printf("--------------the storage is full-------------- ");
                       sleep(1);


                 load_player(ROW,COL,gridarr,undoList);
                return;}


        else if(chooseSaveOR==2){
                 load_player(ROW,COL,gridarr,undoList);

                return;
       }




     if((size<=3)&&(size>=1)){
     save_games=malloc(sizeof(storeGrid)*size);
     }



    address_file=fopen("st.bin","rb");
    fseek(address_file,0,SEEK_SET);
    fread(save_games,sizeof(storeGrid),size,address_file);
    fclose(address_file);



    address_file=fopen("st.bin","wb");
    fwrite(save_games, sizeof(storeGrid),size, address_file);
    fclose(address_file);
    free(save_games);

}

*/
