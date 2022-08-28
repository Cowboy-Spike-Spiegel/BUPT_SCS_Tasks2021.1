
#include"binaryTree.h"
#define Eletype BTptr


// Binary Tree ----------------------------------------------------------------
typedef struct bt {
    struct bt* lChild ;
    struct bt* rChild ;
    int pos ;
    char value ;
} BT , *BTptr ;
// ----------------------------------------------------------------------------


// class queue ----------------------------------------------------------------
class Queue // ignore it can be full
{
private :
    Eletype* queue ;
    int front ;
    int rear ;
    int maxSize ;
public :
    Queue ( void ) ;
    void create ( int size ) ;
    void enqueue ( Eletype obj ) ;
    Eletype delqueue ( void ) ;
    bool isEmpty ( void ) ;
    void burden ( void ) ;
} ;
Queue::Queue ( void ) {
    queue = NULL ;
    maxSize = front = rear = -1 ;
}
void Queue::create ( int size ) {
    queue = (Eletype*) malloc ( sizeof(Eletype)*size ) ;
    maxSize = size ;
}
void Queue::enqueue ( Eletype obj ) {
    rear = (rear+1) % maxSize ;
    queue[rear] = obj ;
}
Eletype Queue::delqueue ( void ) {
    front = (front+1) % maxSize ;
    return queue[front] ;
}
bool Queue::isEmpty ( void ) {
    if ( rear == front )
        return true ;
    return false ;
}
// ----------------------------------------------------------------------------


// class Tree -----------------------------------------------------------------
class Tree
{
private:
    BTptr root ;
    int layers ;
    int eleSize ;
public:
    Tree ( void ) ;
    void create ( std::string input ) ; // 初始化头节点
    void createSon ( BTptr cur , std::string input , int& index , int layer ) ; // 建子树
    void print ( void ) ; // 输出
} ;
Tree::Tree ( void ) {
    root = NULL ;
    layers = 0 ;
    eleSize = 0 ;
}
void Tree::create ( std::string input ) {
    root = new BT ;
    root->pos = 1 ;
    root->lChild = NULL ;
    root->rChild = NULL ;

    Str word ;
    word.print( "\nPos is the code of elements' location in Perfect BinaryTree." ) ;
    word.print( "Ch is the value of characters.\n" ) ;
    int index = 0 ;
    createSon ( root , input , index , 0 ) ;

    if ( index < input.length() ) { // 此时树建完了但还有 * 存在
        word.print( "Warning: binaryTree is builted, but has '*' left.\n" ) ;
        Sleep( 2000 ) ;
    }
    word.print( "The eleSize of this binaryTree is " + std::to_string(eleSize) +"." ) ;
    word.print( "The layers of this binaryTree is " + std::to_string(layers) + "." ) ;

    return ;
}
void Tree::createSon ( BTptr cur , std::string input , int& index , int layer ) {
    
    if ( input[index] == '*' ) {
        cur->value = input[index++] ;
        return ;
    }

    Str word ;
    word.print( "pos = " + std::to_string( cur->pos ) + " ch = " + input[index] ) ;
    cur->value = input[index++] ;
    layers = ( ++layer > layers ) ? layer : layers ;
    eleSize++ ;

    if ( index < input.length() ) {
        cur->lChild = new BT ;
        cur->lChild->pos = 2*cur->pos ; // 左子树完全二叉树编号的传递
        cur->lChild->lChild = NULL ;
        cur->lChild->rChild = NULL ;
        createSon( cur->lChild , input , index , layer ) ;
    }
    if ( index < input.length() ) {
        cur->rChild = new BT ;
        cur->rChild->pos = 2*cur->pos+1 ; // 右子树完全二叉树编号的传递
        cur->rChild->lChild = NULL ;
        cur->rChild->rChild = NULL ;
        createSon( cur->rChild , input , index , layer ) ;
    }

    return ;
}
void Tree::print ( void ) {
    Str word ;
    // empty
    if ( root->value == '*' ) {
        word.print( "\nIt's empty!" ) ;
        return ;
    }
    Sleep( 2000 ) ;
    
    // intialize 
    int size = pow( 2 , layers )-1 ;  // size of elements
    int row = 2*layers-1 ;  // row of lattice
    int column = 3*( pow( 2 , layers )-1 ) ;  // column of lattice
    // location of each element with its row and column
    std::vector<std::vector<int>> location( size , std::vector<int>( 2 , 0 ) ) ;
    // lattice of binaryTree contained with visual chars
    std::vector<std::vector<char>> lattice( row , std::vector<char>( column , ' ' ) ) ;
    
    create_Location_Lattice ( location , lattice , layers ) ;
    word.print( "\nstruct of lattice:" ) ;
    for ( int i=0 ; i < row ; i++ ) {
        for ( int j=0 ; j < column ; j++ ) 
            std::cout << lattice[i][j] ;
        std::cout << "\n" ;
    }
    Sleep( 3000 ) ;

    int flag = 1 ;  // correct tree
    Queue obj ;
    obj.create( size ) ;
    obj.enqueue ( root ) ;
    while ( flag && !obj.isEmpty() ) {
        BTptr cur = obj.delqueue() ;
        // error! -------------------------------------------------------------
        if ( cur->lChild == NULL || cur->rChild == NULL ) {
            word.print( "There are something wrong with this element:" ) ;
            std::cout << "'" << cur->value << "'" ;
            word.print( " has NULL but '*' as its lchild or rchild." ) ;
            Sleep( 3000 ) ;
            flag = 0 ;
            continue ;
        }
        // insert -------------------------------------------------------------
        if ( cur->value != '*' ) {
            lattice[ location[ cur->pos-1 ][0] ][ location[ cur->pos-1 ][1] ] = cur->value ;
            // print
            system("cls");
            std::cout << "Inserting~\n" ;
            for ( int i=0 ; i < row ; i++ ) {
                for ( int j=0 ; j < column ; j++ ) 
                    std::cout << lattice[i][j] ;
                std::cout << "\n" ;
            }
            Sleep( 1000 ) ;
        }
        if ( cur->lChild->value != '*' )
            obj.enqueue( cur->lChild ) ;
        if ( cur->rChild->value != '*' )
            obj.enqueue( cur->rChild ) ;
    }

    system("cls");
    word.print( "\nThe end!!!!!!!!!!\n" ) ;
    if ( flag )
        for ( int i=0 ; i < row ; i++ ) {
            for ( int j=0 ; j < column ; j++ ) 
                std::cout << lattice[i][j] ;
            std::cout << "\n" ;
        }
    else
        word.print( "The input is invalid." ) ;
    std::cout << "\n" ;

    return ;
}
// ----------------------------------------------------------------------------


// main -----------------------------------------------------------------------
int main()
{
    Str word ;
    word.print( "\nPlease input BinaryTree by a line with correct characters.\n" ) ;
    std::string input ;
    std::cin >> input ;
    
    Tree obj ;
    obj.create( input ) ;
    obj.print() ;

    system( "pause" ) ;
    return 0 ;
}