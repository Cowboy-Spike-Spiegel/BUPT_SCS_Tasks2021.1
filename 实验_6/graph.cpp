#include"graph.h"

int main()
{
    Str word ;
    // read the input of size
    word.print( "Please input the size of nodes.\n" ) ;
    int size ;
    while ( 1 ) {
        std::cin >> size ;
        if ( ! std::cin.fail() )
            break ;
        std::cin.clear() ;
        std::cin.sync() ;
        word.print( "Input number is tooooo big! Please try again." ) ;
    }
    std::cin.clear() ;
    std::cin.sync() ;

    // read the form of graph
    word.print( "Please input the form of graph.\n" ) ;
    word.print( "Directed is D/d, Undirected is U/u.\n" ) ;
    char ch ;
    while( 1 ) {
        ch = std::getchar() ;
        std::cin.clear() ;
        std::cin.sync() ;
        if ( ch == 'D' || ch == 'd' || ch == 'U' || ch == 'u' )
            break ;
        word.print( "Invalid input! Please try again." ) ;
    }
    
    // calculate and output the answer
    if ( ch=='U' || ch=='u' ) {
        Undirected_AdjacencyMatrix obj ;
        if ( obj.create_AdjacencyMatrix( size ) ) {
            obj.generate_nearSide() ;
            std::cout << "\nThe answer is:\n" << obj.Max_in_nearside() << "\n" ;
        }
        else
            word.print( "Error! Can't allocate enough memory for your size." ) ;
    }
    else {
        Directed_AdjacencyMatrix obj ;
        if ( obj.create_AdjacencyMatrix( size ) ) {
            obj.generate_nearSide() ;
            std::cout << "\nThe answer is:\n" << obj.Max_in_nearside() << "\n" ;
        }
        else
            word.print( "Error! Can't allocate enough memory for your size." ) ;
    }

    system( "Pause" ) ;
    return 0 ;
}