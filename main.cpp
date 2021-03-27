/*
Aloha Churchill
Homework 1
This program is a multi person maze game with one person and n enemies

*/

#include "Maze.h"
#include "Player.h"
#include <iostream>

int main(){
    Player p1("Player 1", true);

    bool keep_playing = true;

    std::cout << "Welcome to the game. Type -1 to quit (on any turn) and 5 to continue to game (just for this turn). \n";
    

    Maze m1;
    m1.NewGame(&p1, 1);

    while(keep_playing){
        int q;
        std::cin >> q;
        if(q == -1){
            keep_playing = false;
            return 0;
        }

        m1.TakeTurn(&p1);
        Player *p1 = m1.GetNextPlayer();

    }


}