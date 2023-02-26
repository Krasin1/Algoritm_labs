#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <ctime>

template <typename T>
class tree {
   public:
    tree() : value(), left(nullptr), right(nullptr) {}
    tree(T a) : value(a), left(nullptr), right(nullptr) {}

    void fill_rand(size_t count) {
        srand(time(NULL));
        
    }

   private:
    T value;
    tree* left;
    tree* right;
};

#endif
