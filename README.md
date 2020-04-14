# FileFiller
Fills files with the corresponding values. Should work like CMake's "configure" feature.

## Build
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

Tour file can ultimately look like this :
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
