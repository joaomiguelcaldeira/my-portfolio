#ifndef __FIR_AST_BLOCK_NODE_H__
#define __FIR_AST_BLOCK_NODE_H__

#include <cdk/ast/sequence_node.h>

namespace fir {

  /**
   * Class for describing block nodes.
   */
  class block_node: public cdk::basic_node {
    cdk::sequence_node *_declarations, *_instructions;
    bool _is_prologue, _is_epilogue;

  public:
    inline block_node(int lineno, cdk::sequence_node *declarations, cdk::sequence_node *instructions, bool is_prologue, bool is_epilogue) :
        cdk::basic_node(lineno), _declarations(declarations),
        _instructions(instructions), _is_prologue(is_prologue),
         _is_epilogue(is_epilogue) {
    }

  public:
    inline cdk::sequence_node *declarations() {
      return _declarations;
    }

    inline cdk::sequence_node *instructions() {
      return _instructions;
    }

    inline bool is_prologue() {
      return _is_prologue;
    }

    inline bool is_epilogue() {
      return _is_epilogue;
    }

    inline void set_is_epilogue(bool is_epilogue) {
      _is_epilogue = is_epilogue;
    }

    inline void set_is_prologue(bool is_prologue) {
      _is_prologue = is_prologue;
    }


    void accept(basic_ast_visitor *sp, int level) {
      sp->do_block_node(this, level);
    }

  };

} // fir

#endif
