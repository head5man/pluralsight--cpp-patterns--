## What is type erasure?
Type erasure is a programming technique by which the wxplicit type information is removed from the program. It is a type abstraction that ensures that the program does not explicitly depend on some of the data types.

#### What problems does type erasure solve
- The code expects certain behavior
- The code is wrtiten in terms of an abstraction that provides this behavior
- Many concrete types can implement this behavior
- All properties of these types that are not relevant to the behavior are erased, starting with the name of the type
- Type erasure separates the interface from the implementation, so does inheritance, but type erasure does not require common base class
- Type erasure is non-intrusive
- External polymorphism (types do not have to be designed for it)
