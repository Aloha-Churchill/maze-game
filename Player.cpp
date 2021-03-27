#include "Player.h"


/*
Constructor for player, initializes player in top corner
*/
Player::Player(const std::string name, const bool is_human){
    this->name_ = name;
    this->points_ = 0;
    this->pos_.row = 0;
    this->pos_.col = 0;
    this->is_human_ = is_human;
}

/*
Adds points to player if they collect treasure
*/
void Player::ChangePoints(const int x){
    this->points_ = this->points_ + x;
}


/*
Sets player to position on board
*/
void Player::SetPosition(Position pos){
    this->pos_ = pos;

}

/*
Prints out player name and points
*/
std::string Player::Stringify(){
    std::string s = "Player name: " + this->name_ + "\nPlayer Points: " + std::to_string(this->points_) + "\n";
    return s;
}