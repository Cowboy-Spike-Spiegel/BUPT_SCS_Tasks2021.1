#include<iostream>
#include<vector>
#include<string.h>
#include"header.h"

//*main************************************************************************

int main()
{
    // get size of matrix A and B
    int row_A , column_A , numberSize_A , row_B , column_B , numberSize_B ;
    std::cout << "\nPlease input row , column and numberSize of the matrix A:\n" ;
    getSize ( row_A , column_A , numberSize_A ) ;
    std::cout << "\nPlease input row , column and numberSize of the matrix B:\n" ;
    getSize ( row_B , column_B , numberSize_B ) ;
  
    // judge to calculate
    bool judgePlus = ( row_A == row_B && column_A == column_B ) ;
    bool judgeMulAB = ( column_A == row_B ) ;
    bool judgeMulBA = ( column_B == row_A ) ;
    if ( !judgePlus && !judgeMulAB && !judgeMulBA ) {
        std::cout << "\nCan't plus or multiply.\n" ;
        return 0 ;
    }

    // create matrix A
    matrix A ;
    std::cout << "\nThen, create A.\n" ;
    A.create ( row_A , column_A , numberSize_A ) ;

    // create matrix B
    matrix B ;
    std::cout << "\nThen, create B.\n" ;
    B.create ( row_B , column_B , numberSize_B ) ;

    // calculate
    if ( judgePlus ) {
        std::cout << "\nA add B ( equal to B add A ) :\n" ;
        add ( A , B ) ;
    }
    if ( judgeMulAB ) {
        std::cout << "\nA multiply B :\n" ;
        mul ( A , B ) ;
    }
    if ( judgeMulBA ) {
        std::cout << "\nB multiply A :\n" ;
        mul ( B , A ) ;
    }

    return 0 ;
}

//*matrix**********************************************************************

void matrix::create ( int ro , int col , int numsize ) {
    row = ro ;
    column = col ;
    numberSize = numsize ;

    // judge can input
    if ( numberSize == 0 ) {
        std::cout << "No element can be insert.\n" ;
        return ;
    }
    else
        std::cout << "Input the row , column and value of each element.\n" ;
    
    std::vector<int> cnt ;
    cnt.insert ( cnt.begin() , row , 0 ) ;

    std::vector<int> temp ;  // temp triple
    while ( obj.size() < numberSize ) {
        // get imformation for an element
        std::cout << "The " << obj.size()+1 << " element:\n" ;
        getEmt ( temp ) ;

        // ignore invalid input
        if ( temp[0]>row || temp[0]<1 || temp[1]>column || temp[1]<1 ) {
            std::cout << row << " " << column << " " << numberSize << "\n" ;
            std::cout << temp[0] << " " << temp[1] << " " << temp[2] << "\n" ;
            std::cout << "Invalid input. Please try again.\n" ;
        }
        else {
            if ( (temp[0]-1)*column+temp[1] > row*column - (numberSize-obj.size()-1) )                
                std::cout << "There is not enough space for after elements. Please try again.\n" ;
            else {
                if ( obj.size() &&
                    (temp[0]<obj[obj.size()-1][0] ||
                    temp[0]==obj[obj.size()-1][0] && temp[1]<=obj[obj.size()-1][1]) )
                    std::cout << "The location is not after than the previous. Please try again.\n" ;
                else {
                    obj.push_back ( temp ) ;  // insert
                    cnt[temp[0]-1]++ ;  // count
                }
            }
        }
    }

    // calculate start
    start = new int[row+1]() ;
    start[0] = 0 ;
    for ( int i = 1 ; i < row ; i++ )
        start[i] = start[i-1]+cnt[i-1] ;
    start[row] = numberSize ;
}

// add operation of matrix S and matrix T
void add ( matrix& S , matrix& T )
{
    int row = S.row ;
    int column = S.column ;
    
    std::vector<std::vector<int>> answer ;  // answer of triple table
    int** ans = new int* [row] ;            // answer of array
    for ( int i = 0 ; i < row ; i++ ){
        ans[i] = new int[column] ;
        for ( int j = 0 ; j < column ; j++ )
            ans[i][j] = 0 ;
    }

    // add in steps
    for ( int i=0 , j=0 ; i < S.numberSize || j < T.numberSize ; ) {
        // row of matrix S equal to that of matrix T
        if ( S.obj[i][0] == T.obj[j][0] ) {
            // column of matrix S equal to that of matrix T
            if ( S.obj[i][1] == T.obj[j][1] ) {
                answer.push_back ( { S.obj[i][0] , S.obj[i][1] , S.obj[i][2]+T.obj[j][2] } ) ;
                ans[ S.obj[i][0]-1 ][  S.obj[i][1]-1 ] = S.obj[i][2]+T.obj[j][2] ;
                i++ ;
                j++ ;
            }
            // column of matrix S less than that of matrix T
            else if ( S.obj[i][1] < T.obj[j][1] ) {
                answer.push_back ( { S.obj[i][0] , S.obj[i][1] , S.obj[i][2] } ) ;
                ans[ S.obj[i][0]-1 ][  S.obj[i][1]-1 ] = S.obj[i][2] ;
                i++ ;
            }
            // column of matrix S greater than that of matrix T
            else if ( S.obj[i][1] > T.obj[j][1] ) {
                answer.push_back ( { T.obj[j][0] , T.obj[j][1] , T.obj[j][2] } ) ;
                ans[ T.obj[j][0]-1 ][  T.obj[j][1]-1 ] = T.obj[j][2] ;
                j++ ;
            }
        }
        // row of matrix S less than that of matrix T
        else if ( S.obj[i][0] < T.obj[j][0] ) {
            answer.push_back ( { S.obj[i][0] , S.obj[i][1] , S.obj[i][2] } ) ;
            ans[ S.obj[i][0]-1 ][  S.obj[i][1]-1 ] = S.obj[i][2] ;
            i++ ;
        }
        // row of matrix S greater than that of matrix T
        else if ( S.obj[i][0] > T.obj[j][0] ) {
            answer.push_back ( { T.obj[j][0] , T.obj[j][1] , T.obj[j][2] } ) ;
            ans[ T.obj[j][0]-1 ][  T.obj[j][1]-1 ] = T.obj[j][2] ;
            j++ ;
        }
    }
    
    // output answer
    std::cout << "Triple table:\n" ;
    for ( int i = 0 ; i < answer.size() ; i++ )
        std::cout << answer[i][0] << " " << answer[i][1] << " " << answer[i][2] << "\n" ;
    std::cout << "Array:\n" ;
    for ( int i = 0 ; i < row ; i ++ ) {
        for ( int j = 0 ; j < column ; j++ )
            std::cout << ans[i][j] << " " ;
        std::cout << "\n" ;
    }

    // release
    for ( int i = 0 ; i < row ; i++ )
        delete []ans[i] ;
    delete []ans ;
}

// mutiply operation of matrix S and matrix T
void mul ( matrix& S , matrix& T )
{
    int row = S.row ;
    int column = T.column ;

    std::vector<std::vector<int>> answer ;  // answer of triple table
    int** ans = new int* [row] ;            // answer of array
    for ( int i = 0 ; i < row ; i++ ){
        ans[i] = new int[column] ;
        for ( int j = 0 ; j < column ; j++ )
            ans[i][j] = 0 ;
    }

    // multiply two non-zero matrix
    if ( S.numberSize && T.numberSize ) {
        // traverse answer matrix
        for ( int r = 0 ; r < row ; r++ )
            for ( int c = 0 ; c < column ; c++ )
                // find each none-zero elements to add in current location
                for ( int i = S.start[r] ; i < S.start[r+1] ; i++ )
                    for ( int j = T.start[ S.obj[i][1]-1 ] ; j < T.start[ S.obj[i][1] ] ; j++ ) {
                        if ( T.obj[j][1] == c+1 ) {
                            ans[r][c] = S.obj[i][2]*T.obj[j][2] ;
                            answer.push_back ( { r+1 , c+1 , S.obj[i][2]*T.obj[j][2] } ) ;
                        }
                        if ( T.obj[j][1] > c+1 )
                            break ;
                    }
    }

    // output answer
    std::cout << "Triple table:\n" ;
    for ( int i = 0 ; i < answer.size() ; i++ )
        std::cout << answer[i][0] << " " << answer[i][1] << " " << answer[i][2] << "\n" ;
    std::cout << "Array:\n" ;
    for ( int i = 0 ; i < row ; i ++ ) {
        for ( int j = 0 ; j < column ; j++ )
            std::cout << ans[i][j] << " " ;
        std::cout << "\n" ;
    }

    // release
    for ( int i = 0 ; i < row ; i++ )
        delete []ans[i] ;
    delete []ans ;
}

//*getNums*********************************************************************

// for a matrix, get its row, column and numberSize
void getSize ( int& row , int& column , int& numberSize )
{
    while ( 1 ) {
        while ( std::cin.peek() == ' ' )  //input row
            std::cin.get() ;
        if ( std::cin.peek() == '\n' ) {
            std::cin.get() ;
            std::cout << "Invalid input. Please try again.\n" ;
            continue ;
        }
        std::cin >> row ;
        if (std::cin.fail()) 
        {
            std::cin.clear();
            std::cin.sync();
            std::cout << "Invalid input. Please try again.\n" ;
            continue ;
        }

        while ( std::cin.peek() == ' ' )  //input column
            std::cin.get() ;
        if ( std::cin.peek() == '\n' ) {
            std::cin.get() ;
            std::cout << "Invalid input. Please try again.\n" ;
            continue ;
        }
        std::cin >> column ;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.sync();
            std::cout << "Invalid input. Please try again.\n" ;
            continue ;
        }

        while ( std::cin.peek() == ' ' )  //input numberSize
            std::cin.get() ;
        if ( std::cin.peek() == '\n' ) {
            std::cin.get() ;
            std::cout << "Invalid input. Please try again.\n" ;
            continue ;
        }
        std::cin >> numberSize ;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.sync();
            std::cout << "Invalid input. Please try again.\n" ;
            continue ;
        }

        int flag = 1 ;
        while ( flag && std::cin.peek() != '\n' ) {
            if ( std::cin.get() != ' ' ) {
                std::cout << "Invalid input. Please try again.\n" ;
                flag = 0 ;
            }
        }
        while ( std::cin.get() != '\n' ) ;
        if ( !flag )
            continue ;

        if ( row < 1 || column < 1 || numberSize < 0 || numberSize > row*column )
            std::cout << "Invalid input. Please try again.\n" ;
        else
            break ;
    }
}

// for a matrix, get its each tirple consisting loc_row, Loc_col and value
void getEmt ( std::vector<int> & temp )
{
    int m , n , value ;
    while (1) {
        // ignore invalid input
        while ( std::cin.peek() == ' ' )
            std::cin.get() ;
        if ( std::cin.peek() == '\n' ) {
            std::cin.get() ;
            std::cout << "Invalid input. Please try again.\n" ;
            continue ;
        }
        std::cin >> m ;  // get m
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.sync();
            std::cout << "Invalid input. Please try again.\n" ;
            continue ;
        }

        // ignore invalid input
        while ( std::cin.peek() == ' ' )
            std::cin.get() ;
        if ( std::cin.peek() == '\n' ) {
            std::cin.get() ;
            std::cout << "Invalid input. Please try again.\n" ;
            continue ;
        }
        std::cin >> n ;  // get n
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.sync();
            std::cout << "Invalid input. Please try again.\n" ;
            continue ;
        }

        // ignore invalid input
        while ( std::cin.peek() == ' ' )
            std::cin.get() ;
        if ( std::cin.peek() == '\n' ) {
            std::cin.get() ;
            std::cout << "Invalid input. Please try again.\n" ;
            continue ;
        }
        std::cin >> value ;  // get value
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.sync();
            std::cout << "Invalid input. Please try again.\n" ;
            continue ;
        }

        int flag = 1 ;
        while ( flag && std::cin.peek() != '\n' ) {
            if ( std::cin.get() != ' ' ) {
                std::cout << "Invalid input. Please try again.\n" ;
                flag = 0 ;
            }
        }
        while ( std::cin.get() != '\n' ) ;
        if ( !flag )
            continue ;
        
        break ;
    }

    temp = { m , n , value } ;
}

