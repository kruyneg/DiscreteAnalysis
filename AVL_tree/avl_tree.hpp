#include "bin_tree.hpp"

template <typename T>
class avl_tree : public bin_tree<T> {
    using typename bin_tree<T>::__node;
public:
    using bin_tree<T>::iterator;

    avl_tree() : bin_tree<T>() {}
    avl_tree(std::initializer_list<T> l) : bin_tree<T>() {
        for (const T& elem : l) {
            insert(elem);
        }
        _m_size = l.size();
    }
    ~avl_tree() {
        bin_tree<T>::clear();
    }

    void insert(const T& val) override {
        bool flag = true;
        __insert_node(_m_head, val, flag);
        if (_m_size == 1) {
            _m_end_node->left = _m_head;
        }
    }
    void erase(const T& val) override {
        bool flag = true;
        __delete_node(_m_head, val, flag);
        _m_end_node->left = _m_head;
    }
private:
    void __left_rotation(__node*& x) {
        __node* y = x->right;
        __node* tmp = x;
        x = y;
        tmp->right = y->left;
        y->left = tmp;
    }
    void __right_rotation(__node*& y) {
        __node* x = y->left;
        __node* tmp = y;
        y = x;
        tmp->left = x->right;
        x->right = tmp;
    }
    void __simple_balancing_r(__node*& p) {
        __left_rotation(p);
        p->balance = 0;
        p->left->balance = 0;
    }
    void __simple_balancing_l(__node*& p) {
        __right_rotation(p);
        p->balance = 0;
        p->right->balance = 0;
    }
    void __complex_balancing_r(__node*& p) {
        ++p->right->balance;
        __right_rotation(p->right);
        __left_rotation(p);
        p->balance = 0;
        p->left->balance = 0;
    }
    void __complex_balancing_l(__node*& p) {
        --p->left->balance;
        __left_rotation(p->left);
        __right_rotation(p);
        p->balance = 0;
        p->right->balance = 0;
    }

    void __insert_node(__node*& current, const T& val, bool& check) {
        if (!current) {
            current = new __node(val);
            ++_m_size;
            return;
        }
        if (val < current->value) {
            __insert_node(current->left, val, check);
            if (check) {
                --current->balance;
            }
        } else if (val > current->value) {
            __insert_node(current->right, val, check);
            if (check) {
                ++current->balance;
            }
        } else {
            check = false;
            return;
        }
        if (check) {
            if (current->balance == -2) {
                if (current->left->balance <= 0)
                    __simple_balancing_l(current);
                else 
                    __complex_balancing_l(current);
                check = false;
            } else if (current->balance == 2) {
                if (current->right->balance >= 0)
                    __simple_balancing_r(current);
                else
                    __complex_balancing_r(current);
                check = false;
            } else if (current->balance == 0) {
                check = false;
            }
        }
    }

    void __delete_node(__node*& current, const T& val, bool& check) {
        if (!current) {
            check = false;
            return;
        } else if (current->value == val) {
            if (current->left == nullptr && current->right == nullptr) {
                delete current;
                current = nullptr;
                --_m_size;
                return;
            } else if (current->left == nullptr) {
                __node* new_node = current->right;
                delete current;
                current = new_node;
                --_m_size;
                return;
            } else if (current->right == nullptr) {
                __node* new_node = current->left;
                delete current;
                current = new_node;
                --_m_size;
                return;
            } else {
                __node** tmp = &current->right;
                while ((*tmp)->left != nullptr) {
                    tmp = &(*tmp)->left;
                }
                current->value = (*tmp)->value;
                --current->balance;
                __delete_node(*tmp, current->value, check);
            }
        } else if (current->value < val) {
            --current->balance;
            __delete_node(current->right, val, check);
        } else if (current->value > val) {
            ++current->balance;
            __delete_node(current->left, val, check);
        }
        if (check) {
            if (current->balance == -2) {
                if (current->left->balance <= 0)
                    __simple_balancing_l(current);
                else 
                    __complex_balancing_l(current);
                check = false;
            } else if (current->balance == 2) {
                if (current->right->balance >= 0)
                    __simple_balancing_r(current);
                else
                    __complex_balancing_r(current);
                check = false;
            } else if (current->balance == 0) {
                check = false;
            }
        }
    }

    using bin_tree<T>::_m_head;
    using bin_tree<T>::_m_end_node;
    using bin_tree<T>::_m_size;
};
