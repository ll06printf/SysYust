//
// Created by LL06p on 24-7-5.
//

#ifndef SYSYUST_AST_IF_H
#define SYSYUST_AST_IF_H

#include <utility>

#include "Stmt.h"

namespace SysYust::AST {

    class If : public Stmt {
    public:
        If(std::size_t cond, std::size_t stmts);
        If(std::size_t cond, HNode stmts, HNode else_stmts);

        void execute(NodeExecutor *e) override;

        std::size_t cond; ///< 指向的节点一定为 CondExpr 的子类的节点
        std::size_t stmts;
        std::size_t else_stmt = -1;
    };

} // AST

#endif //SYSYUST_AST_IF_H
