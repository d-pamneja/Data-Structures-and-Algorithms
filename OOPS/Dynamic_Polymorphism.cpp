#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Animal{
    public:
    virtual void sound(){
        cout<<"Animal is live."<<endl;
    }
};

class Dog: public Animal{
    public:
    void sound(){
        cout<<"Dog is barking"<<endl;
    }
};

class Cat: public Animal{
    public:
    void sound(){
        cout<<"Cat is meowing"<<endl;
    }
};

void sound(Animal *animal){
    animal->sound(); //polymorphic
}

int main(){
    // Dog *dog = new Dog(); 
    // dog->sound(); // This is how we call methods of instances which are on heap
    // delete dog;

    Animal *animal1 = new Dog(); 
    sound(animal1);

    Animal *animal2 = new Cat(); 
    sound(animal2);

    delete animal1;
    delete animal2;
}

// Notes
// Polymorphism is a feature of OOP that allows objects of different classes to be treated as objects of a common superclass. This allows us to perform a single action in different ways.
// If put simiply, Polymorphism is the ability of a single function to operate on different types of data, effecitvely giving it many forms. 
// "poly" means many and "morph" means forms. 

// 2. Runtime Polymorphism - Dynamic Polymorphism
// Here, the function call is resolved at runtime. This is achieved by function overriding. 
// We can achieve runtime polymorphism by using virtual functions. Now, there are a few conditions to be met for this to work:

// The function in the base class must be declared as virtual.
// The function in the derived class must be declared with the same name and parameters as the base class.
// It depends on the inheritance. If the base class pointer is pointing to the derived class object, then the function call is resolved at runtime.

