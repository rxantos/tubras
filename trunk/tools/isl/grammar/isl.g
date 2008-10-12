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
    ADD; SUB; MUL; DIV;
}

script : statements+ 
    ;

statements :
      classdef
    | assignment
    ;

classdef:
    classType '{' cstatements* '}';

classType :
        classColor
    |   classMaterial
    |   classConfig
    ;
    
classColor : 'color'^ idinherit?;
classMaterial : 'material'^ idinherit?;
classConfig : 'config'^ idinherit?;

cstatements: 
        classdef
    | assignment;

assignment :
    id ASSIGN^ expr_or_def ';'!
    ;
    
expr_or_def :
    (addexpr | classdef)
    ;
    
// using AST construction ops ('^', '!') for arithmetic expressions
addexpr : (mulexpr) ('+'^ mulexpr | '-'^ mulexpr)*;

mulexpr : atom ('*'^ atom | '/'^ atom)*;    
    
atom : 
      id
    | FLOAT
    | INTEGER
    | STRING
    | LPAREN list_or_expr? RPAREN
    ;   
    
list_or_expr
    : addexpr (COMMA? addexpr)* 
    ;    
    
id : NAME (DOT NAME)*;
idinherit : NAME | (NAME COLON^ NAME) ;
           
STRING  : ('"' .* '"') | ('\'' .* '\'') ;
DOT     : '.';
COLON   : ':';
COMMA   : ',';
LPAREN  : '(';
RPAREN  : ')';
INTEGER : ('0'..'9')*;
ASSIGN  : '=';

FLOAT   : INTEGER '.' INTEGER;

NAME    : ('a'..'z' |'A'..'Z' |'_' ) ('a'..'z' |'A'..'Z' |'0'..'9' |'_' )* ;

MCMT    : '/*' .* '*/'  {$channel=HIDDEN;} ;
SCMT    : '//' (~('\n'|'\r'))* {$channel=HIDDEN;};
WS      : ( ' ' | '\t' | '\r' | '\n' )+ { $channel = HIDDEN; } ;

