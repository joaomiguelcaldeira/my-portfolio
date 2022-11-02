#ifndef __FIR_AST_FUNCTION_DEFINITION_H__
#define __FIR_AST_FUNCTION_DEFINITION_H__

#include <string>
#include <cdk/ast/typed_node.h>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include "ast/block_node.h"
#include "ast/body_node.h"


namespace fir {

  //!
  //! Class for describing function definitions.
  //! <pre>
  //! declaration: type qualifier id '(' args ')' block
  //!            {
  //!              $$ = new fir::function_definition(LINE, $1, $2, $3, $5, $7);
  //!            }
  //! </pre>
  //!
  class function_definition_node: public cdk::typed_node {
    int _qualifier;
    std::string _identifier;
    cdk::sequence_node *_arguments;
    fir::body_node *_body;
    cdk::expression_node *_default_ret_val;


  public:
    function_definition_node(int lineno, int qualifier, const std::string &identifier, cdk::sequence_node *arguments,
                             fir::body_node *body, cdk::expression_node *default_ret_val) :
        cdk::typed_node(lineno), _qualifier(qualifier), _identifier(identifier), _arguments(arguments), _body(body),
        _default_ret_val(default_ret_val)  {
      type(cdk::primitive_type::create(0, cdk::TYPE_VOID));
    }

        function_definition_node(int lineno, int qualifier, const std::string &identifier, cdk::sequence_node *arguments,
                             fir::body_node *body, cdk::expression_node *default_ret_val, std::shared_ptr<cdk::basic_type> funType) :
        cdk::typed_node(lineno), _qualifier(qualifier), _identifier(identifier), _arguments(arguments), _body(body),
        _default_ret_val(default_ret_val)  {
      type(funType);
    }


  public:
    int qualifier() {
      return _qualifier;
    }
    const std::string& identifier() const {
      return _identifier;
    }
    cdk::sequence_node* arguments() {
      return _arguments;
    }
    cdk::typed_node* argument(size_t ax) {
      return dynamic_cast<cdk::typed_node*>(_arguments->node(ax));
    }
    fir::body_node* body() {
      return _body;
    }
    cdk::expression_node* default_ret_val() {
      return _default_ret_val;
    }

    void identifier(std::string identifier){
      _identifier = identifier;
    }


    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_definition_node(this, level);
    }

  };

}

#endif
