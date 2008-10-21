grammar isl;

options 
{ 
    output = AST; 
    language = C; 
    ASTLabelType = pANTLR3_BASE_TREE;
}

tokens {
    ASSIGN;
    LIST;
    INHERIT;   
}

@lexer::header
{

void* doInclude(void* plexer, char *filename);
}


script : statements+ 
    ;

statements :
      classdef
    | assignment
    ;

classdef:
    classType SDEF statements* EDEF;

classType :
      classConfig
    | classLayer
    | classMaterial
    | classMatrix
    ;
    
classMaterial : MATDEF^ idinherit?;
classConfig :  CNFDEF^ idinherit?;
classLayer : LAYDEF^ idinherit?;
classMatrix : MTXDEF^ idinherit?;

assignment :
    id ASSIGN expr_or_def SCOLON? -> ^(ASSIGN id ASSIGN expr_or_def)
    ;
    
expr_or_def :
    (classdef | addexpr)
    ;
    
// using AST construction ops ('^', '!') for arithmetic expressions
addexpr : (mulexpr) (ADD^ mulexpr | SUB^ mulexpr)*;

mulexpr : atom (MUL^ atom | DIV^ atom)*;    
    
atom : 
      id
    | FLOAT
    | INTEGER
    | HEX
    | STRING
    | BOOLLITERAL    
    | list_or_expr
    ;   
        
list_or_expr : 
      (LPAREN  addexpr COMMA addexpr (COMMA? addexpr)* RPAREN) => LPAREN addexpr COMMA addexpr (COMMA? addexpr)* RPAREN -> ^(LIST addexpr*)
    | (LPAREN! addexpr RPAREN!)
    ;
        
id : NAME (DOT ! NAME)*;
idinherit : (NAME | INTEGER) | (NAME COLON NAME) -> ^(INHERIT NAME NAME);

// LEXER
CNFDEF : 'config';
MATDEF : 'material';
LAYDEF : 'layer';
MTXDEF : 'matrix';

BOOLLITERAL
    :   'true'
    |   'false'
    ;  
	
STRING
   :	'\'' ( EscapeSequence | ~('\'' | '\\') )* '\''
   |    '"' ( EscapeSequence | ~('\\' | '"') )* '"'
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
SCOLON  : ';';
COMMA   : ',';
LPAREN  : '(';
RPAREN  : ')';
SDEF    : '{';
EDEF    : '}';

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
    
LINE_COMMAND 
    : '#' (' ' | '\t')*
    (
	'include' (' ' | '\t')+ file = STRING (' ' | '\t')* '\r'? '\n'
	{
	    pANTLR3_STRING		fName;
	    pANTLR3_INPUT_STREAM    in;

	    // Create an initial string, then take a substring
	    // We can do this by messing with the start and end
	    // pointers of tokens and so on. This shows a reasonable way to
	    // manipulate strings.
	    //
	    fName = $file.text;
	    in = doInclude(CTX, fName->chars);

	    // Create a new input stream and take advantage of built in stream stacking
	    // in C target runtime.
	    //
	    //in = antlr3AsciiFileStreamNew(fName->chars);
			
	    if(in)
	    	PUSHSTREAM(in);

	}
            
    ) {$channel=HIDDEN;}
    ;    
