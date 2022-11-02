#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "ast/all.h"  // all.h is automatically generated

//---------------------------------------------------------------------------

void fir::postfix_writer::do_nil_node(cdk::nil_node * const node, int lvl) {
  // EMPTY
}
void fir::postfix_writer::do_data_node(cdk::data_node * const node, int lvl) {
  // EMPTY
}
void fir::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
  if (_inFunctionBody) {
    _pf.DOUBLE(node->value()); // integer literal is on the stack: push an integer
  } else {
    _pf.SDOUBLE(node->value()); // integer literal is on the DATA segment
  }
}
void fir::postfix_writer::do_not_node(cdk::not_node * const node, int lvl) {
   ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl + 2);
  _pf.INT(0);
  _pf.EQ();
  //_pf.NOT();
}
void fir::postfix_writer::do_and_node(cdk::and_node * const node, int lvl) {

  ASSERT_SAFE_EXPRESSIONS;
  int lbl = ++_lbl;
  node->left()->accept(this, lvl + 2);
  _pf.DUP32();
  _pf.JZ(mklbl(lbl));
  node->right()->accept(this, lvl + 2);
  _pf.AND();
  _pf.ALIGN();
  _pf.LABEL(mklbl(lbl));

}
void fir::postfix_writer::do_or_node(cdk::or_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl = ++_lbl;
  node->left()->accept(this, lvl + 2);
  _pf.DUP32();
  _pf.JNZ(mklbl(lbl));
  node->right()->accept(this, lvl + 2);
  _pf.OR();
  _pf.ALIGN();
  _pf.LABEL(mklbl(lbl));
}

//---------------------------------------------------------------------------

void fir::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------

void fir::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  if (_inFunctionBody) {
    _pf.INT(node->value()); // integer literal is on the stack: push an integer
  } else {
    _pf.SINT(node->value()); // integer literal is on the DATA segment
  }
}

void fir::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
  int lbl1;
  /* generate the string literal */
  _pf.RODATA(); // strings are readonly DATA
  _pf.ALIGN(); // make sure the address is aligned
  _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
  _pf.SSTRING(node->value()); // output string characters
  if (_function) {
    // local variable initializer
    _pf.TEXT();
    _pf.ADDR(mklbl(lbl1));
  } else {
    // global variable initializer
    _pf.DATA();
    _pf.SADDR(mklbl(lbl1));
  }
}

//---------------------------------------------------------------------------

void fir::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  _pf.NEG(); // 2-complement
}

//---------------------------------------------------------------------------

void fir::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  if(node->type()->name() == cdk::TYPE_DOUBLE && node->left()->type()->name() == cdk::TYPE_INT) {
    _pf.I2D();
  }
  else if(node->type()->name() == cdk::TYPE_POINTER && node->left()->type()->name() == cdk::TYPE_INT) {
    if(cdk::reference_type::cast(node->type())->referenced()->name() == cdk::TYPE_DOUBLE) {
      _pf.INT(3);
    }
    else {
      _pf.INT(2);
    }
    _pf.SHTL();
  }

  node->right()->accept(this, lvl);
  if(node->type()->name() == cdk::TYPE_DOUBLE && node->right()->type()->name() == cdk::TYPE_INT) {
    _pf.I2D();
  } else if(node->type()->name() == cdk::TYPE_POINTER && node->right()->type()->name() == cdk::TYPE_INT) {
    if(cdk::reference_type::cast(node->type())->referenced()->name() == cdk::TYPE_DOUBLE) {
      _pf.INT(3);
    }
    else {
      _pf.INT(2);
    }
    _pf.SHTL();
  }

  if(node->type()->name() == cdk::TYPE_DOUBLE) {
    _pf.DADD();
  }
  else {
    _pf.ADD();
  }
}
void fir::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  if(node->type()->name() == cdk::TYPE_DOUBLE && node->left()->type()->name() == cdk::TYPE_INT) {
    _pf.I2D();
  }

  //not supposed to have INT - POINTER
  node->right()->accept(this, lvl);
  if(node->type()->name() == cdk::TYPE_DOUBLE && node->right()->type()->name() == cdk::TYPE_INT) {
    _pf.I2D();
  }
  else if(node->type()->name() == cdk::TYPE_POINTER && node->right()->type()->name() == cdk::TYPE_INT) {
    if(cdk::reference_type::cast(node->type())->referenced()->name() == cdk::TYPE_DOUBLE) {
      _pf.INT(3);
    }
    else {
      _pf.INT(2);
    }
    _pf.SHTL();
  }
  
  else { //subtração entre números
    if(node->type()->name() == cdk::TYPE_DOUBLE) {
      _pf.DSUB();
    }
    else {
      _pf.SUB();
    }
  }
}
void fir::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  if(node->type()->name() == cdk::TYPE_DOUBLE && node->left()->type()->name() == cdk::TYPE_INT) {
    _pf.I2D();
  }

  node->right()->accept(this, lvl);
  if(node->type()->name() == cdk::TYPE_DOUBLE && node->right()->type()->name() == cdk::TYPE_INT) {
    _pf.I2D();
  }

  if(node->type()->name() == cdk::TYPE_DOUBLE) {
    _pf.DMUL();
  }
  else {
    _pf.MUL();
  }
}
void fir::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  if(node->type()->name() == cdk::TYPE_DOUBLE && node->left()->type()->name() == cdk::TYPE_INT) {
    _pf.I2D();
  }

  node->right()->accept(this, lvl);
  if(node->type()->name() == cdk::TYPE_DOUBLE && node->right()->type()->name() == cdk::TYPE_INT) {
    _pf.I2D();
  }

  if(node->type()->name() == cdk::TYPE_DOUBLE) {
    _pf.DDIV();
  }
  else {
    _pf.DIV();
  }
}
void fir::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}
void fir::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LT();
}
void fir::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LE();
}
void fir::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GE();
}
void fir::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GT();
}
void fir::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.NE();
}
void fir::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.EQ();
}

//---------------------------------------------------------------------------

void fir::postfix_writer::do_variable_node(cdk::variable_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  if(_inFunctionBody){
    if(_function->name() == node->name()){
      _pf.LOCAL(_returnOffset);
      _inFunctionName = true;
    }
    else{
      std::shared_ptr<fir::symbol> p = _symtab.find(node->name());
      _inFunctionName = false;
      if(p->offset() == 0) 
        _pf.ADDR(p->name());
      else 
        _pf.LOCAL(p->offset());
    }
  }
  else
    _pf.ADDR(node->name()); 
}

void fir::postfix_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->lvalue()->accept(this, lvl);
  if (node->type()->name() == cdk::TYPE_DOUBLE) {
    _pf.LDDOUBLE();
  } else {
    // integers, pointers, and strings
    _pf.LDINT();
  }
}

void fir::postfix_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->rvalue()->accept(this, lvl + 2);
  if (node->type()->name() == cdk::TYPE_DOUBLE) {
    if (node->rvalue()->type()->name() == cdk::TYPE_INT) _pf.I2D();
    _pf.DUP64();
  } else {
    _pf.DUP32();
  }

  node->lvalue()->accept(this, lvl);
  if (node->type()->name() == cdk::TYPE_DOUBLE) {
    _pf.STDOUBLE();
  } else if(node->type()->name() == cdk::TYPE_STRING){
    _pf.STFVAL32();
  }else{
    _pf.STINT();
  }

  if(_inFunctionName) { //if the assignment was the return var, we warn the function definition
    returnValueSet = true;
  }

}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void fir::postfix_writer::do_evaluation_node(fir::evaluation_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl);
  _pf.TRASH(node->argument()->type()->size());
}

//---------------------------------------------------------------------------

void fir::postfix_writer::do_read_node(fir::read_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  _pf.CALL("readi");
  _pf.LDFVAL32();
  // node->argument()->accept(this, lvl); // TODO FIXME
  _pf.STINT();
}

//---------------------------------------------------------------------------

void fir::postfix_writer::do_while_node(fir::while_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  _whileIni.push(++_lbl);
  _whileStep.push(++_lbl);
  _whileEnd.push(++_lbl);
  _InWhileInit = true;

  _pf.ALIGN();
  _pf.LABEL(mklbl(_whileIni.top()));
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(_whileEnd.top()));
  _pf.ALIGN();
  _pf.LABEL(mklbl(_whileStep.top()));
  node->block()->accept(this, lvl + 2);
  _pf.ALIGN();
  _pf.JMP(mklbl(_whileIni.top()));
  _pf.LABEL(mklbl(_whileEnd.top()));

  _InWhileInit = false;
  _whileIni.pop();
  _whileStep.pop();
  _whileEnd.pop();
}

//---------------------------------------------------------------------------

void fir::postfix_writer::do_if_node(fir::if_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void fir::postfix_writer::do_if_else_node(fir::if_else_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1 = lbl2));
}
void fir::postfix_writer::do_block_node(fir::block_node * const node, int lvl) {
  

  // ja fazemos um nivel mais a cima
  // if (node->is_prologue())  _symtab.push(); // for block-local vars
  if (node->declarations()) {
    node->declarations()->accept(this, lvl + 2);}
  if (node->instructions()) {
    
    node->instructions()->accept(this, lvl + 2);}
  // if (node->is_prologue())  _symtab.pop();
}

void fir::postfix_writer::do_leave_node(fir::leave_node * const node, int lvl) {
  int el;
  int node_val = node->argument() == nullptr ? 1 : node->argument()->value();
  if(_InWhileInit){

    for(int i = 1; i < node_val; i++){
      if(_whileEnd.empty())
        error(node->lineno(), "leave argument overflow");
      el = _whileEnd.top();
      buff.push(el);
      _whileEnd.pop();
    }
    _pf.JMP(mklbl(_whileEnd.top()));

    int size = buff.size();
    for(el = 0; el < size; el++){
      _whileEnd.push(buff.top());
      buff.pop();
    }
  }
  else
    error(node->lineno(), "leave outside the while");
}

void fir::postfix_writer::do_restart_node(fir::restart_node * const node, int lvl) {
  int el;
  int node_val = node->argument() == nullptr ? 1 : node->argument()->value();
  if(_InWhileInit){
    for(int i = 1; i < node_val; i++){
      if(_whileStep.empty())
        error(node->lineno(), "leave argument overflow");
      el = _whileStep.top();
      buff.push(el);
      _whileStep.pop();
    }
    _pf.JMP(mklbl(_whileStep.top()));

    int size = buff.size();
    for(el = 0; el < size; el++){
      _whileStep.push(buff.top());
      buff.pop();
    }
  }
  else
    error(node -> lineno(), "leave outside the while");

}

//prob has problems
void fir::postfix_writer::do_return_node(fir::return_node * const node, int lvl) {
   ASSERT_SAFE_EXPRESSIONS;
  if(_inFunctionEpilogue) { //otherwise we'd just go to the beginning of the final section
    _pf.JMP(mklbl(returnFunctionLbl));
  }
  else if(hasEpilogue){
    _pf.JMP(mklbl(finalFunctionLbl));
  }
  else
    _pf.JMP(mklbl(returnFunctionLbl));
}

void fir::postfix_writer::do_sizeof_node(fir::sizeof_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  _pf.INT(node->argument()->type()->size());
}

void fir::postfix_writer::do_variable_declaration_node(fir::variable_declaration_node * const node, int lvl) {

  //NEW CODE COPIED from OG
  ASSERT_SAFE_EXPRESSIONS;

  auto id = node->identifier();

  //TODO UNCOMMENT ME

  //std::cout << "INITIAL OFFSET: " << _offset << std::endl;

  // type size?
  int offset = 0, typesize = node->type()->size(); // in bytes
  if (_inFunctionBody) {
    _offset -= typesize;
    offset = _offset;
  } else if (_inFunctionArgs) {
    offset = _offset;
    _offset += typesize;
  } else {
    offset = 0; // global variable
  }

  auto symbol = new_symbol();
  if (symbol) {
    symbol->set_offset(offset);
    reset_new_symbol();
  }

  if (_inFunctionBody) {
    // if we are dealing with local variables, then no action is needed
    // unless an initializer exists
    if (node->initializer()) {
      node->initializer()->accept(this, lvl);
      if (node->is_typed(cdk::TYPE_INT) || node->is_typed(cdk::TYPE_STRING) || node->is_typed(cdk::TYPE_POINTER)) {
        _pf.LOCAL(symbol->offset());
        _pf.STINT();
      } else if (node->is_typed(cdk::TYPE_DOUBLE)) {
        if (node->initializer()->is_typed(cdk::TYPE_INT))
          _pf.I2D();
        _pf.LOCAL(symbol->offset());
        _pf.STDOUBLE();
      } else {
        std::cerr << "cannot initialize" << std::endl;
      }
    }
  } else {
    if (!_function) {
      if (node->initializer() == nullptr) {
        _pf.BSS();
        _pf.ALIGN();
        _pf.LABEL(id);
        _pf.SALLOC(typesize);
      } else {

        if (node->is_typed(cdk::TYPE_INT) || node->is_typed(cdk::TYPE_DOUBLE) || node->is_typed(cdk::TYPE_POINTER)) {
          if (node->constant()) {
            _pf.RODATA();
          } else {
            _pf.DATA();
          }
          _pf.ALIGN();
          _pf.LABEL(id);

          if (node->is_typed(cdk::TYPE_INT)) {
            
            node->initializer()->accept(this, lvl);
          } else if (node->is_typed(cdk::TYPE_POINTER)) {
            node->initializer()->accept(this, lvl);
          } else if (node->is_typed(cdk::TYPE_DOUBLE)) {
            if (node->initializer()->is_typed(cdk::TYPE_DOUBLE)) {
              node->initializer()->accept(this, lvl);
            } else if (node->initializer()->is_typed(cdk::TYPE_INT)) {
              cdk::integer_node *dclini = dynamic_cast<cdk::integer_node*>(node->initializer());
              cdk::double_node ddi(dclini->lineno(), dclini->value());
              ddi.accept(this, lvl);
            } else {
              std::cerr << node->lineno() << ": '" << id << "' has bad initializer for real value\n";
              _errors = true;
            }
          }
        } else if (node->is_typed(cdk::TYPE_STRING)) {
          if (node->constant()) {
            int litlbl;
            // HACK!!! string literal initializers must be emitted before the string identifier
            _pf.RODATA();
            _pf.ALIGN();
            _pf.LABEL(mklbl(litlbl = ++_lbl));
            _pf.SSTRING(dynamic_cast<cdk::string_node*>(node->initializer())->value());
            _pf.ALIGN();
            _pf.LABEL(id);
            _pf.SADDR(mklbl(litlbl));
          } else {
            _pf.DATA();
            _pf.ALIGN();
            _pf.LABEL(id);
            node->initializer()->accept(this, lvl);
          }
        } else {
          std::cerr << node->lineno() << ": '" << id << "' has unexpected initializer\n";
          _errors = true;
        }

      }

    }
  }
}

void fir::postfix_writer::do_write_node(fir::write_node * const node, int lvl) {
 ASSERT_SAFE_EXPRESSIONS;


  for (size_t ix = 0; ix < node->argument()->size(); ix++) {
    auto child = dynamic_cast<cdk::expression_node*>(node->argument()->node(ix));

    std::shared_ptr<cdk::basic_type> etype = child->type();
    child->accept(this, lvl); // expression to print

    if (etype->name() == cdk::TYPE_INT) {
      _functions_to_declare.insert("printi");
      _pf.CALL("printi");
      _pf.TRASH(4); // trash int
    } else if (etype->name() == cdk::TYPE_DOUBLE) {
      _functions_to_declare.insert("printd");
      _pf.CALL("printd");
      _pf.TRASH(8); // trash double
    } else if (etype->name() == cdk::TYPE_STRING) {
      _functions_to_declare.insert("prints");
      _pf.CALL("prints");
      _pf.TRASH(4); // trash char pointer
    } else {
      std::cerr << "cannot print expression of unknown type" << std::endl;
      return;
    }

  }
  if (node->is_writeln()) {
    _functions_to_declare.insert("println");
    _pf.CALL("println");
  }
}
//------------------------------

void fir::postfix_writer::do_address_of_node(fir::address_of_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  // since the argument is an lvalue, it is already an address
  node->lvalue()->accept(this, lvl + 2);
}

void fir::postfix_writer::do_function_call_node(fir::function_call_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  auto symbol = _symtab.find(node->identifier());

  size_t argsSize = 0;
  if (node->arguments()->size() > 0) {
    for (int ax = node->arguments()->size() - 1; ax >= 0; ax--) {
      cdk::expression_node *arg = dynamic_cast<cdk::expression_node*>(node->arguments()->node(ax));
      arg->accept(this, lvl + 2);
      if (symbol->argument_is_typed(ax, cdk::TYPE_DOUBLE) && arg->is_typed(cdk::TYPE_INT)) {
        _pf.I2D();
      }
      argsSize += symbol->argument_size(ax);
    }
  }
  _pf.CALL(node->identifier());
  if (argsSize != 0) {
    _pf.TRASH(argsSize);
  }

  if (symbol->is_typed(cdk::TYPE_INT) || symbol->is_typed(cdk::TYPE_POINTER) || symbol->is_typed(cdk::TYPE_STRING)) {
    _pf.LDFVAL32();
  } else if (symbol->is_typed(cdk::TYPE_DOUBLE)) {
    _pf.LDFVAL64();
  } else {
    // cannot happer!
  }
}
void fir::postfix_writer::do_function_declaration_node(fir::function_declaration_node *const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    if (_inFunctionBody || _inFunctionArgs) {
    error(node->lineno(), "cannot declare function in body or in args");
    return;
  }

  if (!new_symbol()) return;

  auto function = new_symbol();
  _functions_to_declare.insert(function->name());
  reset_new_symbol();
}
void fir::postfix_writer::do_function_definition_node(fir::function_definition_node *const node, int lvl) {

  ASSERT_SAFE_EXPRESSIONS;
  // TODO: Uncomment this after implementing
    if (_inFunctionBody || _inFunctionArgs) {
    error(node->lineno(), "cannot define function in body or in arguments");
    return;
  }


  // remember symbol so that args and body know
  _function = new_symbol();
  // TODO implement this
  _functions_to_declare.erase(_function->name());  // just in case
  reset_new_symbol();

  _currentBodyRetLabel = mklbl(++_lbl);

  _offset = 8; // prepare for arguments (4: remember to account for return address)
  _symtab.push(); // scope of args

  _inFunctionName = false;
  returnValueSet = false;

  if (node->arguments()->size() > 0) {
    _inFunctionArgs = true; //FIXME really needed?
    for (size_t ix = 0; ix < node->arguments()->size(); ix++) {
      cdk::basic_node *arg = node->arguments()->node(ix);
      if (arg == nullptr) break; // this means an empty sequence of arguments
      arg->accept(this, 0); // the function symbol is at the top of the stack
    }
    _inFunctionArgs = false; //FIXME really needed?
  }

  _pf.TEXT();
  _pf.ALIGN();
  if (node->qualifier() == tPUBLIC) {
      _pf.GLOBAL(_function->name(), _pf.FUNC());
  }


  _pf.LABEL(_function->name());

  // compute stack size to be reserved for local variables
  frame_size_calculator lsc(_compiler, _symtab, _function);
  node->accept(&lsc, lvl);
  _pf.ENTER(lsc.localsize()); // total stack size reserve d for local variables

  finalFunctionLbl = ++_lbl;
  returnFunctionLbl = ++_lbl;

  _offset = -node->type()->size(); // prepare for local variable
  _returnOffset = _offset;
  // the following flag is a slight hack: it won't work with nested functions
  _inFunctionBody = true;
  os() << "        ;; before body " << std::endl;
  // TODO, implement prologue and epilogue
  node->body()->accept(this, lvl + 4); // block has its own scope
  os() << "        ;; after body " << std::endl;
  
  _returnSeen = false;

  if(returnValueSet){
    if(node->type()->name() == cdk::TYPE_INT || node->type()->name() == cdk::TYPE_POINTER || 
      node->type()->name() == cdk::TYPE_STRING) {
        _pf.LOCAL(-node->type()->size());
        _pf.LDINT();
        _pf.STFVAL32();
    }
    else if(node->type()->name() == cdk::TYPE_DOUBLE) {
      _pf.LOCAL(-node->type()->size());
      _pf.LDDOUBLE();
      _pf.STFVAL64();
    }
  }
  else if(node->default_ret_val()){
    node->default_ret_val()->accept(this, lvl);
    if(node->type()->name() == cdk::TYPE_INT || node->type()->name() == cdk::TYPE_POINTER || node->type()->name() == cdk::TYPE_STRING)
      _pf.STFVAL32();
    else if(node->type()->name() == cdk::TYPE_DOUBLE){
      //if(node->default_ret_val()->type()->name() == cdk::TYPE_INT)
        _pf.I2D();
      _pf.STFVAL64();
    }
  }else if(node->type()->name() == cdk::TYPE_INT || node->type()->name() == cdk::TYPE_POINTER){
    _pf.INT(0);
    _pf.STFVAL32();
  }
    
  _inFunctionBody = false;
  _pf.LABEL(_currentBodyRetLabel);
  _pf.LEAVE();
  _pf.RET();

  _symtab.pop(); // scope of arguments

  if (node->identifier() == "fir") {
    // declare external functions
    for (std::string s : _functions_to_declare)
      _pf.EXTERN(s);
  }

}
void fir::postfix_writer::do_index_node(fir::index_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->base()->accept(this, lvl);
  node->index()->accept(this, lvl);
  _pf.INT(node->type()->size());
  _pf.MUL();
  _pf.ADD();   //indexation leaves an address on stack
}

void fir::postfix_writer::do_null_node(fir::null_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS; // a pointer is a 32-bit integer
  if (_inFunctionBody) {
    _pf.INT(0);
  } else {
    _pf.SINT(0);
  }
}
void fir::postfix_writer::do_stack_alloc_node(fir::stack_alloc_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); //number of objects to allocate
  if(cdk::reference_type::cast(node->type())->referenced()->name() == cdk::TYPE_DOUBLE) {
    _pf.INT(3);
  }
  else {
    _pf.INT(2);
  }

  _pf.SHTL();
  _pf.ALLOC();    //STACK:  #BYTES (sp) - sp is the end of that allocation
  _pf.SP();
}
void fir::postfix_writer::do_body_node(fir::body_node *const node, int lvl) {
  _inFunctionEpilogue = false;
  hasEpilogue = false;
  if (node->epilogue() != nullptr) hasEpilogue = true;
  if (node->prologue() != nullptr) {node->prologue()->accept(this, lvl + 2);}
  
  _symtab.push(); // for block-local vars
  if (node->main_block() != nullptr) {node->main_block()->accept(this, lvl + 2);}
  _symtab.pop();

  _symtab.push(); // for block-local vars
  if (node->epilogue() != nullptr) {
    _pf.ALIGN();
    _pf.LABEL(mklbl(finalFunctionLbl));
    _inFunctionEpilogue = true;
    node->epilogue()->accept(this, lvl + 2);
    _inFunctionEpilogue = false;
  }
  _symtab.pop();
  _pf.ALIGN();
  _pf.LABEL(mklbl(returnFunctionLbl));
  hasEpilogue = false;
}

void fir::postfix_writer::do_identity_node(fir::identity_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl);
}