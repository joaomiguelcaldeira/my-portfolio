#ifndef __FIR_AST_LEAVE_NODE_H__
#define __FIR_AST_LEAVE_NODE_H__

#include <cdk/ast/integer_node.h>

namespace fir {

  /**
   * Class for describing leave nodes.
   */
  class leave_node: public cdk::basic_node {
    cdk::integer_node *_argument;

  public:
    inline leave_node(int lineno, cdk::integer_node *argument) :
        cdk::basic_node(lineno), _argument(argument) {
    }

  public:
    inline cdk::integer_node *argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_leave_node(this, level);
    }

  };

} // fir

#endif
