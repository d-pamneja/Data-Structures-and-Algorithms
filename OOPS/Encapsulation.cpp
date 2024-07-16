# include <iostream>
# include <stdlib.h>
# include <cmath>
#include <cstdio>

using namespace ::std;



// Notes
// Encapsulation is the process of wrapping up of data and methods into a single unit called class. It is a way to achieve data hiding in C++. It is very different from data abstraction. 
// It is a way of hiding the data from the outside world and providing a public interface to interact with the data.
// By making the data private, we are hiding the data from the outside world. We can only access the data through the member functions of the class.
// Think of it this way, when we create a new class, we are creating a new data type. So, we can create multiple objects of that class, and each object will have its own data members.
// When we have all data members as private of that class and we want to access them, we can use the member functions of that class to access the data members.
// Then, we call that a fully encapsulated class. It is a good practice to make all the data members private and provide public member functions to access them.

// Advantages of Encapsulation : 
// 1. Data Hiding: The user will have no idea about the inner implementation of the class. It will hide the data from the outside world and provide more security.
// 2. Increased Flexibility: It provides the flexibility to change the implementation of the class without affecting the user. The user will only interact with the public interface of the class.
// 3. Read Only Fields: We can make the fields of the class read-only, i.e., we can only read the fields and cannot modify them.
// 4. Code Reusability: Encapsulation also improves the code reusability. We can use the same class in other programs without modifying it.
// 5. Unit Testing: Encapsulation also helps in unit testing. We can test the class independently without affecting the other parts of the program.


class Student{
    private:
        int id;
        int age;
        int nos;
        string name;
        string gfName;

    public:
        Student(int _id, int _age, int _nos, string _name, int _gfName){
            id = _id;
            age = _age;
            nos = _nos;
            name = _name;
            gfName = _gfName;
        }

        int getId(){
            return id;
        }

        void setId(int _id){
            id = _id;
        }

        int getAge(){
            return age;
        }

        void setAge(int _age){
            age = _age;
        }

        int getNos(){
            return nos;
        }

        void setNos(int _nos){
            nos = _nos;
        }

        string getName(){
            return name;
        }

        void setName(string _name){
            name = _name;
        }

        string getGfName(){
            return gfName;
        }

        void setGfName(string _gfName){
            gfName = _gfName;
        }
};

// Here, we can see that the data members of the class Student are private, and we can only access them through the public member functions of the class.
// This is the concept of encapsulation in C++.
