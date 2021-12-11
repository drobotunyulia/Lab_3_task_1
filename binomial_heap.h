#ifndef BIONAMIAL_HEAP_H
#define BIONAMIAL_HEAP_H
#include <stack>
#include <queue>
#include <cmath>
#include <sstream>
#include "heap.h"
#include "heap_exception.h"
#include "comparator.h"

template <typename TKey, typename TValue>
class binomial_heap_creator;

template<typename TKey, typename TValue>
class binomial_heap : public heap<TKey, TValue>
{
private:
    binomial_heap(comparator<TKey> *key_comparator);
    void set_heap_ptr(Node<TKey, TValue>* heap_ptr_1);
    Node<TKey, TValue>* union_tree(Node<TKey, TValue>* , Node<TKey, TValue>*);
    void reverse_heap();
    void update_min(Node<TKey, TValue >*node);
public:
    binomial_heap(Node<TKey, TValue>* node, comparator<TKey> *key_comparator);
    ~binomial_heap();
    void make_heap(comparator<TKey> *key_comparator);
    void insert(const TKey key, const TValue value);
    TValue get_minimum();
    void remove_minimum();
    void union_heap(heap<TKey, TValue> &H_2);
    friend class binomial_heap_creator<TKey, TValue>;
};
template<typename TKey, typename TValue>
void binomial_heap<TKey, TValue>::make_heap(comparator<TKey> *key_comparator)
{
    heap<TKey, TValue>::key_comparator = key_comparator;
    this->heap_ptr = nullptr;
}
template<typename TKey, typename TValue>
binomial_heap<TKey, TValue>::binomial_heap(comparator<TKey> *key_comparator)
{
    binomial_heap<TKey, TValue>::make_heap(key_comparator);
}
template<typename TKey, typename TValue>
binomial_heap<TKey, TValue>::binomial_heap(Node<TKey, TValue>* node, comparator<TKey> *key_comparator)
{
    this->heap_ptr = node;
    this->key_comparator = key_comparator;
}
template<typename TKey, typename TValue>
void binomial_heap<TKey, TValue>::update_min(Node<TKey, TValue > *node)
{
    Node<TKey, TValue>* current = this->heap_ptr;
    compare_t compare_result;
    compare_result = (*(this->key_comparator))(node->key, current->key);
    if (current == nullptr)
    {
        set_heap_ptr(node);
    }
    else if ((node != NULL) && (compare_result == LESS))
    {
        set_heap_ptr(node);
    }
}
template<typename TKey, typename TValue>
void binomial_heap<TKey, TValue>::set_heap_ptr(Node<TKey, TValue>* heap_ptr_1)
{
    this->heap_ptr = heap_ptr_1;
}
template<typename TKey, typename TValue>
Node<TKey, TValue>* binomial_heap<TKey, TValue>::union_tree(Node<TKey, TValue>* new_tree, Node<TKey, TValue>* added_tree)
{
    added_tree->parent = new_tree;
    added_tree->right = new_tree->child;
    new_tree->child = added_tree;
    new_tree->degree += 1;
    return new_tree;
}
template<typename TKey, typename TValue>
void binomial_heap<TKey, TValue>::union_heap(heap<TKey, TValue> &H_2)
{
    compare_t compare_result;
    Node<TKey, TValue> *temporary_heap = nullptr;
    if (this->heap_ptr != nullptr && H_2.heap_ptr != nullptr)
    {
       Node<TKey, TValue>* node_1 = this->heap_ptr;
       Node<TKey, TValue>* node_2 = H_2.heap_ptr;
       Node<TKey, TValue>* new_heap = nullptr;
       Node<TKey, TValue>* temp_heap = nullptr;
       compare_result = (*(this->key_comparator))(node_1->degree, node_2->degree);
       if (compare_result == LESS || compare_result == EQUAL)
       {
           new_heap = node_1;
           node_1 = node_1->right;
       }
       else
       {
           new_heap = node_2;
           node_2 = node_2->right;
       }
       temp_heap = new_heap;
       while (node_1 != nullptr && node_2 != nullptr)
       {
           compare_result = (*(this->key_comparator))(node_1->key, node_2->key);
           if(compare_result == EQUAL)
           {
               throw typename heap<TKey, TValue>::union_heap_error_exception(node_1->key);
           }
           compare_result = (*(this->key_comparator))(node_1->degree, node_2->degree);
           if (compare_result == LESS || compare_result == EQUAL)
           {
              new_heap->right = node_1;
              node_1 = node_1->right;
           }
           else
           {
              new_heap->right = node_2;
              node_2 = node_2->right;
           }
           new_heap = new_heap->right;
        }
        if (node_1 != nullptr)
        {
            while (node_1 != nullptr)
            {
              new_heap->right = node_1;
              node_1 = node_1->right;
              new_heap = new_heap->right;
            }
        }
        if (node_2 != nullptr)
        {
            while (node_2 != nullptr)
            {
              new_heap->right = node_2;
              node_2 = node_2->right;
              new_heap = new_heap->right;
            }
         }
         new_heap = temp_heap;
         Node<TKey, TValue>* prev = nullptr;
         Node<TKey, TValue>* next = new_heap->right;
         while (next != nullptr)
         {
            if(prev && next)
            {
                compare_result = (*(this->key_comparator))(prev->key, next->key);
                if(compare_result == EQUAL)
                {
                    throw typename heap<TKey, TValue>::union_heap_error_exception(next->key);
                }
            }
            if ((new_heap->degree != next->degree)
                || (next->right != nullptr && new_heap->degree == next->right->degree))
            {
              prev = new_heap;
              new_heap = next;
            }
            else
            {
              compare_result = (*(this->key_comparator))(new_heap->key, next->key);
              if (compare_result == LESS || compare_result == EQUAL)
              {
                new_heap->right = next->right;
                binomial_heap::union_tree(new_heap, next);
              }
              else
              {

                if (prev == nullptr)
                {
                  temp_heap = next;
                }
                else
                {
                  prev->right = next;
                }
                binomial_heap::union_tree(next, new_heap);
                new_heap = next;
              }
            }
            next = new_heap->right;
          }
          set_heap_ptr(temp_heap);
        }
   if (this->heap_ptr == nullptr)
   {
       temporary_heap = H_2.heap_ptr;
       binomial_heap<TKey, TValue>::set_heap_ptr(temporary_heap);
   }
   H_2.heap_ptr = nullptr;
}
template<typename TKey, typename TValue>
void binomial_heap<TKey, TValue>::insert(const TKey key, const TValue value)
{
    try
    {
        binomial_heap *new_heap = new binomial_heap(this->key_comparator);
        Node<TKey, TValue> *node = new Node<TKey, TValue>();
        node->key = key;
        node->value = value;
        new_heap->heap_ptr = node;
        binomial_heap<TKey, TValue>::union_heap(*new_heap);
        update_min(node);
    }
    catch (heap_exception &exception)
    {
        throw typename heap<TKey, TValue>::insert_error_exception(key);
    }
}
template<typename TKey, typename TValue>
TValue binomial_heap<TKey, TValue>::get_minimum()
{
    if(this->heap_ptr == nullptr)
    {
       throw typename heap<TKey, TValue>::get_minimum_error_exception();
    }
    return this->heap_ptr->value;
}
template<typename TKey, typename TValue>
void binomial_heap<TKey, TValue>::remove_minimum()
{
    if (!this->heap_ptr)
    {
        throw typename heap<TKey, TValue>::remove_minimum_error_exception();
    }
    Node<TKey, TValue>* prev_node = nullptr;
    Node<TKey, TValue>* min_node = nullptr;
    Node<TKey, TValue>* node = nullptr;
    Node <TKey, TValue>* min_node_child = nullptr;
    compare_t compare_result;
    if (this->heap_ptr)
    {
        Node<TKey, TValue>* min_prev_node = nullptr;
        min_node = this->heap_ptr;
        node = (this->heap_ptr)->right;
        prev_node = this->heap_ptr;
        while (node != nullptr)
        {
            compare_result = (*(this->key_comparator))(node->key, min_node->key);
            if (compare_result == LESS)
            {
                min_node = node;
                min_prev_node = prev_node;
            }
            prev_node = prev_node->right;
            node = node->right;
        }
        if (min_prev_node != nullptr)
        {
            min_prev_node->right = min_node->right;
        }
        else
        {
            this->heap_ptr = min_node->right;
        }
        min_node_child = min_node->child;
        node = min_node_child;
        while (node != nullptr)
        {
            node->parent = min_node->parent;
            node = node->right;
        }
        min_node->right = nullptr;
        min_node->child = nullptr;
        min_node->parent = nullptr;
        delete min_node;
        binomial_heap<TKey, TValue>* heap_1 = new binomial_heap<TKey, TValue>(min_node_child, this->key_comparator);
        heap_1->reverse_heap();
        union_heap(*heap_1);
    }
}
template<typename TKey, typename TValue>
void binomial_heap<TKey, TValue>::reverse_heap()
{
    std::stack<Node<TKey, TValue> *> queue;
    while (this->heap_ptr != nullptr)
    {
      queue.push(this->heap_ptr);
      this->heap_ptr = this->heap_ptr->right;
      queue.top()->right = nullptr;
    }
    this->heap_ptr = queue.top();
    Node<TKey, TValue> *temp = queue.top();
    queue.pop();
    while (!queue.empty())
    {
      this->heap_ptr->right = queue.top();
      queue.pop();
      this->heap_ptr = this->heap_ptr->right;
    }
    this->heap_ptr = temp;
}
template<typename TKey, typename TValue>
binomial_heap<TKey, TValue>::~binomial_heap()
{
    Node<TKey, TValue> *curr_ptr = this->heap_ptr;
    std::vector<Node<TKey, TValue> *> nodes;
    while (curr_ptr != nullptr)
    {
        std::queue<Node<TKey, TValue> *> queue;
        queue.push(curr_ptr);
        while (!queue.empty())
        {
            Node<TKey, TValue> *current = queue.front();
            nodes.push_back(queue.front());
            queue.pop();
            if (current->child != nullptr)
            {
                Node<TKey, TValue>* tempPtr = current->child;
                while (tempPtr != nullptr)
                {
                   queue.push(tempPtr);
                   tempPtr = tempPtr->right;
                }
            }
        }
        curr_ptr = curr_ptr->right;
    }
    for (int i = 0; i < static_cast<int>(nodes.size()); i++)
        delete nodes[ static_cast<int>(i)];
}

template <typename TKey, typename TValue>
class binomial_heap_creator : public heap_creator<TKey, TValue>
{
public:
    binomial_heap<TKey, TValue>* create(comparator<TKey> *key_comparator) override
    {
        return new binomial_heap<TKey, TValue>(key_comparator);
    }
    ~binomial_heap_creator()
    {

    }
};
#endif // BIONAMIAL_HEAP_H
