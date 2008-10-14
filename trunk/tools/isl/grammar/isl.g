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
    | HEX
    | NSTRING
    | STRING
    | BOOLLITERAL
    | list
    ;   
    
    
list : LPAREN addexpr (COMMA? addexpr)* RPAREN -> ^(LIST addexpr*)
    ;
    
id : NAME (DOT ! NAME)*;
idinherit : NAME | (NAME COLON NAME) -> ^(INHERIT NAME NAME);

// lexer           
// LEXER

COLDEF : 'color';
CNFDEF : 'config';
MATDEF : 'material';

BOOLLITERAL
    :   'true'
    |   'false'
    ;  
	
STRING
   :	'\'' ( EscapeSequence | ~('\''|'\\') )* '\''
   |    '"' ( EscapeSequence | ~('\\'|'"') )* '"'
   ;
   
NAME	:('a'..'z'|'A'..'Z'|'_')(options{greedy=true;}:	'a'..'z'|'A'..'Z'|'_'|'0'..'9')*
	;

INTEGER	: ('0'..'9')+;

FLOAT 	:INTEGER? '.' INTEGER ;

HEX	:'0x' ('0'..'9'| ('a'..'f') | ('A'..'F'))+ ;

ASSIGN  : '=';
ADD     : '+';
SUB     : '-';
MUL     : '*';
DIV     : '/';
DOT     : '.';
COLON   : ':';
COMMA   : ',';
LPAREN  : '(';
RPAREN  : ')';
STARTDEF : '{';
ENDDEF : '}';




fragment
EscapeSequence
    :   '\\' ('b'|'t'|'n'|'f'|'r'|'\"'|'\''|'\\')
    |   UnicodeEscape
    |   OctalEscape
    ;
    
fragment
OctalEscape
    :   '\\' ('0'..'3') ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7')
    ;
    
fragment
UnicodeEscape
    :   '\\' 'u' HexDigit HexDigit HexDigit HexDigit
    ;
    
fragment
HexDigit : ('0'..'9'|'a'..'f'|'A'..'F') ;


WS  :  (' '|'\r'|'\t'|'\u000C'|'\n') {$channel=HIDDEN;}
    ;

COMMENT
    :   '/*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
    ;

LINE_COMMENT
    : '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
    ;
