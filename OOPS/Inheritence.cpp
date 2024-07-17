#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Bird{
    public:
    int age,weight,nl;
    string color;

    void eat(){
        cout<<"eating"<<endl;
    }

    void fly(){
        cout<<"flying"<<endl;
    }
};

class Sparrow: public Bird{
    public:
        Sparrow(int _age,int _weight,string _color,int _nl){ //Overriding defualt constructor with parameterized constructor
            this->age = _age;
            this->weight = _weight;
            this->color = _color;
            this->nl = _nl;
        }
        
        void grassing(){
            cout<<"grassing"<<endl;
        }
};

class Piegion: public Bird{
    public:
    void guttering(){
        cout<<"guttering"<<endl;
    }
};


// Notes
// Inheritence is a way to create a new class using an existing class. The new class is called derived (or child) class and the existing class is called base (or parent) class.
// The new class inherits attributes and methods from the base class, adding new features to it. This results in reusability of code.

// We can inherit the base class in the derived class using the colon (:) operator. The derived class can access all the public and protected members of the base class. It can also add new members to the derived class.
// We will have the choice to inherit the parent in in the modes :
// 1. Public mode
// Here, the public members of the base class become public members of the derived class and the protected members of the base class become protected members of the derived class.

// 2. Protected mode
// Here, the public and protected members of the base class become protected members of the derived class.

// 3. Private mode
// Here, the public and protected members of the base class become private members of the derived class.

// Note that under any case, the private members of the base class are not accessible in the derived class, despite the mode of inheritance.

// There is also something called multi level inheritence, where we can inherit a class from a class which is already inherited from another class. This is called multi level inheritence.
// See the example below : 

class Animal{
    public:
    void eat(){
        cout<<"eating"<<endl;
    }
};

class Dog: public Animal{
    public:
    void bark(){
        cout<<"barking"<<endl;
    }
};


class GermanShepherd: public Dog{
    public:
    void guard(){
        cout<<"guarding"<<endl;
    }
};

int main(){

    Piegion p1;
    p1.fly();

    Sparrow s(2,1,"red",3);
    s.grassing();
    cout<<s.color<<endl;

} 