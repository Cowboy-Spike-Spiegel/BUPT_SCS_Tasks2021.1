#include<iostream>
#include<vector>
#include<cmath>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>

// read size numbers, and return false when error occurs.
    bool getnumbers( int size , int* edges ) ;
// cleaner when errors occur
    void clean( int mode ) ;


// struct Side: struct of edge table
typedef struct Side {
    int info ;
    int adjvex ;
    struct Side* nextarc ;
} side , *sidePtr ;
// ------------------------- end struct Side


// class Str: useful tool to print strings
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
// --------------------------- end class Str


// class AdjacencyMatrix: our undirected graph table
class Undirected_AdjacencyMatrix {
private:
    sidePtr* head ;
    int** weights ;
    int* nearEdge ;
    int max_nearEdge ;
    int size ;
public:
    Undirected_AdjacencyMatrix( void ) ;
    bool create_AdjacencyMatrix( int input ) ;
    void generate_nearSide( void ) ;
    int Max_in_nearside( void ) ;
} ;
// initialize
Undirected_AdjacencyMatrix::Undirected_AdjacencyMatrix( void ) {
    head = NULL ;
    weights = NULL ;
    nearEdge = NULL ;
    max_nearEdge = -1 ;
    size = 0 ;
}
// create adjacency matrix
bool Undirected_AdjacencyMatrix::create_AdjacencyMatrix( int input ) {
    size = input ;

    // allocate space for node table-head & matrix-weights
    head = (sidePtr*) malloc ( sizeof(sidePtr)*size ) ;
    weights = (int**) malloc ( sizeof(int*)*size ) ;
    for ( int i=0 ; i < size ; i++ ) {
        head[i] = (sidePtr) malloc ( sizeof(side) ) ;
        head[i]->info = 0 ;
        head[i]->nextarc = NULL ;
        weights[i] = (int*) malloc ( sizeof(int)*size ) ;
        weights[i][i] = 0 ;
    }

    // get size numbers
    for ( int index=0 ; index < size-1 ; index++ ) {
        std::cout << "\nWeight edges of " <<index+1 << " node(" << size-index-1 << " elements):\n" ;
        int* edges = ( int* ) malloc ( sizeof(int)*(size-index-1) ) ;
        while ( ! getnumbers( size-index-1 , edges ) ) ;

        sidePtr preA=head[index] ;
        // find the position fot inserting in index line
        while ( preA->nextarc != NULL )
            preA=preA->nextarc ;
        
        // insert edges in table-head & matrix-weights
        for ( int i=0 ; i < size-index-1 ; i++ ) {
            if ( edges[i] > 0 ) {
                // insert edge in current node
                (head[i]->info)++ ;
                preA->nextarc = new side ;
                preA->nextarc->info = edges[i] ;
                preA->nextarc->adjvex = index+i+2 ;
                preA->nextarc->nextarc = NULL ;
                preA = preA->nextarc ;

                // insert edge in another node of this edge
                (head[index+i+1]->info)++ ;
                sidePtr preB = head[index+i+1] ;
                while ( preB->nextarc != NULL )
                    preB = preB->nextarc ;
                preB->nextarc = new side ;
                preB->nextarc->info = edges[i] ;
                preB->nextarc->adjvex = index+1 ;
                preB->nextarc->nextarc = NULL ;

                // insert in matrix
                weights[index][index+i+1] = edges[i] ;
                weights[index+i+1][index] = edges[i] ;
            }
        }
    }

    return true ;
}
//
void Undirected_AdjacencyMatrix::generate_nearSide( void ) {
    for ( int index=0 ; index < size ; index++ ) {
        for ( int i=0 ; i < size ; i++ ) {
            if ( i == index )
                continue ;
            for ( int j=0 ; j < size ; j++ ) {
                if ( j == index )
                    continue ;
                weights[i][j] =
                ( weights[i][j] < (weights[index][j]+weights[i][index]) ) ?
                weights[i][j] : (weights[index][j]+weights[i][index]) ;
            }
        }
    }
}
//
int Undirected_AdjacencyMatrix::Max_in_nearside( void ) {
    for ( int i=0 ; i < size-1 ; i++ ) {
        for ( int j=i+1 ; j< size ; j++ ) {
            if ( weights[i][j] > 0 ) {
                if ( max_nearEdge == weights[i][j] )
                    std::cout << "Length->" << max_nearEdge << ", nodes: " << i+1 << " " << j+1 << "\n" ;
                if ( max_nearEdge < weights[i][j] ) {
                    max_nearEdge = weights[i][j] ;
                    std::cout << "Length->" << max_nearEdge << ", nodes: " << i+1 << " " << j+1 << "\n" ;
                }
            }
        }
    }
    return max_nearEdge ;
}
// --------------- end class Undirected_AdjacencyMatrix


// class AdjacencyMatrix: our directed graph table
class Directed_AdjacencyMatrix {
private:
    sidePtr* head ;
    int** weights ;
    int* nearEdge ;
    int max_nearEdge ;
    int size ;
public:
    Directed_AdjacencyMatrix( void ) ;
    bool create_AdjacencyMatrix( int input ) ;
    void generate_nearSide( void ) ;
    int Max_in_nearside( void ) ;
} ;
// initialize
Directed_AdjacencyMatrix::Directed_AdjacencyMatrix( void ) {
    head = NULL ;
    weights = NULL ;
    nearEdge = NULL ;
    max_nearEdge = -1 ;
    size = 0 ;
}
// create adjacency matrix
bool Directed_AdjacencyMatrix::create_AdjacencyMatrix( int input ) {
    size = input ;

    // allocate space for node table-head & matrix-weights
    if ( !( head = (sidePtr*) malloc ( sizeof(sidePtr)*size ) ) )
        return false ;
    if ( !( weights = (int**) malloc ( sizeof(int*)*size )) )
        return false ;
    for ( int i=0 ; i < size ; i++ ) {
        if ( !( head[i] = (sidePtr) malloc ( sizeof(side) ) ) )
            return false ;
        head[i]->info = 0 ;
        head[i]->nextarc = NULL ;
        if ( !( weights[i] = (int*) malloc ( sizeof(int)*size ) ) )
            return false ;
        weights[i][i] = 0 ;
    }

    // get size numbers
    for ( int index=0 ; index < size ; index++ ) {
        std::cout << "\nWeight edges of " <<index+1 << " node(" << size-1 << " elements):\n" ;
        int* edges = ( int* ) malloc ( sizeof(int)*(size-1) ) ;
        while ( ! getnumbers( size-1 , edges ) ) ;

        // insert edges in table-head & matrix-weights
        sidePtr preA=head[index] ;
        for ( int i=0 ; i < size ; i++ ) {
            if ( i == index )
                continue ;
            if ( edges[i] > 0 ) {
                // insert edge in current node
                (head[i]->info)++ ;
                preA->nextarc = new side ;
                preA->nextarc->info = edges[i] ;
                preA->nextarc->adjvex = index+i+2 ;
                preA->nextarc->nextarc = NULL ;
                preA = preA->nextarc ;

                // insert in matrix
                if ( i < index )
                    weights[index][i] = edges[i] ;
                else
                    weights[index][i] = edges[i-1] ;
            }
        }
    }

    return true ;
}
//
void Directed_AdjacencyMatrix::generate_nearSide( void ) {
    for ( int index=0 ; index < size ; index++ ) {
        for ( int i=0 ; i < size ; i++ ) {
            if ( i == index )
                continue ;
            for ( int j=0 ; j < size ; j++ ) {
                if ( j == index )
                    continue ;
                weights[i][j] =
                ( weights[i][j] < (weights[index][j]+weights[i][index]) ) ?
                weights[i][j] : (weights[index][j]+weights[i][index]) ;
            }
        }
    }
}
//
int Directed_AdjacencyMatrix::Max_in_nearside( void ) {
    for ( int i=0 ; i < size ; i++ ) {
        for ( int j=0 ; j< size ; j++ ) {
            if ( weights[i][j] > 0 ) {
                if ( max_nearEdge == weights[i][j] )
                    std::cout << "Length->" << max_nearEdge << ", node1: " << i+1 << " node2: " << j+1 << "\n" ;
                if ( max_nearEdge < weights[i][j] ) {
                    max_nearEdge = weights[i][j] ;
                    std::cout << "Length->" << max_nearEdge << ", node1: " << i+1 << " node2: " << j+1 << "\n" ;
                }
            }
        }
    }
    return max_nearEdge ;
}
// --------------- end class AdjacencyMatrix


// read size numbers, and return false when error occurs.
bool getnumbers( int size , int* edges ) {
    // read (size) numbers
    for ( int i = 0 ; i < size ; i++ ) {

        while ( std::cin.peek() == ' ' ) // ignore front spaces
            std::cin.get() ;
        if ( std::cin.peek() == '\n' ) {
            clean(1) ; // error_1: less than size
            return false ;
        }

        // get edge
        std::cin >> edges[i] ;
        
        if ( std::cin.fail() ) {
            clean(3) ; // error_3: overflow
            return false ;
        }
        if ( edges[i] < 0 ) {
            clean(4) ; // error_4: number small than 0
            return false ;
        }
    }
    // ignore tails
    char ch ;
    while ( ch = std::cin.get() ) {
        if ( ch == '\n' ) {
            std::cin.clear() ;
            std::cin.sync() ;
            return true ;
        }
        if ( ch != ' ' ) {
            clean(2) ; // error_2: input more than size
            return false ;
        }
    }

    return false ;
}

// cleaner when errors occur
void clean ( int mode ) {
    std::cin.clear() ;
    std::cin.sync() ;
    
    Str word ;
    if ( mode == 1 )
        word.print( "Less than size! Please try again." ) ;
    else if ( mode == 2 )
        word.print( "More than size! Please try again." ) ;
    else if ( mode == 3 )
        word.print( "Overflow! Please try again." ) ;
    else if ( mode == 4 )
        word.print( "Number can't be minus! Please try again." ) ;
}