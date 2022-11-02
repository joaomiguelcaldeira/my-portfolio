#ifndef __FIR_AST_STACK_ALLOC_NODE_H__
#define __FIR_AST_STACK_ALLOC_NODE_H__

#include <cdk/ast/expression_node.h>

namespace fir {

  class stack_alloc_node: public cdk::expression_node {
    cdk::expression_node *_argument;
  public:
    inline stack_alloc_node(int lineno, cdk::expression_node *argument) :
        cdk::expression_node(lineno), _argument(argument) {
    }

  public:

    cdk::expression_node* argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_stack_alloc_node(this, level);
    }

  };

}

#endif
