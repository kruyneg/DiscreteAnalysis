#include "bin_tree.hpp"
#include <iostream>

template <typename T>
class rb_tree : public bin_tree<T> {
    using typename bin_tree<T>::__node;
public:
    void print(std::ostream& out, __node* cur, int space) {
        if (!cur) {
            return;
        }
        if (cur->right) {
            print(out, cur->right, space + 1);
        }
        int tmp = space;
        while (tmp--) {
            out << '\t';
        }
        // out << "\033[107m";
        if (cur->parent && cur->parent->value > cur->value) {
            out << '\\';
        } else {
            out << '/';
        }
        if (cur->color == red) {
            out << "\033[91m" << cur->value << "\033[39m" << std::endl;
        } else {
            out << "\033[30m" << cur->value << "\033[39m" << std::endl;
        }
        // out << "\033[49m";
        if (cur->left) {
            print(out, cur->left, space + 1);
        }
    }

    using bin_tree<T>::iterator;

    rb_tree() {
        _m_head = nullptr;
        _m_size = 0;
        _m_end_node = new __node(T());
    }
    rb_tree(std::initializer_list<T> l) : bin_tree<T>() {
        for (const T& elem : l) {
            insert(elem);
        }
        _m_size = l.size();
    }
    ~rb_tree() {
        bin_tree<T>::clear();
    }

    void insert(const T& val) override {
        std::cout << "=================================================================" << std::endl;
        print(std::cout, _m_head, 0);
        std::cout << "=================================================================" << std::endl;
        std::cout << "Insert " << val << std::endl;
        __node* parent = bin_tree<T>::__find_parent(_m_head, val);
        if (parent) {
            __node* &target = 
                (val < parent->value) ?
                parent->left :
                parent->right;
            target = new __node(val);
            // if (val < parent->value) {
            //     parent->left = new __node(val);
            //     target = parent->left;
            // } else if (val > parent->value) {
            //     parent->right = new __node(val);
            //     target = parent->right;
            // } else return;
            ++_m_size;
            target->parent = parent;
            target->color = red;
            __node* grandpa = parent->parent;
            if (!grandpa) {
                return;
            }
            __node* uncle = (parent->value < grandpa->value) ? grandpa->right : grandpa->left;
            __insert_balance(target, parent, grandpa, uncle);
        } else {
            _m_head = new __node(val);
            _m_end_node->left = _m_head;
            ++_m_size;
        }
        _m_head->color = black;
        if (_m_size == 1) {
            _m_end_node->left = _m_head;
        }
    }

    void erase(const T& val) {
        std::cout << "=================================================================" << std::endl;
        print(std::cout, _m_head, 0);
        std::cout << "=================================================================" << std::endl;
        std::cout << "Erase " << val << std::endl;
        __node* target = bin_tree<T>::__find(_m_head, val);
        if (target->value != val) {
            return;
        }
        --_m_size;
        __delete_node(target);
        _m_end_node->left = _m_head;
    }

private:
    void __left_rotation(__node* x) {
        __node* y = x->right;
        y->parent = x->parent;
        x->parent = y;
        x->right = y->left;
        if (x->right)
            x->right->parent = x;
        y->left = x;
        if (_m_head == x) {
            _m_head = y;
        }
        if (y->parent) {
            if (y->value < y->parent->value) {
                y->parent->left = y;
            } else {
                y->parent->right = y;
            }
        }
    }
    void __right_rotation(__node* y) {
        __node* x = y->left;
        x->parent = y->parent;
        y->parent = x;
        y->left = x->right;
        if (y->left)
            y->left->parent = y;
        x->right = y;
        if (_m_head == y) {
            _m_head = x;
        }
        if (x->parent) {
            if (x->value < x->parent->value) {
                x->parent->left = x;
            } else {
                x->parent->right = x;
            }
        }

    }
    // void __right_rotation(__node*& y) {
    //     __node* &x = y->left;
    //     x->parent = y->parent;
    //     y->parent = x;
    //     y->left = x->right;
    //     if (y->left)
    //         y->left->parent = y;
    //     x->right = y;
    // }

    void __insert_balance(__node* target, __node* parent, __node* grandpa, __node* uncle) {
        if (parent->color == black) {
            return;
        }
        if (parent == grandpa->left) {
            if (target == parent->right) {
                __left_rotation(parent);
                std::swap(target, parent);
            }
            if (uncle && uncle->color == red) {
                parent->color = black;
                uncle->color = black;
                grandpa->color = red;
                if (grandpa->parent) {
                    __node* ggpa = grandpa->parent;
                    if (ggpa->parent) {
                        __node* gggpa = ggpa->parent;
                        __node* ggpa2 = (ggpa->value < gggpa->value) ? gggpa->right : gggpa->left;
                        __insert_balance(grandpa, ggpa, gggpa, ggpa2);
                    }
                }
            } else {
                __right_rotation(grandpa);
                parent->color = black;
                grandpa->color = red;
            }
        } else {
            if (target == parent->left) {
                __right_rotation(parent);
                std::swap(target, parent);
            }
            if (uncle && uncle->color == red) {
                parent->color = black;
                uncle->color = black;
                grandpa->color = red;
                if (grandpa->parent) {
                    __node* ggpa = grandpa->parent;
                    if (ggpa->parent) {
                        __node* gggpa = ggpa->parent;
                        __node* ggpa2 = (ggpa->value < gggpa->value) ? gggpa->right : gggpa->left;
                        __insert_balance(grandpa, ggpa, gggpa, ggpa2);
                    }
                }
            } else {
                __left_rotation(grandpa);
                parent->color = black;
                grandpa->color = red;
            }
        }
        _m_head->color = black;
    }

    void __erase_balance_(__node* target) {
        while (target != _m_head && target->color == black) {
            __node* parent = target->parent;
            if (parent->left == target) {
                __node* brother = parent->right;
                if (brother && brother->color == red) {
                    brother->color = black;
                    parent->color = red;
                    __left_rotation(parent);
                    brother = parent->right;
                }
                if ((!brother->left || brother->left->color == black) && (!brother->right || brother->right->color == black)) {
                    brother->color = red;
                    target = parent;
                } else {
                    if (!brother->right || brother->right->color == black) {
                        brother->left->color = black;
                        brother->color = red;
                        __right_rotation(brother);
                        brother = parent->right;
                    }
                    brother->color = parent->color;
                    parent->color = black;
                    brother->right->color = black;
                    __left_rotation(parent);
                    target = _m_head;
                }
            } else {
                __node* brother = parent->left;
                if (brother && brother->color == red) {
                    brother->color = black;
                    parent->color = red;
                    __right_rotation(parent);
                    brother = parent->left;
                }
                if ((!brother->right || brother->right->color == black) && (!brother->left || brother->left->color == black)) {
                    brother->color = red;
                    target = parent;
                } else {
                    if (!brother->left || brother->left->color == black) {
                        brother->right->color = black;
                        brother->color = red;
                        __left_rotation(brother);
                        brother = parent->left;
                    }
                    brother->color = parent->color;
                    parent->color = black;
                    brother->left->color = black;
                    __right_rotation(parent);
                    target = _m_head;
                }
            }
        }
        target->color = black;
    }

    void __erase_balance(__node* target, __node* parent, __node* brother) {
        if (target->color == red) {
            target->color = black;
            return;
        }
        if (parent->left == target) {
            if (brother && brother->color == red) {
                __left_rotation(parent);
                parent->color = red;
                brother->color = black;
                brother = parent->right;
                // return;
            }
            if (/* (brother->left && brother->left->color == red) && */ (brother->right && brother->right->color == red)) {
                __left_rotation(parent);
                parent->color = black;
                if (brother->left) {
                    brother->color = brother->left->color;
                } else {
                    brother->color = black;
                }
                return;
            }
            if (brother->left && brother->left->color == red) {
                __right_rotation(brother);
                brother->color = red;
                brother->parent->color = black;
                return __erase_balance(target, parent, brother->parent);
            }
            brother->color = red;
            // parent->color = black;
        } else {
            if (brother && brother->color == red) {
                __right_rotation(parent);
                parent->color = red;
                brother->color = black;
                brother = parent->left;
                // return;
            }
            if (/* (brother->right && brother->right->color == red) && */ (brother->left && brother->left->color == red)) {
                __right_rotation(parent);
                parent->color = black;
                if (brother->right) {
                    brother->color = brother->right->color;
                } else {
                    brother->color = black;
                }
                return;
            }
            if (brother->right && brother->right->color == red) {
                __left_rotation(brother);
                brother->color = red;
                brother->parent->color = black;
                return __erase_balance(target, parent, brother->parent);
            }
            brother->color = red;
            // parent->color = black;
        }
        __node* next_par = parent->parent;
        if (!next_par) {
            return;
        }
        __node* next_bro;
        if (next_par->left == parent) {
            next_bro = next_par->right;
        } else {
            next_bro = next_par->left;
        }
        return __erase_balance(parent, next_par, next_bro);
    }

    void __delete_node(__node* target) {
        if (target->left && target->right) {
            __node* victim = target->right;
            while (victim->left) {
                victim = victim->left;
            }
            target->value = victim->value;
            __delete_node(victim);
            return;
        }
        __node* parent = target->parent;
        if (!parent) {
            return;
        }
        __node* brother;
        __node*& target_edge =
            (parent->left == target) ?
            parent->left :
            parent->right;
        // if (parent->left != target) {
        //     brother = parent->left;
        // } else {
        //     brother = parent->right;
        // }
        // __erase_balance(target, parent, brother);
        __erase_balance_(target);
        if (target->right) {
            target_edge = target->right;
        } else if (target->left) {
            target_edge = target->left;
        } else {
            target_edge = nullptr;
        }
        delete target;
    }

    using bin_tree<T>::_m_head;
    using bin_tree<T>::_m_end_node;
    using bin_tree<T>::_m_size;
};