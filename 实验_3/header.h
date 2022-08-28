class matrix
{
public:
    void create ( int row , int column , int numberSize ) ;

    int row ;
    int column ;
    int numberSize ;
    std::vector<std::vector<int>> obj ;
    int* start ;
} ;

// for a matrix, get its row, column and numberSize
void getSize ( int& row , int& column , int& numberSize ) ;
// for a matrix, get its each tirple consisting loc_row, Loc_col and value
void getEmt ( std::vector<int> & temp ) ;

// add operation of matrix S and matrix T
void add ( matrix& S , matrix& T ) ;
// mutiply operation of matrix S and matrix T
void mul ( matrix& S , matrix& T ) ;