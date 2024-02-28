#pragma once
#include <stack>

template <typename T>
class bin_tree {
protected:
    struct __node {
        T value;
        __node* left;
        __node* right;
        short int balance; // to use in avl tree

        __node(const T& val) : value(val), left(nullptr), right(nullptr), balance(0) {}
        __node(const T& val, __node* l, __node* r) : value(val), left(l), right(r), balance(0) {}
    };
public:
    class iterator {
        friend bin_tree;
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        reference operator*() const {
            return _itr_node->value;
        }
        pointer operator->() const {
            return &_itr_node->value;
        }
        iterator& operator++() {
            if (_itr_node->right) {
                _itr_node = _itr_node->right;
                while (_itr_node->left) {
                    _itr_stack.push(_itr_node);
                    _itr_node = _itr_node->left;
                }
            } else {
                _itr_node = _itr_stack.top();
                _itr_stack.pop();
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp = *this;
            operator++();
            return tmp;
        }
        bool operator==(const iterator& other) const {
            return _itr_node == other._itr_node;
        }
        bool operator!=(const iterator& other) const {
            return _itr_node != other._itr_node;
        }
    private:
        // don't fill stack!
        iterator(__node* x) : _itr_node(x), _itr_stack() {}
        
        __node* _itr_node;
        std::stack<__node*> _itr_stack;
    };

    bin_tree() : _m_head(nullptr), _m_size(0) {
        _m_end_node = new __node(T());
    }
    bin_tree(std::initializer_list<T> l) : _m_head(nullptr) {
        _m_end_node = new __node(T());
        for (const T& elem : l) {
            insert(elem);
        }
        _m_size = l.size();
    }
    ~bin_tree() {
        clear();
    }

    virtual void insert(const T& val) {
        __node* parent = __find_parent(_m_head, val);
        if (parent) {
            if (val < parent->value) {
                parent->left = new __node(val);
            } else if (val > parent->value) {
                parent->right = new __node(val);
            } else return;
        } else {
            _m_head = new __node(val);
            _m_end_node->left = _m_head;
        }
        ++_m_size;
    }

    virtual void erase(const T& val) {
        __node* parent = __find_parent(_m_head, val);
        if (val < parent->value) {
            if (parent->left)
                __delete_node(parent->left);
            else return;
        } else if (val > parent->value) {
            if (parent->right)
                __delete_node(parent->right);
            else return;
        } else {
            __delete_node(_m_head);
        }
        --_m_size;
    }

    bool contains(const T& val) const noexcept {
        return __find(_m_head, val)->value == val;
    }

    iterator find(const T& val) const noexcept {
        iterator result(_m_head);
        result._itr_stack.push(_m_end_node);
        while (result._itr_node && result._itr_node->value != val) {
            if (result._itr_node->value < val) {
                result._itr_node = result._itr_node->right;
            } else {
                result._itr_stack.push(result._itr_node);
                result._itr_node = result._itr_node->left;
            }
        }
        if (!result._itr_node) {
            result._itr_stack = {};
            result._itr_node = _m_end_node;
        }
        
        return result;
    }

    size_t size() const noexcept {
        return _m_size;
    }

    void clear() {
        delete[] _m_head;
        _m_head = nullptr;
        _m_size = 0;
    }

    iterator begin() const noexcept {
        iterator result(_m_end_node);
        while(result._itr_node->left) {
            result._itr_stack.push(result._itr_node);
            result._itr_node = result._itr_node->left;
        }
        return result;
    }
    iterator end() const noexcept {
        iterator result(_m_end_node);
        return result;
    }

protected:
    void __delete_node(__node*& target) {
        if (target->left == nullptr && target->right == nullptr) {
            delete target;
            target = nullptr;
        } else if (target->left == nullptr) {
            __node* new_node = target->right;
            delete target;
            target = new_node;
        } else if (target->right == nullptr) {
            __node* new_node = target->left;
            delete target;
            target = new_node;
        } else {
            __node** tmp = &target->right;
            while ((*tmp)->left != nullptr) {
                tmp = &(*tmp)->left;
            }
            target->value = (*tmp)->value;
            __delete_node(*tmp);
        }
    }
    __node* __find(__node* current, const T& val) const noexcept {
        if (current == nullptr || current->value == val) {
            return current;
        }
        if (val < current->value) {
            if (current->left != nullptr) {
                return __find(current->left, val);
            }
            return current;
        }
        if (val > current->value) {
            if (current->right != nullptr) {
                return __find(current->right, val);
            }
            return current;
        }
        return current;
    }

    /*/ @brief find parent of node with value val
      / @return parent if node exists, else
      node that left or right equal null. 
      If head is null or head->value equal val it returns head.
    */
    __node* __find_parent(__node* current, const T& val) const noexcept {
        if (current == nullptr || current->value == val) {
            return current;
        }
        if (val < current->value) {
            if (current->left != nullptr && current->left->value != val) {
                return __find_parent(current->left, val);
            }
            return current;
        }
        if (val > current->value) {
            if (current->right != nullptr && current->right->value != val) {
                return __find_parent(current->right, val);
            }
            return current;
        }
        return current;
    }

    __node* _m_head;
    __node* _m_end_node;
    size_t _m_size;
};