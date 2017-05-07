# Code Style

## Naming conventions

* File names: Pascal_Case
* Folder names: Pascal_Case

* Class names: Pascal_Case
* Struct names: Pascal_Case
* Class members: m_camelCase
* Class non-owning pointers: m_pCamelCase

* Functions: camelCase
* Local variables: camelCase

* Namespaces: Pascal_Case

* Constants: SCREAMING_SNAKE_CASE

## Class Style

```C++
class Foo_Bar
{
    public:
        Foo_Bar();

        void foo();
        void bar();

    protected:
        void barFoo();

    private:
        void fooBar();

        int m_number;
};
```

* Public functions and members at top, protected in middle, private at bottom
* Notice a space between the final class member/function and the next accessor!
* Private members must be prefixed with "_m"

* Initilzation lists:

```C++
Foo::Foo(int x, int y)
:   m_x (x)
,   m_y (y) { }
```

## Namespaces

* NO `using namespace std;` Your pull request ***will*** be denied if that is included.
* Namespaces should be PascalCase
* Nested namespaces:

```C++
namespace Foo {
namespace Bar
{
    void codeGoesHere()
    {

    }
}}
```

## Includes and Forward Declares order:
* .h file corresponding to this cpp file (if applicable)
* Standard Library Headers
* SFML Headers
* Other includes
* Forward declarations

* Example:
```C++
#include <vector>
#include <memory>
#include <thread>
#include <mutex>

#include <SFML/System/Clock.hpp>

#include "../Physics/AABB.h"

#include "Chunk/CSection.h"
#include "Chunk/CMap.h"
#include "World_Settings.h"

namespace Renderer {  class Master; }
class Player;
class Camera;

class World
{
//etc..
```

## Constants
* Do not use C-Style "defines" for constants.
* Use constexpr instead. It is compile-time determined just like #define is.
* Functions can be marked as "constexpr" as well.

## Functions

* Primitives can be passed by value, or reference
* Objects pass as either const reference (or reference), and NEVER BY VALUE
* Indent style:

```C++
bool functionName(int arg1, const std::string& arg2)
{
    if (arg1 > 5)
    {
        std::cout << arg2 << "\n";
        return true;
    }
    return false;
}
```

* For setter functions, use R-Value references and move scematics eg

```C++
void Foo:setString(std::string&& str)
{
    m_string = std::move(str);
}
```

## Slash

* Don't use the `\`, it can cause errors on Linux. Correct use:
```C++
#include <SFML/Graphics.hpp>
```

* This goes for strings as file paths too!

```C++
    std::string filePath = "forward/slashes/so/it/works/cross/platform.png"
```

## Pointers

* Please prefer unique pointers to raw owning pointers
```C++
int* x = new int(5); //No!
auto y = std::make_unique<int>(5) //Yes!
```

* If you have to use "new", then you are probably doing something wrong.
* Only case raw pointers are fine is if they are a pointer to a variable (So a non-owning pointer)

## Enums
* Use enum class, not regular enums!
