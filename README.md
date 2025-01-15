<p align="center">
  <img src="https://github.com/favicon.ico" /> <a href="https://github.com/BloodhoundAllfather/logger">logger</a>
</p>

## About
This is a cross-platform static C++ logger class that you can use in your projects. Supports both `char` and `wchar_t`. It also supports multi-threaded logging.

## Usage
Add `logger.cpp` and `logger.h` to your project. Then add `#include "logger.h"` into a source file and initialize it:

```C++
// the boolean parameter is the debug flag
logger::init("/home/ec2-user/logger.txt", true);     // Linux

logger::init("C:\\Users\\MyUser\\logger.txt", true); // Windows
```

Now it's ready to use. You can use 5 functions and pass parameters like using `sprintf`:

```C++
logger::error("ReadFile failed: %d", GetLastError());
logger::success("ReadFile was successful: %d", dwReadBytes);
logger::info("Debug enabled");
logger::debug("Initialization failed: %d", errno);
logger::log("Entered the SetPrivilege function");
```
The `error`, `success`, `info` and `debug` functions put a string regarding their log type. The `log` function doesn't add anything at the beginning.

The `debug` messages will appear on the log file if only the debug is enabled. You can enable debug using the second parameter of the `init` function, or just use `setDebug` function anytime.

You can pass parameters to each function like using `sprintf`.

Sample output:

```
2024-08-21 18:46:09 [ERROR] ReadFile failed: 5
2024-08-21 18:46:09 [SUCSS] ReadFile was successful: 1024
2024-08-21 18:46:09 [INFO ] Debug enabled
2024-08-21 18:46:09 [DEBUG] Initialization failed: 32
2024-08-21 18:46:09 Entered the SetPrivilege function
```

## wchar_t Support
If you want to use `wchar_t` strings, you should call the `init` function with `wchar_t`.

```C++
logger::init(L"/home/ec2-user/logger.txt", true);

logger::error(L"ReadFile failed: %d %ls", GetLastError(), L"FAIL");
```

You can use both `char` and `wchar_t` at the same time. But the `init` function should be called separately. You should create a log file using `char` version of `init` function, and create a log file using `whcar_t` version of `init` function.

After this, each type of log will be stored in its log file.

## Multi-thread Support
All logging functions use `std::mutex` with `std::lock_guard`. So you can use the logging functions from different threads simultaneously.

## Old GCC Support
The code has been modified to support old versions of GCC like `4.8` that have older version of `GLIBC`. I tested the code on `Redhat 7.9`, `CentOS 7.9` and `Ubuntu 16`.

## Compilation
No special library is needed for the compilation. If you add the `logger.cpp` and `logger.h` to your projects, your project will be compiled without any additional effort. But still if you want to compile this project, on Linux:

`g++ main.cpp logger.cpp -o logger`

On Windows:

`cl.exe /Zi /EHsc /nologo /Felogger.exe main.cpp logger.cpp`

On Windows, you should call this with from Visual Studio x64 Command Prompt

## License
MIT License

Copyright (c) 2025 BloodhoundAllfather

<small>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

</small>