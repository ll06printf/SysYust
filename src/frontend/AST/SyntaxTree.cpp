//
// Created by LL06p on 24-7-5.
//

#include "utility/Logger.h"

#include "AST/SyntaxTree.h"

namespace SysYust::AST {
    std::size_t SyntaxTree::pushNode() {
        return pushNode(nullptr);
    }

    std::size_t SyntaxTree::pushNode(Node *node) {
        auto rt = _all_nodes.size();
        _all_nodes.push_back(node);
        return rt;
    }

    void SyntaxTree::setNode(std::size_t no, Node *node) {
        if (!_all_nodes[no]) {
            _all_nodes[no] = node;
        } else {
            LOG_WARN("Set Node for a non-nullptr node");
        }
    }

    std::shared_ptr<Env> SyntaxTree::pushEnv() {
        auto newEnv = std::make_shared<Env>(_current_top_env);
        _current_top_env = newEnv;
        return newEnv;
    }

    std::shared_ptr<Env> SyntaxTree::popEnv() {
        auto newEvn = _current_top_env->getParent();
        _current_top_env = newEvn;
        return newEvn;
    }

    std::shared_ptr<Env> SyntaxTree::topEnv() {
        return _current_top_env;
    }

    std::shared_ptr<Env> SyntaxTree::seekEnv(Node *n) {
        return _env_map.at(n);
    }

    void SyntaxTree::setupEnv(Node *n, std::shared_ptr<Env> env) {
        _env_map[n] = std::move(env);
    }

    void SyntaxTree::release() {
        for (auto node : _all_nodes) {
            delete node;
        }
        reset();
    }

    void SyntaxTree::reset() {
        _all_nodes = {};
        _current_top_env = _root_env = std::make_shared<Env>();
        _env_map = {};
    }

    template<std::derived_from<Node> NT>
    NT* SyntaxTree::getNode(std::size_t no) {
        return static_cast<NT*>(_all_nodes[no]);
    }
} // AST