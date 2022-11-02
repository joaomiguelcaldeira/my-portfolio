#ifndef __FIR_AST_WHILE_NODE_H__
#define __FIR_AST_WHILE_NODE_H__

#include <cdk/ast/expression_node.h>

namespace fir {

  /**
   * Class for describing while-cycle nodes.
   */
  class while_node: public cdk::basic_node {
    cdk::expression_node *_condition;
    cdk::basic_node *_block, *_finally;
    // Finally is optional

  public:
    inline while_node(int lineno, cdk::expression_node *condition, cdk::basic_node *block) :
        basic_node(lineno), _condition(condition), _block(block) {
        _finally = 0; // null pointer to indicate that it has no finally block
    }

    inline while_node(int lineno, cdk::expression_node *condition, cdk::basic_node *block, cdk::basic_node *finally) :
    basic_node(lineno), _condition(condition), _block(block), _finally(finally) {
    }

  public:
    inline cdk::expression_node *condition() {
      return _condition;
    }
    inline cdk::basic_node *block() {
      return _block;
    }
    inline cdk::basic_node *finally() {
      return _finally;
    }

    inline bool has_finally() { return _finally != 0;}

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_while_node(this, level);
    }

  };

}

#endif
