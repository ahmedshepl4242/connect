
int noOne_win=0;
int choose_best(int g, long int  size,winner_players  *rank);
int  check(int i,long int size,winner_players *rank);
void top_rank(int yy,int score1,int score2,int high_score);
void top_players(int yy,int score1,int score2);
void display_toPrank(long int size,winner_players *rank,int high_score);



int check(int i,long int  size,winner_players *rank)
{
    int define=1;
    char ch;
    int ctr1=0,ctr2=0;

    while((rank[i-1].name[ctr2]!='\0')&&(rank[size-1].name[ctr1]!='\0'))
    {


        while(isspace(rank[size-1].name[ctr1]))
        {

            ctr1++;

        }
        while(isspace(rank[i-1].name[ctr2]))
        {

            ctr2++;

        }

        if(isupper(rank[size-1].name[ctr1]))
        {
            ch=tolower(rank[size-1].name[ctr1]);

        }
        else if(islower(rank[size-1].name[ctr1]))
        {


            ch=toupper(rank[size-1].name[ctr1]);

        }



        if((rank[i-1].name[ctr2]==ch)||(rank[i-1].name[ctr2]==rank[size-1].name[ctr1]))
        {
            ctr1++;
            ctr2++;
        }
        else
        {
            define=0;

            return 0;

        }



    }
    if(define==1)
    {
        ii=i;
        printf("%d",i);
        return 1;

    }



}


int choose_best(int g,long int  size,winner_players  *rank)
{

    winner_players  ranke;



    if(rank[g-1].score>=rank[size-1].score)
    {

        rank_file=fopen("rank.bin","wb");

        fwrite(rank,sizeof(winner_players),size-1,rank_file);
        fclose(rank_file);
        return 1;

    }


    else if(rank[g-1].score<rank[size-1].score)
    {


        rank[g-1].score=rank[size-1].score;
        rank[g-1].moves=rank[size-1].moves;



        if(g!=1)
        {
            while(rank[g-1].score>=rank[g-2].score)
            {
                ranke=rank[g-1];
                rank[g-1]=rank[g-2];
                rank[g-2]=ranke;

                g--;
                if(g==1)
                {
                    break;
                }
            }
        }

        rank_file=fopen("rank.bin","wb");

        fwrite(rank,sizeof(winner_players),size-1,rank_file);
        fclose(rank_file);
        return 1;
    }
}
void top_players(int yy,int score1,int score2)
{

    char namee[100];
    winner_players  ranke;
    if(player1.score>player2.score)
    {

        printf("-------------------player1 win-----------------\n");
        printf("enter name your name player 1:\n");
        fscanf(stdin, " ");
        fgets(namee,100,stdin);
        strcpy(ranke.name,namee);
        ranke.score= player1.score;
        ranke.moves= player1.moves;
        rank_file=fopen("rank.bin","ab");
        fwrite(&ranke,sizeof(winner_players),1,rank_file);
        fclose(rank_file);


    }
    else if(player2.score>player1.score)
    {

        printf("-------------------player2 win-----------------");
        if (inVsComputer) {
            noOne_win=1;
            return;
        }
        printf("enter name your name player 1:\n");
        fscanf(stdin, " ");
        fgets(namee,100,stdin);
        strcpy(ranke.name,namee);
        ranke.score= player2.score;
        ranke.moves= player2.moves;
        rank_file=fopen("rank.bin","ab");
        fwrite(&ranke,sizeof(winner_players),1,rank_file);
        fclose(rank_file);


    }
    else if((yy!=0)&&(player2.score==player1.score))
    {
        printf("-------------------no one win game--------------------------\n");
        noOne_win=1;
        return;

    }


}
void display_toPrank(long int size,winner_players *rank,int high_score)
{
    int i;
    rank_file=fopen("rank.bin","rb");
    rank=malloc(sizeof(winner_players)*(size));
    fread(rank,sizeof(winner_players),size,rank_file);
    if(size>=high_score){

        size=high_score;
    }

    for(i=0; i<size ; i++)
    {


        printf("score of structure: %d\n",rank[i].score);

        printf("name of structure: %s",rank[i].name);

        printf("moves of structure: %d\n",rank[i].moves);

        printf("------------------------------------\n");

    }

    free(rank);



    fclose(rank_file);



}
void top_rank(int yy,int score1,int score2,int high_score)
{
    player2.score=score2;
    player1.score=score1;
    winner_players  *rank;
    int determin ;
    winner_players  ranke;
    int scores,moves,number_structure,control;
    int x,dd=2;
    unsigned  long  i;



    if(yy==0)
    {

        rank_file=fopen("rank.bin","rb");
        fseek(rank_file,0L,SEEK_END);
        long int size=ftell(rank_file);
        //  size=number_of_winner_players();
        size=(size)/sizeof(winner_players);


        display_toPrank(size,rank,high_score);
        return;


    }
    top_players(yy,player1.score,player2.score);


    //the end position if file
    rank_file=fopen("rank.bin","rb");
    fseek(rank_file,0L,SEEK_END);
    long int size=ftell(rank_file);
    //  size=number_of_winner_players();
    size=(size)/sizeof(winner_players);

    rank=malloc(sizeof(winner_players)*size);
    fseek(rank_file,0,SEEK_SET);
    fread(rank,sizeof(winner_players),size,rank_file);

    fclose(rank_file);

    i=size-1;
    if((size!=1)&&(yy!=0))
    {

        while(i>0)
        {


            x=check(i,size,rank);

            if(x==1)


            {

                dd=choose_best(ii,size,rank);


                break;
            }
            if((i-1)==0)
            {
                dd=0;


                break;
            }


            i--;


        }

    }



    i=size-1;


    if((size!=1)&&(dd==0))
    {
        while(rank[i].score>=rank[i-1].score)
        {

            ranke=rank[i];
            rank[i]=rank[i-1];
            rank[i-1]= ranke;

            i--;
            if(i==0)
            {

                break;
            }

        }
        rank_file=fopen("rank.bin","wb");
        fwrite(rank,sizeof(winner_players),size,rank_file);
        fclose(rank_file);
    }
    free(rank);
    if(noOne_win==0)
    {
        if(dd==1){
           display_toPrank(size-1,rank,high_score);
        }
        if(dd=0){

        display_toPrank(size,rank,high_score);

        }
    }
}
