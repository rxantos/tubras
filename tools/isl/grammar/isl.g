grammar isl;

options 
{ 
    output = AST; 
    language = C; 
    ASTLabelType = pANTLR3_BASE_TREE;
}

tokens {
    OBJECT;
    ASSIGN;
    LIST;
    INHERIT;
    ADD; SUB; MUL; DIV;
}

script : statements+ 
    ;

statements :
      classdef
    | assignment
    ;

classdef:
    classType STARTDEF cstatements* ENDDEF;

classType :
        classColor
    |   classMaterial
    |   classConfig
    ;
    
classColor : COLDEF^ idinherit?;
classMaterial : MATDEF^ idinherit?;
classConfig :  CNFDEF^ idinherit?;

cstatements: 
        classdef
    | assignment;

assignment :
    id ASSIGN expr_or_def ';' -> ^(ASSIGN id ASSIGN expr_or_def)
    ;
    
expr_or_def :
    (addexpr | classdef)
    ;
    
// using AST construction ops ('^', '!') for arithmetic expressions
addexpr : (mulexpr) (ADD^ mulexpr | SUB^ mulexpr)*;

mulexpr : atom (MUL^ atom | DIV^ atom)*;    
    
atom : 
      id
    | FLOAT
    | INTEGER
    | STRING
    | abool
    | list
    ;   
    
    
list : LPAREN addexpr (COMMA? addexpr)* RPAREN -> ^(LIST addexpr*)
    ;
    
abool : BTRUE | BFALSE;
    
id : NAME (DOT! NAME)*;
idinherit : NAME | (NAME COLON NAME) -> ^(INHERIT NAME NAME);
           
STRING  : ('"' .* '"') | ('\'' .* '\'') ;
DOT     : '.';
COLON   : ':';
COMMA   : ',';
LPAREN  : '(';
RPAREN  : ')';
INTEGER : ('0'..'9')*;
BTRUE    : ('TRUE' | 'True' | 'true');
BFALSE   : ('FALSE' | 'False' | 'false');
ASSIGN  : '=';
ADD     : '+';
SUB     : '-';
MUL     : '*';
DIV     : '/';
STARTDEF : '{';
ENDDEF : '}';

COLDEF  : 'color';
MATDEF  : 'material';
CNFDEF  : 'config';

FLOAT   : INTEGER '.' INTEGER;
NAME    : ('a'..'z' |'A'..'Z' |'_' ) ('a'..'z' |'A'..'Z' |'0'..'9' |'_' )* ;

MCMT    : '/*' .* '*/'  { $channel=HIDDEN; } ;
SCMT    : '//' (~('\n'|'\r'))* { $channel=HIDDEN; };
WS      : ( ' ' | '\t' | '\r' | '\n' )+ { $channel = HIDDEN; } ;

