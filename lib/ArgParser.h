#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace ArgumentParser {

class HelpArg{
 public:
  std::string description;
  bool is_initialized = false;
  std::pair<char, std::string> help_flag;
};

class StrArgs {
 public:
  std::string positional_argument = "";
  std::vector<std::pair<std::pair < char, std::string>, std::string>>
  arguments;
  std::vector<std::pair < std::pair < char, std::string>, std::string*>>
  stored_arguments;
  std::vector<std::pair<std::pair < char, std::string>, std::vector<std::string>>>
  mult_arguments;
  std::vector<std::pair < std::pair < char, std::string>, std::vector<std::string>*>>
  mult_stored_arguments;
  std::vector<std::string> arguments_description;
  std::vector<std::string> stored_arguments_description;
  std::vector<std::string> mult_arguments_description;
  std::vector<std::string> mult_stored_arguments_description;
  void Default(const std::string& default_value) {
    arguments[arguments.size() - 1].second = default_value;
    need_init_cnt -= 1;
    arguments_description[arguments_description.size() - 1] += (" [default = " + default_value + "]");
  };
  void StoreValue(std::string& store_value) {
    stored_arguments.push_back({arguments[arguments.size() - 1].first, &store_value});
    arguments.pop_back();
    stored_arguments_description.push_back(arguments_description[arguments_description.size() - 1]);
    arguments_description.pop_back();
  }
  void StoreValues(std::vector<std::string>& store_value) {
    mult_stored_arguments.push_back({mult_arguments[mult_arguments.size() - 1].first, &store_value});
    mult_arguments.pop_back();
    mult_stored_arguments_description.push_back(mult_arguments_description[mult_arguments_description.size() - 1]);
    mult_arguments_description.pop_back();
  }
  StrArgs& MultiValue(uint32_t minArgs = 0) {
    need_init_cnt += minArgs;
    mult_arguments.push_back({arguments[arguments.size() - 1].first, {}});
    arguments.pop_back();
    mult_arguments_description.push_back(arguments_description[arguments_description.size() - 1]);
    arguments_description.pop_back();

    return *this;
  }
  StrArgs& Positional() {
    positional_argument = mult_arguments[mult_arguments.size() - 1].first.second;
    return *this;
  }
  int32_t need_init_cnt = 0;
 private:
};

class IntArgs {
 public:
  std::string positional_argument = "";
  std::vector<std::pair<std::pair < char, std::string>, int32_t>>
  arguments;
  std::vector<std::pair < std::pair < char, std::string>, int32_t*>>
  stored_arguments;
  std::vector<std::pair<std::pair < char, std::string>, std::vector<int32_t>>>
  mult_arguments;
  std::vector<std::pair < std::pair < char, std::string>, std::vector<int32_t>*>>
  mult_stored_arguments;
  std::vector<std::string> arguments_description;
  std::vector<std::string> stored_arguments_description;
  std::vector<std::string> mult_arguments_description;
  std::vector<std::string> mult_stored_arguments_description;
  void Default(int32_t default_value) {
    arguments[arguments.size() - 1].second = default_value;
    need_init_cnt -= 1;
    arguments_description[arguments_description.size() - 1] += (" [default = " + std::to_string(default_value) + "]");
  };
  void StoreValue(int32_t& store_value) {
    stored_arguments.push_back({arguments[arguments.size() - 1].first, &store_value});
    arguments.pop_back();
    stored_arguments_description.push_back(arguments_description[arguments_description.size() - 1]);
    arguments_description.pop_back();
  }
  void StoreValues(std::vector<int32_t>& store_value) {
    mult_stored_arguments.push_back({mult_arguments[mult_arguments.size() - 1].first, &store_value});
    mult_arguments.pop_back();
    mult_stored_arguments_description.push_back(mult_arguments_description[mult_arguments_description.size() - 1]);
    mult_arguments_description.pop_back();
  }
  IntArgs& MultiValue(uint32_t minArgs = 0) {
    need_init_cnt += minArgs;
    mult_arguments.push_back({arguments[arguments.size() - 1].first, {}});
    arguments.pop_back();
    mult_arguments_description.push_back(arguments_description[arguments_description.size() - 1]);
    arguments_description.pop_back();

    return *this;
  }
  IntArgs& Positional() {
    positional_argument = mult_arguments[mult_arguments.size() - 1].first.second;
    return *this;
  }
  int32_t need_init_cnt = 0;
 private:
};

class FlagArgs {
 public:
  std::vector<std::pair<std::pair <char, std::string>, bool>>
  arguments;
  std::vector<std::pair < std::pair < char, std::string>, bool*>>
  stored_arguments;
  std::vector<std::string> arguments_description;
  std::vector<std::string> stored_arguments_description;
  void Default(bool default_value) {
    arguments[arguments.size() - 1].second = default_value;
    need_init_cnt -= 1;
    if(default_value) arguments_description[arguments_description.size() - 1] += (" [default = true]");
    else arguments_description[arguments_description.size() - 1] += (" [default = false]");
  };
  void StoreValue(bool& store_value) {
    stored_arguments.push_back({arguments[arguments.size() - 1].first, &store_value});
    arguments.pop_back();
    stored_arguments_description.push_back(arguments_description[arguments_description.size() - 1]);
    arguments_description.pop_back();
  }
  int32_t need_init_cnt = 0;
};

class ArgParser {
 public:
  ArgParser(std::string name_arg);

  bool Parse(std::vector<std::string> vec);
  bool Parse(int amount, char** vec);

  std::string HelpDescription();
  void AddHelp(char short_form, std::string long_form, std::string description="");
  void AddHelp(std::string long_form, std::string description="");
  bool Help();

  StrArgs& AddStringArgument(char short_form, std::string long_form, std::string description="");
  StrArgs& AddStringArgument(std::string long_form, std::string description="");
  std::string GetStringValue(std::string arg_name, uint32_t arg_ind);
  std::string GetStringValue(std::string arg_name);

  IntArgs& AddIntArgument(char short_form, std::string long_form, std::string description="");
  IntArgs& AddIntArgument(std::string long_form, std::string description="");
  int32_t GetIntValue(std::string arg_name, uint32_t arg_ind);
  int32_t GetIntValue(std::string arg_name);

  FlagArgs& AddFlag(char short_form, std::string long_form, std::string description="");
  FlagArgs& AddFlag(std::string long_form, std::string description="");
  bool GetFlag(std::string arg_name);

 private:
  std::string name;
  HelpArg HelpArgument;
  StrArgs StringArguments;
  IntArgs IntArguments;
  FlagArgs FlagArguments;
};
} // namespace ArgumentParser