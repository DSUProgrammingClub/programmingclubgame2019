#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

//Stop players from going out of walls

using namespace std;

int player_x;
int player_y;
string map[10];

void init(){
    for(int i=0;i<10;i++){
        if(i == 0 || i == 9){
            map[i] = "##########";
        }else{
            map[i] = "#        #";
        }
    }
    player_x = 3;
    player_y = 3;
}

void update(){
    char input;
    cin >> input;
    map[player_y][player_x] = ' ';
    if(input == 'a'){
        player_x--;
    }else if(input == 'd'){
        player_x++;
    }else if(input == 's'){
        player_y++;
    }else if(input == 'w'){
        player_y--;
    }
    map[player_y][player_x] = '+';
}

void render(){
    system("clear");
    for(int i  = 0;i < 10;i++){
        cout << map[i] << endl;
    }
}


int main(){
    //Init board
    init();

    while(1){
        render();
        update();
    }

    return 0;
}
