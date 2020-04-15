# FileFiller
Fills files with the corresponding values using `@@TAGS@@`. Should work in a similar fashion to CMake's "configure" feature.

The `FileFiller` utility is available as a standalone program and a C++ library you can include in your own project.

Using a Tag mapping string or file that looks like this :
```csv
USER_ID;5;
USER_NAME;"Clovel";
USER_EMAIL;"cd.clovel19@gmail.com";
```
You can configure a file, resulting in the following substitutions :
<table>
<tr>
    <th>
        Input file/string
    </th>
    <th>
        Output file/string
    </th>
</tr>

<tr>
<td>
<pre>
{
    "id": @@USER_ID@@,
    "username": @@USER_NAME@@,
    "email": @@USER_EMAIL@@
}
</pre>
</td>
<td>
<pre>
{
    "id": 5,
    "username": "Clovel",
    "email": "cd.clovel19@gmail.com",
}
</pre>
</td>
</tr>
</table>

## Build
This project uses the CMake build tool. 

To build the project, follow these steps :
```bash
mkdir build
cd build/
cmake ..
make -j$(nproc)
```

The default configuration is "Debug". To build with the "Release" configuration, follow these steps :
```bash
mkdir build
cd build/
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

To launch unit tests, follow these steps :
```bash
mkdir build
cd build/
cmake ..
make -j$(nproc)
ctest -VV       # -VV flag to see printouts. It can be omitted.
```

___

# Executable utility
## Usage
To use the FileFiller, call the program like this : 
```bash
./FileFiller-util <path/to/input/file> <path/to/output/path> <path/to/tag/mapping/file>
```

A help output can be accessed by either calling
```bash
./FileFiller-util --help
```
Or by calling the executable without the correct number of arguments, like this :
```bash
./fileFiller-util
```

## Tag mapping file
A tag mapping file loogs like this :
```csv
TAG1;Value1;
TAG2;Value2;
TAG3;Value3;
```

## Input file
A replacable tag looks like this :
```txt
This sentence contains a replaceable tag : @@REPLACABLE_TAG@@
```

An input file can ultimately look like this :
```txt
I like to eat @@FOOD_1@@ and @@FOOD_2@@ but I don't like @@FOOD_3@@.
```
With a tag mapping file looking like this :
```csv
FOOD_1;apples;
FOOD_2;oranges;
FOOD_3;pears;
```
Resulting in the following output file :
```txt
I like to eat apples and oranges but I don't like pears.
```

## Remove line
If a tag has `@@REMOVE_LINE@@` as it's value, then all lines in the input file containing this tag will be removed in the output.

**WARNING** : The removal of line takes place before replacing the tags.
This means that the "number of replacements" return value of the parse methods only counts replacement AFTER line removals.

Using a Tag mapping string or file that looks like this :
```csv
USER_ID;5;
USER_NAME;"Clovel";
USER_EMAIL;"cd.clovel19@gmail.com";
USER_CODE;@@REMOVE_LINE@@;
```
You can configure a file, resulting in the following substitutions :
<table>
<tr>
    <th>
        Input file/string
    </th>
    <th>
        Output file/string
    </th>
</tr>

<tr>
<td>
<pre>
{
    "id": @@USER_ID@@,
    "username": @@USER_NAME@@,
    "email": @@USER_EMAIL@@
    "usercode": @@USER_CODE&&
}
</pre>
</td>
<td>
<pre>
{
    "id": 5,
    "username": "Clovel",
    "email": "cd.clovel19@gmail.com",
}
</pre>
</td>
</tr>
</table>

___

# FileFiller library
You can use the FileFiller as a library in your own program. To do so, link the FileFiller library to your program.

## Usage
To call the FileFiller in your program, you need two things :
- A tag mapping, with the `std::map<std::string, std::string>` type.
- An imput string, with the `std::string`
  - You can build the string from a file containing tags, using `parseFile`.
  - You can build a string with a `std::string` variable containing tags, and replace those tags with `parseString`


### Static `parseFile` usage
```cpp
std::map<std::string, std::string> map;
map["TAG1"] = "val1";
map["TAG2"] = "val2";
map["TAG3"] = "val3";

const std::string filePath = "/path/to/input/file";
const std::string outputFilePath = "";
std::string outputString = "";

if(0 > parseFile(map, filePath, outputFilePath, outputString)) {
    std::cerr << "[ERROR] parseFile failed" << std::endl;
} else {
    std::cout << "[INFO ] Got output string : " << outputString << std::endl;
}

/* Output file created */
```

### Static `parseString` usage
```cpp
std::map<std::string, std::string> map;
map["TAG1"] = "val1";
map["TAG2"] = "val2";
map["TAG3"] = "val3";

const std::string inputString = "String : @@TAG1@@, @@TAG2@@, @@TAG3@@.";
const std::string outputString = "";

if(0 > parseString(map, inputString, outputString)) {
    std::cerr << "[ERROR] parseString failed" << std::endl;
} else {
    std::cout << "[INFO ] Got output string : " << outputString << std::endl;
}

/* Output file created */
```

### FileFiller class method `parseFile` usage
```cpp
std::map<std::string, std::string> map;
map["TAG1"] = "val1";
map["TAG2"] = "val2";
map["TAG3"] = "val3";

const std::string inputFilePath = "/path/to/input/file";
const std::string outputFilePath = "";
std::string outputString = "";

FileFiller parser(map, inputFilePath, outputFilePath);

if(0 > parser.parseFile(&outputString)) {
    std::cerr << "[ERROR] parseFile failed" << std::endl;
} else {
    std::cout << "[INFO ] Got output string : " << outputString << std::endl;
}

/* Output file created */
```

### FileFiller class method `parseString` usage
```cpp
std::map<std::string, std::string> map;
map["TAG1"] = "val1";
map["TAG2"] = "val2";
map["TAG3"] = "val3";

const std::string inputString = "String : @@TAG1@@, @@TAG2@@, @@TAG3@@.";
const std::string outputString = "";

FileFiller parser(map, inputString);

if(0 > parser.parseString(&outputString)) {
    std::cerr << "[ERROR] parseString failed" << std::endl;
} else {
    std::cout << "[INFO ] Got output string : " << outputString << std::endl;
}

/* Output file created */
```

# Other languages
## C
A Simple API has been added to use this library with a C program.
An example is available in `examples/example-c`.
The example is compiled with the rest of the project.

### Usage in C
To use the C API, you just need to include the C header :
```c
#include "C_FileFiller.h"
```

## Swift
In the `swift` direcotry you will find `FileFiller.swift`, a Swift API for the static `FileFiller` methods.
There is a Swift example Xcode project in `examples/example-swift`.

### Usage in Swift
Once the library and the C header are added to your project, that you have set up the library paths, rpaths and include paths, just call the static methods of the FileFiller class. 
The little subtlety is that you have to specify as an argument the size of the allocated memory for the output string.

Here is an example call to `Filefiller.parseFile` :
```swift
let lResult: (Int32, String) = FileFiller.parseFile(inputFilePath: CommandLine.arguments[1], outputFilePath: CommandLine.arguments[2], tagFilePath: CommandLine.arguments[3], allocationSize: 4096);
```
