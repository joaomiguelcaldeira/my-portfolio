#ifndef __FIRSCANNER_H__
#define __FIRSCANNER_H__

#undef yyFlexLexer
#define yyFlexLexer fir_scanner_FlexLexer
#include <FlexLexer.h>

typedef fir_scanner_FlexLexer fir_scanner;

#endif
