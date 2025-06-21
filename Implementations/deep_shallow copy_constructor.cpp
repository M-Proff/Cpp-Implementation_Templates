class MyClass {
public:
    int* data;

    MyClass(int val) {
        data = new int(val);
    }

    // No custom copy constructor => shallow copy
    ~MyClass() {
        delete data;
    }
};

int main() {
    MyClass obj1(10);
    MyClass obj2 = obj1; // default copy constructor: shallow copy
}
//-------------------------------------------------------------------------------------

//Deep Copy

class MyClass {
public:
    int* data;

    MyClass(int val) {
        data = new int(val);
    }

    // Custom copy constructor for deep copy
    MyClass(const MyClass& other) {
        data = new int(*other.data); // deep copy
    }

    ~MyClass() {
        delete data;
    }
};
