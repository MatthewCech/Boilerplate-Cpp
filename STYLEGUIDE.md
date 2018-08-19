C++ Style Guide
---

#### Indenting
2 spaces are used in lieu of tabs to keep code more compact and consistently spaced across editors. However, if someone is insisting on tabs and won't work on the project otherwise, then tabs should be used because it's often easier for space users to tweak settings to make tabs look consistent than the other way around. A mix of tabs and spaces is quite possibly the worst outcome, and should be avoided at all costs regardless of personal indent opinions.

#### Comments
Single line comments have a space before them to ensure consistent formatting and readability, and to differentiate them from commented out code which has no space.
```c++
// Single line comments

/* 
 * Multi-line comments
 * are to be formatted 
 * like this.
 */

//CommentedOutCode();
```

#### Braces
When braces are present, Allman style is used. Braces should be used to prevent scope confusion. While it's acceptable to omit them for single line statements, statements should never be adjusted to make them one line just to avoid brace usage. Try and avoid nesting single-line statements to help combat bugs.

```c++
if(foo == 1)
  return;

if(bar)
{
  printf("...Hello?\n");
  printf("It's me;\n");
}

if(foo)
{
  if(bar)
    printf("Outer statement has braces, innermost doesn't have to.\n");
}
else
{
  printf("B/c of this, we know this 'else' belongs to the first 'if'!\n");
}
```

#### Conditionals
If a contitional is used, it is to be explained in a comment. Under no circumstance will conditionals be chained together or used in one-line statements to avoid brace usage.
```c++
// Return 5 if derp is true, otherwise return 3.
return derp ? 5 : 3;
```

#### Includes
Includes should only be present if used. To help enforce this, a brief comment detailing what is used from a header file should be placed after each include. Library headers and local headers should be grouped. Larger groups may be labeled if necessary, and file paths should be based on the project root. It's recommended that project-specific headers be placed after library headers.
```c++
// Algorithm Related
#include <algorithm> // find
#include <math.h>    // atan

// Input Processing
#include <string>         // string object
#include <fstream>        // file IO
#include "MyPrint.hpp"    // printing assist
#include "Net/Parser.hpp" // string parsing
```

#### Classes/Structures
Class and Struct declarations should be capitalized.
```c++
class Foo
{
  // ...
};
```

#### Functions
Public functions should be capitalized, whereas private should not be. This is to prevent name conflict between them, and make it recognizable as to which is which.
```c++
class Foo
{
public:
  Bar();

private:
  baz();
};
```

#### Variables
Member variables have an underscore post-fix to differentiate between them and local variables, which start with a lowercase character. Public member variables and global variables should be capitalized. Realistically, an `m` prefix is acceptable for private member variables, but this can get a bit icky if methods and other variables start using a lot of `M`s in their name. Using underscore as a prefix is generally not advisable if you're interacting with any C code, given a lot of larger libraries use single or double underscore to denote internal variables. If used, this can lead to unfortunate and breaking name overlaps.
```c++
class Foo
{
public:
  int FooCount;

private:
  double fooCount_;
}
```

#### Implementation Formatting
Code should be separated into logical chunks, with spaces after variable declarations, after `if`, `for`, and `while` statements, and after groups of associated functions. Blocks of code should be commented with brief explenations.
```c++
// Takes derp objects and converts them to floop objects if possible.
std::vector<Floop *> MyFunction(Derp derp, Floop *floop)
{
  std::vector<Floop *> floopVec;
  int derpSize = derp.Size();
  int counter = 0;

  // Convert derp obj if it evaluates to 42
  for(int i = 0; i < derpSize; ++i)
  {
    Derp tmpDerp = derp.PopFront();

    if(tmpDerp == 42)
      floopVec.pushBack(Floop(tmpDerp, floop[i]));
    else
      ++counter;
  }

  // Warn if low success rate
  if(counter < derpSize / 2 - 1)
    printf("Warning! Less than 50% success rate");

  return floopVec;
}
```
#### Varaible and Function Naming
Variables and functions should be named appropriately without being abbreviated to the point of not being able to understand them. When it doubt, make the name longer and more descriptive. For example, 'a' is not a reasonable variable name if you are using it for something like sound amplitude, whereas 'amplitude' is more appropriate.

Ideally, names go from less to more specific. Instead of two variables called `applesInFoo` and `pearsInFoo`, the names `fooPearsCount` and `fooApplesCount` are preferred because they allow us to narrow down the category the variable falls under from left to right. `Foo` is the part they both share, so we lead with foo, and because we may add other variables to do with Pears later, we put `Pears` in the middle. That way, two new variables, `fooPearsCreated` and `fooApplesCreated` can be added and can follow the same pattern. The bonus of this broad to specific naming style is that intellisense and autocomplete gets faster to use and narrow.

#### File Naming
- Header files should use the `.hpp` extension unless you are explicity able to compile the file in `C`, at which point the `.h` extension is appropriate.
- Template implementation should be placed in a `.tpp` file, then included at the bottom of the corresponding header file.
- Files aside from `main.cpp` should be capitalized.
- No spaces in filenames. Spaces can add unnecessary complications when trying to write out a path.
