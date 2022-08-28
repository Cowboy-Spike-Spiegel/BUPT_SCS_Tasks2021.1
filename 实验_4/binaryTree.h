#include<iostream>
#include<vector>
#include<cmath>
#include<stdlib.h>
#include<windows.h>


// create location & lattice --------------------------------------------------
void create_Location_Lattice( std::vector<std::vector<int>>& location ,
                              std::vector<std::vector<char>>& lattice ,
                              int layers ) ;
void create_Location_Lattice( std::vector<std::vector<int>>& location ,
                              std::vector<std::vector<char>>& lattice ,
                              int layers ) {
    // variables needed
    int row = 2*layers-1 ;
    int column = 3*( pow( 2 , layers )-1 ) ;
    int size = pow( 2 , layers )-1 ;

    // initialize location&lattice of last line
    for ( int j=0 ; j < pow( 2 , layers-1 ) ; j++ ) {
        
        location[j+(size+1)/2-1][0] = row-1 ;
        location[j+(size+1)/2-1][1] = 6*j+1 ;
        
        lattice[row-1][6*j] = '(' ;
        lattice[row-1][6*j+2] = ')' ;
    }

    // bulid the upper line with lower line
    for ( int line = layers-1 ; line > 0 ; line-- ) {
        /*  size of current line
            and number of first element of this line is (lineSize)
        */
        int lineSize = pow( 2 , line-1 ) ;
        for ( int cnt = 0 ; cnt < lineSize ; cnt++ ) {
            // location
            location[cnt+lineSize-1][0] = 2*line-2 ;
            location[cnt+lineSize-1][1]
                = ( location[ 2*(cnt+lineSize)-1][1] + location[ 2*(cnt+lineSize)][1] )/2 ;
            // lattice
            lattice[2*line-2][ location[cnt+lineSize-1][1]-1 ] = '(' ;
            lattice[2*line-2][ location[cnt+lineSize-1][1]+1 ] = ')' ;
            for ( int j=location[cnt+lineSize-1][1]-2 ; j > location[ 2*(cnt+lineSize)-1][1] ; j-- )
                lattice[2*line-2][j] = '_' ;
            lattice[2*line-1][ location[ 2*(cnt+lineSize)-1][1] ] = '|' ;
            for ( int j=location[cnt+lineSize-1][1]+2 ; j < location[ 2*(cnt+lineSize)][1] ; j++ )
                lattice[2*line-2][j] = '_' ;
            lattice[2*line-1][ location[ 2*(cnt+lineSize)][1] ] = '|' ;
        }
    }

    return ;
}
// ----------------------------------------------------------------------------


// class str ------------------------------------------------------------------
class Str
{
private :
    std::string obj ;
public :
    void print ( std::string input ) ;
} ;
void Str::print ( std::string input ) {
    obj = input ;
    for ( int i=0 ; i < obj.length() ; i++ ) {
        std::cout << obj[i] ;
        Sleep( 40 ) ;
    }
    std::cout << "\n" ;
    Sleep( 300 ) ;
}
// ----------------------------------------------------------------------------