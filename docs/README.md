<p align="center">
  <img src="../sugar.png" width="700"/>
</p>

# Sugar.Lang

Sugar is a compiled (transpiled) programming language I started working on a couple of years back. It initially started as a C# project. I transitioned to C++ in an attempt to grow comfortable with the language as this is my first "proper" C++ project.

I aimed to create something simple but useful. Syntactically, sugar inspired by C# but a sweeter version maybe? Personally, I think C# is a wonderful language and while sugar doesn't come close to it in regard of features, I've tried my best at implementing those aspects which I think are fundamental.

## The Basics

### Variables
```c++
int: x;
```

The type of the variable is post fixed with a `:`, followed by the name. Variables may be initialized and you may declare multiple variables at once.
```c++
int: x, y = 10;
```
Although sugar is statically typed, it does let one use the `let` keyword to perform type inference.
```rust
let: x = 10; //type inference to integer
```

### Functions
```c++
int Add(int: x, int: y)
{
    return x + y;
}
```
```c++
int: result = Add(10, 20);
```
Function declarations and calling is similar to that in C# and C++.

### Conditions
Sugar offers `if` conditions only as a control based structure. Sugar also offers C#/Java style ternary expression.
```python
if (condition)
{
    
}
elif (condition2)
{
    
}
else
{
    
}

string: result = 0 % 2 == 0 ? "0 is even" : "0 is odd";
```

### Loops
Sugar offers the `for`, `while` and `do while`.
```c++
while (condition)
{ }

for(int x = 0; x < 10; x++)
{ }

do { } while(condition) 
```

### I/O Functions
Sugar uses the `print`, `println`, and `input` functions for output and input.
```python
print("hello world: ");
string: result = input();
```

## Data Structures

Sugar supports custom data structures: `class`, `struct` and `enum`.

### Memory Implications (`class` vs `struct`)

Sugar is garbage collected since it compiles to CIL. The only difference between a class and a struct in sugar is how they're handled in memory.

| Criteria  | Class                 | Struct                              |
|:---------:|-----------------------|-------------------------------------|
| Creation  | Allocated on the heap | Allocated on the stack              |
| Arguments | Passed by reference   | Passed by value (unless using `ref`) |
| Returning | Returned a reference  | Returns a copy                      |

```cs
class Type
{
    [public] int: x;
    
    [public] void Modify() { x = 10; }
}

let: a = create Type();
let: b = a; // references the same instance

b.Modify();

print(a.x) // prints 10
print(b.x) // prints 10
```

```cs
struct Type
{
    [public] int: x;
    
    [public] void Modify() { x = 10; }
}

let: a = create Type();
let: b = a; // creates a copy (even without explicitly using `create`)

a.Modify(); // the original is modified, the copy is unchanged.

print(a.x) // prints 10
print(b.x) // prints 0
```

### Built In Types
These data types are built into sugar:
1. Integers: `short [signed 2 bytes]`, `int [signed 4 bytes]`, `long [signed 8 bytes]`
2. Floating Point: `float [signed 7 digit precision]`, `double [signed 15 digit precision]`
3. Characters, Booleans and Strings: `char`, `bool` and `string`. Strings are immutable.
4. Arrays, Lists, Dictionaries and Tuples: `array`, `list`, `dictionary` and `tuple`.
5. Func and Action: `func` and `action`.
6. Nullable: `nullable` represents nullable value types.
7. Exception: `exception` represents run time exceptions that can be thrown.
8. Math: `math` is a static class that defines mathematical constants and functions.
9. Object: `object` is the base object reference for any type (as in C#).

#### Collections

Sugar supports the collections mentioned above.
1. `array`: 
```c++
let: collection = create array<int>(3);

collection[2] = 3;
print(collection[2]);
```
2. `list`: 
```c++
let: collection = create list<int>();

collection.Add(5);
print(collection[0]);
```

- You may create arrays and lists using the { } expression too
```
let: array = create array<int> { 1, 2, 3 };
let: list = create list<int> { 1, 2, 3, 4, 5 };
```

3.  `dictionary`:
```c++
let: collection = create dictionary<int, string>();

collection.Add(10, "ten");
print(collection[10]);
```

4.  `tuple`:
```c++
let: collection = create tuple<int, string>(1, "one");

print(collection.Element1);
print(collection.Element2);
```

A tuple is a value type in Sugar.

#### Nullable
```cs
let: nullableInt = create nullable<int>(); // int with value "null"

if (nullableInt.IsNull)
    print("int is null");

print(nullableInt.Value); // will throw an error as the value is "null"
```

> Nullable wraps around value types only and is itself a value type.

#### Exceptions
```cs
let: e = create Exception("something went wrong!");
throw e;
```

> Object creation in sugar is carried out through the `create` keyword. 

#### Delegates (?)
Sugar offers partial delegate functionality using `func` and `action`.
```c++
void HelloWorld(string: message) 
{ 
    print(message);
}

action</* argument types are passed in order of declaration */ string>: helloWorld = funcref</* arguement types in order of declaration */ string>(/* load function from this */ this, HelloWorld);
```

The `funcref` function is used to get the reference to a function. It contains 2 necessary arguments: the object of interest and the name of the function to be called. 

The argument signature is passed in using generic expression. Unfortunately, sugar does not feature the ability to create functions dynamically. 

Delegates may be invoked using the `invoke` function.
```c++
int Add(int x, int y) 
{ 
    return x + y;
}

func</* first arg is the return type */ int, int, int>: add = funcref<int, int>(Add);
int: result = invoke(add, 10, 20);
```
> Sugar technically supports generics, but only for built-in types and functions.

### Enums
Enums in sugar are a collection of immutable constant integers. Members are initialised to compile time constant values.
```cs
enum EncodingBase
{
    Binary = 2,
    Octal = Binary << 2,
    Hex = Binary << 3,
    Base64 = Binary << 5
}
```

Enums implicitly define bitwise operations and an explicit conversion to their integer value.

## Describers
Taking inspiration from C#'s attributes, which I adore, sugar has describers.
```cs
[public]
class Human
{
    [public] int: age;
    [public] string: name;
    
    [public, static]
    Human CreateHuman(string: name)
    {
        let: human = create Human();
        human.name = name;
        human.age = 0;
        return human;
    }
}
```
Describers can contain the following keywords:
1. `static`: Declares a member static.
2. `public`: An access specifier for public items.
3. `private`: An access specifier for private items.


4. `const`: A runtime constant.
5. `constexpr`: A compile time constant.


6. `ref`: Allows reference like behaviour with structs.

### `const` and `constexpr`

`const` is used to guarantee runtime constancy. It's implications differ based on context:

1. Global Fields: `const` enforces that a global field can only be assigned to in the constructor or through inline initialisation.
2. Function Arguments: `const` enforces a function argument cannot be assigned to.

In both cases this only enforces assignment, not immutability.

`constexpr` must be initialised to a compile time constant and enforces immutability. They can only be primitives or strings. It's also worth noting these values are implicitly static. 

### The `ref` keyword 

`ref` is special in sugar because it lets you avoid struct copying, this is useful with have large structs. 
The `ref` function is used to obtain references of values. It expects one argument which must be a variable.

```cs
let: x = 20;
[ref] int: y = ref(x); 

y = 10;
print(x); // prints 10
```

A referenced struct is treated as a different data type. `copy` is used to create a value copy of the reference.

A few more rules with references:
1. References must be initialized and cannot be reassigned. This ensures validity of lifetimes.
2. Member fields and properties cannot be of a referenced struct type and functions cannot return a reference type.

```cs
int FunctionDescribers([ref] int: x)
{
    return copy(x = 10);
}

let: a = 20;
let: b = PassByReference(a);

print(++b); //prints 11
print(a); //prints 10
```

References will inherit functions, fields and indexers defined by their base class. They do not however inherit any operator or cast overloads, to use them `copy` must be called to explicitly dereference and create a value.

## Properties
Sugar lets you customise member fields using properties. A rather basic implementation:
```cs
[public] int: x { get; [private] set; }
```
- A public get, private set property. It can be accessed anywhere but changed only in the implementation of the structure it's defined in
```cs
[private] int: x { [public] get; [public] set; }  // a private get set property
```
- In case of conflicts like above, the describer on the field definition is given preference.
```cs
list<int> values = create list<int>();
[public] int: Count { get { return values.Count; } }
```
- Accessors can define bodies. the `set` accessor implicitly define the `value` parameter to represent the value assigned.
#### Special Cases
The absence of a body in get only and set only properties can lead to special cases.
```cs
[public] int: x { get; }
```
- Creates a runtime constant that can only be initialised.
```cs
[public] int: x { set; }
```
- A set only property. This is essentially the same thing as a function.

## Special Functions
Sugar features functions for cast overloading, operator overloading, indexers and constructors.

```cs
struct Complex
{
    float: real { [public] get; [private] set; }
    float: imaginary { [public] get; [private] set; }
    
    [public]
    constructor() 
    {
        real = imaginary = 0;
    }

    [public]
    indexer float (int: index) // allows instances of complex to be indexed using []
    {
        get { return index == 0 ? real : imaginary; }
        [private] set { if (index == 0) real = value; else imaginary = value; }
    }
    
    [public, static]
    explicit string(Complex: person) //allows the explicit conversion of complex to a string, internally called by tostring() and format()
    {
        return format("{0} + {1}j", real, imaginary);
    }
    
    [public, static]
    implicit float(Complex: person) //allows the implicit conversion of complex to a float
    {
        return math.pow(real * real + imaginary * imaginary, 0.5);
    }
    
    [public, static]
    operator Complex +(Complex: a, Complex b) //allows the usage of + operator between two complexs
    {
        Complex: complex = create Complex();
        
        complex.real = a.real + b.real;
        complex.imaginary = a.imaginary + b.imaginary;
        
        return complex;
    }
}
```
Cast and operator overloads must be public and static. Constructors may be static but a class can only define one parameterless static constructor. Indexers, however, cannot be static. All structures have a default string conversion and constructor unless specified.

## Import Statements
Sugar defaults the directory structure as the project structure. Import statements are used to navigate this structure using relative file paths.
```java
import "..directory.sub_directory.file.Class";
```
```java
import "..directory.sub_directory.file.Class";

//code

let: x = create Class(param1, param2);
```
Importing a directory imports all files whereas importing a file imports all public structures within it. You may also import a specific public structure.

## Questions ?!
So yes there a few things here. No try-catch-finally blocks, no switch statements, no generics and no destructors.

But the big question: What about OOP? In the original C# version it was included. But even with CILs amazing features I realised I was in over my head and took it out of this version.

Will I add it? Maybe but sugar is functional. I'm not an OOP skeptic, I love it on the contrary. But it was too much for this project.
That's not to say there's no chance of me revisiting it in the future. Here's the syntax I had planned for generics and OOP:
```cs
interface IArea<TDimension : INumeric> 
{
    [public] TDimension Area();
}

class Shape<TDimension : INumeric> : IArea<TDiemsion>
{
    [public] string: name { [public] get; }
    
    [protected]
    constructor(string: name) 
    {
        this.name = name;
    }
    
    [public, abstract]
    TDimension Area();
}

class Square : Shape<int>
{
   [private] int side;
   
   [public]
   constructor(string: name, int: side) : super(name)
   {
       this.side = side;
   }    
   
   [public, override] int Area() { return side * side; }
}
```
