Creating a module is a straight forward process. 
All of your code for this module will be self contained in a single header.

This guide assumes you already have a development environment setup following [this](prequisites.md) page.

Now create a file in the `ImplantFramework/lib/source/modules` folder. 
Your file must follow the naming convention `<target os>_<name of your module>.hpp`.
For example `windows_ping.hpp` or `linux_ping.hpp`. 

Next place this starter module code in your file:

```cpp
/** @file target_example.hpp
 * @brief Contains implementation for the Example module
 * @author My name
 */
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_MODULES_TARGET_EXAMPLE_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_MODULES_TARGET_EXAMPLE_HPP_
#include "module.hpp"
#include "module_factory.hpp"

namespace hivemind_lib {
/**
 * @brief Struct for the parsing arguments to this module.
 */
struct ExampleArgParse {
  std::string some_string{};
};

/**
 * @brief An Example module to show people how to make one.
 */
class TargetExampleModule : public Module {
 public:
  ModuleInfo Init() override{
    // Create this struct to describe a function in your module. One for each exported function.
    struct ModuleFuncInfo module_func_info;
    // Fill in the struct. One for each exported function.
    module_func_info.param_names.emplace_back("SomeParam");
    module_func_info.param_types.emplace_back("String");
    module_func_info.module_func_name = "SomeFunction";
    module_func_info.module_func_desc = "SomeFunction's description";
    module_func_info.param_num = 1;

    // Fill in this struct to describe your module.
    this->mod_info_.module_funcs.push_back(module_func_info);
    this->mod_info_.module_name = "EXAMPLE";
    this->mod_info_.module_desc = "An example module";

    // Setup the safe pointer to all of your exported functions.
    // All functions are of this type and take a single argument (the placeholder)
    std::function<std::string(std::string)> f = std::bind(&TargetExampleModule::YourFunction, this, std::placeholders::_1);

    // Place the function in the function map.
    this->func_map_.insert({"SOME_FUNCTION", f});
    this->timeout_map_.insert({"SOME_FUNCTION", 60}); // In seconds
    
    // Always return this
    return this->mod_info_;
  }

  // An example function, all functions need to only take in a string
  std::string YourFunction(std::string json) {
    auto args = ParseData<ExampleArgParse>(std::move(json));
    return "";
  }

  TargetExampleModule() = default;
};


// Required for the system to be able to use your module. Registers it in the global module factory.
REGISTER_MODULE_FACTORY(TargetExampleModule, "ExampleModule");

// Required to setup parsing of json into your struct. Name of the struct first then all it's members in order.
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ExampleArgParse, some_string);

}
#endif
```

This starter code is a fully implemented example module that has a function called `YourFunction` which returns an empty string.

1. To make this your own module start by renaming the `TargetExampleModule` to what ever your target and module name is. 
1. Next implement all the functions you want this module to have. These modules can only take in a single string which will be a json string.
They must also return a string. To deal with the hassle of parsing json a json library is included in this framework. 
To pull parameters from the json create a struct like the one in the example code called `ExampleArgParse` and fill it with the things your function takes as an argument. 
Then using `NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ExampleArgParse, some_string);` your struct is ready to parse some json. 
To then parse the string into your struct call `ParseData<ExampleArgParse>(std::move(json))` like in `YourFunction`.
You can then access members of the struct and use them as you want. 
1. The last part required is the `init` function.
This is what informs the Teamserver all about this module, what functions it has, the required parameters for each and the types. 
First fill out a `ModuleFuncInfo` for each function, the valid parameter types are `String`, `Int`, `Double` and `Bool`. 
Then add these function structs to the `this->mod_info_` struct as well as filling in the rest of the data in the mod_info struct. 
For each function set up a safe pointer to it following the example in the example code. Then add this to the ` this->func_map_` map.

Your module is now complete! Rerun the cmake/make and your module should be ready to use. 