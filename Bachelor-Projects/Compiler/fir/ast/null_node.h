#ifndef __FIR_AST_NULL_H__
#define __FIR_AST_NULL_H__

#include <cdk/ast/expression_node.h>

namespace fir {

  class null_node: public cdk::expression_node {
  public:
    null_node(int lineno) :
        cdk::expression_node(lineno) {
    }

  public:
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_null_node(this, level);
    }

  };

}

#endif
