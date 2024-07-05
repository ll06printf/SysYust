//
// Created by LL06p on 24-7-5.
//

#ifndef SYSYUST_AST_SYNTAXTREE_H
#define SYSYUST_AST_SYNTAXTREE_H

#include <vector>
#include <memory>
#include <concepts>

#include "Env.h"
#include "Node.h"
#include "Type.h"
#include "IdAllocator.h"

namespace SysYust::AST {

    /**
     * @brief 语法树对象，包含了AST的节点结构和符号表等信息
     * @details 使用默认的拷贝控制使得 SyntaxTree 具有引用语义，析构函数不会释放资源，资源由 release 函数释放.
     *
     * 使用这想要完整的访问需要保存语法树对象的引用，当前访问的节点的局部符号表的引用。
     */
    class SyntaxTree {
    public:

        /**
         * @brief 在节点列表末尾添加节点，暂时不指定节点
         * @return 返回该节点的 id
         */
        std::size_t pushNode();
        /**
         * @brief 在节点列表末尾添加节点
         * @param node 添加到末尾的节点
         * @return 返回该节点的 id
         */
        std::size_t pushNode(Node *node);

        /**
         * @brief 设置指定位置的节点，仅当该位置的指针为 nullptr 有效
         */
        void setNode(std::size_t no, Node *node);

        /**
         * @brief 获取指定索引的节点，无条件转换至 NT* 。
         */
        template<std::derived_from<Node> NT = Node>
        NT* getNode(std::size_t no);

        /**
         * @brief 添加一层 Env
         * @return 返回创建的 Env
         */
        std::shared_ptr<Env> pushEnv();
        /**
         * @brief 弹出一层 Env
         * @return 返回当前 Env 的父 Env
         */
        std::shared_ptr<Env> popEnv();
        /**
         * @brief 获取当前的顶层 Env
         */
        std::shared_ptr<Env> topEnv();
        /**
         * @brief 根据 FuncDecl 或 Block 获取对应的 Env
         */
        std::shared_ptr<Env> seekEnv(Node *n);
        /**
         * @brief 为指定节点设置对应的环境
         */
        void setupEnv(Node *n, std::shared_ptr<Env> env);

        /**
         * @brief 释放所有节点, 置该对象为初始状态
         */
        void release();
        /**
         * @brief 将该对象置为初始状态，但是不释放资源
         */
         void reset();
    private:
        std::shared_ptr<Env> _root_env = std::make_shared<Env>();
        std::shared_ptr<Env> _current_top_env = _root_env;
        std::vector<Node*> _all_nodes = {};
        std::unordered_map<Node*, std::shared_ptr<Env>> _env_map = {};
    };

} // AST

#endif //SYSYUST_AST_SYNTAXTREE_H
