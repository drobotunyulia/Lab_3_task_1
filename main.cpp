#include <iostream>
#include <set>
#include "binary_heap.h"
#include "binomial_heap.h"
#include"fibonacci_heap.h"
using namespace std;

void example_1();
void example_2();
void example_3();

int main()
{
    cout << "Laba 3 Task 1" << endl;
    cout << "Drobotun Yuliya M8o-210B-20" << endl << endl;
    example_1();
    getchar();
    example_2();
    getchar();
    example_3();
}
void example_1()
{
    cout << "Example 1" << endl;
    //Example binary heap
    comparator<int> *comparator_int = new comparator<int>;
    binary_heap_creator<int, int> *heap_creator = new binary_heap_creator<int, int>;
    binary_heap<int, int> *example = heap_creator->create(comparator_int);
    binary_heap<int, int> *example_1 = heap_creator->create(comparator_int);
    cout << "Binary heap name: example" << endl;
    try
    {
       cout << "Get minimum :";
       cout << example->get_minimum() << endl;
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
        cout << "Insert 9 : 3" << endl;
        example->insert(9, 3);
        cout << "Insert 1 : 3" << endl;
        example->insert(1, 3);
        cout << "Insert 7 : 5" << endl;
        example->insert(7, 5);
        cout << "Insert 6 : 22" << endl;
        example->insert(6, 22);
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
       cout << "Get minimum :";
       cout << example->get_minimum() << endl;
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
       cout << "Remove minimum" << endl;
       example->remove_minimum();
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
       cout << "Get minimum :";
       cout << example->get_minimum() << endl;
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    cout << "Binary heap name: example_1" << endl;
    try
    {
        cout << "Insert -9 : 3" << endl;
        example_1->insert(-9, 3);
        cout << "Insert -1 : 3" << endl;
        example_1->insert(-1, 3);
        cout << "Insert -7 : 5" << endl;
        example_1->insert(-7, 5);
        cout << "Insert -6 : 22" << endl;
        example_1->insert(-6, 22);
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
       cout << "Union heap example with example_1" << endl;
       example->union_heap(*example_1);
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
       cout << "Get minimum :";
       cout << example->get_minimum() << endl;
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    delete comparator_int;
    delete heap_creator;
    delete example;
    delete example_1;
}
void example_2()
{
    cout << "Example 2" << endl;
    //Example binomial heap
    comparator<int> *comparator_int = new comparator<int>;
    binomial_heap_creator<int, int> *heap_creator = new binomial_heap_creator<int, int>;
    binomial_heap<int, int> *example = heap_creator->create(comparator_int);
    binomial_heap<int, int> *example_1 = heap_creator->create(comparator_int);
    cout << "Binomial heap name: example" << endl;
    try
    {
       cout << "Get minimum :";
       cout << example->get_minimum() << endl;
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
        cout << "Insert 9 : 3" << endl;
        example->insert(9, 3);
        cout << "Insert 1 : 3" << endl;
        example->insert(1, 3);
        cout << "Insert 7 : 5" << endl;
        example->insert(7, 5);
        cout << "Insert 6 : 22" << endl;
        example->insert(6, 22);
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
        cout << "Get minimum :";
        cout << example->get_minimum() << endl;
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
       cout << "Remove minimum" << endl;
       example->remove_minimum();
    }
    catch (heap_exception &exception)
    {
        cout << exception.what() << endl;
    }
    try
    {
       cout << "Get minimum :";
       cout << example->get_minimum() << endl;
    }
    catch (heap_exception &exception)
    {
        cout << exception.what() << endl;
    }
    cout << "Binomial heap name: example_1" << endl;
    try
    {
        cout << "Insert -9 : 3" << endl;
        example_1->insert(-9, 3);
        cout << "Insert -1 : 3" << endl;
        example_1->insert(-1, 3);
        cout << "Insert -7 : 5" << endl;
        example_1->insert(-7, 5);
        cout << "Insert -6 : 2" << endl;
        example_1->insert(-6, 22);
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
       cout << "Union heap example with example_1" << endl;
       example->union_heap(*example_1);
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
       cout << "Get minimum :";
       cout << example->get_minimum() << endl;
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    delete comparator_int;
    delete heap_creator;
    delete example;
    delete example_1;
}
void example_3()
{
    cout << "Example 3" << endl;
    comparator<int> *comparator_int = new comparator<int>;
    //Example fibonacci heap
    fibonacci_heap_creator<int, int> *heap_creator = new fibonacci_heap_creator<int, int>;
    fibonacci_heap<int, int> *example = heap_creator->create(comparator_int);
    fibonacci_heap<int, int> *example_1 = heap_creator->create(comparator_int);
    cout << "Fibonacci heap name: example" << endl;
    try
    {
       cout << "Get minimum :";
       cout << example->get_minimum() << endl;
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
        cout << "Insert 9 : 3" << endl;
        example->insert(9, 3);
        cout << "Insert 1 : 3" << endl;
        example->insert(1, 3);
        cout << "Insert 7 : 5" << endl;
        example->insert(7, 5);
        cout << "Insert 6 : 22" << endl;
        example->insert(6, 22);
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
        cout << "Get minimum :";
        cout << example->get_minimum() << endl;
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
       cout << "Remove minimum" << endl;
       example->remove_minimum();
    }
    catch (heap_exception &exception)
    {
        cout << exception.what() << endl;
    }
    try
    {
       cout << "Get minimum :";
       cout << example->get_minimum() << endl;
    }
    catch (heap_exception &exception)
    {
        cout << exception.what() << endl;
    }
    cout << "Fibonacci heap name: example_1" << endl;
    try
    {
        cout << "Insert -9 : 3" << endl;
        example_1->insert(-9, 3);
        cout << "Insert -1 : 3" << endl;
        example_1->insert(-1, 3);
        cout << "Insert -7 : 5" << endl;
        example_1->insert(-7, 5);
        cout << "Insert -6 : 22" << endl;
        example_1->insert(-6, 22);
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
       cout << "Union heap example with example_1" << endl;
       example->union_heap(*example_1);
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    try
    {
       cout << "Get minimum :";
       cout << example->get_minimum() << endl;
    }
    catch (heap_exception &exception)
    {
         cout << exception.what() << endl;
    }
    delete comparator_int;
    delete heap_creator;
    delete example;
    delete example_1;
}
