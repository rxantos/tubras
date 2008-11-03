//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
grammar isl;

options 
{ 
    output = AST; 
    language = C; 
    ASTLabelType = pANTLR3_BASE_TREE;
}

tokens {
    ASSIGN;
    TUPLE;
    INHERIT;   
}

@lexer::header
{

void* doInclude(void* plexer, char *filename);
}


script : statements+ 
    ;

statements :
      object
    | assignment
    ;

object:
    objectType block 
    ;
    
block:
    SDEF statements* EDEF
    ;

objectType :
      objectConfig
    | objectLayer
    | objectMaterial
    | objectMatrix
    ;
    
objectMaterial : MATDEF^ idinherit?;
objectConfig :  CNFDEF^ idinherit?;
objectLayer : LAYDEF^ idinherit?;
objectMatrix : MTXDEF^ idinherit?;

assignment :
    id ASSIGN object_or_expr SCOLON? -> ^(ASSIGN id ASSIGN object_or_expr)
    ;
    
object_or_expr :
    (object | expr)
    ;
    
// using AST construction ops ('^', '!') for arithmetic expressions
expr : (mexpr) (ADD^ mexpr | SUB^ mexpr)*;

mexpr : atom (MUL^ atom | DIV^ atom)*;    
    
atom : 
      id
    | FLOAT
    | INTEGER
    | HEX
    | STRING
    | BOOLLITERAL    
    | tuple_or_expr
    ;   
        
tuple_or_expr : 
      (LPAREN  expr COMMA expr (COMMA? expr)* RPAREN) => LPAREN expr COMMA expr (COMMA? expr)* RPAREN -> ^(TUPLE expr*)
    | (LPAREN! expr RPAREN!)
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

INTEGER	: '-' ('0'..'9')+
        | ('0'..'9')+;

FLOAT 	:INTEGER? '.' ('0'..'9')+ ;

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
