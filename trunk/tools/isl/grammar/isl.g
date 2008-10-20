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
    classType STARTDEF cstatements* ENDDEF;

classType :
        classMaterial
    |   classConfig
    ;
    
classMaterial : MATDEF^ idinherit?;
classConfig :  CNFDEF^ idinherit?;

cstatements: 
        classdef
    | assignment;

assignment :
    id ASSIGN expr_or_def ';'? -> ^(ASSIGN id ASSIGN expr_or_def)
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
    | STRING
    | BOOLLITERAL    
    | list_or_expr
    ;   
    
list_or_expr : 
      ('('  addexpr COMMA addexpr (COMMA? addexpr)* ')') => '('  addexpr COMMA addexpr (COMMA? addexpr)* ')' -> ^(LIST addexpr*)
    | ('('! addexpr ')'!)
    ;
    
id : NAME (DOT ! NAME)*;
idinherit : NAME | (NAME COLON NAME) -> ^(INHERIT NAME NAME);

// LEXER
CNFDEF : 'config';
MATDEF : 'material';

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
    
// ignore #line info for now
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

			// Note that the input stream is not closed when it EOFs, I don't bother
			// to do it here (hence this is leaked at the program end), 
			// but it is up to you to track streams created like this
			// and destroy them when the whole parse session is complete. Remember that you
			// don't want to do this until all tokens have been manipulated all the way through 
			// your tree parsers etc as the token does not store the text it just refers
			// back to the input stream and trying to get the text for it will abort if you
			// close the input stream too early.
			//

		}
            
	) {$channel=HIDDEN;}
    ;    
