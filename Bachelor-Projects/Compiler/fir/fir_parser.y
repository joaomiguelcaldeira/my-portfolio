%{
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <algorithm>
#include <memory>
#include <cstring>
#include <cdk/compiler.h>
#include <cdk/types/types.h>
#include "ast/all.h"
#define LINE                  compiler->scanner()->lineno()
#define yylex()               compiler->scanner()->scan()
#define yyerror(compiler, s)  compiler->scanner()->error(s)
//-- don't change *any* of these --- END!

#define NIL (new cdk::nil_node(LINE))
%}

%parse-param {std::shared_ptr<cdk::compiler> compiler}

%union {
  //--- don't change *any* of these: if you do, you'll break the compiler.
  YYSTYPE() : type(cdk::primitive_type::create(0, cdk::TYPE_VOID)) {}
  ~YYSTYPE() {}
  YYSTYPE(const YYSTYPE &other) { *this = other; }
  YYSTYPE& operator=(const YYSTYPE &other) { type = other.type; return *this; }

  std::shared_ptr<cdk::basic_type> type;        /* expression type */
  //-- don't change *any* of these --- END!

  int                   i;  /* integer value */
  double                d;  /* integer value */
  std::string          *s;  /* symbol name or string literal */

  cdk::basic_node      *node; /* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  cdk::lvalue_node     *lvalue;
  

  fir::block_node       *block;
  fir::body_node        *body;
}

%token tAND tOR tNE tLE tGE tSIZEOF tNOT
%token tINPUT tWRITE tWRITELN
%token tPRIVATE tPUBLIC
%token tTYPE_STRING tTYPE_INT tTYPE_FLOAT tTYPE_VOID
%token tIF tTHEN tELIF tELSE
%token tWHILE tFINALLY tDO
%token tLEAVE tRESTART tRETURN
%token tARROW tEPILOGUE tAT

%token<i> tINTEGER
%token<d> tREAL
%token<s> tSTRING tID
%token<expression> tNULLPTR

%type<node> instruction return
%type<sequence> file instructions opt_instructions 
%type<sequence> expressions opt_expressions
%type<expression> expression integer real opt_initializer
%type<lvalue> lvalue
%type<block> block epilogue prologue



%type<node>     declaration  argdec  vardec fundec fundef while
%type<sequence> declarations argdecs vardecs opt_vardecs

%type<s> string
%type<type> data_type



%type<body> body

%nonassoc tIF
%nonassoc tTHEN
%nonassoc tELIF tELSE

%right tARROW tDO tFINALLY
%left tAT 

%right '='
%left tOR
%left tAND
%right '~'
%left tNE tEQ
%left '<' tLE tGE '>'
%left '+' '-'
%left '*' '/' '%'
%right tUMINUS
%nonassoc '(' ')' '[' ']'

%%
file         : /* empty */    { compiler->ast($$ = new cdk::sequence_node(LINE)); }
             | declarations { compiler->ast($$ = $1); }
             ;

declarations :              declaration { $$ = new cdk::sequence_node(LINE, $1);     }
             | declarations declaration { $$ = new cdk::sequence_node(LINE, $2, $1); }
             ;

declaration  : vardec ';' { $$ = $1; } 
             | fundef     { $$ = $1; }
             | fundec     { $$ = $1; }

             ;

vardec       : data_type '?' tID                         { $$ = new fir::variable_declaration_node(LINE, tPUBLIC,  $1, *$3, nullptr); }
             | data_type '*' tID         opt_initializer { $$ = new fir::variable_declaration_node(LINE, tPUBLIC,  $1, *$3, $4); }
             | data_type  tID         opt_initializer { $$ = new fir::variable_declaration_node(LINE, tPRIVATE, $1, *$2, $3); }
             ;

vardecs      : vardec ';'          { $$ = new cdk::sequence_node(LINE, $1);     }
             | vardecs vardec ';' { $$ = new cdk::sequence_node(LINE, $2, $1); }
             ;
             
opt_vardecs  : /* empty */ { $$ = NULL; }
             | vardecs     { $$ = $1; }
             ;
             
             
data_type    : tTYPE_STRING                     { $$ = cdk::primitive_type::create(4, cdk::TYPE_STRING);  }
             | tTYPE_INT                        { $$ = cdk::primitive_type::create(4, cdk::TYPE_INT);     }
             | tTYPE_FLOAT                      { $$ = cdk::primitive_type::create(8, cdk::TYPE_DOUBLE);  }
             | '<' data_type '>'                { $$ = cdk::reference_type::create(4, $2); }
             ;
       
opt_initializer  : /* empty */         { $$ = nullptr; /* must be nullptr, not NIL */ }
                 | '=' expression      { $$ = $2; }
                 ;




fundec   :  data_type          tID '(' argdecs ')' { $$ = new fir::function_declaration_node(LINE, tPRIVATE, $1, *$2, $4); }
         |  data_type '?' tID '(' argdecs ')' { $$ = new fir::function_declaration_node(LINE, tPUBLIC, $1, *$3, $5); }
         |  data_type '*'  tID '(' argdecs ')' { $$ = new fir::function_declaration_node(LINE, tPUBLIC,  $1, *$3, $5); }
         |  tTYPE_VOID          tID '(' argdecs ')' { $$ = new fir::function_declaration_node(LINE, tPRIVATE, *$2, $4); }
         |  tTYPE_VOID '?' tID '(' argdecs ')' { $$ = new fir::function_declaration_node(LINE, tPUBLIC, *$3, $5); }
         |  tTYPE_VOID '*'  tID '(' argdecs ')' { $$ = new fir::function_declaration_node(LINE, tPUBLIC,  *$3, $5); }
         ;

         
fundef   :  data_type '*' tID '(' argdecs ')' tARROW expression body{ $$ = new fir::function_definition_node(LINE, tPUBLIC, *$3, $5, $9, $8, $1); }
         |  data_type '?' tID '(' argdecs ')' tARROW expression body{ $$ = new fir::function_definition_node(LINE, tPUBLIC, *$3, $5, $9, $8, $1); }
         |  data_type tID '(' argdecs ')' tARROW expression body{ $$ = new fir::function_definition_node(LINE, tPRIVATE, *$2, $4, $8, $7, $1); }
         |  data_type tID '(' argdecs ')' body{ $$ = new fir::function_definition_node(LINE, tPRIVATE, *$2, $4, $6, nullptr, $1); }
         |  data_type '*' tID '(' argdecs ')' body{ $$ = new fir::function_definition_node(LINE, tPUBLIC, *$3, $5, $7, nullptr, $1); }
         |  data_type '?' tID '(' argdecs ')' body{ $$ = new fir::function_definition_node(LINE, tPUBLIC, *$3, $5, $7, nullptr, $1); }
         |  tTYPE_VOID '*' tID '(' argdecs ')' body{ $$ = new fir::function_definition_node(LINE, tPUBLIC, *$3, $5, $7, nullptr); }
         |  tTYPE_VOID '?' tID '(' argdecs ')' body{ $$ = new fir::function_definition_node(LINE, tPUBLIC, *$3, $5, $7, nullptr); }
         |  tTYPE_VOID tID '(' argdecs ')' body{ $$ = new fir::function_definition_node(LINE, tPRIVATE, *$2, $4, $6, nullptr); }
         |  data_type  tID '(' argdecs ')' tARROW expression { $$ = new fir::function_definition_node(LINE, tPRIVATE, *$2, $4, nullptr, $7, $1); }
         |  data_type  '*' tID '(' argdecs ')' tARROW expression { $$ = new fir::function_definition_node(LINE, tPUBLIC, *$3, $5, nullptr, $8, $1); }
         |  data_type  '?' tID '(' argdecs ')' tARROW expression { $$ = new fir::function_definition_node(LINE, tPUBLIC, *$3, $5, nullptr, $8, $1); }
         ;

argdecs  : /* empty */         { $$ = new cdk::sequence_node(LINE);  }
         |             argdec  { $$ = new cdk::sequence_node(LINE, $1);     }
         | argdecs ',' argdec  { $$ = new cdk::sequence_node(LINE, $3, $1); }
         ;

argdec   : data_type tID { $$ = new fir::variable_declaration_node(LINE, tPRIVATE, $1, *$2, nullptr); }
         ;


  /* ========================================================================== */
  /*                                function body                               */
  /* ========================================================================== */
  

block    : '{' opt_vardecs opt_instructions '}' { $$ = new fir::block_node(LINE, $2, $3, false, false); }
         ;


prologue : tAT block { $2->set_is_prologue(true); $$ = $2;}
         ;
epilogue : tEPILOGUE block {$2->set_is_epilogue(true); $$ = $2;}
         ;
        

body     : prologue { $$ = new fir::body_node(LINE, $1, nullptr, nullptr); }
         | prologue block { $$ = new fir::body_node(LINE, $1, $2, nullptr); }
         | prologue block epilogue { $$ = new fir::body_node(LINE, $1, $2, $3); }
         | block epilogue { $$ = new fir::body_node(LINE, nullptr, $1, $2); }
         | epilogue { $$ = new fir::body_node(LINE, nullptr, nullptr, $1); }
         | prologue epilogue { $$ = new fir::body_node(LINE, $1, nullptr, $2); }
         | block { $$ = new fir::body_node(LINE, nullptr, $1 , nullptr); }
         ;

while:      tWHILE expression tDO instruction {$$ = new fir::while_node(LINE, $2, $4);}
          | tWHILE expression tDO instruction tFINALLY instruction {$$ = new fir::while_node(LINE, $2, $4, $6);}
          ;

return          : tRETURN              { $$ = new fir::return_node(LINE); }
                ;

instructions    : instruction                { $$ = new cdk::sequence_node(LINE, $1);   }
                | instructions instruction   { $$ = new cdk::sequence_node(LINE, $2, $1); }
                ;

opt_instructions: /* empty */  { $$ = new cdk::sequence_node(LINE); }
                | instructions { $$ = $1; }
                ;

instruction     : tIF expression tTHEN instruction                                          { $$ = new fir::if_node(LINE, $2, $4); }
                | tIF expression tTHEN instruction tELSE instruction                        { $$ = new fir::if_else_node(LINE, $2, $4, $6); }
                | expression ';'                                                            { $$ = new fir::evaluation_node(LINE, $1); }
                | while                                                                     { $$ = $1; }
                | tWRITE   expressions ';'                                                  { $$ = new fir::write_node(LINE, $2, false); }
                | tWRITELN expressions  ';'                                                { $$ = new fir::write_node(LINE, $2, true);  }
                | tLEAVE  tINTEGER ';'                                                         { $$ = new fir::leave_node(LINE, new cdk::integer_node(LINE, $2));  }
                | tRESTART  tINTEGER  ';'                                                      { $$ = new fir::restart_node(LINE, new cdk::integer_node(LINE, $2)); }
                | tLEAVE  ';'                                                               { $$ = new fir::leave_node(LINE, nullptr);  }
                | tRESTART  ';'                                                             { $$ = new fir::restart_node(LINE, nullptr); }
                | return                                                                    { $$ = $1; }
                | block                                                                     { $$ = $1; }
                ;

lvalue          : tID                                            { $$ = new cdk::variable_node(LINE, *$1); delete $1; }
                | lvalue             '[' expression ']'          { $$ = new fir::index_node(LINE, new cdk::rvalue_node(LINE, $1), $3); }
                | '(' expression ')' '[' expression ']'          { $$ = new fir::index_node(LINE, $2, $5); }
                | tID '(' opt_expressions ')' '[' expression ']' { $$ = new fir::index_node(LINE, new fir::function_call_node(LINE, *$1, $3), $6); }
                ;

expression      : integer                       { $$ = $1;}
                | real                          { $$ = $1; }
                | string                        { $$ = new cdk::string_node(LINE, $1); }
                | tNULLPTR                      { $$ = new fir::null_node(LINE); }
                /* LEFT VALUES */
                | lvalue                        { $$ = new cdk::rvalue_node(LINE, $1); }
                /* ASSIGNMENTS */
                | lvalue '=' expression         { $$ = new cdk::assignment_node(LINE, $1, $3); }
                /* ARITHMETIC EXPRESSIONS */
                | expression '+' expression    { $$ = new cdk::add_node(LINE, $1, $3);}
                | expression '-' expression    { $$ = new cdk::sub_node(LINE, $1, $3); }
                | expression '*' expression    { $$ = new cdk::mul_node(LINE, $1, $3);  }
                | expression '/' expression    { $$ = new cdk::div_node(LINE, $1, $3); }
                | expression '%' expression    { $$ = new cdk::mod_node(LINE, $1, $3); }
                /* LOGICAL EXPRESSIONS */
                | expression  '<' expression    { $$ = new cdk::lt_node(LINE, $1, $3); }
                | expression tLE  expression    { $$ = new cdk::le_node(LINE, $1, $3); }
                | expression tEQ  expression    { $$ = new cdk::eq_node(LINE, $1, $3); }
                | expression tGE  expression    { $$ = new cdk::ge_node(LINE, $1, $3); }
                | expression  '>' expression    { $$ = new cdk::gt_node(LINE, $1, $3); }
                | expression tNE  expression    { $$ = new cdk::ne_node(LINE, $1, $3); }
                /* LOGICAL EXPRESSIONS */
                | expression tAND  expression    { $$ = new cdk::and_node(LINE, $1, $3); }
                | expression tOR   expression    { $$ = new cdk::or_node (LINE, $1, $3); }
                /* UNARY EXPRESSION */
                | '-' expression %prec tUMINUS  { $$ = new cdk::neg_node(LINE, $2); }
                | '+' expression %prec tUMINUS  { $$ = $2; }
                | '~' expression                { $$ = new cdk::not_node(LINE, $2); }
                /* OTHER EXPRESSION */
                | tINPUT                        { $$ = new fir::read_node(LINE); }
                /* OTHER EXPRESSION */
                | tID '(' opt_expressions ')'   { $$ = new fir::function_call_node(LINE, *$1, $3); delete $1; }
                /* OTHER EXPRESSION */
                | '(' expression ')'            { $$ = $2; }
                | '[' expression ']'            { $$ = new fir::stack_alloc_node(LINE, $2); }
                | lvalue '?'                    { $$ = new fir::address_of_node(LINE, $1); }
                | tAT                           {$$ = new fir::read_node(LINE);}
                ;

expressions     : expression                     { $$ = new cdk::sequence_node(LINE, $1); }
                | expressions ',' expression     { $$ = new cdk::sequence_node(LINE, $3, $1); }
                ;

opt_expressions : /* empty */         { $$ = new cdk::sequence_node(LINE); }
                | expressions         { $$ = $1; }
                ;

integer         : tINTEGER                      { $$ = new cdk::integer_node(LINE, $1); };
real            : tREAL                         { $$ = new cdk::double_node(LINE, $1); };
string          : tSTRING                       { $$ = $1; }
                | string tSTRING                { $$ = $1; $$->append(*$2); delete $2; }
                ;

%%
