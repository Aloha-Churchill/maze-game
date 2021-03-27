#include "Maze.h"

/*
Constructor for maze, initializes new board and empty players_ vector
*/
Maze::Maze(){
	board_ = new Board();
	this->players_ = {}; // {new Player("Owl", true), new Player("Enemy 1", false), new Player("Enemy 2", false)}
	this->turn_count_ = 0;
    this->eaten = false; //has player been eaten?
    this->finish = false; // has player finished game?
}

/*
initializes players_ for new game with one human and multiple enemies
*/
void Maze::NewGame(Player *human, const int enemies){
    this->players_.push_back(human);
    for(int i = 0; i<enemies; i++){
        std::string s = "Enemy " + std::to_string(i+1);
        this->players_.push_back(new Player(s, false));

        //defines position for enemies
        int ex = rand()%this->board_->get_rows();
        int ey = rand()%this->board_->get_cols();
        Position enemyPos = {ex,ey};
        this->board_->SetSquareValue(enemyPos, SquareType::Enemy);
    }

}

/*
Player can choose one of possible positions to move in by specifiying index. 
Will check if player is eaten or finished based on their move.
*/

void Maze::TakeTurn(Player *p){
    std::cout << this->board_->StringifyBoard();

    std::cout << "Possible Positions: ";
    std::vector<Position> possible_positions = this->board_->GetMoves(p);
    for(int i = 0; i < (int) possible_positions.size(); i++){
        std::cout << "(" << possible_positions[i].row << "," << possible_positions[i].col <<")" << " , ";
    }

    int pick_pos;
    std::cout << "\n Where do you want to move, choose a position based on index shown (zero selects the 1st possible position displayed etc. ? \n";
    std::cin >> pick_pos;

    if(pick_pos == -1){
        return;
    }
    Position next_pos = possible_positions[pick_pos];

    if(this->board_->get_square_value(next_pos) == SquareType::Enemy && p->is_human()){
        this->eaten = true;
    }
    if(this->board_->get_square_value(next_pos) == SquareType::Exit && p->is_human()){
        this->finish = true;
    }
    
    if(this->IsGameOver()){
        std::cout<<this->GenerateReport();
    }
    else{
        this->board_->MovePlayer(p, next_pos);
        this->turn_count_ = this->turn_count_ + 1;
        Player *p = this->GetNextPlayer();
        this->TakeTurn(p);
    }

}


/*
Returns next player in line to take turn
*/
Player * Maze::GetNextPlayer(){
    return this->players_[this->turn_count_];
}

/*
checks if person has been eaten or if they have finished game and gotten to the exit
*/
bool Maze::IsGameOver(){
    if(this->eaten || this->finish){
        return true;
    }
    return false;

}

/*
Prints out outcome of the game
*/
std::string Maze::GenerateReport(){
    std::string s = "";
    if(this->eaten){
        s = s + "Game Over: Eaten by Enemy";
    }
    else if(this->finish){
        s = s + "Game Over: Success! ";
    }
    return s;
}

/*
std::ostream& operator<<(std::ostream& os, const Maze &m){

}
*/



