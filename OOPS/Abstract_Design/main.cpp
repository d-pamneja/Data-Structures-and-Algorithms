#include <iostream>
#include "Bird.h"

using namespace std;

void birdDoesSomething(BIRD *&bird)
{
    bird->eat();
    bird->fly();
    bird->eat();
    bird->fly();
    bird->eat();
    bird->fly();
    bird->eat();
    bird->fly();
    bird->eat();
    bird->fly();
    bird->eat();
    bird->fly();
    bird->eat();
    bird->fly();
}

int main(){
    BIRD *bird = new Sparrow();
    birdDoesSomething(bird);
    return 0;
}

// Notes
// Abstraction is a concept of hiding the implementation details and showing only the functionality to the user. In C++, we can achieve abstraction using abstract classes and pure virtual functions.
// An abstract class is a class that has at least one pure virtual function. A pure virtual function is a function that has no definition in the base class and must be overridden in the derived class.
// Now, in the above example, we have created an abstract class BIRD with two pure virtual functions eat() and fly(). The classes Sparrow and Eagle are derived from the BIRD class and they have implemented the pure virtual functions.
// The user cannot see the implementation details of the eat() and fly() functions, but they can use the functionality of these functions. This is an example of abstraction.

// Difference between Abstraction and Encapsulation :

// 1. Abstraction is a concept of hiding the implementation details and showing only the functionality to the user. Encapsulation is a concept of wrapping the data (variables) and methods (functions) that operate on the data into a single unit (class).
// 2. Abstraction is achieved using abstract classes and pure virtual functions. Encapsulation is achieved using access specifiers (public, private, protected) in C++.
// 3. Abstraction focuses on the outside view of the object, while encapsulation focuses on the inside view of the object.

// In a way, abstraction is a broader concept that includes encapsulation. Encapsulation is a way to achieve abstraction.
// Encapsulation means information hiding, while abstraction means implementation hiding.