---
title: Creational Design Patterns in C++
markmap:
  colorFreezeLevel: 2
---

<!-- @format -->

## Creational Design Patterns

### Overview

- **Purpose**: Creational patterns focus on object creation mechanisms, trying to create objects in a manner suitable to the situation.
- **Common Goal**: Decoupling the system from the concrete class instantiations and focusing on _what to create_ instead of _how to create_.

### Factory Pattern

- **Definition**: A design pattern that defines an interface for creating objects but lets subclasses alter the type of objects that will be created.
- **When to Use**:
  - When you don’t know ahead of time what type of objects you need.
  - When classes are designed so that they interact with interfaces, not concrete implementations.
- **Real-life Example**:
  - **Vending Machine**: You insert money, and based on your selection, it dispenses a soda, juice, or snack. The vending machine (factory) doesn’t need to know the exact class or type of product you are requesting.
- **Structure**:

  ```cpp
  class Shape {
  public:
      virtual void draw() = 0;
  };

  class Circle : public Shape {
  public:
      void draw() override { /* Draw a circle */ }
  };

  class ShapeFactory {
  public:
      static Shape* createShape(const std::string& type) {
          if (type == "CIRCLE") return new Circle();
          return nullptr;
      }
  };
  ```

### Abstract Factory Pattern

- **Definition**: Interface for creating families of related objects without specifying concrete classes.
- **Real-life Example**: Furniture factory producing modern or Victorian sets.
- **Implementation**:

  - Code:

    ```cpp
    class Button { /* Base class */ };
    class WindowsButton : public Button { /* Windows version */ };
    class MacButton : public Button { /* MacOS version */ };

    class GUIFactory {
    public:
        virtual Button* createButton() = 0;
    };

    class WindowsFactory : public GUIFactory {
    public:
        Button* createButton() override { return new WindowsButton(); }
    };

    class MacFactory : public GUIFactory {
    public:
        Button* createButton() override { return new MacButton(); }
    };
    ```

### Prototype Pattern

- **Definition**: Creating new objects by cloning existing ones (prototypes).
- **Real-life Example**: Cloning a car configuration.
- **Implementation**:

  - Code:

    ```cpp
    class Prototype {
    public:
        virtual Prototype* clone() const = 0;
    };

    class ConcretePrototype : public Prototype {
    public:
        Prototype* clone() const override { return new ConcretePrototype(*this); }
    };
    ```

### Builder Pattern

- **Definition**: Separate the construction of a complex object from its representation.
- **Real-life Example**: Building a custom pizza with different ingredients.
- **Implementation**:

  - Code:

    ```cpp
    class Pizza {
        std::string dough, sauce, topping;
    public:
        void setDough(const std::string& d) { dough = d; }
        void setSauce(const std::string& s) { sauce = s; }
        void setTopping(const std::string& t) { topping = t; }
    };

    class PizzaBuilder {
    public:
        virtual void buildDough() = 0;
        virtual void buildSauce() = 0;
        virtual void buildTopping() = 0;
        virtual Pizza* getPizza() = 0;
    };

    class HawaiianPizzaBuilder : public PizzaBuilder {
        Pizza* pizza;
    public:
        HawaiianPizzaBuilder() { pizza = new Pizza(); }
        void buildDough() override { pizza->setDough("cross"); }
        void buildSauce() override { pizza->setSauce("mild"); }
        void buildTopping() override { pizza->setTopping("ham+pineapple"); }
        Pizza* getPizza() override { return pizza; }
    };
    ```

### Singleton Pattern

- **Definition**: Ensures a class has only one instance and provides a global point of access.
- **Real-life Example**: A single printer spooler managing all print jobs.
- **Implementation**:

  - Code:

    ```cpp
    class Singleton {
    private:
        static Singleton* instance;
        Singleton() {} // Private constructor
    public:
        static Singleton* getInstance() {
            if (!instance)
                instance = new Singleton();
            return instance;
        }
    };

    Singleton* Singleton::instance = nullptr;
    ```

## Copy vs Shallow Copy

### Shallow Copy

- **Definition**: Copies values but not objects pointed to by pointers.
- **Example**: Copying a struct with pointers only replicates the pointers.

### Deep Copy

- **Definition**: Copies all fields and makes new copies of dynamically allocated memory.
- **Example**: Duplicating objects for all dynamically allocated members.

## Pointers Deep Dive

### Basics

- **Definition**: Variables that store memory addresses.
  - **Example**: `int* p = &var;` stores the address of `var` in `p`.

### Pointer Arithmetic

- **Definition**: Performing arithmetic operations on pointers.
  - **Example**: `p++` moves the pointer to the next memory location.

### Smart Pointers

- **Definition**: Pointers that manage memory automatically (e.g., `std::shared_ptr`, `std::unique_ptr`).
