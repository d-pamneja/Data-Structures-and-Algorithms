#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Vector{
    int x,y;

    public:

    Vector(int _x, int _y):x(_x),y(_y){}; // Constructor using Initialisation List

    void display(){
        cout<<"x: "<<x<<" "<<"y: "<<y<<endl;
    }

    int getX(){
        return x;
    }

    int getY(){
        return y;
    }

    void operator+(Vector &v2){ // addition answer should be stored in v1, hence we use OPERATOR CONSTRUCTOR OVERRIDING
        cout<<"Overrided addition constructor has been called"<<endl;
        this->x = this->x +  v2.x;
        this->y = this->y +  v2.y;
    }

    void operator-(Vector &v2){ // subtraction answer should be stored in v1, hence we use OPERATOR CONSTRUCTOR OVERRIDING
        cout<<"Overrided subtraction constructor has been called"<<endl;
        this->x = this->x -  v2.x;
        this->y = this->y -  v2.y;
    }

    void operator++(){
        cout<<"Overrided ++ constructor has been called"<<endl;
        this->x++;
        this->y++;
    }
};

int main(){
    Vector v1(4,5);
    Vector v2(3,8);
    Vector v3(1,2);

    // v1 + v2;
    // v1.display();

    // v2 - v1;
    // v2.display();

    v1+v2;
    v1.display();
}

// Notes
// Polymorphism is a feature of OOP that allows objects of different classes to be treated as objects of a common superclass. This allows us to perform a single action in different ways.
// If put simiply, Polymorphism is the ability of a single function to operate on different types of data, effecitvely giving it many forms. 
// "poly" means many and "morph" means forms. 

// 1. Compile Time Polymorphism - Static Polymorphism
// Here, the function to be invoked is decided at the compile time. This is also called as Early Binding or Static Binding.
// Compile time polymorphism is achieved using function overloading and operator overloading.
// Function Overloading: When two or more functions in the same scope have the same name but different parameters, it is called function overloading.
// We can do function overloading by changing the number of arguments, changing the data type of arguments, or changing the sequence of arguments.
// Note that just by changing the return type of the function, we cannot do function overloading.

// Operator Overloading: Operator overloading is a type of polymorphism in which an operator is overloaded to give user-defined meaning to it.
// Operator overloading is a compile-time polymorphism. It is a type of static polymorphism. It is also known as Operator Ad-hoc polymorphism.
// We can overload operators by defining a function that will be invoked when the operator is used. We can see the example above.

