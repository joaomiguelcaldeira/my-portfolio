#include <string>
#include "targets/frame_size_calculator.h"
#include "targets/type_checker.h"
#include "targets/symbol.h"
#include "ast/all.h"

fir::frame_size_calculator::~frame_size_calculator() {
  os().flush();
}

void fir::frame_size_calculator::do_add_node(cdk::add_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_and_node(cdk::and_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_assignment_node(cdk::assignment_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_data_node(cdk::data_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_div_node(cdk::div_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_double_node(cdk::double_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_eq_node(cdk::eq_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_ge_node(cdk::ge_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_gt_node(cdk::gt_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_variable_node(cdk::variable_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_integer_node(cdk::integer_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_le_node(cdk::le_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_lt_node(cdk::lt_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_mod_node(cdk::mod_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_mul_node(cdk::mul_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_ne_node(cdk::ne_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_neg_node(cdk::neg_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_nil_node(cdk::nil_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_not_node(cdk::not_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_or_node(cdk::or_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_rvalue_node(cdk::rvalue_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_string_node(cdk::string_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_sub_node(cdk::sub_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_evaluation_node(fir::evaluation_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_write_node(fir::write_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_read_node(fir::read_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_address_of_node(fir::address_of_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_function_call_node(fir::function_call_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_function_declaration_node(fir::function_declaration_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_index_node(fir::index_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_restart_node(fir::restart_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_null_node(fir::null_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_return_node(fir::return_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_stack_alloc_node(fir::stack_alloc_node *const node, int lvl) {
  // EMPTY
}
void fir::frame_size_calculator::do_leave_node(fir::leave_node *const node, int lvl) {
  // EMPTY
  // TODO implement
}

void fir::frame_size_calculator::do_sequence_node(cdk::sequence_node *const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    cdk::basic_node *n = node->node(i);
    if (n == nullptr) break;
    n->accept(this, lvl + 2);
  }
}

void fir::frame_size_calculator::do_block_node(fir::block_node *const node, int lvl) {
  if (node->declarations()) node->declarations()->accept(this, lvl + 2);
  if (node->instructions()) node->instructions()->accept(this, lvl + 2);
}


void fir::frame_size_calculator::do_if_node(fir::if_node *const node, int lvl) {
  node->block()->accept(this, lvl + 2);
}

void fir::frame_size_calculator::do_if_else_node(fir::if_else_node *const node, int lvl) {
  node->thenblock()->accept(this, lvl + 2);
  if (node->elseblock()) node->elseblock()->accept(this, lvl + 2);
}

void fir::frame_size_calculator::do_variable_declaration_node(fir::variable_declaration_node *const node, int lvl) {
  _localsize += node->type()->size();
}

void fir::frame_size_calculator::do_identity_node(fir::identity_node *const node, int lvl) {
//   _localsize += node->type()->size();
// TODO think about this
}

void fir::frame_size_calculator::do_function_definition_node(fir::function_definition_node *const node, int lvl) {
    _localsize += node->type()->size();
    node->body()->accept(this, lvl + 2);
  // TODO is this ok?
}

void fir::frame_size_calculator::do_while_node(fir::while_node *const node, int lvl) {
  node->condition()->accept(this, lvl + 2);
  node->block()->accept(this, lvl + 2);
  if(node->finally())
    node->finally()->accept(this, lvl + 2);
  // TODO is this ok?
}


void fir::frame_size_calculator::do_body_node(fir::body_node *const node, int lvl) {
  if(node->prologue())
      node->prologue()->accept(this, lvl + 2);
  if(node->main_block())
    node->main_block()->accept(this, lvl + 2);
  if(node->epilogue())
    node->epilogue()->accept(this, lvl + 2);
}



void fir::frame_size_calculator::do_sizeof_node(fir::sizeof_node *const node, int lvl) {
  // EMPTY
}