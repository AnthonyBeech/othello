#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 8
#define L 32

typedef struct Player{
    char name[L];
    int score;
} Player;


void delay(unsigned int mseconds);
void drawboard(char board[N][N]);
struct Player * details(int m);
int totscore(char board[N][N],int pl);
int updateboard(char uboard[N][N],int r, int c,char ch1,char ch2);
int valid(char vboard[N][N],int r, int c,char ch1,char ch2);
void endgame(Player py1,Player py2,int t);
int anymoves(char aboard[N][N],char dboard[N][N],char ch1,char ch2);
void AI(char aboard[N][N],char dboard[N][N],int *r,int *c,char ch1,char ch2);
void savegame(char board[N][N],Player py1,Player py2,int t);

int main(){
    int turn=1,check,end=1,row,collumn,option;
    char name1[L],name2[L];
    char game[N][N]={{0}};
    char nextgame[N][N]={{0}};
    char movesgame[N][N]={{0}};

    Player *p1=NULL;
    Player *p2=NULL;

    printf("-----------------------RULES------------------------\n"
           "-Each move must result in the flipping of a counter \n"
           "-Counters are flipped when your counters trap a line\n"
           " of the opponents counters\n"
           "-to save the game and exit to the menu, enter a row\n"
           "value of 55\n");

    printf("-----------------------MENU-------------------------\n"
          "\t 1. NEW 2 PLAYER GAME\n"
          "\t 2. NEW AI GAME\n"
          "\t 3. LOAD 2 PLAYER GAME\n"
          "\t 4. LOAD AI GAME\n"
          "\t 0. QUIT\n");
    scanf("%d", &option);

    p1=details(0);
    p2=details(0);

while(end==1){
    switch (option){

case 0:

    printf("Goodbye, thank you for playing\n");
    exit(99);

case 1:

    if(turn==1){
        p1=details(1);
        p2=details(2);
    }

    while(end==1){
        if(turn==1){
            game[N/2-1][N/2-1]='b';
            game[N/2][N/2-1]='w';
            game[N/2-1][N/2]='w';
            game[N/2][N/2]='b';
            drawboard(game);
        }
        if(turn%2==1){
            p1->score=totscore(game,1);
            if(anymoves(movesgame,game,'b','w')==0){
                turn++;
                check++;
                printf("\n%s has no valid moves",p1->name);
                if(check==2){
                    endgame(*p1,*p2,turn);
                }
                break;
            }
            check=0;
            printf("\n%s,you're b,Turn: %d,Score: %d\n",p1->name,turn,p1->score);
            printf("enter row value\n");
            scanf("%d",&row);
            if(row==55){
                savegame(game,*p1,*p2,turn);
            }
            printf("enter collumn value\n");
            scanf("%d",&collumn);
            nextgame[row][collumn] = 'b';
            if(valid(game,row,collumn,'b','w')==1){
                game[row][collumn]=nextgame[row][collumn];
                drawboard(game);
            }
            else{
                printf("invalid\n");
                --turn;
            }
            nextgame[row][collumn] = '-';

        }
        else{
            p2->score=totscore(game,2);
            if(anymoves(movesgame,game,'w','b')==0){
                turn++;
                check++;
                printf("\n%s has no valid moves",p2->name);
                if(check==2){
                    endgame(*p1,*p2,turn);
                }
                break;
            }
            check=0;
            printf("\n%s,you're b,Turn: %d,Score: %d\n",p2->name,turn,p2->score);
            printf("enter row value\n");
            scanf("%d",&row);
            if(row==55){
                savegame(game,*p1,*p2,turn);
            }
            printf("enter collumn value\n");
            scanf("%d",&collumn);
            nextgame[row][collumn] = 'w';
            if(valid(game,row,collumn,'w','b')==1){
                game[row][collumn]=nextgame[row][collumn];
                drawboard(game);
            }
            else{
                printf("invalid\n");
                --turn;
            }
            nextgame[row][collumn] = '-';
        }
        turn++;
        }
        break;

case 2:
    if(turn==1){
        p1=details(1);
        p2=details(2);
    }

    while(end==1){
        if(turn==1){
            game[N/2-1][N/2-1]='b';
            game[N/2][N/2-1]='w';
            game[N/2-1][N/2]='w';
            game[N/2][N/2]='b';
            drawboard(game);
        }
        if(turn%2==1){
            p1->score=totscore(game,1);
            if(anymoves(movesgame,game,'b','w')==0){
                turn++;
                check++;
                printf("\n%s has no valid moves",p1->name);
                if(check==2){
                endgame(*p1,*p2,turn);
                }
                break;
            }
            check=0;
            printf("\n%s,you're b,Turn: %d,Score: %d\n",p1->name,turn,p1->score);
            printf("enter row value\n");
            scanf("%d",&row);
            if(row==55){
                savegame(game,*p1,*p2,turn);
            }
            printf("enter collumn value\n");
            scanf("%d",&collumn);
            nextgame[row][collumn] = 'b';
            if(valid(game,row,collumn,'b','w')==1){
                game[row][collumn]=nextgame[row][collumn];
                drawboard(game);
            }
            else{
                printf("invalid\n");
                --turn;
            }
            nextgame[row][collumn] = '-';
        }
        else{
            p2->score=totscore(game,2);
            if(anymoves(movesgame,game,'w','b')==0){
                turn++;
                check++;
                printf("\n%s has no valid moves",p2->name);
                if(check==2){
                    endgame(*p1,*p2,turn);
                }
                break;
            }
            check=0;
            printf("\n%s,Turn: %d,Score: %d\n",p2->name,turn,p2->score);
            AI(movesgame,game,&row,&collumn,'w','b');
                delay(1000);

            nextgame[row][collumn] = 'w';
            if(valid(game,row,collumn,'w','b')==1){
                game[row][collumn]=nextgame[row][collumn];
                drawboard(game);
            }
            else{
                printf("invalid\n");
                --turn;
            }
            nextgame[row][collumn] = '-';
        }
        turn++;
        }
        break;

case 3:
    printf("\n\n\n--------------------GAME LOADED---------------------\n\n\n");
    int j,k;
    FILE *lfile;
    lfile=fopen("Savefile.txt","r");
    for(j=0;j<N;++j){
        for(k=0;k<N;++k){
            fscanf(lfile,"%c\n",&game[j][k]);
        }
    }

    fscanf(lfile,"%d\n",&turn);
    fscanf(lfile,"%s\n",p1->name);
    fscanf(lfile,"%s\n",p2->name);
    drawboard(game);
    option=1;
    break;

case 4:
    printf("\n\n\n--------------------GAME LOADED---------------------\n\n\n");
    int o,p;
    FILE *l2file;
    l2file=fopen("Savefile.txt","r");
    for(o=0;o<N;++o){
        for(p=0;p<N;++p){
            fscanf(l2file,"%c\n",&game[o][p]);
        }
    }

    fscanf(l2file,"%d\n",&turn);
    fscanf(l2file,"%s\n",p1->name);
    fscanf(l2file,"%s\n",p2->name);
    drawboard(game);
    option=2;
    break;
}
}
    return 0;
}

void delay(unsigned int mseconds){
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void drawboard(char board[N][N]){
    int x,y;
    printf("  0 1 2 3 4 5 6 7\n0");
    for(x=0;x<N;++x){
        for(y=0;y<N;++y){
            if(board[x][y]){
                printf("|%c",board[x][y]);
            }
            else{
            printf("|-");
            }
        }
        if(x<7){
            printf("|\n%d",x+1);
        }
        if(x==7){
            printf("|\n");
        }
    }
}

struct Player * details(int m){
    Player *p;
    p=malloc(sizeof *p);

    if(m!=0){
        printf("Player %d enter your name\n",m);
        scanf("%s",p->name);
    }

return p;
}

int totscore(char board[N][N],int pl){
    int x,y,s=0;
    for(x=0;x<N;++x){
        for(y=0;y<N;++y){
            if(pl==1){
                if(board[x][y]=='b'){
                    s++;
                }
            }
            else{
                if(board[x][y]=='w'){
                    s++;
                }
            }
        }
    }
    return s;
}

 int updateboard(char uboard[N][N],int r, int c,char ch1,char ch2){

   int counter = 0,x=1;
    //down
    while((r+x)<N){
        if(uboard[r+x][c]==ch2){
            uboard[r+x][c]=ch1;
            if((r+x)==N-1){
                for(x=x;x>=1;--x){
                    if(uboard[r+x][c]==ch1){
                        uboard[r+x][c]=ch2;
                    }
                }
                break;
            }
            x++;
        }
        else if(uboard[r+x][c]==ch1&&x==1){
            break;
        }
        else if(uboard[r+x][c]==ch1&&x!=1){
            counter++;
            break;
        }
        else if(uboard[r+x][c]!=(ch1||ch2)&&x!=1){
                --x;
            for(x=x;x>=1;--x){
                    if(uboard[r+x][c]==ch1){
                        uboard[r+x][c]=ch2;
                    }
                }
            break;
        }
        else if(uboard[r+x][c]!=(ch1||ch2)&&x==1){
            break;
        }
    }
    x=1;//up
    while((r-x)>=0){
        if(uboard[r-x][c]==ch2){
            uboard[r-x][c]=ch1;
            if((r-x)==0){
                for(x=x;x>=1;--x){
                    if(uboard[r-x][c]==ch1){
                        uboard[r-x][c]=ch2;
                    }
                }
                break;
            }
            x++;
        }
        else if(uboard[r-x][c]==ch1&&x==1){
            break;
        }
        else if(uboard[r-x][c]==ch1&&x!=1){
            counter++;
            break;
        }
        else if(uboard[r-x][c]!=(ch1||ch2)&&x!=1){
                --x;
            for(x=x;x>=1;--x){
                    if(uboard[r-x][c]==ch1){
                        uboard[r-x][c]=ch2;
                    }
                }
            break;
        }
        else if(uboard[r-x][c]!=(ch1||ch2)&&x==1){
            break;
        }
    }
    x=1;//right
    while((c+x)<N){
        if(uboard[r][c+x]==ch2){
            uboard[r][c+x]=ch1;
            if((c+x)==N-1){
                for(x=x;x>=1;--x){
                    if(uboard[r][c+x]==ch1){
                        uboard[r][c+x]=ch2;
                    }
                }
                break;
            }
            x++;
        }
        else if(uboard[r][c+x]==ch1&&x==1){
            break;
        }
        else if(uboard[r][c+x]==ch1&&x!=1){
            counter++;
            break;
        }
        else if(uboard[r][c+x]!=(ch1||ch2)&&x!=1){
                --x;
            for(x=x;x>=1;--x){
                    if(uboard[r][c+x]==ch1){
                        uboard[r][c+x]=ch2;
                    }
                }
            break;
        }
        else if(uboard[r][c+x]!=(ch1||ch2)&&x==1){
            break;
        }
    }
    x=1;//left
    while((c-x)>=0){
        if(uboard[r][c-x]==ch2){
            uboard[r][c-x]=ch1;
            if((c-x)==0){
                for(x=x;x>=1;--x){
                    if(uboard[r][c-x]==ch1){
                        uboard[r][c-x]=ch2;
                    }
                }
                break;
            }
            x++;
        }
        else if(uboard[r][c-x]==ch1&&x==1){
            break;
        }
        else if(uboard[r][c-x]==ch1&&x!=1){
            counter++;
            break;
        }
        else if(uboard[r][c-x]!=(ch1||ch2)&&x!=1){
                --x;
            for(x=x;x>=1;--x){
                    if(uboard[r][c-x]==ch1){
                        uboard[r][c-x]=ch2;
                    }
                }
            break;
        }
        else if(uboard[r][c-x]!=(ch1||ch2)&&x==1){
            break;
        }
    }
    x=1;//down,right
    while(((r+x)<N)&&((c+x)<N)){
        if(uboard[r+x][c+x]==ch2){
            uboard[r+x][c+x]=ch1;
            if(((r+x)==N-1)||((c+x)==N-1)){
                for(x=x;x>=1;--x){
                    if(uboard[r+x][c+x]==ch1){
                        uboard[r+x][c+x]=ch2;
                    }
                }
                break;
            }
            x++;
        }
        else if(uboard[r+x][c+x]==ch1&&x==1){
            break;
        }
        else if(uboard[r+x][c+x]==ch1&&x!=1){
            counter++;
            break;
        }
        else if(uboard[r+x][c+x]!=(ch1||ch2)&&x!=1){
                --x;
            for(x=x;x>=1;--x){
                    if(uboard[r+x][c+x]==ch1){
                        uboard[r+x][c+x]=ch2;
                    }
                }
            break;
        }
        else if(uboard[r+x][c+x]!=(ch1||ch2)&&x==1){
            break;
        }
    }
    x=1;//up,left
    while(((r-x)>=0)&&((c-x)>=0)){
        if(uboard[r-x][c-x]==ch2){
            uboard[r-x][c-x]=ch1;
            if(((r-x)==0)||((c-x)==0)){
                for(x=x;x>=1;--x){
                    if(uboard[r-x][c-x]==ch1){
                        uboard[r-x][c-x]=ch2;
                    }
                }
                break;
            }
            x++;
        }
        else if(uboard[r-x][c-x]==ch1&&x==1){
            break;
        }
        else if(uboard[r-x][c-x]==ch1&&x!=1){
            counter++;
            break;
        }
        else if(uboard[r-x][c-x]!=(ch1||ch2)&&x!=1){
                --x;
            for(x=x;x>=1;--x){
                    if(uboard[r-x][c-x]==ch1){
                        uboard[r-x][c-x]=ch2;
                    }
                }
            break;
        }
        else if(uboard[r-x][c-x]!=(ch1||ch2)&&x==1){
            break;
        }
    }
    x=1;//down,left
    while(((r+x)<N)&&((c-x)>=0)){
        if(uboard[r+x][c-x]==ch2){
            uboard[r+x][c-x]=ch1;
            if(((r+x)==N-1)||((c-x)==0)){
                for(x=x;x>=1;--x){
                    if(uboard[r+x][c-x]==ch1){
                        uboard[r+x][c-x]=ch2;
                    }
                }
                break;
            }
            x++;
        }
        else if(uboard[r+x][c-x]==ch1&&x==1){
            break;
        }
        else if(uboard[r+x][c-x]==ch1&&x!=1){
            counter++;
            break;
        }
        else if(uboard[r+x][c-x]!=(ch1||ch2)&&x!=1){
                --x;
            for(x=x;x>=1;--x){
                    if(uboard[r+x][c-x]==ch1){
                        uboard[r+x][c-x]=ch2;
                    }
                }
            break;
        }
        else if(uboard[r+x][c-x]!=(ch1||ch2)&&x==1){
            break;
        }
    }
    x=1;//up,right
    while(((r-x)>=0)&&((c+x)<N)){
        if(uboard[r-x][c+x]==ch2){
            uboard[r-x][c+x]=ch1;
            if(((r-x)==0)||((c+x)==N-1)){
                for(x=x;x>=1;--x){
                    if(uboard[r-x][c+x]==ch1){
                        uboard[r-x][c+x]=ch2;
                    }
                }
                break;
            }
            x++;
        }
        else if(uboard[r-x][c+x]==ch1&&x==1){
            break;
        }
        else if(uboard[r-x][c+x]==ch1&&x!=1){
            counter++;
            break;
        }
        else if(uboard[r-x][c+x]!=(ch1||ch2)&&x!=1){
                --x;
            for(x=x;x>=1;--x){
                    if(uboard[r-x][c+x]==ch1){
                        uboard[r-x][c+x]=ch2;
                    }
                }
            break;
        }
        else if(uboard[r-x][c+x]!=(ch1||ch2)&&x==1){
            break;
        }
    }

    if(counter>0){
        return 0;
    }
    else{
        return 1;
    }
}

int valid(char vboard[N][N],int r, int c,char ch1,char ch2){
    if(vboard[r][c]=='b'||vboard[r][c]=='w'){
        return 0;
    }
    else if(r<0||r>N-1){
        return 0;
    }
    else if(c<0||c>N-1){
        return 0;
    }
    if(updateboard(vboard,r,c,ch1,ch2)==1){
        return 0;
    }
    return 1;
}

void endgame(Player py1,Player py2,int t){
    printf("\n\n\n---------------------GAME ENDED---------------------\n");
    printf("%s Score: %d %s Score: %d Turns: %d\n\n\n\n",
           py1.name,py1.score,py2.name,py2.score,t);


    main();

}

int anymoves(char aboard[N][N],char dboard[N][N],char ch1,char ch2){
    int x,y,s=0;
    for(x=0;x<N;++x){
        for(y=0;y<N;++y){
            aboard[x][y]=dboard[x][y];
        }
    }
    for(x=0;x<N;++x){
        for(y=0;y<N;++y){
            s=s+valid(aboard,x,y,ch1,ch2);
        }
    }

    return s;
}

void AI(char aboard[N][N],char dboard[N][N],int *r,int *c,char ch1,char ch2){
    int x,y,x1,y1,max=1,t[N][N];
    for(x=0;x<N;++x){
        for(y=0;y<N;++y){
                for(x1=0;x1<N;++x1){
                    for(y1=0;y1<N;++y1){
                        aboard[x1][y1]=dboard[x1][y1];
                    }
                }
                if(valid(aboard,x,y,ch1,ch2)==1){
                    t[x][y]=totscore(aboard,2);
                    if(t[x][y]>max){
                        max=t[x][y];
                        *r=x;
                        *c=y;
                    }
                }

        }
    }
}

void savegame(char board[N][N],Player py1,Player py2,int t){
    int x,y;
    FILE *sfile;
    sfile = fopen("Savefile.txt","w");

    for(x=0;x<N;++x){
        for(y=0;y<N;++y){
                if(board[x][y]){
                    fprintf(sfile,"%c\n",board[x][y]);
                }
                else fprintf(sfile,"-\n");
        }
    }
    fprintf(sfile,"%d\n",t);
    fprintf(sfile,"%s\n",py1.name);
    fprintf(sfile,"%s\n",py2.name);


    fclose(sfile);
    printf("\n\n\n---------------------GAME SAVED---------------------\n\n\n");
    main();
}
