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
Sugar uses the `print` and `input` functions for output and input respectively.
```python
print("hello world");
string: result = input();
```

All data types in sugar are converted to strings using the `tostring` function. Sugar also provides built in string formatting using the `format` method.
```js
let: y = format("{0} ate {1}", /* 0th argument */ tostring(7), /* 1st argument */ 9);
print(y); // "7 ate 9"
```
### Data Types
These data types are built into sugar:
1. Integers: `short [signed 2 bytes]`, `int [signed 4 bytes]`, `long [signed 8 bytes]`
2. Floating Point: `float [signed 7 digit precision]`, `double [signed 15 digit precision]`
3. Characters, Booleans and Strings: `char`, `bool` and `string`. Strings are immutable.
4. Arrays, List, Dictionaries and Tuple: `array`, `list`, `dictionary` and `tuple`.
5. Funcs and Action: `func` and `action`.
6. Nullable: `nullable` serves a generic type to create nullable value type equivalents.
7. Exception: `exception` serves to represent compile time exceptions that can be thrown.
8. Math: `math` serves as a built in static class to define mathematical constants and functions.
9. Object: `object` serves as the base object reference for any type (as in C#).

#### Collections

Sugar supports the collections mentioned above.
1. `array`:
```c++
array<int>: collection = { 1, 2, 3, 4 };
collection[3] = 3;
print(collection[3]);
```
2. `list`:
```c++
list<int>: collection = { 1, 2, 3, 4 };
collection.Add(5);
print(collection[4]);
```

3.  `dictionary`:
```c++
let: collection = create dictionary<int, string>();;
collection[10] = "ten";
print(collection[10]);
```

4.  `tuple`:
```c++
let: collection = create tuple<int, string>(1, "one");
print(collection[0]);
print(collection[1]);
```

#### Nullable
```cs
let: nullableInt = create nullable<int>(null);
if (nullableInt == null)
    print("int is null");
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

## Data Structures

Sugar supports custom data structures: `class`, `struct` and `enum`.
1. `enum`: A type that can store multiple compile type constant integer values.
2. `class`: A reference type that is always created on the heap.
3. `struct`: A value type that is always created on the stack.

Sugar is garbage collected since it compiles to CIL.

### Describers
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

4. `ref`: Allows passing a value type by reference into a function.

```cs
void FunctionDescribers([ref] int: x)
{
    x = 10;
}

int: a = 20;
PassByReference(a);

print(a); //prints 10
```

> This behaviour is also applicable when functions are used as delegates

### Properties
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
[public] int: x { get; }
```
- Creates a runtime constant that can only be initialised in a constructor or during creation.
```cs
[public] int: x { set; }
```
- While it compiles, the above has virtually no practical use.

### Special Functions
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
    indexer float (int index) // allows instances of complex to be indexed using []
    {
       get { return index == 0 ? real : imaginary; }
       [private] set { if (index == 0) real = value; else imaginary = value; }
    }
    
    [public, static]
    explicit string(Complex: person) //allows the explicit conversion of complex to a string
    {
        return format(real,"i +", imaginary, "j");
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
Cast and operator overloads must be static. indexers and constructors cannot be. 
> The explicit conversion to a string is internally called by the `tostring` and `format` function. 

### Import Statements
Sugar defaults the directory structure as the project structure. Import statements are used to navigate this structure using relative file paths.
```java
import "..directory.sub_directory.file.Class";
```
```java
import "..directory.sub_directory.file.Class";

//code

let: x = create Class(param1, param2);
```
Importing a directory imports all files whereas importing a file imports all public structures within it.

## Questions ?!
So yes there a few things here. No try-catch-finally statements, no switch statements, no generics, no destructors and may have even noticed that there is no static constructor either.

But the big question: What about OOP? In the original C# version it was included. But even with CILs amazing features I realised I was in over my head and took it out of this version.

Will I add it? Maybe but sugar is functional. I'm not an OOP skeptic, I love it on the contrary. But it was too much for this project.
That's not to say there's no chance of me revisiting it in the future. Here's the syntax I had planned for generics and OOP:
```cs
[public]
interface IArea<TDimension : INumeric> 
{
    [public] TDimension Area();
}

[public, asbtract]
class Shape<TDimension : INumeric> : IArea<TDiemsion>
{
    string: name { [public] get; }
    
    [protected]
    constructor(string: name) 
    {
        this.name = name;
    }
}

[public]
class Square : Shape<int>
{
   [private] int side;
   
   [public]
   constructor(string: name, int: side) : super(name)
   {
       this.name = name;
       this.side = side;
   }    
   
   [public] int Area() { return side * side; }
}
```
