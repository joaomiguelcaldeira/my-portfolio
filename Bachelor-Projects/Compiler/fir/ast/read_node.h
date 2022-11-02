#ifndef __FIR_AST_READ_NODE_H__
#define __FIR_AST_READ_NODE_H__

#include <cdk/ast/expression_node.h>

namespace fir {

  /**
   * Class for describing read nodes.
   */
  class read_node: public cdk::expression_node {

  public:
    inline read_node(int lineno) :
        cdk::expression_node(lineno) {
    }

  public:

    void accept(basic_ast_visitor *sp, int level) { 
      sp->do_read_node(this, level);
    }

  };

} // fir

#endif
