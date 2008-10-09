grammar isl;

options 
{ 
    output = AST; 
    language = C; 
    ASTLabelType = pANTLR3_BASE_TREE;
}

script : statements+ 
    ;

statements :
      classdef
    | assignment
    ;

classdef:
    classType '{' cstatements* '}'
{
    pANTLR3_STRING	ct;

    ct = $classType.text;
    
    printf("parsing class '\%s' ...\n", ct->chars);
};

classType :
        classColor
    |   classMaterial
    |   classPass
    ;
    
classColor : 'color' idinherit?;
classMaterial : 'material' idinherit?;
classPass : 'pass' INTEGER?;

cstatements: 
        classdef
    | assignment;

assignment :
    id ('=' | ':') (expr | classdef) ';'
    ;
    
expr : addsubexpr;
    
    
addsubexpr : 
    muldivexpr (('+' | '-') muldivexpr)*
    ;
       
muldivexpr : 
    atom (('*' | '/') atom)*
    ;
    
atom : 
      id
    | FLOAT
    | INTEGER
    | STRING
    | LPAREN list_or_expr? RPAREN
    ;   
    
list_or_expr
    : expr (COMMA? expr)* 
    ;    
    
id : NAME (DOT NAME)*;
idinherit : NAME | (NAME COLON NAME) ;
           
STRING  : ('"' .* '"') | ('\'' .* '\'') ;
DOT     : '.';
COLON   : ':';
COMMA   : ',';
LPAREN  : '(';
RPAREN  : ')';
INTEGER : ('0'..'9')*;

FLOAT   : INTEGER '.' INTEGER;

NAME    : ('a'..'z' |'A'..'Z' |'_' ) ('a'..'z' |'A'..'Z' |'0'..'9' |'_' )* ;


MCMT    : '/*' .* '*/'  {$channel=HIDDEN;} ;
SCMT    : '//' (~('\n'|'\r'))* {$channel=HIDDEN;};
WS      : ( ' ' | '\t' | '\r' | '\n' )+ { $channel = HIDDEN; } ;

