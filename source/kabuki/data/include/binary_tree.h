/** kabuki::data
    @version 0.x
    @file    ~/source/data/include/binary_tree.h
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <calemccollough.github.io>;
             All right reserved (R). Licensed under the Apache License, Version 
             2.0 (the "License"); you may not use this file except in 
             compliance with the License. You may obtain a copy of the License 
             [here](http://www.apache.org/licenses/LICENSE-2.0). Unless 
             required by applicable law or agreed to in writing, software
             distributed under the License is distributed on an "AS IS" BASIS,
             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
             implied. See the License for the specific language governing 
             permissions and limitations under the License.
*/

#ifndef KABUKI_DATA_BINARYTREE_H
#define KABUKI_DATA_BINARYTREE_H

#include "iterator.h"

namespace kabuki { namespace data {

/** @warning This is some of the first code I EVER wrote; please don't make fun
             of me for how bad this is. */

template<typename T>
struct BinaryNode {
    BinaryNode<T> * root,          //< Pointer to the root node.
                  * left,          //< Pointer to the left child node.
                  * right;         //< Pointer to the right child node.
    bool            been_left,     //< Flag for if left child has been traversed.
                    been_right;    //< Flag for if right child has been traversed.
    uintptr_t       index;         //< The index of this node.
    T               data;          //< Node contents.
};
    
/** A binary tree.
    @code
    
    @endcode
*/
template<typename T>
class BinaryTree
{
    public:
    
    /** Constructs a BinaryTree with the given Size. */
    BinaryTree () {
        Clear ();
    }
    
    /** Deletes the tree. */
    ~BinaryTree () {

    }
    
    /** Deletes all items. */
    void Clear () {
        root_ = new BinaryNode<T> ();
        size_ = 0;
    }
    
    BinaryNode<T>* FindDepthFirst (BinaryNode<T>* root, void* ptr) {
        BinaryNode<T>* current = root;
        while (!BinaryNodeContains (current, ptr)) {
            while (true) {
                if (current->left != nullptr && current->been_left == false) {
                    current = current->left;// can go this way
                    current->been_left = true;// flag the node so it knows were its been
                } else if (current->right != nullptr && current->been_right == false) {
                    current = current->right;// can go that way
                    current->been_right = true;// flag the node so it knows were its been
                } else if (current->root != nullptr) {
                    current = current->root;
                    current->been_right = current->been_right = false;
                    // now were done with this op-tree so we reset the flags so that
                    // we don't have to reset the whole tree to search it again
                } else {
                    current->been_right = current->been_right = false;
                    return nullptr;
                }
            }
        }
        return current;
    }
    
    BinaryNode<T>* FindDepthFirst (void* ptr) {
        return FindDepthFirst (root_, ptr);
    }
    
    bool FindBreathFirst (void* ptr) {
        return false;
    }
    
    bool Contains (void* ptr) {
        if (FindDepthFirst (ptr) == nullptr)
            return false;
        return true;
    }

    int GetIndex () {
        return index_;
    }

    int GetSize () {
        return size_;
    }

    Iterator* GetIterator () {
        return 0;
    }
        
    private:
    
    BinaryNode<T>* root_, 
              * left_,
              * right_;
    int         size_,
                index_;
};

}       //< namespace data
}       //< namespace kabuki
#endif  //< KABUKI_DATA_BINARYTREE_H
