%option c++ prefix="fir_scanner_" outfile="fir_scanner.cpp"
%option stack noyywrap yylineno 8bit debug
%{ 
// make relevant includes before including the parser's tab file
#include <string>
#include <sstream>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include <cstring>
#include <cdk/ast/lvalue_node.h>
#include "fir_parser.tab.h"

static std::ostringstream strlit;

// don't change this
#define yyerror LexerError
%}
%x X_STRING X_COMMENT X_TILDE


DIGIT							    [0-9]
EXPONENT          		            [eE][-+]?{DIGIT}+
REAL							    {DIGIT}+{EXPONENT}|({DIGIT}+"."{DIGIT}*|{DIGIT}*"."{DIGIT}+){EXPONENT}?

B10_INT							    [1-9]{DIGIT}*|0
B8_INT							    0[0-7]+


%%

 /* ========================================================================== */
 /*                        comment to run tests without verbose                */
 /* ========================================================================== */

  //  {yydebug=1; set_debug(1);}







  /* ====================================================================== */
  /* ====[                      2.2 - COMMENTS                        ]==== */
  /* ====================================================================== */

"!!".*$                /* match the whole line (it is ignored) */

"(*"                   yy_push_state(X_COMMENT);
<X_COMMENT>"*)"        yy_pop_state();
<X_COMMENT>.|"\n"      ;  /* ignore inside comments */



  /* ====================================================================== */
  /* ====[                  1.1   - Tipos de dados                    ]==== */
  /* ====[                  1.1   - Null pointers                     ]==== */
  /* ====[                  1.1   - Procedures                        ]==== */
  /* ====================================================================== */

"int"                  return tTYPE_INT;
"float"                return tTYPE_FLOAT;
"string"               return tTYPE_STRING;
"void"                 return tTYPE_VOID;
"sizeof"               return tSIZEOF;
"null"                 return tNULLPTR;

[<>]                     return *yytext;

  /* ====================================================================== */
  /* ====[                 5.5 - Instrução condicional                ]==== */
  /* ====================================================================== */
"if"                   return tIF; 
"else"                 return tELSE;



  /* ====================================================================== */
  /* ====[                 5.5 - Instrução de iteração                ]==== */
  /* ====[                 5.5 - Instrução de terminação              ]==== */
  /* ====[                 5.4 - Instrução de continuação             ]==== */
  /* ====================================================================== */
"do"                   return tDO;
"while"                return tWHILE;
"leave"                return tLEAVE;
"restart"              return tRESTART;
"finally"              return tFINALLY;


  /* ====================================================================== */
  /* ====[                 6 - Operadores de expressões               ]==== */
  /* ====================================================================== */
">="                   return tGE; 
"<="                   return tLE; 
"=="                   return tEQ; 
"!="                   return tNE;
"&&"                   return tAND;
"||"                   return tOR;
"~"                    return tNOT;



  /* ====================================================================== */
  /* ====[              3   - Delimitadores e separadores             ]==== */
  /* ====[              4.3 - Corpo (de função)                       ]==== */
  /* ====[                 5.3 - Instrução de retorno                 ]==== */
  /* ====================================================================== */

"return"               return tRETURN;
"then"                 return tTHEN;
"write"                return tWRITE;
"writeln"              return tWRITELN;


    /* ========================================================================== */
    /*                 6. Outros tokens que nao seI onde colocaer                 */
    /* ========================================================================== */
"->"                   return tARROW;
">>"                   return tEPILOGUE;
"@"                    return tAT; // faz input e prologo

[#\[\](){};:!,]                return *yytext;

[\[\](),?]           return *yytext;
[-+*/%~<>@?=]        return *yytext;



  /* ====================================================================== */
  /* ====[                   2.7.1 - inteiros    e reais                     ]==== */
  /* ====================================================================== */
{REAL}                 { yylval.d = std::strtod(yytext, nullptr);		    if(errno == ERANGE) yyerror("Overflow..."); return tREAL;  }
{B8_INT}			   { yylval.i = std::strtol(yytext, nullptr, 8);	        if(errno == ERANGE) yyerror("Overflow..."); return tINTEGER; }
{B10_INT}              { yylval.i = std::strtol(yytext, nullptr, 10);	    if(errno == ERANGE) yyerror("Overflow..."); return tINTEGER; }

  
    /* ====================================================================== */
    /* ====[                2.6 - Identificadores (nomes)               ]==== */
    /* ====================================================================== */

[A-Za-z][A-Za-z0-9_]*  yylval.s = new std::string(yytext); return tID;


  /* ====================================================================== */
  /* ====[              2.7.3 - Cadeias de caracteres                 ]==== */
  /* ====================================================================== */

'                          yy_push_state(X_STRING); 
<X_STRING>~                    yy_push_state(X_TILDE);
<X_STRING>'               { 
                                 yylval.s = new std::string(strlit.str());
                                 strlit.str("");
                                 yy_pop_state();
                                 return tSTRING;
                               }
<X_STRING>.                    strlit << *yytext;

<X_TILDE>n                 strlit << '\n'; yy_pop_state();
<X_TILDE>r                 strlit << '\r'; yy_pop_state();
<X_TILDE>t                 strlit << '\t'; yy_pop_state();
<X_TILDE>~                strlit << '~'; yy_pop_state();

<X_TILDE>[[:xdigit:]]{1,2} {
                                 strlit << (char)(unsigned char)strtoul(yytext, NULL, 16);
                                 yy_pop_state();
                               }
<X_TILDE>.                 strlit << *yytext; yy_pop_state();


[0-9]+                 yylval.i = strtol(yytext, nullptr, 10); return tTYPE_INT;


[[:space:]]               ; /* ignore whitespace */

.                      yyerror("Unknown character");


%%
