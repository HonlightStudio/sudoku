#include <iostream>
#include "clui.h"
#include <conio.h>
#include <ctime>
#include <fstream>
using namespace std;

int row = get_window_rows();
int column = get_window_cols();
char* username = new char[100];
short int** d;

void showscors();
int startmenu();
bool loadgame();
short int prematch();
short int** randomSodu(short int** sudoarr);
void endgame(short int** sudogame,int difficulty,int wrong,int correct,int rtime);
int game(int difficulty,int rtime,bool isload,int HP,short int ** a);
short int** readyforgame(int digitcount,short int** sudoarr);
void split (char * a, char * user, char* pass, char d);
int game(int difficulty ,bool isload,short int ** a);
struct color{
    int r,g,b;
};
int scorecount = 0;
struct scorest{
    char * username = new char[100];
    int score;
    int wrong;
    int correct;
    int rtime;
};

 scorest* scores = new scorest[500];

struct position{
    int x,y;
};

bool compair(char * a, char * b){
    int i = 0;
    while (a[i] != '\0'){
        if(a[i]!=b[i])return false;
        i++;
    }
    return (b[i] == '\0');


}


void PrepareCMD(color TextColor, position StartPos,int backcolor){
    int x = StartPos.x,y = StartPos.y;
    cursor_to_pos(x,y);
    change_color_rgb(TextColor.r,TextColor.g,TextColor.b);
    change_background_color(backcolor);
}
short int min(int a, int b){
    return a>b ? b:a;
}
short int max(int a, int b){
    return a<b ? b:a;
}



short int** makesudo(){

    short int** sudo = new short int*[9];
    for (int i = 0; i < 9; i++) {
        sudo[i] = new short int[9];
    }
    fstream sudofile("sudokus.txt");
    string setxt;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudo[i][j]=sudofile.get()-'0';
        }
    }
    return randomSodu(sudo);
}

void swap(short int &a,short int &b){
    short int c = a;
    a = b;
    b = c;

}
short int** randomSodu(short int** sudoarr){


    srand(time(0));

    for (int i = 0; i < 10; i++) {
        int from = rand() % 9;
        int to = rand() % 9;
        for (int j = 0; j < 9; j++) {
            swap(sudoarr[from][j],sudoarr[to][j]);

        }
    }
    for (int i = 0; i < 10; i++) {
        int from = rand() % 9;
        int to = rand() % 9;
        for (int j = 0; j < 9; j++) {
            swap(sudoarr[j][from],sudoarr[j][to]);

        }
    }

    return sudoarr;
}

short int** readyforgame(int digitcount,short int** sudoarr){

    short int** sudocopy = new short int*[9];
    for (int i = 0; i < 9; i++) {
        sudocopy[i] = new short int[9];
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudocopy[i][j]=sudoarr[i][j];
        }
    }

    srand(time(0));
    int x = 81 - digitcount;
    for (int i = 0; i < x; ++i) {

        int x = rand() % 9;
        int y = rand() % 9;

        sudocopy[y][x] = 0;

    }


    return sudocopy;


}

int startmenu(){
    short int select = 1;

    clear_screen();
    reset_color();
    PrepareCMD({100, 100, 100}, {row / 2 - 5, column / 2 - 5},
               select == 1 ? 2:0 );
    cout << "1)Start new Game";
    PrepareCMD({100, 100, 100}, {row / 2 - 4, column / 2 - 5},
               select == 2 ? 2:0 );
    cout << "2)load Game";
    PrepareCMD({100, 100, 100}, {row / 2 - 3, column / 2 - 5},
               select == 3 ? 2:0 );
    cout << "3)scores";
    PrepareCMD({100, 100, 100}, {row / 2 - 2, column / 2 - 5},
               select == 4 ? 2:0 );
    cout << "4)Exite";

    bool isrun = true;
    while (isrun) {
        if(is_keyboard_hit()){
            char key = _getch();
            switch (key) {
                case 72: select = max(select-1,1);
                    break;
                case 80: select = min(select+1,4);
                    break;
                case 13:isrun=false;
            }


            PrepareCMD({100, 100, 100}, {row / 2 - 5, column / 2 - 5},
                       select == 1 ? 2:0 );
            cout << "1)Start new Game";
            PrepareCMD({100, 100, 100}, {row / 2 - 4, column / 2 - 5},
                       select == 2 ? 2:0 );
            cout << "2)load Game";
            PrepareCMD({100, 100, 100}, {row / 2 - 3, column / 2 - 5},
                       select == 3 ? 2:0 );
            cout << "3)scores";
            PrepareCMD({100, 100, 100}, {row / 2 - 2, column / 2 - 5},
                       select == 4 ? 2:0 );
            cout << "4)Exite";
        }

        reset_color();
    }
    clear_screen();


    switch(select){
        case 1 :
            int dif;
            dif = prematch();
            game(dif,240/dif ,false,(4-dif)*5,new short int*[9]);
            break;
        case 2:
            if(!loadgame()) select = startmenu();
            break;
        case 3:
            showscors();
            break;
        case 4:
            quit();
            break;

    }


    return select;
}


short int prematch(){
    bool isrun = true;
    short int select = 1;


    PrepareCMD({20, 200, 20}, {row / 2 - 5, column / 2 - 5}, 1 );
    cout << "1)easy";
    PrepareCMD({10, 200, 200}, {row / 2 - 4, column / 2 - 5},0 );
    cout << "2)normal";
    PrepareCMD({255, 0, 100}, {row / 2 - 3, column / 2 - 5},0 );
    cout << "3)hard";

    while (isrun) {
        if(is_keyboard_hit()){
            char key = _getch();
            switch (key) {
                case 72 : select = max(select-1,1);
                    break;
                case 80 : select = min(select+1,3);
                    break;
                case 13:isrun=false;
            }


            PrepareCMD({20, 200, 20}, {row / 2 - 5, column / 2 - 5},
                       select == 1 ? 1:0 );
            cout << "1)easy";
            PrepareCMD({10, 200, 200}, {row / 2 - 4, column / 2 - 5},
                       select == 2 ? 1:0 );
            cout << "2)normal";
            PrepareCMD({255, 0, 100}, {row / 2 - 3, column / 2 - 5},
                       select == 3 ? 1:0 );
            cout << "3)hard";
        }

        reset_color();
    }
    clear_screen();
    return select;



}






bool testsudo(short int ** sudo , int x , int y){
    short int a = sudo[y][x];
    for (int i = 1; i <9; i++) {
        if(a == sudo[y][(x+i)%9]){
            sudo[y][x] = 0;
            return false;
        }
    }
    for (int i = 1; i <9; i++) {
        if(a == sudo[(y+i)%9][x]){
            sudo[y][x] = 0;
            return false;
        }
    }
    return true;

}
int drawsudocu(short int ** sudo){
    PrepareCMD({112, 41, 138}, {0,0},0 );
    int non0 = 0;
    for(int i = 1; i<=19; i++){
        for (int j = 1; j <= 9; j++) {
            if(i%2 == 1){
                cout << "----";
            }else{
                cout<<"|";
                change_background_color(1);
                if(sudo[(i/2) - 1][j-1]!=0) {
                    cout << " " << sudo[(i / 2) - 1][j - 1] << " ";
                    non0++;
                }
                else cout<<"   ";
                change_background_color(0);

            }

        }
        if(i%2 == 0){
            cout << '|';
        }else{
            cout << '-';
        }
        cout<<'\n';

    }
    return non0;
}



int game(int difficulty,int rtime,bool isload,int HP = 10 ,short int ** a = d){
    clear_screen();
    int non0 = 0;
    int correct = 0;
    short int ** sudohelp;
    short int ** sudogame;
    if(isload) {


        sudogame = a;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout<<sudogame[i][j];

            }
            cout <<'\n';
        }
    }
    else{
        sudohelp = makesudo();
        sudogame = readyforgame(30/difficulty,sudohelp);
    }


    int x = 0;
    int y = 0;
    bool isrunning = true;
    bool isstop = false;
    int start = time(0);
    int current = time(0);
    drawsudocu(sudogame);
    PrepareCMD({112, 41, 138}, {0, 45},3 );
    cout << username;
    while (isrunning){
        if(is_keyboard_hit()) {
            char key = _getch();
            switch (key) {
                case 27:
                    isstop = !isstop;
                    if(isstop){
                        clear_screen();
                        PrepareCMD({10, 200, 200}, {row / 2 - 4, column / 2 - 5},0 );
                        cout<<"pause";
                    } else{
                        clear_screen();
                        drawsudocu(sudogame);
                    }

                    break;
                case 75 ://left
                    x = max(x - 1, 0);
                    PrepareCMD({112, 41, 138}, {y*2 + 2,x*4 + 3},0 );
                    break;
                case 77 ://right
                    x = min(x + 1, 8);
                    PrepareCMD({112, 41, 138}, {y*2 + 2,x*4 + 3},0 );
                    break;
                case 80://up
                    y = min(y + 1, 8);
                    PrepareCMD({112, 41, 138}, {y*2 + 2,x*4 + 3},0 );
                    break;
                case 72://down
                    y = max(y - 1, 0);
                    PrepareCMD({112, 41, 138}, {y*2 + 2,x*4 + 3},0 );
                    break;
                case 120:
                    sudogame[y][x] = 0;
                    drawsudocu(sudogame);
                    break;
                case 's':
                    ofstream savefile("saves.txt", ios::app);
                    savefile << username << '|';
                    for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                            savefile<<sudogame[i][j];
                        }
                    }
                    savefile<<'|'<<HP << '|'<< rtime <<'\n';
                    break;



            }
            if(key>=49 && key<=57){
                sudogame[y][x] = sudogame[y][x] == 0 ?  key - 48 : sudogame[y][x];
                if(!testsudo(sudogame,x,y))HP--;
                else correct++;
                non0 = drawsudocu(sudogame);
                PrepareCMD({112, 41, 138}, {y*2 + 2,x*4 + 3},0 );
            }

        } else if (current != time(0) && !isstop){
            PrepareCMD({112, 41, 138}, {3,45},3 );
            current = time(0);
            cout<<"time: "<<rtime<<"   ";
            PrepareCMD({112, 41, 138}, {5,45},3 );
            cout<<"HP: "<<HP<<"   ";
            PrepareCMD({112, 41, 138}, {y*2 + 2,x*4 + 3},0 );
            rtime--;

        }

        if(rtime <= 0 || HP<=0 || non0 >= 81){
            endgame(sudogame,difficulty,10-HP,correct,rtime);
        }




    }
    return 0;
}

int str2int(char* a){
    int n = 0;
    int r = 0;
    bool isnegetive = a[0]=='-';
    if(a[0]=='-')n++;
    while (a[n]!='\0'){
        r+=a[n]-'0';
        r*=10;
        n++;

    }
    r/=10;
    return (isnegetive? -r:r);

}

void endgame(short int** sudogame,int difficulty,int wrong,int correct,int rtime){
    int score = 0;
    int maxscore = 0;
    for (int i = 0; i < 9; i++) {
        delete[] sudogame[i];
    }
    delete[] sudogame;
    score = difficulty*(correct-wrong);
    ofstream scoref("scores.txt", ios::app);
    scoref << username << '|'<<score<<'|'<<correct<<'|'<<wrong<<'|'<<rtime<<'\n';
    scoref.close();


    fstream saves("scores.txt");
    char * user = new char[100];
    char * scwr = new char[100];
    char * cwr = new char[100];
    char * wr = new char[100];
    char * scorestr = new char[100];
    char * line = new char[100];
    char * wrongc = new char[100];
    char * timec = new char[100];
    char * correctc = new char[100];

    while (line[0] != 0){
        saves.getline(line,100);
        split(line,user,scwr,'|');
        split(scwr,scorestr,cwr,'|');
        split(cwr,correctc,wr,'|');
        split(wr,wrongc,timec,'|');
        if(compair(username,user)){
            maxscore = str2int(scorestr)>maxscore? str2int(scorestr):maxscore;
        }
    }

    clear_screen();
    PrepareCMD({250, 41, 0}, {1,1},0 );
    cout<<"this game score: ( corrects:"<<correct<<"- wrongs:"<<wrong<<")* difficulty score:"<<difficulty <<" = " << score <<'\n'<<"max game score: "<< maxscore;
    getch();
    startmenu();


}


bool loadgame(){


    fstream saves("saves.txt");

    char * shr = new char[100];
    char * user = new char[100];
    char * hr = new char[100];
    char * hpc = new char[100];
    char * rtimec = new char[100];
    char * lastuser = new char[100];
    char * loadsudo = new char[100];
    char * line = new char[100];
    int hp = 0;
    int rtime = 0;
    bool isfind = false;
    saves.getline(line,100);
    short int** a = new short int*[9];
    while (line[0] != 0){


        split(line,user,shr,'|');
        split(shr,loadsudo,hr,'|');
        split(hr,hpc,rtimec,'|');

        if(compair(user, username)){

            for (int i = 0; i < 9; i++) {
                a[i] = new short int[9];
            }
            for (int i = 0; i < 81; i++) {
                a[i/9][i%9]= loadsudo[i]-'0';
            }
            hp = str2int(hpc);
            rtime = str2int(rtimec);
            isfind = true;
        }
        saves.getline(line,100);
    }
    if(isfind){
        game(2, rtime, true,hp,a);
        return true;
    }
    return false;


}





int login(){
    bool isrun = true;

    clear_screen();
    reset_color();
    int select = 1;
    PrepareCMD({20, 200, 20}, {row / 2 - 5, column / 2 - 5},
               select == 1 ? 1:0 );
    cout << "1) login";
    PrepareCMD({10, 200, 200}, {row / 2 - 4, column / 2 - 5},
               select == 2 ? 1:0 );
    cout << "2) SignUp";
    PrepareCMD({255, 0, 100}, {row / 2 - 3, column / 2 - 5},
               select == 3 ? 1:0 );
    cout << "3) Guest";
    while (isrun) {
        if(is_keyboard_hit()){
            char key = _getch();
            switch (key) {
                case 72 : select = max(select-1,1);
                    break;
                case 80 : select = min(select+1,3);
                    break;
                case 13:
                    isrun=false;
                    return select;
                    break;
            }


            PrepareCMD({20, 200, 20}, {row / 2 - 5, column / 2 - 5},
                       select == 1 ? 1:0 );
            cout << "1) login";
            PrepareCMD({10, 200, 200}, {row / 2 - 4, column / 2 - 5},
                       select == 2 ? 1:0 );
            cout << "2) SignUp";
            PrepareCMD({255, 0, 100}, {row / 2 - 3, column / 2 - 5},
                       select == 3 ? 1:0 );
            cout << "3) Guest";
        }

        reset_color();
    }
    clear_screen();
    return select;

}

void split (char * a, char * user, char* pass, char d){
    int i = 0;
    while (a[i] != d){
        user[i] = a [i];
        i++;
    }
    user[i] = '\0';
    i++;
    int j = 0;
    while (a[i] != '\0'){

        pass[j] = a [i];
        j++;
        i++;

    }

    pass[j] = '\0';

}

void loginpage(bool first){
    clear_screen();
    char * line = new char[100];
    char * user= new char[100];
    char * pass = new char[100];
    if(!first){

        PrepareCMD({255, 0, 100}, {row / 2 -5, column / 2 -5},0);
        cout << "wrong user pass";
    }
    fstream users("users.txt");
    PrepareCMD({255, 0, 100}, {row / 2 - 3, column / 2 - 5},0);
    cout << "UserName: ";
    cin >> user;
    cout << '\n';
    PrepareCMD({255, 0, 100}, {row / 2 - 2, column / 2 - 5},0);
    cout << "password: ";
    cin >> pass;
    char * user2= new char[100];
    char * pass2 = new char[100];
    users.getline(line,100);
    while (line[0] != 0){


        split(line,user2,pass2,'|');
        if(compair(user, user2) && compair(pass, pass2)){
            username = user;
            return;
        }
        users.getline(line,100);
    }
    loginpage(false);
}




void sighnup(bool first){
    clear_screen();
    char * line = new char[100];
    char * user= new char[100];
    char * pass = new char[100];
    if(!first){

        PrepareCMD({255, 0, 100}, {row / 2 -5, column / 2 -5},0);
        cout << "user name is exist";
    }
    fstream users("users.txt");
    PrepareCMD({255, 0, 100}, {row / 2 - 3, column / 2 - 5},0);
    cout << "UserName: ";
    cin >> user;
    cout << '\n';
    PrepareCMD({255, 0, 100}, {row / 2 - 2, column / 2 - 5},0);
    cout << "password: ";
    cin >> pass;

    char * user2= new char[100];
    char * pass2 = new char[100];
    while (line[0] != 0) {

        users.getline(line, 100);
        split(line, user2, pass2,'|');

        if (compair(user, user2)) {
            sighnup(false);
            return;
        }
    }
    ofstream savefile("users.txt", ios::app);
    savefile << user << '|' << pass<<'\n';
    username = user;
}

void swap(scorest &s1, scorest &s2){


    scorest t = s1;
    s1 = s2;
    s2 = t;
    return;
}

void sortscors(){
    for (int i = 0; i < scorecount - 1; i++) {
        for (int j = 0; j < scorecount - i - 1; j++) {
            if (scores[j].score < scores[j + 1].score)
                swap(scores[j], scores[j + 1]);
            else if(scores[j].score == scores[j + 1].score && scores[j].rtime < scores[j + 1].rtime)
                swap(scores[j], scores[j + 1]);
        }
    }
}

void copystr(char* from, char* to){
    int n = 0;
    while (from[n] != '\0'){
        to[n]=from[n];
        n++;

    }

    to[n]='\0';
}

void showscors(){

    clear_screen();
    PrepareCMD({50, 30, 100}, {0, column / 2 -20},4);
    cout << "leader board";
    fstream saves("scores.txt");
    char * user = new char[100];
    char * scwr = new char[100];
    char * cwr = new char[100];
    char * wr = new char[100];
    char * scorestr = new char[100];
    char * line = new char[100];
    char * wrongc = new char[100];
    char * timec = new char[100];
    char * correctc = new char[100];
    saves.getline(line, 100);
    while (line[0] != 0) {

        split(line, user, scwr, '|');
        split(scwr, scorestr, cwr, '|');
        split(cwr, correctc, wr, '|');
        split(wr, wrongc, timec, '|');
        char * copyuser = new char[200];
        copystr(user,copyuser);

        scores[scorecount++] = {copyuser, str2int(scorestr), str2int(wrongc),
                                str2int(correctc), str2int(timec)};
        saves.getline(line, 100);

    }
    sortscors();
    for (int i = 0; i < scorecount; i++) {
        PrepareCMD({255, 0, 100}, {i+5, column / 2 -20},0);
        cout<<i+1<<":) "<<"user : "<<scores[i].username<<" score: "<<scores[i].score<<" wrongs: "<<scores[i].wrong<<
        " correct: "<<scores[i].correct<<" time: "<<scores[i].rtime<<'\n';

    }
    scorecount = 0;
    cout<<"press any key:";
    getch();
    startmenu();

}


int main() {
    int mode1 = login();
    int mode2 = 0;
    switch(mode1){
        case 1 :
            loginpage(true);
            break;
        case 2:
            sighnup(true);
            break;
        case 3:
            username = "Guest";
            break;

    }

    mode2 = startmenu();


    getch();
}
