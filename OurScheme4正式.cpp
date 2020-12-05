# include <ctype.h>
# include <stdio.h>
# include <iostream>		
# include <string>		
# include <vector>		
# include <cstdlib>		
# include <iomanip>		
# include <string.h>
# include <stdlib.h>

using namespace std;

enum TokenType {
  LP = '(', RP = ')', DOT = '.', QUOTE = '\'', INT = 333333, FLOAT = 444444, 
  NIL = 555555, T = 666666, STRING = 777777, SYMBOL = 888888, RESERW = 999999
}; 


typedef char StrOTE[1024];

struct gPuin {
  int define;
  int AnoDef;
  bool   hasAnD;
} ;

struct Token {
  int    type;   
  int   value;  
  int    line;   
  int  column;   
  int address;
  Token * next;
}; 

typedef Token * TokenPtr;

struct Tnode {
  TokenPtr  tok;
  int tieNum;
  Tnode *  left;
  Tnode * right;
}; 

typedef Tnode * TnodePtr;

struct LocalSymbol {
  TnodePtr   ting; 
  int        localId;
  LocalSymbol * next;
};

typedef LocalSymbol * LocalSymPtr;

struct Entry {            
  StrOTE         tokenStr; 
  TnodePtr        ting; 
  LocalSymPtr localSymbol;
}; 

int gLId = 0;
int gPTC = 0;
int gINMP = 0;
char gCB[ 5 ]; 
bool gIE = false ;
int gCBp = 0;    
TokenPtr gLT  = NULL;
int gLine = 1, gColumn = 0;
int gTokentype = '\0'; 
int gMA = 0;
StrOTE gLTS; 
int gLTS_top = -1;
char gSpr[128];
TokenPtr gSQh = NULL;
TnodePtr gPT = NULL;
bool gHQu = false;
Entry gSymT[1009] ; 
StrOTE gStrT[1009] ; 
double gFT[1009]  ;
int gIT[1009]  ;  
StrOTE gRT[101] ;
bool paste ;
bool dpaste;
gPuin dfuse ;
int dcount = 0 ;
vector<gPuin> uset;

TnodePtr ShinFun( TnodePtr head, TnodePtr mid, bool isLambda ) ;
bool CFAN( TnodePtr dest, TnodePtr src ) ;
TnodePtr EUF( TnodePtr input, TnodePtr func, int level ) ;
TnodePtr LamO( TnodePtr input ) ;
TnodePtr LetO( TnodePtr input, int level ) ;
TokenPtr gSexp = NULL, gLastSexp = NULL;  
void InSp( TokenPtr tok ) ;
void FrSp() ;
TokenPtr SeDeQ() ;
void SePush( TokenPtr tok ) ;
TnodePtr Ntnode( TokenPtr parseTree ) ;
TnodePtr BPTree() ; 
void CoutTok( TokenPtr tok, bool isPrintTree, bool isNewline ) ;
void CoutTree( TnodePtr parseTree, int i, bool isWrite ) ;
bool Parser( TnodePtr & parseTree ) ;
bool GetSe( TokenPtr tok ) ;
void CoutSE( TokenPtr tok, char c ) ;
void Information() ;            
void Escape_scheme() ;      
bool Emp( int top ) ;     
int GetCh() ;        
void NoCh( int c ) ; 
int GetToken() ;    
int GetStr()   ;     
void SkipL() ;
bool IsSpr( char c ) ;
bool InformationTok( StrOTE tok ) ;
bool IsFTok( StrOTE tok ) ;
TokenPtr ShinToken( int type, int value, int line, int column ) ;
bool ArthurOppo( double & result, bool & hasFloat, TnodePtr mid, int opr, int level ) ;
bool StrOppo( int & answer, TnodePtr mid, int opr, int level ) ;
TnodePtr StrApp( TnodePtr mid, int level ) ;
bool TnT( TnodePtr dest, TnodePtr src ) ;
TnodePtr LogOppo( TnodePtr mid, int opr, int level ) ;
TnodePtr PartSus( TnodePtr mid, int funcType, int level ) ;
TnodePtr Ifoppo( TnodePtr input, int level ) ;
TnodePtr Prerequis( TnodePtr input, int level ) ;
void LTS_push( char c ) ;
int Hash( StrOTE src ) ;   
int SymTPush( int hvalue ) ;
bool SGetting( TnodePtr & ting, TokenPtr symbol ) ;
void SSetting( int symValue, TnodePtr sexp ) ;
void SSetHere( int value, TnodePtr ting, int localId ) ;
void WashEv() ;
LocalSymPtr ShinHere( TnodePtr ting, int localId ) ;
void PopHereS( int symValue ) ;
int StrTPush( StrOTE src ) ;        
int FTPush( double d ) ;
int ITPush( int i ) ;
int RTSearch( int hvalue ) ;  
TokenPtr TokCpy( TokenPtr src  ) ;
TnodePtr TreeCpy( TnodePtr root ) ;
void LFTree( TnodePtr root ) ;
TnodePtr Evolution( TnodePtr parseTree, int level ) ;
TnodePtr KBuiFun( TnodePtr input, int funcType, int level ) ;
void GBF( TnodePtr input ) ;

StrOTE gEMsg;
bool gIRd = false;
bool gVbM = true;

int main() {
  int tNum = 0;
  if ( scanf( "%d", &tNum ) == EOF ) 
    Escape_scheme();
  Information();
  printf( "Welcome to OurScheme!\n" );
  for ( ; true ; ) {
    printf( "\n> " );
    if ( Parser( gPT ) && !gIE ) {
      TnodePtr answer = Evolution( gPT, 0 );
      if ( answer ) {
        if ( answer -> tok -> type == -3 )
          printf( "ERROR (no return value) : " ), CoutTree( gPT, 1, false );
        else CoutTree( answer, 1, false );
        LFTree( answer );
      } // if

      LFTree( gPT ), gPT = NULL;
    } // if
    
    if ( gIE ) 
      printf( "\n" ), Escape_scheme();
  } // for
} // main()

TnodePtr ShinFun( TnodePtr head, TnodePtr mid, bool isLambda ) {
  TnodePtr put = new Tnode;
  int      type = 7557;
  if ( isLambda ) type = 333;
  put -> tok   = ShinToken( type, 1, 0, 0 );
  put -> left  = head;
  put -> right = mid;
  put -> tieNum = 0;
  return put;
} // ShinFun()

LocalSymPtr ShinHere( TnodePtr ting, int localId ) {
  LocalSymPtr here = new LocalSymbol;
  here ->  ting = ting;
  here ->  localId = localId;
  here ->  next = NULL;
  return here;
} // ShinHere()

void SSetHere( int value, TnodePtr ting, int localId ) {
  if ( !gSymT[ value ].localSymbol ) {
    gSymT[ value ].localSymbol = ShinHere( ting, localId );
    return;
  } // if

  LocalSymPtr temp = ShinHere( ting, localId );
  temp   ->   next = gSymT[  value ].localSymbol;
  gSymT[ value ].localSymbol = temp;
} // SSetHere()

void PopHereS( int symValue ) {
  LocalSymPtr temp = gSymT[ symValue ].localSymbol;
  gSymT[ symValue ].localSymbol = gSymT[ symValue ].localSymbol -> next;
  LFTree( temp -> ting );
  delete temp;
} // PopHereS()

bool SGetting( TnodePtr & ting, TokenPtr symbol ) {
  if ( gSymT[ symbol -> value ].localSymbol && 
       gSymT[ symbol -> value ].localSymbol -> localId == gLId ) {
    ting = gSymT[ symbol -> value ].localSymbol -> ting;
    if ( !ting ) {
      printf( "ERROR (unbound local symbol) : " ), CoutTok( symbol, false, 92 );
      return false;
    } // if
    
    return true;
  } // if
  
  ting = gSymT[ symbol -> value ].ting;
  if ( !ting ) {
    printf( "ERROR (unbound symbol) : " ), CoutTok( symbol, false, 92 );
    return false;
  } // if
  
  return true;
} // SGetting()

void SSetting( int value, TnodePtr sexp ) {
  if ( gSymT[ value ].ting ) {
    if      ( gSymT[ value ].ting == sexp ) return;
    if      ( gSymT[ value ].ting -> tieNum >  1 ) gSymT[ value ].ting -> tieNum--;
    else if ( gSymT[ value ].ting -> tieNum == 1 ) LFTree( gSymT[ value ].ting );
  } // if

  sexp -> tieNum++;
  gSymT[ value ].ting = sexp;
} // SSetting()

void WashEv() {
  gMA = 0;
  for ( int i = 1 ; i < 1009 ; i++ ) {
    if ( i != 243 && gSymT[ i ].tokenStr[ 0 ] ) gSymT[ i ].tokenStr[ 0 ] = '\0';
    if ( gSymT[ i ].ting ) {
      if ( gSymT[ i ].ting -> tieNum == 1 )
        LFTree( gSymT[ i ].ting ),     gSymT[ i ].ting = NULL;
      else if ( gSymT[ i ].ting -> tieNum > 1 )
        gSymT[ i ].ting -> tieNum--,  gSymT[ i ].ting = NULL;
    } // if
    
    if ( gStrT[ i ][ 0 ] ) gStrT[ i ][ 0 ] = '\0';
    if ( gIT[ i ]      ) gIT[ i ]      =   0 ;
    if ( gFT[ i ]      ) gFT[ i ]      =   0 ;
  } // for
} // WashEv()

TokenPtr TokCpy( TokenPtr src ) {
  if ( !src ) 
    return NULL;
  return ShinToken( src -> type, src -> value, src -> line, src -> column );
} // TokCpy()

TnodePtr TreeCpy( TnodePtr root ) {
  if ( !root ) 
    return NULL;
  TnodePtr     temp = Ntnode( TokCpy( root -> tok ) );
  temp -> tieNum = root -> tieNum;
  temp ->      left = TreeCpy( root ->  left );
  temp ->     right = TreeCpy( root -> right );
  return temp;
} // TreeCpy()

void LFTree( TnodePtr root ) {
  if ( !root ) 
    return;
  LFTree( root ->  left );
  LFTree( root -> right );
  delete root -> tok, delete root;
} // LFTree()

TnodePtr PrimitivePredicates( TnodePtr mid, int opr, int level ) {
  if ( !mid || ( mid && mid -> right ) ) {
    printf( "ERROR (incorrect number of arguments) : %s\n", gRT[ opr ] );
    return NULL;
  } // if 
  
  TnodePtr node = Evolution( mid -> left, level+1 );
  if ( !node ) return NULL;
  int type  = node -> tok -> type, value = node -> tok -> value;
  LFTree( node );
  if ( type == -3 ) {
    printf( "ERROR (unbound condition) : " ), CoutTree( mid -> left, 1, false );
    return NULL;
  } // if
  
  if       ( opr  == 26  )
    return type   == STRING ? Ntnode( ShinToken( T, 1, 0, 0 ) ) : Ntnode( ShinToken( NIL, 1, 0, 0 ) );
  else if  ( opr  == 78  )
    return ( type == SYMBOL || type == RESERW ) ?
      Ntnode( ShinToken( T, 1, 0, 0 ) ) : Ntnode( ShinToken( NIL, 1, 0, 0 ) );
  else if  ( opr  == 84  )
    return type   == INT    ? Ntnode( ShinToken( T, 1, 0, 0 ) ) : Ntnode( ShinToken( NIL, 1, 0, 0 ) );
  else if  ( opr  == 8 )
    return type   == NIL    ? Ntnode( ShinToken( T, 1, 0, 0 ) ) : Ntnode( ShinToken( NIL, 1, 0, 0 ) );
  else if  ( opr  == 81 ) {
    if     ( type == NIL || type == T ) return Ntnode( ShinToken(   T, 1, 0, 0 ) );
    else                                return Ntnode( ShinToken( NIL, 1, 0, 0 ) );
  } // else if
  else if  ( opr  == 70 || opr == 46 ) { 
    if     ( type == INT   || type == FLOAT ) return Ntnode( ShinToken(   T, 1, 0, 0 ) );
    else                                      return Ntnode( ShinToken( NIL, 1, 0, 0 ) );
  } // else if
  else if  ( opr  == 99 )
    if     ( type == LP || type == 7557 || type == 333 ) return Ntnode( ShinToken( NIL, 1, 0, 0 ) );
    else                                                       return Ntnode( ShinToken(   T, 1, 0, 0 ) );
  else if  ( opr  == 64 )
    return type   == LP ? Ntnode( ShinToken( T, 1, 0, 0 ) ) : Ntnode( ShinToken( NIL, 1, 0, 0 ) );
  else if  ( opr  == 100 ) {
    if     ( type == LP && value != 7477 ) return Ntnode( ShinToken( T, 1, 0, 0 ) );
    return Ntnode( ShinToken( NIL, 1, 0, 0 ) );
  } // else if
  else return NULL;
} // PrimitivePredicates()

TnodePtr SFC_begin( TnodePtr input, int level ) {
  TnodePtr arcv = NULL, mid = input -> right;
  if ( !mid ) {
    printf( "ERROR (incorrect number of arguments) : " );
    CoutTok( input -> left -> tok, false, 92 );
    return NULL;
  } // if
  
  for ( ; true ; mid = mid -> right ) {
    arcv = Evolution( mid -> left, level+1 );
    if ( !arcv ) 
      return NULL;
    if ( !mid -> right ) 
      return arcv;
    else LFTree( arcv );
  } // for
} // SFC_begin()

TnodePtr PartSus( TnodePtr mid, int funcType, int level ) {
  if ( !mid || ( mid &&  mid -> right ) )  {
    printf( "ERROR (incorrect number of arguments) : %s\n", gRT[ funcType ] );
    return NULL;
  } // if
  
  TnodePtr arcv = NULL, tmp;
  arcv = Evolution( mid -> left, level+1 );
  if ( !arcv ) return NULL;
  if ( arcv -> tok -> type == -3 ) {
    printf( "ERROR (unbound parameter) : " ), CoutTree( mid -> left, 1, false );
    LFTree( arcv );
    return NULL;
  } // if
  
  if ( arcv -> tok -> type != LP ) {
    printf( "ERROR (%s with incorrect argument type) : ", gRT[ funcType ] );
    CoutTree( arcv, 1, false );
    return NULL;
  } // if
  
  if ( funcType == 98 ) tmp = arcv -> left, arcv -> left = NULL;  // return left  child
  else {                                                         // return right child
    if ( !arcv -> right ) 
      return Ntnode( ShinToken( NIL, 1, 0, 0 ) );
      
    tmp = arcv -> right;
    arcv -> right = NULL;
    
    if ( tmp -> tok -> type == 777 ) 
      tmp -> tok -> type = LP;
    else if ( tmp -> tok -> type == DOT ) {
      mid = tmp;
      tmp  = tmp ->  left;
      mid -> left = NULL;
      LFTree( mid );
    } // else if
  } // else

  LFTree( arcv );
  return tmp;
} // PartSus()

TnodePtr LogOppo( TnodePtr mid, int opr, int level ) {
  if ( ( opr == 59 && ( !mid || ( mid &&  mid -> right ) ) ) ||
       ( opr != 59 && ( !mid || ( mid && !mid -> right ) ) ) ) {
    printf( "ERROR (incorrect number of arguments) : %s\n", gRT[ opr ] );
    return NULL;
  } // if
  
  TnodePtr arg = NULL;
  for ( int tokenType ; mid ; mid = mid -> right ) {
    arg = Evolution( mid -> left, level+1 );
    if ( !arg ) 
      return NULL;
    if ( arg -> tok -> type == -3 ) {
      LFTree( arg );
      printf( "ERROR (unbound condition) : " ), CoutTree( mid -> left, 1, false );
      return NULL;
    } // if
 
    tokenType = arg -> tok -> type;
    if ( opr == 59 ) {
      LFTree( arg );
      if ( tokenType == NIL ) 
        return Ntnode( ShinToken(   T, 1, 0, 0 ) );
      else                    
        return Ntnode( ShinToken( NIL, 1, 0, 0 ) );
    } // if
    else if ( opr == 77 && tokenType == NIL ) return arg; // if and get false, return false
    else if ( opr == 77 && !mid  ->  right ) return arg; // and peek next node, if the node is null, return
    else if ( opr ==  5 && tokenType != NIL ) return arg; // if or get true, return
    LFTree( arg );                        // if and get true goto next node; if or get false goto next node
  } // for
  
  return Ntnode( ShinToken( NIL, 1, 0, 0 ) ); // Or will enter the null node, and will not
} // LogOppo()

bool GetLeftNodeStrValue( int & value, TnodePtr mid, int level, int func ) {
  TnodePtr node = Evolution( mid -> left, level+1 );
  if ( !node ) 
    return false;
  if ( node -> tok -> type == -3 ) {
    printf( "ERROR (unbound parameter) : " ), CoutTree( mid -> left, 1, false );
    LFTree( node );
    return false;
  } // if
  
  int type = node -> tok -> type;
  if ( type != STRING ) {
    printf( "ERROR (%s with incorrect argument type) : ", gRT[ func ] );
    CoutTree( node, 1, false ), LFTree( node );
    return false;
  } // if
  
  value = node -> tok -> value, LFTree( node );
  return true;
} // GetLeftNodeStrValue()

TnodePtr StrApp( TnodePtr input, int level ) {
  TnodePtr mid = input -> right;
  if ( !mid || !mid -> right ) {
    printf( "ERROR (incorrect number of arguments) : " );
    CoutTok( input -> left -> tok, false, 92 );
    return NULL;
  } // if
  
  int value;
  if ( !GetLeftNodeStrValue( value, mid, level, 69 ) ) 
    return NULL;
    
  StrOTE buf;
  strcpy( buf, gStrT[ value ] );
  for ( mid = mid -> right ; mid ; mid = mid -> right ) {
    if ( !GetLeftNodeStrValue( value, mid, level,  69 ) ) return NULL;
    strcat( buf, gStrT[ value ] );
  } // for

  return Ntnode( ShinToken( STRING, StrTPush( buf ), 0, 0 ) );
} // StrApp()

bool StrOppo( int & answer, TnodePtr inode, int opr, int level ) {
  TnodePtr mid = inode -> right;
  if ( !mid || !mid -> right ) {
    printf( "ERROR (incorrect number of arguments) : " );
    CoutTok( inode -> left -> tok, false, 92 );
    return false;
  } // if
  
  if ( !GetLeftNodeStrValue( answer, mid, level, opr  ) ) 
    return false;
    
  mid = mid -> right;
  for ( int value = false, isDone = false; mid ; mid = mid -> right ) {
    if ( !GetLeftNodeStrValue( value, mid, level, opr ) ) 
      return false;
      
    if ( isDone ) ;
    else if ( opr == 88 && strcmp( gStrT[ answer ], gStrT[ value ] ) ) 
      answer = false, isDone = true;
    else if ( opr == 89 ) { 
      if ( strcmp( gStrT[ answer ], gStrT[ value ] ) > 0 ) ;
      else 
        answer = false, isDone = true;
    } // else if
    else if ( opr == 87 ) { 
      if ( strcmp( gStrT[ answer ], gStrT[ value ] ) < 0 ) ;
      else 
        answer = false, isDone = true;
    } // else if
    
    if ( !isDone ) 
      answer = value;
  } // for
  
  return true;
} // StrOppo()

bool ArthurOppo( double & result, bool & hasFloat, TnodePtr mid, int opr, int level ) {
  if ( !mid || !mid -> right ) {
    printf( "ERROR (incorrect number of arguments) : %s\n", gRT[ opr ] );
    return false;
  } // if

  bool isDone = false;
  for ( int i = 1; mid ; mid = mid -> right, i++ ) {
    TnodePtr node = Evolution( mid -> left, level+1 );
    if ( !node ) 
      return false;
      
    if ( node -> tok -> type == -3 ) {
      printf( "ERROR (unbound parameter) : " ), CoutTree( mid -> left, 1, false );
      LFTree( node );
      return false;
    } // if
    
    TokenPtr operand = node -> tok;
    if ( operand -> type != INT && operand -> type != FLOAT ) {
      printf( "ERROR (%s with incorrect argument type) : ", gRT[ opr ] );
      CoutTree( node, 1, false ), LFTree( node );
      return false;
    } // if
    
    double operandValue = 0;
    if      ( operand -> type ==   INT )
      operandValue = ( operand -> value == -1 ) ? 0 : gIT[ operand -> value ];
    else if ( operand -> type == FLOAT )
      operandValue = ( operand -> value == -1 ) ? 0 : gFT[ operand -> value ], hasFloat = true;
    LFTree( node );
    if      ( i   ==    1 ) 
      result  = operandValue;
    else if ( opr == 43 ) 
      result += operandValue;
    else if ( opr ==  45 ) result -= operandValue;
    else if ( opr ==  42 ) result *= operandValue;
    else if ( opr ==  47 ) {
      if ( operandValue == 0 ) {
        printf( "ERROR (division by zero) : /\n" );
        return false;
      } // if
    
      result /= operandValue;
    } // else if
    else if ( isDone ) ;
    else if ( opr == 61 && result != operandValue ) result = false, isDone = true; // =
    else if ( opr == 62 ) { // >
      if ( result <= operandValue ) result = false, isDone = true;
      else result =  operandValue;
    } // else if
    else if ( opr == 60 ) {  // <
      if ( result >= operandValue ) result = false, isDone = true;
      else result =  operandValue;
    } // else if
    else if ( opr == 21 ) { // <=
      if ( result >  operandValue ) result = false, isDone = true;
      else result =  operandValue;
    } // else if
    else if ( opr == 24 ) { // >=
      if ( result <  operandValue ) result = false, isDone = true;
      else result =  operandValue;
    } // else if
  } // for
  
  if ( isDone && result == false ) return true;  
  if ( result == 0 && ( opr == 61 || opr == 62 || opr == 60 || opr == 21 || opr == 24 ) )
    result = true;
  return true;
} // ArthurOppo()

TnodePtr New_Cons( TnodePtr mid, int level ) {
  if ( !mid || ( mid && !mid -> right ) || ( mid -> right && mid -> right -> right ) ) {
    printf( "ERROR (incorrect number of arguments) : cons\n" );
    return NULL;
  } // if
  
  TnodePtr arg = NULL, result = NULL;
  arg = Evolution( mid -> left, level+1 );
  if ( !arg ) return NULL;
  if ( arg -> tok -> type == -3 ) {
    printf( "ERROR (unbound parameter) : " ), CoutTree( mid -> left, 1, false );
    LFTree( arg );
    return NULL;
  } // if
  
  arg -> tok -> line = 0;
  result = Ntnode( ShinToken( LP, 1, 0, 0 ) );
  result -> left = arg;
  arg = Evolution( mid -> right -> left, level+1 ); // this is second arguments
  if ( !arg ) {
    LFTree( result );
    return NULL;
  } // if
  else if ( arg -> tok -> type == -3 ) {
    printf( "ERROR (unbound parameter) : " ), CoutTree( mid -> left, 1, false );
    LFTree( arg );
    return NULL;
  } // else if
  
  if ( arg -> tok -> type == NIL ) { // if second arguments is nil, delete
    LFTree( arg );
    return result;
  } // if

  arg -> tok -> line = 0;
  if ( arg -> tok -> type != LP ) { // this arguments is terminal
    result -> right = Ntnode( ShinToken( DOT, 1, 0, 0 ) );
    result -> right ->  left = arg;
    result -> tok   -> value = 7477;
    return result;
  } // if
                              
  result -> right = arg;            // this arguments is pair
  result -> right -> tok -> type = 777;
  return result;
} // New_Cons()

TnodePtr New_List( TnodePtr mid, int level ) {
  TnodePtr arg = NULL, result = NULL, tmp = NULL;
  if ( !mid ) return Ntnode( ShinToken( NIL, 1, 0, 0 ) );
  arg = Evolution( mid -> left, level+1 );
  if ( !arg  ) return NULL;
  if ( arg -> tok -> type == -3 ) {
    printf( "ERROR (unbound parameter) : " ), CoutTree( mid -> left, 1, false );
    LFTree( arg );
    return NULL;
  } // if

  arg -> tok -> line = 0;
  result = Ntnode( ShinToken( LP, 1, 0, 0 ) );
  result -> left = arg;
  tmp = result;
  for ( mid = mid -> right ; mid ; mid = mid -> right ) {
    arg = Evolution( mid -> left, level+1 );
    if ( !arg || arg -> tok -> type == -3 ) {
      if ( arg ) {
        printf( "ERROR (unbound parameter) : " ), CoutTree( mid -> left, 1, false );
        LFTree( arg );
      } // if
      
      LFTree( result );
      return NULL;
    } // if

    arg -> tok -> line = 0;
    tmp -> right = Ntnode( ShinToken( 777, 1, 0, 0 ) );
    tmp = tmp -> right;
    tmp -> left  = arg;
  } // for

  return result;
} // New_List()

bool TnT( TnodePtr dest, TnodePtr src ) {
  if (   !dest && !src ) return true;
  if ( ( !dest &&  src ) || ( dest && !src ) ) return false;
  if ( dest -> tok -> type == src -> tok -> type ) {
    int type = dest -> tok -> type;
    if ( type == INT || type == FLOAT || type == SYMBOL || type == STRING || type == RESERW )
      if ( dest -> tok -> value != src -> tok -> value ) return false;
  } // if
  else return false;
  return ( TnT( dest -> left, src -> left ) && TnT( dest -> right, src -> right ) );
} // TnT()

TnodePtr Equals( TnodePtr mid, int level ) {
  TnodePtr arg = NULL, arg2 = NULL;
  arg  = Evolution( mid -> left, level+1 );
  if ( !arg ) return NULL;
  arg2 = Evolution( mid -> right -> left, level+1 );
  if ( !arg2 ) {
    LFTree( arg );
    return NULL;
  } // if
  
  int result = NIL;
  if ( TnT( arg, arg2 ) ) result = T;
  LFTree( arg ), LFTree( arg2 );
  return Ntnode( ShinToken( result, 1, 0, 0 ) );
} // Equals()

TnodePtr Eqv( TnodePtr mid, int level ) {
  if ( !mid || ( mid && !mid -> right ) || ( mid -> right && mid -> right -> right ) ) {
    printf( "ERROR (incorrect number of arguments) : eqv?\n" );
    return NULL;
  } // if
  
  int arg1Type = mid -> left -> tok -> type, arg2Type = mid -> right -> left -> tok -> type, result = NIL;
  if ( arg1Type == STRING || arg2Type == STRING || arg1Type == QUOTE     || arg2Type == QUOTE     ||
       arg1Type == 7557   || arg2Type == 7557   || arg1Type == 333 || arg2Type == 333 )
    return Ntnode( ShinToken( result, 1, 0, 0 ) );
  TnodePtr arg1_after_eval = NULL, arg2_after_eval = NULL;
  arg1_after_eval = Evolution( mid -> left, level+1 );
  if ( !arg1_after_eval ) return NULL;
  arg2_after_eval = Evolution( mid -> right -> left, level+1 );
  if ( !arg2_after_eval ) {
    LFTree( arg1_after_eval );
    return NULL;
  } // if
  
  if ( TnT( arg1_after_eval, arg2_after_eval ) ) {
    result = T;
    int type = arg1_after_eval -> tok -> type;
    printf( "%d\n", dfuse.AnoDef );
    if (  type != INT && ( arg1Type != SYMBOL || arg2Type != SYMBOL ) ) result = NIL;
    
    std::cout << arg1_after_eval -> tok-> type << std::endl;
    std::cout << arg2_after_eval -> tok-> type << std::endl;
    std::cout << arg1_after_eval -> tok-> address << std::endl;
    std::cout << arg2_after_eval -> tok-> address << std::endl;
    std::cout << arg1_after_eval -> tok-> value << std::endl;
    std::cout << arg2_after_eval -> tok-> value << std::endl;
  } // if

  LFTree( arg1_after_eval ), LFTree( arg2_after_eval );
  return Ntnode( ShinToken( result, 1, 0, 0 ) );
} // Eqv()

TnodePtr Ifoppo( TnodePtr input, int level ) {
  if ( !input -> right || !input -> right -> right || ( input -> right -> right -> right &&
                                                        input -> right -> right -> right -> right ) ) {
    printf( "ERROR (incorrect number of arguments) : " );
    CoutTok( input -> left -> tok, false, 92 );
    return NULL;
  } // if
  
  TnodePtr cond = NULL, trueResult = NULL, falseResult = NULL;
  cond = Evolution( input -> right -> left, level+1 );
  if ( !cond ) return NULL;
  if ( cond -> tok -> type == -3 ) {
    printf( "unbound test-condition" ), CoutTree( input -> right -> left, 1, false );
    LFTree( cond );
    return NULL;
  } // if
  
  int condType  = cond  -> tok   -> type;
  LFTree( cond );
  trueResult    = input -> right -> right -> left;
  if ( input   -> right -> right -> right && input -> right -> right -> right -> left ) {
    falseResult = input -> right -> right -> right -> left;
    if ( condType == NIL ) return Evolution( falseResult, level+1 );
    return Evolution( trueResult, level+1 );
  } // if
  
  if ( condType == NIL ) return Ntnode( ShinToken( -3, 1, 0, 0 ) );
  return Evolution( trueResult, level+1 );
} // Ifoppo()

bool GetLogOppo( TnodePtr & result, TnodePtr sexp, TnodePtr input, int level ) {
  TnodePtr logiSexp = sexp -> left;
  if ( !logiSexp ) {
    printf( "ERROR (COND format) : " ), CoutTree( input, 1, false );
    return false;
  } // if
  
  if ( logiSexp -> tok -> type == SYMBOL ) {
    if ( logiSexp -> tok -> value == 243 && logiSexp -> tok -> line != -1 ) ;
    else if ( !SGetting( logiSexp, logiSexp -> tok ) ) return false;
    
    logiSexp = TreeCpy( logiSexp );
  } // if
  else {
    TnodePtr tmp = Evolution( logiSexp, level+1 );
    if ( !tmp ) return false;
    if ( tmp -> tok -> type == -3 ) {
      printf( "unbound test-condition" ), CoutTree( logiSexp, 1, false ), LFTree( tmp );
      return false;
    } // if

    logiSexp = tmp;
  } // else
  
  if ( logiSexp -> tok -> type == NIL ) {
    result = NULL, LFTree( logiSexp );
    return true;
  } // if
  
  LFTree( logiSexp ), sexp = sexp -> right;
  for ( ; sexp && sexp -> right ; sexp = sexp -> right ) {
    logiSexp = Evolution( sexp -> left, level+1 );
    if ( !logiSexp ) return false;
    LFTree( logiSexp );
  } // for
  
  TnodePtr tmp = Evolution( sexp -> left, level+1 );
  if ( !tmp ) return false;
  if ( tmp -> tok -> type == -3 ) {
    result = tmp;
    return false;
  } // if
  
  result = tmp;
  return  true;
} // GetLogOppo()

bool CheckCondArgument( TnodePtr input ) {
  if ( !input -> right ) return false;
  for ( TnodePtr tmp = input -> right, mostLeftNode = NULL; tmp ; tmp = tmp -> right ) {
    if ( tmp -> left -> tok -> type != LP || !tmp -> left -> right ) return false;
    mostLeftNode = tmp -> left -> left;
    if ( ( tmp -> right ) && ( mostLeftNode -> tok -> value == 243 &&
                               mostLeftNode -> tok -> type  == SYMBOL ) )
      mostLeftNode -> tok -> line = -1;
    else if ( tmp -> right && ( mostLeftNode -> left && mostLeftNode -> left -> tok -> type == LP 
                                && mostLeftNode -> tok -> type != QUOTE ) ) return false;
  } // for
  
  return true;
} // CheckCondArgument()

TnodePtr Prerequis( TnodePtr input, int level ) {
  if ( !CheckCondArgument( input ) ) {
    printf( "ERROR (COND format) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if
  
  TnodePtr result =  NULL, tmp = NULL;
  bool     isDone = false;
  for ( TnodePtr iter = input -> right; iter ; iter = iter -> right ) {
    if ( !GetLogOppo( tmp, iter -> left, input, level ) ) {
      if ( result ) LFTree( result );
      if ( tmp ) return tmp;
      return NULL;
    } // if
    
    if ( !isDone ) {
      result = tmp;
      if ( result ) return result;
    } // if
    else if ( tmp ) LFTree( tmp );
    
    if ( result ) isDone = true;
    tmp = NULL;
  } // for
  
  if ( !result ) return Ntnode( ShinToken( -3, 1, 0, 0 ) );
  return result;
} // Prerequis()

void GBF( TnodePtr input ) {
  for ( TnodePtr arg = input -> right; arg ; arg = arg -> right )
    if ( arg -> tok -> type == DOT ) {
      input -> right -> tok -> value = 7477;
      return;
    } // if
} // GBF()

TnodePtr DefineOper( TnodePtr input, int level ) { // define symbol sexp
  bool isDefineFun = false;
  TnodePtr    head =  NULL, sexp = NULL;
  TokenPtr  symbol =  NULL;  // first arg token
  if ( !input -> right || !input -> right -> right || ( !input -> right -> left  -> left &&
                                                        input  -> right -> right -> right ) ) {
    printf( "ERROR (DEFINE format) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if

  sexp = input -> right -> right;
  std::cout<<sexp->tok->address<<std::endl;
  TnodePtr tmp = input -> right -> left; // first arg node
  if ( ( !tmp -> left && tmp -> tok -> type != SYMBOL ) || ( tmp -> left && tmp -> tok -> type != LP ) ) {
        // symbol is atom, no left child
    printf( "ERROR (DEFINE format) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if

  for ( TnodePtr node = tmp; node && node -> left ; node = node -> right ) // ( SYMBOL zero-or-more-symbols )
    if ( node -> left -> tok -> type != SYMBOL ) { 
      printf( "ERROR (DEFINE format) : " ), CoutTree( input, 1, false );
      return NULL;
    } // if
  
  if ( tmp -> tok -> type == LP )
    sexp = input -> right -> right, head = tmp -> right, isDefineFun = true, tmp = tmp -> left;
  symbol = tmp -> tok;
  if ( !isDefineFun ) {
    TnodePtr r = Evolution( sexp -> left, level+1 );   // if second arg is not symbol, eval
    if ( !r ) return NULL;
    if ( r -> tok -> type == -3 ) {
      printf( "ERROR (no return value) : " ), CoutTree( sexp -> left, 1, false );
      LFTree( r );
      return NULL;
    } // if
    
    sexp = r;
  } // if
  else if ( isDefineFun )
    sexp = ShinFun( TreeCpy( head ), TreeCpy( sexp ), false ), sexp -> tok -> value = symbol -> value;

  SSetting( symbol -> value, sexp );
  if ( gVbM ) CoutTok( symbol, false, false ), printf( " defined\n" );
  printf("%s", gSymT[ symbol -> value ].tokenStr ) ;
  return Ntnode( ShinToken( 23, 1, 0, 0 ) );
} // DefineOper()

TnodePtr SetOper( TnodePtr input, int level ) { // set! symbol sexp
  bool isDefineFun = false;
  TnodePtr    head =  NULL, sexp = NULL;
  TokenPtr  symbol =  NULL;  // first arg token
  if ( !input -> right || !input -> right -> right || ( !input -> right -> left  -> left &&
                                                        input  -> right -> right -> right ) ) {
    printf( "ERROR (SET format) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if
  
  sexp = input -> right -> right;
  TnodePtr tmp = input -> right -> left; // first arg node
  if ( ( !tmp -> left && tmp -> tok -> type != SYMBOL ) || ( tmp -> left && tmp -> tok -> type != LP ) ) {
        // symbol is atom, no left child
    printf( "ERROR (SET format) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if

  for ( TnodePtr node = tmp; node && node -> left ; node = node -> right ) // ( SYMBOL zero-or-more-symbols )
    if ( node -> left -> tok -> type != SYMBOL ) { 
      printf( "ERROR (SET format) : " ), CoutTree( input, 1, false );
      return NULL;
    } // if
  
  if ( tmp -> tok -> type == LP )
    sexp = input -> right -> right, head = tmp -> right, isDefineFun = true, tmp = tmp -> left;
  symbol = tmp -> tok;
  if ( !isDefineFun ) {
    TnodePtr r = Evolution( sexp -> left, level+1 );   // if second arg is not symbol, eval
    if ( !r ) return NULL;
    if ( r -> tok -> type == -3 ) {
      printf( "ERROR (no return value) : " ), CoutTree( sexp -> left, 1, false );
      LFTree( r );
      return NULL;
    } // if
    
    sexp = r;
  } // if
  else if ( isDefineFun )
    sexp = ShinFun( TreeCpy( head ), TreeCpy( sexp ), false ), sexp -> tok -> value = symbol -> value;

  if ( gSymT[ symbol -> value ].localSymbol && 
       gSymT[ symbol -> value ].localSymbol -> localId == gLId ) {
    if ( !gSymT[ symbol -> value ].localSymbol -> ting )
      gSymT[ symbol -> value ].localSymbol -> ting = sexp;
    else {
      LFTree( gSymT[ symbol -> value ].ting );
      gSymT[ symbol -> value ].localSymbol -> ting = sexp;
    } // else

    return TreeCpy( sexp );
  } // if

  SSetting( symbol -> value, sexp );
  return TreeCpy( sexp );
} // SetOper()

TnodePtr LamO( TnodePtr input ) {
  if ( !input -> right || !input -> right -> right ) {
    printf( "ERROR (LAMBDA format) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if
  
  TnodePtr head = input -> right -> left; // first arg node : head
  if ( head -> tok -> type != LP && head -> tok -> type != NIL ) {
    printf( "ERROR (LAMBDA format) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if
  
  if ( !head -> left ) head = NULL;
  for ( TnodePtr node = head; node ; node = node -> right ) // ( zero-or-more-symbols )
    if ( node -> left -> tok -> type != SYMBOL ) {
      printf( "ERROR (LAMBDA format) : " ), CoutTree( input, 1, false );
      return NULL;
    } // if

  return ShinFun( TreeCpy( head ), TreeCpy( input -> right -> right ), 333 );
} // LamO()

bool LetBindAnalysis( TnodePtr node ) { // ( SYMBOL S-expression )
  if ( node -> tok -> type != LP || node -> left -> tok -> type != SYMBOL || !node -> right ||
       node -> right -> right )
    return false;
  return true;
} // LetBindAnalysis()

bool LetLocalSymBind( TnodePtr heads, int level ) {
  for ( TnodePtr result = NULL, tmp = heads; tmp ; tmp = tmp -> right ) {
    result = Evolution( tmp -> left -> right -> left, level+1 );
    if ( !result || result -> tok -> type == -3  ) {
      if ( result ) {
        printf( "ERROR (no return value) : " );
        CoutTree( tmp -> left -> right -> left, 1, false );
        LFTree( result );
      } // if
      
      for ( ; heads && heads != tmp ; heads = heads -> right )
        LFTree( heads -> left -> left -> left ), heads -> left -> left -> left = NULL;
      return false;
    } // if
    
    tmp -> left -> left -> left = result;
  } // for
  
  for ( TnodePtr tmp = heads; tmp ; tmp = tmp -> right ) {
    SSetHere( tmp -> left -> left -> tok -> value, tmp -> left -> left -> left, gLId );
    tmp -> left -> left -> left = NULL;
  } // for
  
  return true;
} // LetLocalSymBind()

void PopLetBinding( TnodePtr heads ) {
  for ( ; heads ; heads = heads -> right )
    PopHereS( heads -> left -> left -> tok -> value );
} // PopLetBinding()

TnodePtr LetO( TnodePtr input, int level ) {
  if ( !input -> right || !input -> right -> right ) {
    printf( "ERROR (LET format) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if
  
  TnodePtr heads = input -> right -> left; // first arg node : heads ( multi head )
  if ( heads -> tok -> type != LP && heads -> tok -> type != NIL ) {
    printf( "ERROR (LET format) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if
  
  if ( !heads -> left ) heads = NULL;
  for ( TnodePtr node = heads; node && node -> left ; node = node -> right )
    if ( !LetBindAnalysis( node -> left ) ) {
      printf( "ERROR (LET format) : " ), CoutTree( input, 1, false );
      return NULL;
    } // if
  
  if ( heads ) {
    heads = TreeCpy( heads );
    if ( !LetLocalSymBind( heads, level ) ) {
      LFTree( heads );
      return NULL;
    } // if
  } // if
  
  TnodePtr mids = TreeCpy( input -> right -> right ); 
  TnodePtr tmp   = mids, result = NULL;
  for ( ; tmp && tmp -> right ; tmp = tmp -> right ) {
    result = Evolution( tmp -> left, 0 );
    if ( !result ) {
      LFTree( mids );
      if ( heads ) PopLetBinding( heads ), LFTree( heads );
      return NULL;
    } // if
    
    LFTree( result );
  } // for
  
  result = Evolution( tmp -> left, 0 );
  LFTree( mids );
  if ( heads ) PopLetBinding( heads ), LFTree( heads );
  return result;
} // LetO()

TnodePtr NewLineOper( TnodePtr input, int level ) {
  if ( input -> right ) {
    printf( "ERROR (NEWLINE format) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if

  printf( "\n" );
  return Ntnode( ShinToken( NIL, 1, 0, 0 ) );
} // NewLineOper()

TnodePtr WriteOper( TnodePtr input, int level ) {
  if ( !input -> right || input -> right -> right ) {
    printf( "ERROR (incorrect number of arguments) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if
  
  TnodePtr arg = input -> right -> left;
  arg = Evolution( arg, level+1 );
  if ( !arg ) return NULL;
  if ( arg -> tok -> type == -3 ) {
    printf( "ERROR (unbound parameter) : " ), CoutTree( input -> right -> left, 1, false );
    LFTree( arg );
    return NULL;
  } // if
  
  CoutTree( arg, 1, true );
  return arg;
} // WriteOper()

TnodePtr DisplayStr( TnodePtr input, int level ) {
  if ( !input -> right || input -> right -> right ) {
    printf( "ERROR (incorrect number of arguments) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if
  
  TnodePtr arg = input -> right -> left;
  arg = Evolution( arg, level+1 );
  if ( !arg ) return NULL;
  if ( arg -> tok -> type == -3 ) {
    printf( "ERROR (unbound parameter) : " ), CoutTree( input -> right -> left, 1, false );
    LFTree( arg );
    return NULL;
  } // if
  
  if ( arg -> tok -> type != STRING && arg -> tok -> type != -5 ) {
    printf( "ERROR (%s with incorrect argument type) : ", gRT[ 93 ] );
    CoutTree( arg, 1, false ), LFTree( arg );
    return NULL;
  } // if
  
  printf( "%s", gStrT[ arg -> tok-> value ] );
  return arg;
} // DisplayStr()

TnodePtr ReadOper( TnodePtr input, int level ) {
  if ( input -> right ) {
    printf( "ERROR (READ format) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if

  TnodePtr result = NULL;
  gIRd = true;
  if ( Parser( result ) ) {
    gIRd = false;
    return result;
  } // if
  
  gIRd = false;
  return Ntnode( ShinToken( -5, StrTPush( gEMsg ), 0, 0 ) );
} // ReadOper()

TnodePtr IsErrObj( TnodePtr input, int level ) {
  if ( !input -> right || input -> right -> right ) {
    printf( "ERROR (incorrect number of arguments) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if
  
  TnodePtr arg = input -> right -> left;
  arg = Evolution( arg, level+1 );
  if ( !arg ) return NULL;
  if ( arg -> tok -> type == -3 ) {
    printf( "ERROR (unbound condition) : " ), CoutTree( input -> right -> left, 1, false );
    LFTree( arg );
    return NULL;
  } // if
  
  int type = arg -> tok -> type;
  LFTree( arg );
  return ( type == -5 ) ? Ntnode( ShinToken( T, 1, 0, 0 ) ) : Ntnode( ShinToken( NIL, 1, 0, 0 ) );
} // IsErrObj()

TnodePtr New_ErrObj( TnodePtr input, int level ) {
  if ( !input -> right || input -> right -> right ) {
    printf( "ERROR (incorrect number of arguments) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if
  
  TnodePtr arg = input -> right -> left;
  arg = Evolution( arg, level+1 );
  if ( !arg ) return NULL;
  if ( arg -> tok -> type == -3 ) {
    printf( "ERROR (unbound parameter) : " ), CoutTree( input -> right -> left, 1, false );
    LFTree( arg );
    return NULL;
  } // if
  
  if ( arg -> tok -> type != STRING ) {
    printf( "ERROR (%s with incorrect argument type) : ", gRT[ 3 ] );
    CoutTree( arg, 1, false ), LFTree( arg );
    return NULL;
  } // if
  
  arg -> tok -> type = -5;
  return arg;
} // New_ErrObj()

TnodePtr EvalOper( TnodePtr input, int level ) {
  if ( !input -> right || input -> right -> right ) {
    printf( "ERROR (incorrect number of arguments) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if
  
  TnodePtr arg = input -> right -> left, result = NULL;
  arg = Evolution( arg, level+1 );
  if ( !arg ) return NULL;
  if ( arg -> tok -> type == -3 ) {
    printf( "ERROR (unbound parameter) : " ), CoutTree( input -> right -> left, 1, false );
    LFTree( arg );
    return NULL;
  } // if
  
  result = Evolution( arg, 0 );
  LFTree( arg );
  return result;
} // EvalOper()

TnodePtr SymToStr( TnodePtr input, int level ) {
  if ( !input -> right || input -> right -> right ) {
    printf( "ERROR (incorrect number of arguments) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if
  
  TnodePtr arg = input -> right -> left, r;
  arg = Evolution( arg, level+1 );
  if ( !arg ) return NULL;
  if ( arg -> tok -> type == -3 ) {
    printf( "ERROR (unbound parameter) : " ), CoutTree( input -> right -> left, 1, false );
    LFTree( arg );
    return NULL;
  } // if
  
  if ( arg -> tok -> type != SYMBOL && arg -> tok -> type != RESERW ) {
    printf( "ERROR (%s with incorrect argument type) : ", gRT[ 33 ] );
    CoutTree( arg, 1, false ), LFTree( arg );
    return NULL;
  } // if

  if ( arg -> tok -> type == SYMBOL )
    r = Ntnode( ShinToken( STRING, StrTPush( gSymT[ arg -> tok -> value ].tokenStr ), 0, 0 ) );
  else
    r = Ntnode( ShinToken( STRING, StrTPush( gRT[ arg -> tok -> value ] ), 0, 0 ) );
  LFTree( arg );
  return r;
} // SymToStr()

TnodePtr NumToStr( TnodePtr input, int level ) {
  if ( !input -> right || input -> right -> right ) {
    printf( "ERROR (incorrect number of arguments) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if
  
  TnodePtr arg = input -> right -> left;
  arg = Evolution( arg, level+1 );
  if ( !arg ) return NULL;
  if ( arg -> tok -> type == -3 ) {
    printf( "ERROR (unbound parameter) : " ), CoutTree( input -> right -> left, 1, false );
    LFTree( arg );
    return NULL;
  } // if

  if ( arg -> tok -> type != INT && arg -> tok -> type != FLOAT ) {
    printf( "ERROR (%s with incorrect argument type) : ", gRT[ 30 ] );
    CoutTree( arg, 1, false ), LFTree( arg );
    return NULL;
  } // if

  StrOTE buf;
  if ( arg -> tok -> type == INT ) sprintf( buf,   "%d", gIT[ arg -> tok -> value ] );
  else                             sprintf( buf, "%.3f", gFT[ arg -> tok -> value ] );
  LFTree( arg );
  return Ntnode( ShinToken( STRING, StrTPush( buf ), 0, 0 ) );
} // NumToStr()

TnodePtr VerbOper( TnodePtr input, int level ) {
  if ( !input -> right || input -> right -> right ) {
    printf( "ERROR (incorrect number of arguments) : " ), CoutTree( input, 1, false );
    return NULL;
  } // if

  TnodePtr arg = input -> right -> left;
  arg = Evolution( arg, level+1 );
  if ( !arg ) return NULL;
  if ( arg -> tok -> type == -3 ) {
    printf( "ERROR (unbound parameter) : " ), CoutTree( input -> right -> left, 1, false );
    LFTree( arg );
    return NULL;
  } // if
  
  int type = arg -> tok -> type;
  LFTree( arg );
  if ( type == NIL ) gVbM = false;
  else               gVbM =  true, type = T;
  
  return Ntnode( ShinToken( type, 1, 0, 0 ) );
} // VerbOper()

TnodePtr KBuiFun( TnodePtr input, int funcType, int level ) {
  TnodePtr mid = input -> right;
  int  result_i = 0;
  if ( funcType == 23 ) {
    if ( level != 0 ) {
      printf( "ERROR (level of DEFINE)\n" );
      return NULL;
    } // if
    
    return DefineOper( input, level );
  } // if
  else if ( funcType == 22 ) {
    if ( level != 0 ) {
      printf( "ERROR (level of EXIT)\n" );
      return NULL;
    } // if
    
    if ( mid ) {
      printf( "ERROR (incorrect number of arguments) : exit\n" );
      return NULL;
    } // if
    
    gIE = true;
    return NULL;
  } // if
  else if ( funcType == 66 ) {
    if ( level != 0 ) {
      printf( "ERROR (level of CLEAN-ENVIRONMENT)\n" );
      return NULL;
    } // if
    
    WashEv();
    if ( gVbM ) printf( "environment cleaned\n" );
    return NULL;
  } // else if
  else if ( funcType == 28 ) return LamO(     input );
  else if ( funcType == 29    ) return LetO( input, level );
  else if ( funcType == 37   ) return New_List( mid, level );
  else if ( funcType == 91   ) return New_Cons( mid, level );
  else if ( funcType == 43 || funcType == 45    || funcType == 42    || funcType == 47    ||
            funcType == 61  || funcType == 62 || funcType == 60  || funcType == 21 ||
            funcType == 24 ) {
    double  result_d = 0;
    bool    hasFloat = false; // -1 has float, 0 execute failure, 1 no float
    if ( ArthurOppo( result_d, hasFloat, mid, funcType, level ) ) {
      if  ( funcType == 61  || funcType == 62 || funcType == 60 || funcType == 21 ||
            funcType == 24 ) {
        if ( result_d ) return Ntnode( ShinToken( T, 1, 0, 0 ) );
        return Ntnode( ShinToken( NIL, 1, 0, 0 ) );
      } // if
      
      if ( hasFloat ) return Ntnode( ShinToken( FLOAT, FTPush( result_d ), 0, 0 ) );
      result_i = ( int ) result_d;
      return Ntnode( ShinToken( INT, ITPush( result_i ), 0, 0 ) );
    } // if
    else return NULL;
  } // else if
  else if ( funcType == 77 || funcType == 5 || funcType == 59 ) return LogOppo( mid, funcType, level );
  else if ( ( funcType == 88 || funcType == 87 || funcType == 89 ) &&
            StrOppo( result_i, input, funcType, level ) )
    return  result_i ? Ntnode( ShinToken( T, 1, 0, 0 ) ) : Ntnode( ShinToken( NIL, 1, 0, 0 ) );
  else if ( funcType == 69    ) return StrApp(  input, level );
  else if ( funcType == 99 || funcType == 64 || funcType == 100 || funcType == 8 ||
            funcType == 84  || funcType == 46 || funcType == 70  || funcType == 26  ||
            funcType == 81 || funcType == 78 )
    return  PrimitivePredicates( mid, funcType, level );
  else if ( funcType == 98    || funcType == 63 ) return PartSus( mid, funcType, level );
  else if ( funcType == 27     ) return Eqv(           mid, level );
  else if ( funcType == 19     ) return Equals(        mid, level );
  else if ( funcType == 58        ) return Ifoppo(      input, level );
  else if ( funcType == 94       ) return SetOper(      input, level );
  else if ( funcType == 56      ) return ReadOper(     input, level );
  else if ( funcType == 33    ) return SymToStr(     input, level );
  else if ( funcType == 30    ) return NumToStr(     input, level );
  else if ( funcType == 31   ) return VerbOper(     input, level );
  else if ( funcType == 82  ) return EvalOper(     input, level );
  else if ( funcType == 79  ) return IsErrObj(     input, level );
  else if ( funcType == 25     ) return SFC_begin(    input, level );
  else if ( funcType == 20     ) return WriteOper(    input, level );
  else if ( funcType == 93  ) return DisplayStr(   input, level );
  else if ( funcType == 3 ) return New_ErrObj(   input, level );
  else if ( funcType == 92   ) return NewLineOper(  input, level );
  else if ( funcType == 90      ) return Prerequis( input, level );
  else if ( funcType == 97   ) return gVbM ? Ntnode( ShinToken( T, 1, 0, 0 ) ) :
                                      Ntnode( ShinToken( NIL, 1, 0, 0 ) );
  return NULL;
} // KBuiFun()

bool CFAN( TnodePtr dest, TnodePtr src ) {
  for ( ; dest && src ; dest = dest -> right, src = src -> right )
    ;
  if ( !dest && !src ) return true;
  return false;
} // CFAN()

bool AssignLocalSymbol( TnodePtr head, TnodePtr src, int localId, int level ) {
  for ( TnodePtr tmp = head, result = NULL; tmp ; tmp = tmp -> right, src = src -> right ) {
    result = Evolution( src -> left, level+1 );
    if ( !result || result -> tok -> type == -3 ) {
      if ( result ) {
        printf( "ERROR (unbound parameter) : " ), CoutTree( src -> left, 1, false );
        LFTree( result );
      } // if
      
      for ( TnodePtr t = head; t && t != tmp ; t = t -> right ) {
        LFTree( t -> left -> left );
        t -> left -> left = NULL;
      } // for
      
      return false;
    } // if

    tmp -> left -> left = result;
  } // for

  for ( TnodePtr tmp = head; tmp ; tmp = tmp -> right )
    SSetHere( tmp -> left -> tok -> value, tmp -> left -> left, localId ), tmp -> left -> left = NULL;
  return true;
} // AssignLocalSymbol()

void PopHeadBinding( TnodePtr head ) {
  for ( ; head ; head = head -> right )
    PopHereS( head -> left -> tok -> value );
} // PopHeadBinding()

TnodePtr EUF( TnodePtr input, TnodePtr func, int level ) {
  TnodePtr head = func -> left, mids = func -> right;
  if ( !CFAN( input -> right, head ) ) {
    printf( "ERROR (incorrect number of arguments) : " );
    if ( func -> tok -> type == 333 )  printf( "lambda\n" );
    else                  CoutTok( func -> tok, false, 92 );
    return NULL;
  } // if
  
  if ( head ) {
    head = TreeCpy( head );
    if ( !AssignLocalSymbol( head, input -> right, gLId+1, level ) ) {
      LFTree( head );
      return NULL;
    } // if
  } // if
  
  ++gLId, mids = TreeCpy( mids );
  TnodePtr tmp = mids, result = NULL;
  for ( ; tmp && tmp -> right ; tmp = tmp -> right ) {
    result = Evolution( tmp -> left, 0 );
    if ( !result ) {
      LFTree( mids ), --gLId;
      if ( head ) PopHeadBinding( head ), LFTree( head );
      return NULL;
    } // if
    
    LFTree( result );
  } // for
  
  result = Evolution( tmp -> left, 0 );
  --gLId, LFTree( mids );
  if ( head ) PopHeadBinding( head ), LFTree( head );
  return result;
} // EUF()

TnodePtr Evolution( TnodePtr parseTree, int level ) {
  TnodePtr tmp = parseTree, result = NULL;
  if ( tmp -> tok -> type == LP ) {
    bool hasEvolution = false;
    tmp = parseTree -> left;
    if ( tmp -> tok -> type == LP ) {
      result = Evolution( tmp, level+1 );
      if ( !result ) return NULL;
      if ( result -> tok -> type == -3 ) {
        printf( "ERROR (no return value) : " ), CoutTree( tmp, 1, false );
        LFTree( result );
        return NULL;
      } // if
      
      tmp = result;
      hasEvolution = true;
    } // if
    
    if ( tmp -> tok -> type == SYMBOL && tmp -> tok -> line != -2 ) {
      if ( !SGetting( result, tmp -> tok ) ) {
        if ( hasEvolution ) LFTree( tmp );
        return NULL;
      } // if
      
      if ( hasEvolution ) LFTree( tmp );
      tmp = result;
    } // if
    
    GBF( parseTree );
    if ( parseTree -> right && parseTree -> right -> tok -> value == 7477 ) {
      printf( "ERROR (non-list) : " ), CoutTree( parseTree, 1, false );
      if ( hasEvolution ) LFTree( tmp );
      return NULL;
    } // if
    
    int type = tmp -> tok -> type, value = tmp -> tok -> value;
    if ( type == RESERW && value == 80 && tmp -> tok -> line != -2 ) { // it is quote
      if ( !parseTree -> right || parseTree -> right -> right ) {
        printf( "ERROR (incorrect number of arguments) : " ), CoutTree( parseTree, 1, false );
        return NULL;
      } // if
      
      if ( hasEvolution ) LFTree( tmp );
      tmp = TreeCpy( parseTree -> right -> left ), tmp -> tok -> line = -2;
      return tmp;
    } // if
    else if ( ( type == 7557 || type == 333 ) && tmp -> tok -> line != -2 ) {
      result = EUF( parseTree, tmp, level );
      if ( hasEvolution ) LFTree( tmp );
      return result;
    } // else if
    else if ( type == RESERW && tmp -> tok -> line != -2 ) {
      result = KBuiFun( parseTree, value, level );
      if ( hasEvolution ) LFTree( tmp );
      return result;
    } // else if
    
    printf( "ERROR (attempt to apply non-function) : " ), CoutTree( tmp, 1, false );
    return NULL;
  } // if
  else if ( tmp -> tok -> type == QUOTE ) {
    for   ( TnodePtr arg = parseTree -> left; arg ; arg = arg -> right )
      if  ( arg -> tok -> type == DOT ) parseTree -> left -> tok -> value = 7477;
    tmp = TreeCpy( parseTree -> left ), tmp -> tok -> line = -2;
    return tmp;
  } // else if
  else if  ( tmp -> tok -> type == SYMBOL && tmp -> tok -> line != -2 ) {
  	//std::cout << tmp -> tok -> 
    return ( SGetting( tmp, parseTree -> tok ) ) ? TreeCpy( tmp ) : NULL;
  } // else if
  else return TreeCpy( parseTree );
} // Evolution()

bool Emp( int top ) { return ( top == -1 ) ? true : false; } // Emp()

void LTS_push( char c ) { gLTS[ ++gLTS_top ] = c; } // LTS_push()

TokenPtr ShinToken( int type, int value, int line, int column ) {
  TokenPtr   tok = new Token;
  tok ->    type =   type;
  tok ->   value =  value;
  tok ->    line =   line;
  tok ->  column = column;
  tok -> address = gMA++;
  tok ->    next = NULL;
  return tok;
} // ShinToken()

int Hash( StrOTE src ) {
  int hvalue = 0, i = 0;
  while ( src[ i ] ) {
    hvalue += src[ i++ ];
    if ( src[ i ] ) hvalue += ( src[ i++ ] ) << 8;
  } // while
  
  return hvalue;
} // Hash()

int StrTPush( StrOTE src ) {
  int currentBucket, homeBucket = Hash( src ) % 1009;
  for ( currentBucket = homeBucket ; gStrT[ currentBucket ][ 0 ]
        && strcmp( gStrT[ currentBucket ], src ) ; ) {
    currentBucket = ( currentBucket + 1 ) % 1009;
    if ( currentBucket == homeBucket ) printf( "can't push in string table" ),  exit( EXIT_FAILURE );
  } // for
  
  if ( gStrT[ currentBucket ][ 0 ] && !strcmp( gStrT[ currentBucket ], src ) )
    return currentBucket;
  strcpy( gStrT[ currentBucket ], src );
  return currentBucket;
} // StrTPush()

int ITPush( int i ) {
  if ( i == 0 ) return -1;
  StrOTE buf;
  sprintf( buf, "%d", i );
  int currentBucket, homeBucket = Hash( buf ) % 1009;
  for ( currentBucket = homeBucket ; gIT[ currentBucket ]
        && gIT[ currentBucket ] != i ; ) {
    currentBucket = ( currentBucket + 1 ) % 1009;
    if ( currentBucket == homeBucket ) printf( "can't push in integer table" ), exit( EXIT_FAILURE );
  } // for
  
  if ( gIT[ currentBucket ] && gIT[ currentBucket ] == i ) return currentBucket;
  gIT[ currentBucket ] = i;
  return currentBucket;
} // ITPush()

int FTPush( double d ) {
  if ( d == 0.0 ) return -1;
  StrOTE buf;
  sprintf( buf, "%.3f", d );
  if ( !strcmp( buf, "-0.000" ) ) return -1;
  
  int currentBucket, homeBucket = Hash( buf ) % 1009;
  for ( currentBucket = homeBucket ; gFT[ currentBucket ]
        && gFT[ currentBucket ] != d ; ) {
    currentBucket = ( currentBucket + 1 ) % 1009;
    if ( currentBucket == homeBucket ) printf( "can't push in float table" ), exit( EXIT_FAILURE );
  } // for
    
  if ( gFT[ currentBucket ] && gFT[ currentBucket ] == d ) return currentBucket;
  gFT[ currentBucket ] = d;
  return currentBucket;
} // FTPush()

int SymTPush( int hvalue ) {
  int currentBucket, homeBucket = hvalue % 1009;
  for ( currentBucket = homeBucket ; gSymT[ currentBucket ].tokenStr[ 0 ]
        && strcmp( gSymT[ currentBucket ].tokenStr, gLTS ) ; ) {
    currentBucket = ( currentBucket + 1 ) % 1009;
    if ( currentBucket == homeBucket ) printf( "can't push into symbol table" ), exit( EXIT_FAILURE );
  } // for
    
  if ( gSymT[ currentBucket ].tokenStr[ 0 ] && !strcmp( gSymT[ currentBucket ].tokenStr, gLTS ) )
    return currentBucket;
  strcpy( gSymT[ currentBucket ].tokenStr, gLTS );
  return currentBucket;
} // SymTPush()

int RTSearch( int hvalue ) {
  int currentBucket, homeBucket = hvalue % 101;
  for ( currentBucket = homeBucket ; gRT[ currentBucket ][ 0 ]
        && strcmp( gRT[ currentBucket ], gLTS ) ; ) {
    currentBucket = ( currentBucket + 1 ) % 101;
    if ( currentBucket == homeBucket ) return 0;
  } // for
    
  if ( gRT[ currentBucket ][ 0 ] && !strcmp( gRT[ currentBucket ], gLTS ) )
    return currentBucket;
  return 0;
} // RTSearch()

int GetCh() {
  char ch = 0;
  if ( gCBp > 0 ) ch = gCB[ --gCBp ];
  else {
    ch = getchar();
    if ( ch == EOF ) gColumn++, NoCh( ch ), ch = '\n';
  } // else
  
  gColumn++;
  return ch;
} // GetCh()

void NoCh( int c ) {         // push character back on input
  if ( gCBp >= 5 ) printf( "ungetch: too many character\n" ), exit( EXIT_FAILURE );
  gCB[ gCBp++ ] = c, gColumn--;
  if ( gColumn < 0 ) printf( "column < 0 !!\n" ), exit( EXIT_FAILURE );
} // NoCh()

void Escape_scheme() { printf( "Thanks for using OurScheme!\n" ), exit( EXIT_SUCCESS ); } 

bool IsSpr( char c ) { return isspace( c ) ? true : ( gSpr[ ( int ) c ] == c ) ? true : false; }

bool IsFTok( StrOTE tok ) { // check if the last token is a float
  int i = 0, dotNum = 0;
  bool hasDigit = false;
  if ( ( tok[ i ] == '+' || tok[ i ] == '-' ) && !tok[ ++i ] ) return false;
  for ( ; tok[ i ] ; i++ )
    if  ( isdigit( tok[ i ] ) ) hasDigit = true;
    else if ( tok[ i ] == '.' ) dotNum++;
    else return false;

  return ( dotNum > 1 || dotNum == 0 || !hasDigit ) ? false : true;
} // IsFTok()

bool InformationTok( StrOTE tok ) { // check if the last token is a integer
  int i = 0;
  if ( ( tok[  i ] == '+' || tok[ i ] == '-' ) && !tok[ ++i ] ) return false;
  for ( ; tok[ i ] ; i++ )
    if ( !isdigit( tok[ i ] ) ) return false;
  return true;
} // InformationTok()

void InSp( TokenPtr tok ) {
  if ( !gSexp ) gLastSexp = gSexp = tok;
  else {
    gLastSexp -> next = tok;
    gLastSexp = gLastSexp -> next;
  } // else
} // InSp()

void FrSp() {
  if ( !gSexp ) return;
  for ( TokenPtr sexp = NULL; gSexp ; gSexp = sexp )
    sexp = gSexp -> next, delete gSexp;
  gLastSexp = NULL;
} // FrSp()

void CoutTok( TokenPtr tok, bool isCoutTree, bool isNewline ) {
  int type   = tok -> type, value = tok -> value, column = gPTC;
  gPTC = 0;
  if      ( type ==   T ) printf( "#t"  );
  else if ( type == NIL ) printf( "nil" );
  else if ( type == STRING || type == -5 ) printf( "\"%s\"", gStrT[ value ] );
  else if ( type ==  FLOAT ) {
    if ( value == -1 ) printf( "%.3f", 0.0 );
    else printf( "%.3f", gFT[ value ]  );
  } // else if
  else if ( type ==    INT ) {
    if ( value == -1 ) printf( "0" );
    else printf( "%d", gIT[ value ] );
  } // else if
  else if ( type == SYMBOL ) printf( "%s", gSymT[ value ].tokenStr );
  else if ( type == RESERW ) printf( "%s", gRT[ value ] );
  else if ( type == 777 ) gPTC = column;
  else if ( type == QUOTE ) printf( "( quote" );
  else if ( type ==    LP ) {
    if ( isCoutTree ) printf( "( " ), gPTC = column + 2;
    else               printf( "("  );
  } // else if
  else if ( type == 333 ) printf( "#<procedure lambda>" );
  else if ( type ==      7557 ) printf( "%s", gSymT[ value ].tokenStr );
  else if ( type == 23 ) ;
  else printf( "%c", type  ) ;

  if ( isNewline ) printf( "\n" );
} // CoutTok()

void StrcatTok( StrOTE dest, TokenPtr tok ) {
  StrOTE buf;
  int type = tok -> type, value = tok -> value;
  if      ( type ==      T ) sprintf( buf, "#t"  );
  else if ( type ==    NIL ) sprintf( buf, "nil" );
  else if ( type == STRING ) sprintf( buf, "\"%s\"", gStrT[  value ] );
  else if ( type ==  FLOAT ) {
    if ( value == -1 ) sprintf( buf, "%.3f", 0.0 );
    else sprintf( buf, "%.3f", gFT[ value ]  );
  } // else if
  else if ( type ==    INT ) {
    if ( value == -1 ) sprintf( buf, "0" );
    else sprintf( buf, "%d", gIT[ value ] );
  } // else if
  else if ( type == SYMBOL ) strcpy( buf, gSymT[  value ].tokenStr );
  else if ( type == RESERW ) sprintf( buf, "%s", gRT[ value ] );
  else                       sprintf( buf, "%c", type );
  strcat( dest, buf );
} // StrcatTok()

int GetStr() {
  char peekCh, ch = GetCh();
  while ( ch != '\"' && ch != '\n' ) {
    if ( ch == '\\' ) {
      peekCh = GetCh();
      if      ( peekCh == 'n'  ) LTS_push( '\n' ); // \n
      else if ( peekCh == 't'  ) LTS_push( '\t' ); // \t
      else if ( peekCh == '\"' ) LTS_push( '\"' ); // >> \" -> " <<
      else if ( peekCh == '\\' ) LTS_push( '\\' ); // >> \\ -> \ <<
      else {
        LTS_push( ch    );
        NoCh( peekCh );
      } // else
    } // if
    else LTS_push( ch );
    ch = GetCh();
  } // while

  if ( ch == '\n' ) {
    if ( !gIRd )
      printf( "ERROR (no closing quote) : END-OF-LINE encountered at Line %d Column %d\n", gLine, gColumn );
    else
      sprintf( gEMsg, "ERROR (no closing quote) : END-OF-LINE encountered at Line %d Column %d\n",
               gLine, gColumn );
    NoCh( ch );
    return false;
  } // if

  LTS_push( '\0' );
  return true;
} // GetStr()

void SkipL() {
  for ( int ch = '\0'; ch != '\n' && ch != EOF ; )
    ch = GetCh();
  gLine++, gColumn = 0;
} // SkipL()

int SkipWhiteSpaceGetch() {
  char ch = GetCh();
  while ( isspace( ch ) ) {  // skip whitespace
    if ( ch == '\n' ) gLine++, gColumn = 0;
    ch = GetCh();
  } // while

  if ( ch == EOF ) printf( "ERROR (no more input) : END-OF-FILE encountered\n" ), Escape_scheme();
  return ch;
} // SkipWhiteSpaceGetch()

int GetToken() {         // return next token
  char    ch = SkipWhiteSpaceGetch();
  printf( "%c",ch );
  if( ch == 'd' )
    paste = true ;
  else if ( ch == 'e' )
    paste = false ;
  int column = gColumn;
  gLT = NULL, gLTS_top = -1;
  if ( ch == '\"' ) {     // get a string
    if ( !GetStr() ) return gTokentype = 999;
    gLT = ShinToken( STRING, StrTPush( gLTS ), gLine, column );
    return gTokentype = STRING;
  } // if
  else if ( ch == ';' ) { // skip comment
    SkipL();
    return GetToken();
  } // else if
  
  while ( !IsSpr( ch ) ) LTS_push( ch ), ch = GetCh(),printf( "%c",ch ); // get char util char is separator
  if ( Emp( gLTS_top ) && !isspace( ch ) ) LTS_push( ch );
  else                                         NoCh(  ch );
  LTS_push( '\0' );
  if ( !strcmp( gLTS, "(" ) ) {  // if get LP
    ch = SkipWhiteSpaceGetch();
    if ( ch == RP )     gTokentype = NIL;
    else NoCh( ch ), gTokentype = LP;
  } // if
  else if ( !strcmp(  gLTS, ")" ) )    gTokentype = RP;
  else if ( !strcmp(  gLTS, "." ) )    gTokentype = DOT;
  else if ( !strcmp(  gLTS, "nil" ) ||
            !strcmp(  gLTS, "#f"  ) ||
            !strcmp(  gLTS, "()" ) )   gTokentype = NIL;
  else if ( !strcmp(  gLTS, "t"  )  ||
            !strcmp(  gLTS, "#t" ) )   gTokentype = T;
  else if ( !strcmp(  gLTS, "\'" ) )   gTokentype = QUOTE;
  else if ( InformationTok( gLTS ) ) {
    gLT = ShinToken( INT, ITPush( atoi( gLTS ) ), gLine, column );
    return gTokentype = INT;
  } // else if
  else if ( IsFTok( gLTS ) ) {
    gLT = ShinToken( FLOAT, FTPush( atof( gLTS ) ), gLine, column );
    return gTokentype = FLOAT;
  } // else if
  else {
    int hvalue = Hash( gLTS ), index = RTSearch( hvalue );
    if ( index ) gTokentype = RESERW;    // if token is a function set type
    else {
      index      = SymTPush( hvalue ); // if token is not a function, then it is a symbol
      gTokentype = SYMBOL;
      if( paste == true )
      printf( "SYMbol\n" ),dfuse.AnoDef = index,dpaste = true;
      
      if( dpaste == true )
      printf( "ok" ),dfuse.define = index,dfuse.hasAnD = true,uset.push_back(dfuse);
      
      std::cout<<gSymT[index].tokenStr<<std::endl;
      paste = false;
      dpaste = false ;
      printf( "%d", index );
    } // else
    
    gLT = ShinToken( gTokentype, index, gLine, column );
    return gTokentype;
  } // else
  

  gLT = ShinToken( gTokentype, 1, gLine, column );
  return gTokentype;
} // GetToken()

void CoutSE( TokenPtr tok, char c ) {
  if ( !gIRd ) {
    printf( "ERROR (unexpected token) : atom or '%c' expected when token at Line %d Column %d is >>",
            c, tok -> line, tok -> column );
    CoutTok( tok, false, false ), printf( "<<\n" );
  } // if
  else {
    char tmp[] = "<<";
    sprintf( gEMsg,
             "ERROR (unexpected token) : atom or '%c' expected when token at Line %d Column %d is >>",
             c, tok -> line, tok -> column );
    StrcatTok( gEMsg, gLT );
    strcat( gEMsg, tmp );
  } // else
} // CoutSE()

bool GetSe( TokenPtr tok ) { // Get a <S-exp>
  bool isSexp = false;
  if ( tok -> type == 999 ) return false;
  if ( tok -> type == RP ) { // <ATOM> ')'
    if ( gINMP < 1 ) {
      CoutSE( tok, '(' );
      return false;
    } // if
    
    InSp( tok ), --gINMP;
    return true;
  } // if
  
  if ( tok -> type == DOT ) { // '.'
    CoutSE( tok, '(' );
    return false;
  } // if
  
  if ( tok -> type == LP ) { // LEFT-PAREN <S-exp> { <S-exp> } [ DOT <S-exp> ] RIGHT-PAREN
    InSp( tok );
    int currentParen = gINMP++;
    if ( GetToken() == 999 ) return false;
    isSexp = GetSe( gLT );
    while ( isSexp && ( gINMP != currentParen ) ) {
      if ( GetToken() == 999 ) return false;
      if ( gTokentype ==   DOT ) {
        InSp( gLT );
        if ( GetToken() == 999 ) return false;
        if ( gTokentype ==    RP ) {          
          CoutSE( gLT, '(' );
          return false;
        } // if
        
        if ( !GetSe( gLT ) || GetToken() == 999 ) return false;
        if ( gTokentype != RP ) {
          if ( !gIRd ) {
            printf( "ERROR (unexpected token) : ')' expected when token at Line %d Column %d is >>",
                    gLT -> line, gLT -> column );
            CoutTok( gLT, false, false ), printf( "<<\n" );
            return false;
          } // if
          else {
            sprintf( gEMsg,
                     "ERROR (unexpected token) : ')' expected when token at Line %d Column %d is >>",
                     gLT -> line, gLT -> column );
            StrcatTok( gEMsg, gLT );
            strcat( gEMsg, "<<" );
            return false;
          } // else
        } // if
        
        InSp( gLT ), --gINMP;
        return true;
      } // if
      
      isSexp = GetSe( gLT );
    } // while
    
    return ( isSexp && ( gINMP == currentParen ) ) ? true : false;
  } // if
  
  if ( tok -> type == QUOTE ) { // QUOTE <S-exp>
    InSp( tok );
    if ( GetToken() == 999 || !GetSe( gLT ) ) return false;
    InSp( ShinToken( RP, 1, 1, 1 ) );
    return true;
  } // if

      // <ATOM>, or terminal
  if ( tok -> type == SYMBOL || tok -> type == RESERW || tok -> type == INT || tok -> type == FLOAT ||
       tok -> type == STRING || tok -> type == NIL    || tok -> type == T ) {
    InSp( tok );
    return true;
  } // if

  return false;
} // GetSe()

TnodePtr Ntnode( TokenPtr tok ) {
  TnodePtr tnode = new Tnode;
  tnode ->   tok = tok;
  tnode ->  left = tnode -> right = NULL;
  tnode -> tieNum = 0;
  return tnode;
} // Ntnode()

TokenPtr SeDeQ() {
  if ( !gSQh ) return NULL;
  TokenPtr sexp = gSQh;
  gSQh    = gSQh -> next;
  return sexp;
} // SeDeQ()

void SePush( TokenPtr tok ) { tok -> next = gSQh, gSQh = tok; } // SePush()

TnodePtr BPTree() { // return a root of parse tree
  TokenPtr current = SeDeQ();  
  if ( !current ) return NULL;
  TokenPtr next = ( current -> next ) ? ( current -> next ) : NULL;
  if ( next && current -> type != DOT && current -> type != LP &&
       current -> type != 777       && current -> type != QUOTE
       && next -> type != DOT && next -> type != RP )
    SePush( ShinToken( 777, 1, 0, 0 ) );
  TnodePtr root = NULL;
        // <ATOM>, or terminal
  if ( current -> type == RP )  return NULL;
  if ( current -> type == SYMBOL || current -> type == RESERW || current -> type == INT ||
       current -> type == FLOAT  || current -> type == STRING || current -> type ==   T ||
       current -> type == NIL )
    return root = Ntnode( TokCpy( current ) );            // QUOTE <S-exp>
  else if ( current -> type == QUOTE ) root = Ntnode( TokCpy( current ) ), gHQu = true; 
  else if ( current -> type == DOT || current -> type == LP || current -> type == 777 ) {
        // LEFT-PAREN <S-exp> { <S-exp> } [ DOT <S-exp> ] RIGHT-PAREN
    if ( current -> type == DOT && current -> next -> type == NIL && !gHQu ) {
      SeDeQ();
      SeDeQ();
      return NULL;
    } // if
    else if ( current -> type == DOT && current -> next -> type == LP ) {
      SeDeQ();
      SePush( ShinToken( 777, 1, 0, 0 ) );
      root = Ntnode( ShinToken( 777, 1, 0, 0 ) );
    } // if
    else root = Ntnode( TokCpy( current ) );
  } // else if

  root -> left  = BPTree();
  root -> right = BPTree();
  if ( current -> type == QUOTE ) gHQu = false;
  if ( gHQu && root -> left && !root -> right &&  // delete the nil node
       ( root -> tok -> type == DOT ) && ( root -> left -> tok -> type == NIL ) )
    delete root -> left, delete root -> left -> tok, delete root, delete root -> tok, root = NULL; 
  else if ( !root -> left && !root -> right &&  // delete the nil node
            ( root -> tok -> type == 777 || root -> tok -> type == LP ||
              root -> tok -> type == DOT   || root -> tok -> type == QUOTE ) )
    delete root, delete root -> tok, root = NULL;
  return root;
} // BPTree()

void CoutTree( TnodePtr parseTree, int i, bool isWrite ) {
  if ( !parseTree ) return;
  TokenPtr rootTok = parseTree -> tok;
  if ( rootTok -> type == 7557 && i == 1 && rootTok -> line != -2 ) {
    printf( "#<procedure %s>", gSymT[ rootTok -> value ].tokenStr );
    if ( !isWrite || i != 1 ) printf( "\n" );
    return;
  } // if
  else if ( rootTok -> type == RESERW && i == 1 && rootTok -> line != -2 ) {
    printf( "#<procedure %s>", gRT[ rootTok -> value ] );
    if ( !isWrite || i != 1 ) printf( "\n" );
    return;
  } // else if
  else if ( rootTok -> type == 333 ) {
    printf( "#<procedure lambda>" );
    if ( !isWrite || i != 1 ) printf( "\n" );
    return;
  } // else if
  else if ( rootTok -> type == 23 ) return;
  
  while ( gPTC < gINMP ) printf( "  " ), gPTC += 2;
  CoutTok( rootTok, true, false );
  if ( rootTok -> type != LP  && rootTok -> type != 777 && ( !isWrite || i != 1 ) ) printf( "\n" );
  if ( rootTok -> type == LP  || rootTok -> type == QUOTE ) gINMP += 2;
  CoutTree( parseTree ->  left, i+1, isWrite );
  CoutTree( parseTree -> right, i+1, isWrite );
  if ( rootTok -> type == LP  || rootTok -> type == QUOTE ) {
    gINMP -= 2;
    while ( gPTC < gINMP ) printf( "  " ), gPTC += 2;
    printf( ")" ),   gPTC = 0;
    if ( !isWrite || gPTC < gINMP ) printf( "\n" );
  } // if
} // CoutTree()

bool Parser( TnodePtr & parseTree ) { // parse OurScheme syntax
  gINMP = 0, gLT = NULL, gHQu = false;

  if ( GetToken() != 999 && GetSe( gLT ) ) {

    // build parse tree
    gSQh = gSexp; // set sex q
    parseTree  = BPTree();
    gColumn    = 1;
    char ch    = GetCh();      // skip ' ' && '\t'
    FrSp();
    while   ( ch == ' ' || ch == '\t' ) ch = GetCh();
    if      ( ch == ';'  ) gLine = 0;  // if ; || '\n' next line is first line
    else if ( ch == '\n' ) gLine = 0;
    else                   gLine = 1, gColumn--;
    NoCh( ch );
    return true;
  } // if
  
  SkipL(), FrSp(), gLine = 1;  // if error, ignored this line
  if ( gLT )  delete gLT;
  return false;
} // Parser()

void Information() {
  gSpr[ 40 ] = '(', gSpr[ 41 ] =  ')', gSpr[ 39 ] = '\'';
  gSpr[ 59 ] = ';', gSpr[ 34 ] = '\"';
  strcpy( gSymT[243].tokenStr, "else" );
  strcpy( gSymT[0].tokenStr, ">_ourScheme_ERR<" );
  strcpy( gRT[0], ">>_ourScheme_ERR_<<" );
  strcpy( gRT[3], "create-error-object" );
  strcpy( gRT[22], "exit"      ), strcpy( gRT[ 23      ], "define"         );
  strcpy( gRT[43], "+"         ), strcpy( gRT[ 45         ], "-"              );
  strcpy( gRT[42], "*"         ), strcpy( gRT[ 47         ], "/"              );
  strcpy( gRT[61], "="         ), strcpy( gRT[ 98         ], "car"            );
  strcpy( gRT[63], "cdr"       ), strcpy( gRT[ 91        ], "cons"           );
  strcpy( gRT[37], "list"      ), strcpy( gRT[ 80         ], "quote"          );
  strcpy( gRT[58], "if"        ), strcpy( gRT[ 90        ], "cond"           );
  strcpy( gRT[8], "null?"     ), strcpy( gRT[ 21      ], "<="             );
  strcpy( gRT[24], ">="        ), strcpy( gRT[ 25       ], "begin"          );
  strcpy( gRT[26], "string?"   ), strcpy( gRT[ 27       ], "eqv?"           );
  strcpy( gRT[46], "real?"     ), strcpy( gRT[ 19       ], "equal?"         );
  strcpy( gRT[59], "not"       ), strcpy( gRT[ 60       ], "<"              );
  strcpy( gRT[62], ">"         ), strcpy( gRT[ 64      ], "pair?"          );
  strcpy( gRT[100], "list?"     ), strcpy( gRT[ 70       ], "number?"        );
  strcpy( gRT[99], "atom?"     ), strcpy( gRT[ 78       ], "symbol?"        );
  strcpy( gRT[81], "boolean?"  ), strcpy( gRT[ 84       ], "integer?"       );
  strcpy( gRT[87], "string<?"  ), strcpy( gRT[ 88      ], "string=?"       );
  strcpy( gRT[89], "string>?"  ), strcpy( gRT[ 28      ], "lambda"         );
  strcpy( gRT[94], "set!"      ), strcpy( gRT[ 29         ], "let"            );
  strcpy( gRT[69], "string-append"     ), strcpy( gRT[ 77 ], "and"            );
  strcpy( gRT[66], "clean-environment" ), strcpy( gRT[ 5  ], "or"             );
  strcpy( gRT[56], "read"      ), strcpy( gRT[ 93    ], "display-string" );
  strcpy( gRT[20], "write"     ), strcpy( gRT[ 33      ], "symbol->string" );
  strcpy( gRT[82], "eval"      ), strcpy( gRT[ 30      ], "number->string" );
  strcpy( gRT[31], "verbose"   ), strcpy( gRT[ 97     ], "verbose?"       );
  strcpy( gRT[92], "newline"   ), strcpy( gRT[ 79    ], "error-object?"  );
} // Information()
