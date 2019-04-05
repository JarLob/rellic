/*
 * Copyright (c) 2019 Trail of Bits, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "rellic/AST/Compat/Expr.h"
#include "rellic/BC/Version.h"

namespace rellic {

clang::UnaryOperator *CreateUnaryOperator(clang::ASTContext &ast_ctx,
                                          clang::UnaryOperatorKind opc,
                                          clang::Expr *op,
                                          clang::QualType res_type) {
#if LLVM_VERSION_NUMBER >= LLVM_VERSION(7, 0)
  return new (ast_ctx)
      clang::UnaryOperator(op, opc, res_type, clang::VK_RValue,
                           clang::OK_Ordinary, clang::SourceLocation(), false);
#else
  return new (ast_ctx)
      clang::UnaryOperator(op, opc, res_type, clang::VK_RValue,
                           clang::OK_Ordinary, clang::SourceLocation());
#endif
}

clang::BinaryOperator *CreateBinaryOperator(clang::ASTContext &ast_ctx,
                                            clang::BinaryOperatorKind opc,
                                            clang::Expr *lhs, clang::Expr *rhs,
                                            clang::QualType res_type) {
#if LLVM_VERSION_NUMBER >= LLVM_VERSION(5, 0)
  return new (ast_ctx) clang::BinaryOperator(
      lhs, rhs, opc, res_type, clang::VK_RValue, clang::OK_Ordinary,
      clang::SourceLocation(), clang::FPOptions());
#else
  return new (ast_ctx)
      clang::BinaryOperator(lhs, rhs, opc, res_type, clang::VK_RValue,
                            clang::OK_Ordinary, clang::SourceLocation(),
                            /*fpContractable=*/false);
#endif
}

clang::IfStmt *CreateIfStmt(clang::ASTContext &ctx, clang::Expr *cond,
                            clang::Stmt *then) {
#if LLVM_VERSION_NUMBER >= LLVM_VERSION(8, 0)
  return clang::IfStmt::Create(ctx, clang::SourceLocation(),
                               /* IsConstexpr=*/false,
                               /* init=*/nullptr,
                               /* var=*/nullptr, cond, then);
#else
  return new (ctx)
      clang::IfStmt(ctx, clang::SourceLocation(), /* IsConstexpr=*/false,
                    /* init=*/nullptr,
                    /* var=*/nullptr, cond, then);
#endif
}

clang::WhileStmt *CreateWhileStmt(clang::ASTContext &ctx, clang::Expr *cond,
                                  clang::Stmt *body) {
#if LLVM_VERSION_NUMBER >= LLVM_VERSION(8, 0)
  return clang::WhileStmt::Create(ctx, nullptr, cond, body,
                                  clang::SourceLocation());
#else
  return new (ctx)
      clang::WhileStmt(ctx, nullptr, cond, body, clang::SourceLocation());
#endif
}

clang::ReturnStmt *CreateReturnStmt(clang::ASTContext &ctx, clang::Expr *expr) {
#if LLVM_VERSION_NUMBER >= LLVM_VERSION(8, 0)
  return clang::ReturnStmt::Create(ctx, clang::SourceLocation(), expr, nullptr);
#else
  return new (ctx) clang::ReturnStmt(clang::SourceLocation(), expr, nullptr);
#endif
}

clang::CompoundStmt *CreateCompoundStmt(clang::ASTContext &ctx,
                                        std::vector<clang::Stmt *> &stmts) {
#if LLVM_VERSION_NUMBER >= LLVM_VERSION(6, 0)
  return clang::CompoundStmt::Create(ctx, stmts, clang::SourceLocation(),
                                     clang::SourceLocation());
#else
  return new (ctx) clang::CompoundStmt(ctx, stmts, clang::SourceLocation(),
                                       clang::SourceLocation());
#endif
}

clang::Expr *CreateCallExpr(clang::ASTContext &ctx, clang::Expr *func,
                            std::vector<clang::Expr *> &args,
                            clang::QualType res_type) {
#if LLVM_VERSION_NUMBER >= LLVM_VERSION(8, 0)
  return clang::CallExpr::Create(ctx, func, args, res_type, clang::VK_RValue,
                                 clang::SourceLocation());
#else
  return new (ctx) clang::CallExpr(ctx, func, args, res_type, clang::VK_RValue,
                                   clang::SourceLocation());
#endif
}

}  // namespace rellic