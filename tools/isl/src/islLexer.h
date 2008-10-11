/** \file
 *  This C header file was generated by $ANTLR version 3.1.1
 *
 *     -  From the grammar source file : C:\\gdev\\iTubras\\tools\\isl\\grammar\\isl.g
 *     -                            On : 2008-10-11 13:38:59
 *     -                 for the lexer : islLexerLexer *
 * Editing it, at least manually, is not wise. 
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The lexer islLexer has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 * 
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef pislLexer, which is returned from a call to islLexerNew().
 *
 * As this is a generated lexer, it is unlikely you will call it 'manually'. However
 * the methods are provided anyway.
 * * The methods in pislLexer are  as follows:
 *
 *  -  void      pislLexer->T__18(pislLexer)
 *  -  void      pislLexer->T__19(pislLexer)
 *  -  void      pislLexer->T__20(pislLexer)
 *  -  void      pislLexer->T__21(pislLexer)
 *  -  void      pislLexer->T__22(pislLexer)
 *  -  void      pislLexer->T__23(pislLexer)
 *  -  void      pislLexer->T__24(pislLexer)
 *  -  void      pislLexer->T__25(pislLexer)
 *  -  void      pislLexer->T__26(pislLexer)
 *  -  void      pislLexer->T__27(pislLexer)
 *  -  void      pislLexer->T__28(pislLexer)
 *  -  void      pislLexer->STRING(pislLexer)
 *  -  void      pislLexer->DOT(pislLexer)
 *  -  void      pislLexer->COLON(pislLexer)
 *  -  void      pislLexer->COMMA(pislLexer)
 *  -  void      pislLexer->LPAREN(pislLexer)
 *  -  void      pislLexer->RPAREN(pislLexer)
 *  -  void      pislLexer->INTEGER(pislLexer)
 *  -  void      pislLexer->FLOAT(pislLexer)
 *  -  void      pislLexer->NAME(pislLexer)
 *  -  void      pislLexer->MCMT(pislLexer)
 *  -  void      pislLexer->SCMT(pislLexer)
 *  -  void      pislLexer->WS(pislLexer)
 *  -  void      pislLexer->Tokens(pislLexer)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
#ifndef	_islLexer_H
#define _islLexer_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */
 
#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct islLexer_Ctx_struct islLexer, * pislLexer;



#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule 
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#endif


/** Context tracking structure for islLexer
 */
struct islLexer_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_LEXER    pLexer;


     void (*mT__18)	(struct islLexer_Ctx_struct * ctx);
     void (*mT__19)	(struct islLexer_Ctx_struct * ctx);
     void (*mT__20)	(struct islLexer_Ctx_struct * ctx);
     void (*mT__21)	(struct islLexer_Ctx_struct * ctx);
     void (*mT__22)	(struct islLexer_Ctx_struct * ctx);
     void (*mT__23)	(struct islLexer_Ctx_struct * ctx);
     void (*mT__24)	(struct islLexer_Ctx_struct * ctx);
     void (*mT__25)	(struct islLexer_Ctx_struct * ctx);
     void (*mT__26)	(struct islLexer_Ctx_struct * ctx);
     void (*mT__27)	(struct islLexer_Ctx_struct * ctx);
     void (*mT__28)	(struct islLexer_Ctx_struct * ctx);
     void (*mSTRING)	(struct islLexer_Ctx_struct * ctx);
     void (*mDOT)	(struct islLexer_Ctx_struct * ctx);
     void (*mCOLON)	(struct islLexer_Ctx_struct * ctx);
     void (*mCOMMA)	(struct islLexer_Ctx_struct * ctx);
     void (*mLPAREN)	(struct islLexer_Ctx_struct * ctx);
     void (*mRPAREN)	(struct islLexer_Ctx_struct * ctx);
     void (*mINTEGER)	(struct islLexer_Ctx_struct * ctx);
     void (*mFLOAT)	(struct islLexer_Ctx_struct * ctx);
     void (*mNAME)	(struct islLexer_Ctx_struct * ctx);
     void (*mMCMT)	(struct islLexer_Ctx_struct * ctx);
     void (*mSCMT)	(struct islLexer_Ctx_struct * ctx);
     void (*mWS)	(struct islLexer_Ctx_struct * ctx);
     void (*mTokens)	(struct islLexer_Ctx_struct * ctx);    const char * (*getGrammarFileName)();
    void	    (*free)   (struct islLexer_Ctx_struct * ctx);
        
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pislLexer islLexerNew         (pANTLR3_INPUT_STREAM instream);
ANTLR3_API pislLexer islLexerNewSSD      (pANTLR3_INPUT_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the lexer will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif 
#define INTEGER      7
#define T__28      28
#define T__27      27
#define T__26      26
#define T__25      25
#define T__24      24
#define T__23      23
#define T__22      22
#define T__21      21
#define T__20      20
#define MCMT      15
#define FLOAT      6
#define EOF      -1
#define LPAREN      9
#define COLON      14
#define T__19      19
#define RPAREN      10
#define NAME      12
#define WS      17
#define T__18      18
#define OBJECT      4
#define COMMA      11
#define ASSIGN      5
#define DOT      13
#define SCMT      16
#define STRING      8
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for islLexer
 * =============================================================================
 */
/** \} */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
