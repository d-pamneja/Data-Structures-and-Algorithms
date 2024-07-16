#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student
{
private:
    string gf;

public:
    int id;
    int age;
    bool present;
    string name;
    int nos;
    int *v;

    // ctor: Default ctor: assigns garbage value
    // no khokhla student
    Student()
    {
        cout << "Student ctor called" << endl;
    }

    // paremeterized ctor
    Student(int id, int age, bool present, string name, int nos, string gf)
    {
        this->id = id;
        this->age = age;
        this->present = present;
        this->name = name;
        this->nos = nos;
        this->gf = gf;
        this->v = new int(10);
        cout << "Student paremeterized ctor called" << endl;
    }

    Student(int id, int age, bool present, string name, int nos)
    {
        this->id = id;
        this->age = age;
        this->present = present;
        this->name = name;
        this->nos = nos;
        cout << "Student paremeterized ctor w/o gf called" << endl;
    }

    // copy ctor
    Student(const Student &srcobj)
    {
        cout << "Student copy ctor called" << endl;
        this->name = srcobj.name;
        this->age = srcobj.age;
        this->gf = srcobj.gf;
        this->nos = srcobj.nos;
        this->present = srcobj.present;
        this->id = srcobj.id;
    }

    // getter / setter
    string getGfName()
    {
        return gf;
        // return this->gf;
    }

    void setGfName(string gf)
    {
        this->gf = gf;
    }

    void study()
    {
        cout << "studying" << endl;
    }
    void sleep()
    {
        cout << "sleeping" << endl;
    }
    void bunk()
    {
        cout << "bunking" << endl;
    }

    // ~Student()
    // {
    //     cout << "Student dtor called" << endl;
    //     delete v;
    // }

private:
    void gfchatting()
    {
        cout << "Chatting" << endl;
    }

    void cheating()
    {
        cout << "Cheating" << endl;
    }
};

int main()
{
    // cout << sizeof(Student) << endl;
    // Student s1;

    // Student s2(1, 12, 1, "Chota Bheem", 1, "Chutki");
    // cout << s2.name << endl;
    // cout << s2.id << endl;

    // Student s3(2, 15, 0, "Lokesh", 5);
    // cout << s3.name << endl;

    // // alocating on heap
    // Student *s4 = new Student(3, 34, 1, "Chintu", 6);
    // cout << s4->name << endl;
    // cout << (*s4).name << endl;

    // delete s4; // no LEAK

    // s1.name = "Goli";
    // s1.age = 12;
    // s1.id = 1;
    // s1.nos = 5;
    // s1.present = 1;

    // Student s2;
    // s2.name = "Chota Bheem";
    // s2.age = 11;
    // s2.id = 2;
    // s2.nos = 1;
    // s2.present = 0;

    // copy ctor
    // Student s1(1, 12, 1, "Chota Bheem", 1, "Chutki");
    // Student s2 = s1;
    // Student s2(s1);

    // Student s2 = s1;

    // cout << s1.name << endl;
    // cout << s2.name << endl;

    Student s1(1, 12, 1, "Chota Bheem", 1);
    cout << s1.name << endl;
    cout << s1.getGfName() << endl;

    s1.setGfName("Indumati");

    cout << s1.getGfName() << endl;

    return 0;
}

// NOTES 
// 1. Empty Class
// In case of empty class, sizeof class is 1 byte. System gives one byte for identification of object. It is called as "Empty Class Optimization".

// 2. Access Modifiers
// Access Modifiers are used to restrict the access of class members. There are three types of access modifiers in C++:
// Public: Members of a class that are declared as public are accessible from anywhere in the program.
// Private: Members of a class that are declared as private are accessible only from within the class. By default, all the members of a class are private if not specified.
// Protected: Members of a class that are declared as protected are accessible from the class itself and from the classes derived from that class.

// 3. Getter and Setter
// Getter and Setter methods are used to access and modify the private members of a class. 
// Getter methods are used to access the value of a private member and Setter methods are used to modify the value of a private member.
// Although, we can use getters and setters for public members also, but it is not a good practice as it will increase the complexity of the code.

// 4. Padding and Greedy Allignment
// Padding is done by the compiler to make the size of the structure multiple of the largest data member. This is done to make the access of the data members faster.
// Greedy Allignment: The size of the structure is equal to the size of the largest data member. This is called greedy allignment.

// 5. THIS keyword
// THIS keyword is a pointer that points to the object that invokes the member function. It is used to refer to the current object within a class.
// Basically, this keyword stores the address of the current object, and it is used to access the members of the current object.

// 6. Constructor
// Constructor is a special member function that is called when an object is created. It is used to initialize the object of a class.
// Note that when you create an object of a class, the constructor is called automatically.
// If you create a constructor, the compiler destroys all default constructor.

// 7. Copy Constructor
// Copy Constructor is a type of constructor that is used to create a copy of an object. It is used to initialize a new object as a copy of an existing object.
// Note that when you create an object of a class, the copy constructor is called automatically.
// If you create a copy constructor, the compiler destroys all default copy constructor.
// The default copy constructor performs shallow copy. If you have pointers in your class, you need to create your own copy constructor to perform deep copy.

// 8. Shallow Copy
// Shallow Copy: Shallow copy is a bit-wise copy of an object. A new object is created that stores the address of the memory location of the original object. It does not create a copy of dynamically allocated memory.
// In a way, when you shallow copy an object, you are copying the reference of the memory location of the original object. So, when the original object is deleted, the memory location is also deleted, and the new object will be pointing to a memory location that no longer exists.
// Any changes made to the new object will affect the original object, and vice versa.

// 9. Deep Copy: Deep copy is a process in which the copying process occurs recursively. It means first constructing a new collection object and then, to the extent possible, copying the elements from the original collection to the copy.
// In a way, when you deep copy an object, you are creating a new object and copying the content of the original object to this new object. So, when the original object is deleted, the new object will not be affected.
// Any changes made to the new object will not affect the original object, and vice versa.

// 10. Copy Assignment Operator
// Copy Assignment Operator is a type of assignment operator that is used to assign an object to another object. It is used to copy the content of one object to another object.

// 11. Destructor
// Destructor is a special member function that is called when an object is destroyed. It is used to release the resources that are acquired by the object during its lifetime.
// Destructor is called automatically when an object goes out of scope or is deleted. However, if in you object you have allocated memory dynamically, then you need to delete it in your created destructor.

// 12. Const Keyword
// Const keyword is used to make a variable constant. Once a variable is declared as const, its value cannot be changed.
// In OOPS, const keyword is used to make a member function constant. A constant member function is a member function that does not modify the object for which it is called.
// In a constant member function, you cannot modify any member variables of the class. 

// 13. Static Datatype
// Static is used to define a static member of a class. A static member is shared by all objects of the class. It is used to define the properties of a class that are shared by all objects of the class.
// Static member variables are initialized only once. They are shared by all objects of the class. They are stored in the static memory.
// To access it, you can use the class name followed by the scope resolution operator. Eg: Student::count; // This will give the count, which is a static member of the Student class.

// 14. Static Funtion
// Static function is a member function of a class that can be called even if an object of the class is not created. It is used to define the properties of a class that are shared by all objects of the class.
// A static function can only access static data members and static member functions. It cannot access non-static data members and member functions.

// 15. Initialization List
// Initialization list is used to initialize the data members of a class. It is used to pass the arguments to the constructor of the class.
// Initialization list is used to initialize the data members of a class before the constructor body is executed. It is used to pass the arguments to the constructor of the class.
// Eg: Student(int id, int age, bool present, string name, int nos, string gf): id(id), age(age), present(present), name(name), nos(nos), gf(gf) {}


