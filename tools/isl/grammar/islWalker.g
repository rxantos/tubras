tree grammar islWalker;

options 
{
    tokenVocab  = isl;
    ASTLabelType = pANTLR3_BASE_TREE;
    language = C;
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
    
classColor : 'color' idinherit?;
classMaterial : 'material' idinherit?;
classConfig : 'config' idinherit?;

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
