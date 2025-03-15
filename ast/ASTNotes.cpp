// Object Oriented Programming in C++

/** 
 ** Constructors and Destructors
*
** Virtual Destructors and why they should be mandatory if inheritance is
** intended.
* As already discussed, the `virtual` keyword enables runtime polymorphism.
* A virtual destructor is required if inheritance is intended, in order to
* ensure proper clean up of objects once they are no longer in use.
* 
* For example,
* class Base {
*      ~Base() {
*          std::cout << "Base destructor\n";
*      }; // no virtual destructor
* }
* 
* class Derived : public Base {
*      ~Derived() {
*          std::cout << "Derived destructor\n";
*      }; // no overriding
* }
* 
* int main() {
*      Base* ptr = new Derived();
*      delete ptr; // destructor of Base class is called only
*      return 0;
* }
* 
* Output:
* Base destructor
* 
* Why does this happen?
* This happens because the destructor in the Base class is statically
* bound (resolved at compile time).
* This means that the compiler does not follow a vptr to dynamically
* dispatch destructor definitions correctly, leading to memory leaks.
* 
* (How memory leaks? Resources unique to Derived class may not be clean)
* 
* Solution: Virtual destructor
* With virtual destructors, the copmiler follows vptr and the vtable,
* dynamically dispatching the correct destructor for the object's class.
* 
* Note that the parent class's destructor always exists implictly inside
* the child's destructor, regardless of virtual keyowrd or override.
* 
* Let's look at an example:
* if class MoreDerived inherits Derived, and Derived inherits Base:
* 
* MoreDerived -> Derived -> Base
* 
* Then in the MoreDerived destructor, Derived destructor will exist
* implicitly. As will the Base destructor in Derived destructor.
* 
* This ensures proper clean up of objects.
* 
* class Base {
*      virtual ~Base() {
*          std::cout << "Base destructor\n";
*      }; // virtual destructor
* }
* 
* class Derived : public Base {
*      ~Derived() override {
*          std::cout << "Derived destructor\n";
*      }; // overriding
* }
* 
* int main() {
*      Base* ptr = new Derived();
*      delete ptr; // destructor of derived class is called
*      return 0;
* }
* 
* Output:
* Derived destructor
* Base destructor // parent's destructor is also called
* 
* The virtual keyword made it so that Derived class's destructor is
* called. This occured because of vptr that exists because we made
* the destructor virtual.
* 
* You can think of the implications of virtual keyword in any method.
* The class gets a vtable and a vptr after all.
*/

/**
 * Virtual keyword
 * The virtual keyword is used to enable runtime polymorphism.
 * 
 * By defining a method or function virtual, the compiler creates a vtable
 * for the class.
 * 
 * A vtable is a virtual table, which is just an array of pointers that
 * stores the addresses of virtual functions.
 * 
 * Each class that has at least one virtual function gets its own vtable.
 * For example,
 * 
 * class Base {
 *  public:
 *      virtual void show() { cout << "Base show()\n"; }
 * };
 * class Derived : public Base {
 *      void show() override { cout << "Derived show()\n"; }
 * };
 * 
 * int main() {
 *      Base* ptr = new Derived();
 *      ptr->show();
 *      delete ptr;
 * }
 * 
 * Base class has its own vtable.
 * Derived class has its own vtable.
 * 
 * When ptr calls the virtual method "show()", the compiler resolves
 * the function's definition using the vtable.
 * 
 * Each object has a hidden vptr that points to the vtable that belongs
 * to its class's vtable, whether it is derived or not.
 * 
 * For example, the Base class has its associated vtable, and the Derived
 * class has its separate vtable with overridden definition of the virtual
 * function.
 * 
 * So, when ptr->show() is called, the compiler follows to vptr -> vtable
 * looks up the definition of Derived::show() and uses that at runtime.
 * 
 * By "follows the vptr", here is what is meant:
 * The compiler assigns a hidden vptr to the object at object creation,
 * which points to the vtable of the object's class.
 * The reference type does not matter to the vptr, as it always points
 * to the vtable of the object's class.
 * 
 * At runtime, when an overridden virtual function is called, the compiler
 * simply follows the vptr assigned to the object at creation time and
 * uses the definition in the vtable.
 * This is called "dynamic dispatch". The compiler "dispatches" the
 * function based on vptr.
 * 
 * So, for example,
 * 
 * class Base {
 *  public:
 *      virtual void foo() { cout << "Base foo()\n"; }
 * };
 * 
 * class Derived : public Base {
 *      void foo() override { cout << "Derived foo()\n"; }
 * };
 * 
 * int main() {
 *     ?vptr assigned to ptr, points to vtable of Derived class
 *      Base* ptr = new Derived();
 * 
 *     ?this call follows vptr assigned to ptr, uses Derived::show() definition
 *      ptr->show();
 * 
 *      delete ptr;
 * }
 */