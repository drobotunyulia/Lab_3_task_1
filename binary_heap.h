#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H
#include <iostream>
#include <string.h>
#include <sstream>
#include "heap.h"
#include "heap_exception.h"

template <typename TKey, typename TValue>
class binary_heap_creator;

template <typename TKey, typename TValue>
class binary_heap: public heap<TKey, TValue>
{
private:
    bool is_empty();
    void heapify(int);
public:
    binary_heap(comparator<TKey> *key_comparator);
    ~binary_heap();
    void make_heap(comparator<TKey> *key_comparator);
    void insert(const TKey key, const TValue value);
    TValue get_minimum();
    void remove_minimum();
    void union_heap(heap<TKey, TValue>& H_2);
    friend class binary_heap_creator<TKey, TValue>;
};
template<typename TKey, typename TValue>
void binary_heap<TKey, TValue>::make_heap(comparator<TKey> *key_comparator)
{
    heap<TKey, TValue>::heap_size = 0;
    heap<TKey, TValue>::key_comparator = key_comparator;
}
template <typename TKey, typename TValue>
binary_heap<TKey, TValue>::binary_heap(comparator<TKey> *key_comparator)
{
    binary_heap<TKey, TValue>::make_heap(key_comparator);
}
template <typename TKey, typename TValue>
bool binary_heap<TKey, TValue>::is_empty()
{
    return (heap<TKey, TValue>::heap_size == 0);
}
template <typename TKey, typename TValue>
void binary_heap<TKey, TValue>::insert(const TKey key, const TValue value)
{
    Node<TKey, TValue> *inner_heap_ptr = new Node<TKey, TValue>[heap<TKey, TValue>::heap_size + 1];
    for(int i = 0; i < heap<TKey, TValue>::heap_size; i++)
    {
        inner_heap_ptr[i] = this->heap_ptr[i];
    }
    delete [] this->heap_ptr;
    this->heap_ptr = inner_heap_ptr;
    int index, parent;
    index = heap<TKey, TValue>::heap_size;
    compare_t compare_result;
    heap<TKey, TValue>::heap_ptr[index].key = key;
    heap<TKey, TValue>::heap_ptr[index].value = value;
    parent = (index-1)/2;
    while(parent >= 0 && index > 0)
    {
       compare_result = (*(this->key_comparator))(heap<TKey, TValue>::heap_ptr[index].key, heap<TKey, TValue>::heap_ptr[parent].key);
       if(compare_result == EQUAL)
       {
           throw typename heap<TKey, TValue>::insert_error_exception(key);
       }
       compare_result = (*(this->key_comparator))(index, 2*parent+1);
       if(compare_result == EQUAL)
       {
           compare_result = (*(this->key_comparator))(heap<TKey, TValue>::heap_ptr[index].key, heap<TKey, TValue>::heap_ptr[2*parent+2].key);
           if(compare_result == EQUAL)
           {
               throw typename heap<TKey, TValue>::insert_error_exception(key);
           }
       }
       compare_result = (*(this->key_comparator))(index, 2*parent+2);
       if(compare_result == EQUAL)
       {
           compare_result = (*(this->key_comparator))(heap<TKey, TValue>::heap_ptr[index].key, heap<TKey, TValue>::heap_ptr[2*parent+1].key);
           if(compare_result == EQUAL)
           {
               throw typename heap<TKey, TValue>::insert_error_exception(key);
           }
       }
       compare_result = (*(this->key_comparator))(heap<TKey, TValue>::heap_ptr[index].key, heap<TKey, TValue>::heap_ptr[parent].key);
       if(compare_result == LESS)
       {
          Node<TKey, TValue> temp = heap<TKey, TValue>::heap_ptr[index];
          heap<TKey, TValue>::heap_ptr[index] = heap<TKey, TValue>::heap_ptr[parent];
          heap<TKey, TValue>::heap_ptr[parent] = temp;
       }
       index = parent;
       parent = (index-1)/2;
     }
     heap<TKey, TValue>::heap_size++;
}
template <typename TKey, typename TValue>
TValue binary_heap<TKey, TValue>::get_minimum()
{
    if(is_empty())
    {
        throw typename heap<TKey, TValue>::get_minimum_error_exception();
    }
    return heap<TKey, TValue>::heap_ptr[0].value;
}
template <typename TKey, typename TValue>
void binary_heap<TKey, TValue>::heapify(int i)
{
    int left, right;
    Node<TKey, TValue> temp;
    left = 2*i+1;
    right = 2*i+2;
    compare_t compare_result;
    compare_result = (*(this->key_comparator))(left, heap<TKey, TValue>::heap_size);
    if(compare_result == LESS)
    {
      compare_result = (*(this->key_comparator))(heap<TKey, TValue>::heap_ptr[i].key, heap<TKey, TValue>::heap_ptr[left].key);
      if(compare_result == GREAT)
      {
        temp = heap<TKey, TValue>::heap_ptr[i];
        heap<TKey, TValue>::heap_ptr[i] = heap<TKey, TValue>::heap_ptr[left];
        heap<TKey, TValue>::heap_ptr[left] = temp;
        heapify(left);
      }
    }
    compare_result = (*(this->key_comparator))(right, heap<TKey, TValue>::heap_size);
    if(compare_result == LESS)
    {
      compare_result = (*(this->key_comparator))(heap<TKey, TValue>::heap_ptr[i].key, heap<TKey, TValue>::heap_ptr[right].key);
      if(compare_result == GREAT)
      {
        temp = heap<TKey, TValue>::heap_ptr[i];
        heap<TKey, TValue>::heap_ptr[i] = heap<TKey, TValue>::heap_ptr[right];
        heap<TKey, TValue>::heap_ptr[right] = temp;
        heapify(right);
      }
    }
}
template <typename TKey, typename TValue>
void binary_heap<TKey, TValue>::remove_minimum()
{
    if(is_empty())
    {
        throw typename heap<TKey, TValue>::remove_minimum_error_exception();
    }
    Node<TKey, TValue> min;
    min = heap<TKey, TValue>::heap_ptr[0];
    heap<TKey, TValue>::heap_ptr[0] = heap<TKey, TValue>::heap_ptr[heap<TKey, TValue>::heap_size-1];
    heap<TKey, TValue>::heap_size--;
    heapify(0);
}
template <typename TKey, typename TValue>
void binary_heap<TKey, TValue>::union_heap(heap<TKey, TValue> &H_2)
{
    int i = 0;
    try
    {
        for(i = 0; i < H_2.heap_size; i++)
        {
            insert(H_2.heap_ptr[i].key, H_2.heap_ptr[i].value);
        }
     }
     catch (heap_exception &exception)
     {
        throw typename heap<TKey, TValue>::union_heap_error_exception(this->heap_ptr[i].key);
     }
}
template <typename TKey, typename TValue>
binary_heap<TKey, TValue>::~binary_heap()
{
    delete [] heap<TKey, TValue>::heap_ptr;
    heap<TKey, TValue>::heap_size = 0;
}

template <typename TKey, typename TValue>
class binary_heap_creator : public heap_creator<TKey, TValue>
{
public:
    binary_heap<TKey, TValue>* create(comparator<TKey> *key_comparator) override
    {
        return new binary_heap<TKey, TValue>(key_comparator);
    }
    ~binary_heap_creator()
    {

    }
};
#endif // BINARY_HEAP_H
