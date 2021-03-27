#include "Maze.h"

/*
Constructor for board. Initializes walls and treasure in random positions and then places player and exit
*/
Board::Board(){
	for(int row =0; row<this->get_rows(); row++){
        for(int col = 0; col<this->get_cols(); col++){
            this->arr_[row][col] = SquareType::Empty;
        }
    }

    //initialize walls
    for(int w = 0; w < 3; w++){
        int wx = rand()%this->get_rows();
        int wy = rand()%this->get_cols();

        this->arr_[wx][wy] = SquareType::Wall;
    }

    //initialize treats
    for(int t = 0; t< 3; t++){
        int tx = rand()%this->get_rows();
        int ty = rand()%this->get_cols();

        this->arr_[tx][ty] = SquareType::Wall;    
    }

    this->arr_[0][0] = SquareType::Human;
    this->arr_[this->get_rows()-1][this->get_cols()-1] = SquareType::Exit;


	this->rows_ = this->get_rows();
	this->cols_ = this->get_cols();
}

/*
Returns square type of a certain position on the board
*/
SquareType Board::get_square_value(Position pos) const{
    return this->arr_[pos.row][pos.col];  

}


/*
Sets square type of position to value
*/
void Board::SetSquareValue(Position pos, SquareType value){
    this->arr_[pos.row][pos.col] = value;
}

/*
// get the possible Positions that a Player could move to
//	// (not off the board or into a wall)
It does this by checking neighboring cells (north, east, south, west) to make sure they are not a wall or ouside grid
*/
std::vector<Position> Board::GetMoves(Player *p){
    Position n1 = {p->get_position().row-1, p->get_position().col};
    Position n2 = {p->get_position().row+1, p->get_position().col};
    Position n3 = {p->get_position().row, p->get_position().col-1};
    Position n4 = {p->get_position().row, p->get_position().col+1};

    std::vector<Position> possible_positions = {n1, n2, n3, n4};

    for(int i = 0; i< possible_positions.size(); i++){
        if(possible_positions[i].row < 0 || possible_positions[i].col < 0){
            possible_positions.erase(possible_positions.begin()+i);
        }
    
        if(possible_positions[i].row >= this->get_cols() || possible_positions[i].col >= this->get_cols()){
            possible_positions.erase(possible_positions.begin()+i);
        }
        if(get_square_value(possible_positions[i]) == SquareType::Wall){
            possible_positions.erase(possible_positions.begin()+i);    
        }
    }
    
    return possible_positions;
    
}

/*
Moves player to next position, sets previous player cell to empty and sets pos cell to player
*/
bool Board::MovePlayer(Player *p, Position pos){
    
    std::vector<Position> v = GetMoves(p);
    for(int i = 0; i<v.size(); i++){
        if(v[i] == pos){
            p->SetPosition(pos);
            SetSquareValue(pos, SquareType::Empty);

            SquareType sq = SquareType::Enemy;
            if(p->is_human()){
                sq = SquareType::Human;
            }
            SetSquareValue(pos, sq);
            return true;
        }
    }
    return false;

}

/*
Returns type of exit cell
*/
SquareType Board::GetExitOccupant(){
    Position exit = {this->get_rows()-1,this->get_cols()-1};
    return get_square_value(exit);
}

/*
Operator overloader that prints out board. This also defines what symbols everything is printed out as.
*/
std::ostream& operator<<(std::ostream& os, const Board &b){
    std::string s = "";
    for(int i = 0; i< b.get_rows(); i++){
        for(int j = 0; j< b.get_cols(); j++){
            Position pos = {i,j};
            if(b.get_square_value(pos) == SquareType::Wall){
                s = s + "   X   ";
            }
            else if(b.get_square_value(pos) == SquareType::Empty){
                s = s + "   _   ";
            }
            else if(b.get_square_value(pos) ==SquareType::Exit){
                s = s + "   !   ";
            }
            else if(b.get_square_value(pos) == SquareType::Human){
                s = s + "   H   ";
            }
            else if(b.get_square_value(pos) == SquareType::Enemy){
                s = s + "   E   ";
            }
            else if(b.get_square_value(pos) == SquareType::Treasure){
                s = s + "   T   ";
            }
        }
        s = s + "\n";
    }
    os << s;
    return os;
}

std::string Board::StringifyBoard(){
    std::string s = "";
        for(int i = 0; i< this->get_rows(); i++){
            for(int j = 0; j< this->get_cols(); j++){
                Position pos = {i,j};
                if(this->get_square_value(pos) == SquareType::Wall){
                    s = s + "   X   ";
                }
                else if(this->get_square_value(pos) == SquareType::Empty){
                    s = s + "   _   ";
                }
                else if(this->get_square_value(pos) ==SquareType::Exit){
                    s = s + "   !   ";
                }
                else if(this->get_square_value(pos) == SquareType::Human){
                    s = s + "   H   ";
                }
                else if(this->get_square_value(pos) == SquareType::Enemy){
                    s = s + "   E   ";
                }
                else if(this->get_square_value(pos) == SquareType::Treasure){
                    s = s + "   T   ";
                }
            }
            s = s + "\n";
    }
    return s;
}
