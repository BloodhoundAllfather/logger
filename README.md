## About
This is a cross-platform C++ logger class that you can use in your projects. Supports both `char` and `wchar_t`.

## Usage
Add `logger.cpp` and `logger.h` to your project. Then add `#include "logger.h"` into a source file and initialize it:

`logger::init("/home/ec2-user/logger.txt"); // Linux`

`logger::init("C:\\Users\\MyUser\\logger.txt"); // Windows`

Now it's ready to use. You can use 4 functions and pass parameters like using `sprintf`:

`logger::error("ReadFile failed: %d", GetLastError());`

`logger::success("ReadFile was successful: %d", dwReadBytes);`

`logger::info("Debug enabled");`

`logger::log("Entered the SetPrivilege function");`

The `error`, `success` and `info` functions put a string regarding their log type. The `log` function doesn't add anything at the beginning.

You can pass parameters to each function like using `sprintf`.

Sample output:

```
2024-08-21 18:46:09 [Error  ] ReadFile failed: 5
2024-08-21 18:46:09 [Success] ReadFile was successful: 1024
2024-08-21 18:46:09 [Info   ] Debug enabled
2024-08-21 18:46:09 Entered the SetPrivilege function
```

### wchar_t Support
If you want to use `wchar_t` strings, you should call the `init` function with `wchar_t`.

`logger::init(L"/home/ec2-user/logger.txt");`

`logger::error(L"ReadFile failed: %d %ls", GetLastError(), L"FAIL");`

You can use both `char` and `wchar_t` at the same time. But the `init` function should be called separately. You should create a log file using `char` version of `init` function, and create a log file using `whcar_t` version of `init` function.

After this, each type of log will be stored in its log file.

## Compilation
No special library is needed for the compilation. If you add the `logger.cpp` and `logger.h` to your projects, your project will be compiled without any additional effort. But still if you want to compile this project, on Linux:

`g++ main.cpp logger.cpp -o logger`

On Windows:

`cl.exe /Zi /EHsc /nologo /Felogger.exe main.cpp logger.cpp`

On Windows, you should call this with from Visual Studio x64 Command Prompt

