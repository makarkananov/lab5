#include "ArgParser.h"

using namespace ArgumentParser;

ArgParser::ArgParser(std::string name_arg) {
  name = name_arg;
}

bool ArgParser::Parse(std::vector<std::string> vec) {
  int32_t initialized = 0;
  for (int i = 1; i < vec.size(); ++i) {
    if (vec[i][0] == '-') { //parsing not positional
      if (vec[i][1] == '-') { //parsing full named args
        if (std::string::npos == vec[i].find("=")) { //parsing full named flags
          if (vec[i].substr(2) == HelpArgument.help_flag.second) { //parsing full named help flag
            HelpArgument.is_initialized = true;
            return true;
          }
          std::string need_to_find = vec[i].substr(2);
          bool success_find = false;

          for (int j = 0; j < FlagArguments.arguments.size(); ++j) {
            if (FlagArguments.arguments[j].first.second == need_to_find) {
              success_find = true;
              FlagArguments.arguments[j].second = true;
              initialized++;
              break;
            }
          }
          if (!success_find) {
            for (int j = 0; j < FlagArguments.stored_arguments.size(); ++j) {
              if (FlagArguments.stored_arguments[j].first.second == need_to_find) {
                success_find = true;
                *FlagArguments.stored_arguments[j].second = true;
                initialized++;
                break;
              }
            }
          }
          if (!success_find) return false;
        } else { //parsing full named str and int
          std::string need_to_find = vec[i].substr(2, vec[i].find("=") - 2);
          std::string value = vec[i].substr(vec[i].find("=") + 1);
          bool success_find = false;
          for (int j = 0; j < StringArguments.arguments.size(); ++j) {
            if (StringArguments.arguments[j].first.second == need_to_find) {
              success_find = true;
              StringArguments.arguments[j].second = value;
              initialized++;
              break;
            }
          }
          if (!success_find) {
            for (int j = 0; j < StringArguments.stored_arguments.size(); ++j) {
              if (StringArguments.stored_arguments[j].first.second == need_to_find) {
                success_find = true;
                *StringArguments.stored_arguments[j].second = value;
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < StringArguments.mult_arguments.size(); ++j) {
              if (StringArguments.mult_arguments[j].first.second == need_to_find) {
                success_find = true;
                StringArguments.mult_arguments[j].second.push_back(value);
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < StringArguments.mult_stored_arguments.size(); ++j) {
              if (StringArguments.mult_stored_arguments[j].first.second == need_to_find) {
                success_find = true;
                (*StringArguments.mult_stored_arguments[j].second).push_back(value);
                initialized++;
                break;
              }
            }
          }

          if (!success_find) {
            for (int j = 0; j < IntArguments.arguments.size(); ++j) {
              if (IntArguments.arguments[j].first.second == need_to_find) {
                success_find = true;
                IntArguments.arguments[j].second = std::stoi(value);
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < IntArguments.stored_arguments.size(); ++j) {
              if (IntArguments.stored_arguments[j].first.second == need_to_find) {
                success_find = true;
                *IntArguments.stored_arguments[j].second = std::stoi(value);
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < IntArguments.mult_arguments.size(); ++j) {
              if (IntArguments.mult_arguments[j].first.second == need_to_find) {
                success_find = true;
                IntArguments.mult_arguments[j].second.push_back(std::stoi(value));
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < IntArguments.mult_stored_arguments.size(); ++j) {
              if (IntArguments.mult_stored_arguments[j].first.second == need_to_find) {
                success_find = true;
                (*IntArguments.mult_stored_arguments[j].second).push_back(std::stoi(value));
                initialized++;
                break;
              }
            }
          }
          if (!success_find) return false;
        }
      } else {
        if (std::string::npos == vec[i].find("=")) { //parsing short named flags
          for (int k = 1; k < vec[i].length(); ++k) {
            char need_to_find = vec[i][k];
            if (need_to_find == HelpArgument.help_flag.first) { //parsing full named help flag
              HelpArgument.is_initialized = true;
              return true;
            }
            bool success_find = false;
            for (int j = 0; j < FlagArguments.arguments.size(); ++j) {
              if (FlagArguments.arguments[j].first.first == need_to_find) {
                success_find = true;
                FlagArguments.arguments[j].second = true;
                initialized++;
                break;
              }
              if (!success_find) {
                for (int j = 0; j < FlagArguments.stored_arguments.size(); ++j) {
                  if (FlagArguments.stored_arguments[j].first.first == need_to_find) {
                    success_find = true;
                    *FlagArguments.stored_arguments[j].second = true;
                    initialized++;
                    break;
                  }
                }
              }
              if (!success_find) return false;
            }
          }
        } else { //parsing short named str and int
          std::string need_to_find = vec[i].substr(1, vec[i].find("=") - 1);
          std::string value = vec[i].substr(vec[i].find("=") + 1);
          bool success_find = false;
          for (int j = 0; j < StringArguments.arguments.size(); ++j) {
            if (StringArguments.arguments[j].first.first == need_to_find[0]) {
              success_find = true;
              StringArguments.arguments[j].second = value;
              initialized++;
              break;
            }
          }
          if (!success_find) {
            for (int j = 0; j < StringArguments.stored_arguments.size(); ++j) {
              if (StringArguments.stored_arguments[j].first.first == need_to_find[0]) {
                success_find = true;
                *StringArguments.stored_arguments[j].second = value;
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < StringArguments.mult_arguments.size(); ++j) {
              if (StringArguments.mult_arguments[j].first.first == need_to_find[0]) {
                success_find = true;
                StringArguments.mult_arguments[j].second.push_back(value);
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < StringArguments.mult_stored_arguments.size(); ++j) {
              if (StringArguments.mult_stored_arguments[j].first.first == need_to_find[0]) {
                success_find = true;
                (*StringArguments.mult_stored_arguments[j].second).push_back(value);
                initialized++;
                break;
              }
            }
          }

          if (!success_find) {
            for (int j = 0; j < IntArguments.arguments.size(); ++j) {
              if (IntArguments.arguments[j].first.first == need_to_find[0]) {
                success_find = true;
                IntArguments.arguments[j].second = std::stoi(value);
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < IntArguments.stored_arguments.size(); ++j) {
              if (IntArguments.stored_arguments[j].first.first == need_to_find[0]) {
                success_find = true;
                *IntArguments.stored_arguments[j].second = std::stoi(value);
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < IntArguments.mult_arguments.size(); ++j) {
              if (IntArguments.mult_arguments[j].first.first == need_to_find[0]) {
                success_find = true;
                IntArguments.mult_arguments[j].second.push_back(std::stoi(value));
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < IntArguments.mult_stored_arguments.size(); ++j) {
              if (IntArguments.mult_stored_arguments[j].first.first == need_to_find[0]) {
                success_find = true;
                (*IntArguments.mult_stored_arguments[j].second).push_back(std::stoi(value));
                initialized++;
                break;
              }
            }
          }
          if (!success_find) return false;
        }
      }
    } else { //positional arguments parsing
      bool success_find = false;
      if (StringArguments.positional_argument != "") {
        std::string need_to_find = StringArguments.positional_argument;
        std::string value = vec[i];
        for (int j = 0; j < StringArguments.mult_arguments.size(); ++j) {
          if (StringArguments.mult_arguments[j].first.second == need_to_find) {
            success_find = true;
            StringArguments.mult_arguments[j].second.push_back(value);
            initialized++;
            break;
          }
        }
        if (!success_find) {
          for (int j = 0; j < StringArguments.mult_stored_arguments.size(); ++j) {
            if (StringArguments.mult_stored_arguments[j].first.second == need_to_find) {
              success_find = true;
              (*StringArguments.mult_stored_arguments[j].second).push_back(value);
              initialized++;
              break;
            }
          }
        }
      } else if (IntArguments.positional_argument != "") {
        std::string need_to_find = IntArguments.positional_argument;
        std::string value = vec[i];
        for (int j = 0; j < IntArguments.mult_arguments.size(); ++j) {
          if (IntArguments.mult_arguments[j].first.second == need_to_find) {
            success_find = true;
            IntArguments.mult_arguments[j].second.push_back(std::stoi(value));
            initialized++;
            break;
          }
        }
        if (!success_find) {
          for (int j = 0; j < IntArguments.mult_stored_arguments.size(); ++j) {
            if (IntArguments.mult_stored_arguments[j].first.second == need_to_find) {
              success_find = true;
              (*IntArguments.mult_stored_arguments[j].second).push_back(std::stoi(value));
              initialized++;
              break;
            }
          }
        }
      }
      if (!success_find) return false;
    }
  }
  if (StringArguments.need_init_cnt + IntArguments.need_init_cnt + FlagArguments.need_init_cnt - initialized > 0)
    return false;
  return true;
}

bool ArgParser::Parse(int amount, char** vec) {
  int32_t initialized = 0;
  for (int i = 1; i < amount; ++i) {
    if (vec[i][0] == '-') { //parsing not positional
      if (vec[i][1] == '-') { //parsing full named args
        if (std::string::npos == std::string(vec[i]).find("=")) { //parsing full named flags
          if (std::string(vec[i]).substr(2) == HelpArgument.help_flag.second) { //parsing full named help flag
            HelpArgument.is_initialized = true;
            return true;
          }
          std::string need_to_find = std::string(vec[i]).substr(2);
          bool success_find = false;

          for (int j = 0; j < FlagArguments.arguments.size(); ++j) {
            if (FlagArguments.arguments[j].first.second == need_to_find) {
              success_find = true;
              FlagArguments.arguments[j].second = true;
              initialized++;
              break;
            }
          }
          if (!success_find) {
            for (int j = 0; j < FlagArguments.stored_arguments.size(); ++j) {
              if (FlagArguments.stored_arguments[j].first.second == need_to_find) {
                success_find = true;
                *FlagArguments.stored_arguments[j].second = true;
                initialized++;
                break;
              }
            }
          }
          if (!success_find) return false;
        } else { //parsing full named str and int
          std::string need_to_find = std::string(vec[i]).substr(2, std::string(vec[i]).find("=") - 2);
          std::string value = std::string(vec[i]).substr(std::string(vec[i]).find("=") + 1);
          bool success_find = false;
          for (int j = 0; j < StringArguments.arguments.size(); ++j) {
            if (StringArguments.arguments[j].first.second == need_to_find) {
              success_find = true;
              StringArguments.arguments[j].second = value;
              initialized++;
              break;
            }
          }
          if (!success_find) {
            for (int j = 0; j < StringArguments.stored_arguments.size(); ++j) {
              if (StringArguments.stored_arguments[j].first.second == need_to_find) {
                success_find = true;
                *StringArguments.stored_arguments[j].second = value;
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < StringArguments.mult_arguments.size(); ++j) {
              if (StringArguments.mult_arguments[j].first.second == need_to_find) {
                success_find = true;
                StringArguments.mult_arguments[j].second.push_back(value);
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < StringArguments.mult_stored_arguments.size(); ++j) {
              if (StringArguments.mult_stored_arguments[j].first.second == need_to_find) {
                success_find = true;
                (*StringArguments.mult_stored_arguments[j].second).push_back(value);
                initialized++;
                break;
              }
            }
          }

          if (!success_find) {
            for (int j = 0; j < IntArguments.arguments.size(); ++j) {
              if (IntArguments.arguments[j].first.second == need_to_find) {
                success_find = true;
                IntArguments.arguments[j].second = std::stoi(value);
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < IntArguments.stored_arguments.size(); ++j) {
              if (IntArguments.stored_arguments[j].first.second == need_to_find) {
                success_find = true;
                *IntArguments.stored_arguments[j].second = std::stoi(value);
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < IntArguments.mult_arguments.size(); ++j) {
              if (IntArguments.mult_arguments[j].first.second == need_to_find) {
                success_find = true;
                IntArguments.mult_arguments[j].second.push_back(std::stoi(value));
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < IntArguments.mult_stored_arguments.size(); ++j) {
              if (IntArguments.mult_stored_arguments[j].first.second == need_to_find) {
                success_find = true;
                (*IntArguments.mult_stored_arguments[j].second).push_back(std::stoi(value));
                initialized++;
                break;
              }
            }
          }
          if (!success_find) return false;
        }
      } else {
        if (std::string::npos == std::string(vec[i]).find("=")) { //parsing short named flags
          for (int k = 1; k < std::string(vec[i]).length(); ++k) {
            char need_to_find = vec[i][k];
            if (need_to_find == HelpArgument.help_flag.first) { //parsing full named help flag
              HelpArgument.is_initialized = true;
              return true;
            }
            bool success_find = false;
            for (int j = 0; j < FlagArguments.arguments.size(); ++j) {
              if (FlagArguments.arguments[j].first.first == need_to_find) {
                success_find = true;
                FlagArguments.arguments[j].second = true;
                initialized++;
                break;
              }
              if (!success_find) {
                for (int j = 0; j < FlagArguments.stored_arguments.size(); ++j) {
                  if (FlagArguments.stored_arguments[j].first.first == need_to_find) {
                    success_find = true;
                    *FlagArguments.stored_arguments[j].second = true;
                    initialized++;
                    break;
                  }
                }
              }
              if (!success_find) return false;
            }
          }
        } else { //parsing short named str and int
          std::string need_to_find = std::string(vec[i]).substr(1, std::string(vec[i]).find("=") - 1);
          std::string value = std::string(vec[i]).substr(std::string(vec[i]).find("=") + 1);
          bool success_find = false;
          for (int j = 0; j < StringArguments.arguments.size(); ++j) {
            if (StringArguments.arguments[j].first.first == need_to_find[0]) {
              success_find = true;
              StringArguments.arguments[j].second = value;
              initialized++;
              break;
            }
          }
          if (!success_find) {
            for (int j = 0; j < StringArguments.stored_arguments.size(); ++j) {
              if (StringArguments.stored_arguments[j].first.first == need_to_find[0]) {
                success_find = true;
                *StringArguments.stored_arguments[j].second = value;
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < StringArguments.mult_arguments.size(); ++j) {
              if (StringArguments.mult_arguments[j].first.first == need_to_find[0]) {
                success_find = true;
                StringArguments.mult_arguments[j].second.push_back(value);
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < StringArguments.mult_stored_arguments.size(); ++j) {
              if (StringArguments.mult_stored_arguments[j].first.first == need_to_find[0]) {
                success_find = true;
                (*StringArguments.mult_stored_arguments[j].second).push_back(value);
                initialized++;
                break;
              }
            }
          }

          if (!success_find) {
            for (int j = 0; j < IntArguments.arguments.size(); ++j) {
              if (IntArguments.arguments[j].first.first == need_to_find[0]) {
                success_find = true;
                IntArguments.arguments[j].second = std::stoi(value);
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < IntArguments.stored_arguments.size(); ++j) {
              if (IntArguments.stored_arguments[j].first.first == need_to_find[0]) {
                success_find = true;
                *IntArguments.stored_arguments[j].second = std::stoi(value);
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < IntArguments.mult_arguments.size(); ++j) {
              if (IntArguments.mult_arguments[j].first.first == need_to_find[0]) {
                success_find = true;
                IntArguments.mult_arguments[j].second.push_back(std::stoi(value));
                initialized++;
                break;
              }
            }
          }
          if (!success_find) {
            for (int j = 0; j < IntArguments.mult_stored_arguments.size(); ++j) {
              if (IntArguments.mult_stored_arguments[j].first.first == need_to_find[0]) {
                success_find = true;
                (*IntArguments.mult_stored_arguments[j].second).push_back(std::stoi(value));
                initialized++;
                break;
              }
            }
          }
          if (!success_find) return false;
        }
      }
    } else { //positional arguments parsing
      bool success_find = false;
      if (StringArguments.positional_argument != "") {
        std::string need_to_find = StringArguments.positional_argument;
        std::string value = vec[i];
        for (int j = 0; j < StringArguments.mult_arguments.size(); ++j) {
          if (StringArguments.mult_arguments[j].first.second == need_to_find) {
            success_find = true;
            StringArguments.mult_arguments[j].second.push_back(value);
            initialized++;
            break;
          }
        }
        if (!success_find) {
          for (int j = 0; j < StringArguments.mult_stored_arguments.size(); ++j) {
            if (StringArguments.mult_stored_arguments[j].first.second == need_to_find) {
              success_find = true;
              (*StringArguments.mult_stored_arguments[j].second).push_back(value);
              initialized++;
              break;
            }
          }
        }
      } else if (IntArguments.positional_argument != "") {
        std::string need_to_find = IntArguments.positional_argument;
        std::string value = vec[i];
        for (int j = 0; j < IntArguments.mult_arguments.size(); ++j) {
          if (IntArguments.mult_arguments[j].first.second == need_to_find) {
            success_find = true;
            IntArguments.mult_arguments[j].second.push_back(std::stoi(value));
            initialized++;
            break;
          }
        }
        if (!success_find) {
          for (int j = 0; j < IntArguments.mult_stored_arguments.size(); ++j) {
            if (IntArguments.mult_stored_arguments[j].first.second == need_to_find) {
              success_find = true;
              (*IntArguments.mult_stored_arguments[j].second).push_back(std::stoi(value));
              initialized++;
              break;
            }
          }
        }
      }
      if (!success_find) return false;
    }
  }
  if (StringArguments.need_init_cnt + IntArguments.need_init_cnt + FlagArguments.need_init_cnt - initialized > 0)
    return false;
  return true;
}

StrArgs& ArgParser::AddStringArgument(char short_form, std::string long_form, std::string description) {
  StringArguments.arguments.push_back({{short_form, long_form}, ""});
  StringArguments.arguments_description.push_back(description);
  StringArguments.need_init_cnt += 1;

  return StringArguments;
}
StrArgs& ArgParser::AddStringArgument(std::string long_form, std::string description) {
  StringArguments.arguments.push_back({{'-', long_form}, {}});
  StringArguments.arguments_description.push_back(description);
  StringArguments.need_init_cnt += 1;

  return StringArguments;
}

IntArgs& ArgParser::AddIntArgument(char short_form, std::string long_form, std::string description) {
  IntArguments.arguments.push_back({{short_form, long_form}, {}});
  IntArguments.arguments_description.push_back(description);
  IntArguments.need_init_cnt += 1;

  return IntArguments;
}
IntArgs& ArgParser::AddIntArgument(std::string long_form, std::string description) {
  IntArguments.arguments.push_back({{'-', long_form}, {}});
  IntArguments.arguments_description.push_back(description);
  IntArguments.need_init_cnt += 1;

  return IntArguments;
}

FlagArgs& ArgParser::AddFlag(char short_form, std::string long_form, std::string description) {
  FlagArguments.arguments.push_back({{short_form, long_form}, {}});
  FlagArguments.arguments_description.push_back(description);
  FlagArguments.need_init_cnt += 1;

  return FlagArguments;
}
FlagArgs& ArgParser::AddFlag(std::string long_form, std::string description) {
  FlagArguments.arguments.push_back({{'-', long_form}, {}});
  FlagArguments.arguments_description.push_back(description);
  FlagArguments.need_init_cnt += 1;

  return FlagArguments;
}

std::string ArgParser::GetStringValue(std::string arg_name) {
  for (int j = 0; j < StringArguments.arguments.size(); ++j) {
    if (StringArguments.arguments[j].first.second == arg_name) {
      return StringArguments.arguments[j].second;
      break;
    }
  }
  for (int j = 0; j < StringArguments.stored_arguments.size(); ++j) {
    if (StringArguments.stored_arguments[j].first.second == arg_name) {
      return *StringArguments.stored_arguments[j].second;
      break;
    }
  }
  std::cout << "Cannot find the argument" << std::endl;
  exit(1);
}
std::string ArgParser::GetStringValue(std::string arg_name, uint32_t arg_ind) {
  for (int j = 0; j < StringArguments.mult_arguments.size(); ++j) {
    if (StringArguments.mult_arguments[j].first.second == arg_name) {
      return StringArguments.mult_arguments[j].second[arg_ind];
      break;
    }
  }
  for (int j = 0; j < StringArguments.mult_stored_arguments.size(); ++j) {
    if (StringArguments.mult_stored_arguments[j].first.second == arg_name) {
      return (*StringArguments.mult_stored_arguments[j].second)[arg_ind];
      break;
    }
  }
  std::cout << "Cannot find the argument" << std::endl;
  exit(1);
}

int32_t ArgParser::GetIntValue(std::string arg_name) {
  for (int j = 0; j < IntArguments.arguments.size(); ++j) {
    if (IntArguments.arguments[j].first.second == arg_name) {
      return IntArguments.arguments[j].second;
      break;
    }
  }
  for (int j = 0; j < IntArguments.stored_arguments.size(); ++j) {
    if (IntArguments.stored_arguments[j].first.second == arg_name) {
      return *IntArguments.stored_arguments[j].second;
      break;
    }
  }
  std::cout << "Cannot find the argument" << std::endl;
  exit(1);
}
int32_t ArgParser::GetIntValue(std::string arg_name, uint32_t arg_ind) {
  for (int j = 0; j < IntArguments.mult_arguments.size(); ++j) {
    if (IntArguments.mult_arguments[j].first.second == arg_name) {
      return IntArguments.mult_arguments[j].second[arg_ind];
      break;
    }
  }
  for (int j = 0; j < IntArguments.mult_stored_arguments.size(); ++j) {
    if (IntArguments.mult_stored_arguments[j].first.second == arg_name) {
      return (*IntArguments.mult_stored_arguments[j].second)[arg_ind];
      break;
    }
  }
  std::cout << "Cannot find the argument" << std::endl;
  exit(1);
}

bool ArgParser::GetFlag(std::string arg_name) {
  for (int j = 0; j < FlagArguments.arguments.size(); ++j) {
    if (FlagArguments.arguments[j].first.second == arg_name) {
      return FlagArguments.arguments[j].second;
      break;
    }
  }
  for (int j = 0; j < FlagArguments.stored_arguments.size(); ++j) {
    if (FlagArguments.stored_arguments[j].first.second == arg_name) {
      return *FlagArguments.stored_arguments[j].second;
      break;
    }
  }
  std::cout << "Cannot find the argument" << std::endl;
  exit(1);
}

bool ArgParser::Help() {
  return HelpArgument.is_initialized;
}

void ArgParser::AddHelp(char short_form, std::string long_form, std::string description) {
  HelpArgument.help_flag = {short_form, long_form};
  HelpArgument.description = description;
}
void ArgParser::AddHelp(std::string long_form, std::string description) {
  HelpArgument.help_flag = {'-', long_form};
  HelpArgument.description = description;
}

std::string ArgParser::HelpDescription() {
  std::string result;
  result += (name + "\n");
  result += (HelpArgument.description + "\n\n");

  for (int i = 0; i < StringArguments.arguments.size(); ++i) {
    result += ("-" + std::string(1, StringArguments.arguments[i].first.first));
    result += (", --" + StringArguments.arguments[i].first.second);
    result += ("=<string>,  " + StringArguments.arguments_description[i]);
    result += "\n";
  }
  for (int i = 0; i < StringArguments.stored_arguments.size(); ++i) {
    result += ("-" + std::string(1, StringArguments.stored_arguments[i].first.first));
    result += (", --" + StringArguments.stored_arguments[i].first.second);
    result += ("=<string>,  " + StringArguments.stored_arguments_description[i]);
    result += " [stored]";
    result += "\n";
  }
  for (int i = 0; i < StringArguments.mult_arguments.size(); ++i) {
    result += ("-" + std::string(1, StringArguments.mult_arguments[i].first.first));
    result += (",  --" + StringArguments.mult_arguments[i].first.second);
    result += ("=<string>,  " + StringArguments.mult_arguments_description[i]);
    result += " [multi value]";
    result += "\n";
  }
  for (int i = 0; i < StringArguments.mult_stored_arguments.size(); ++i) {
    result += ("-" + std::string(1, StringArguments.mult_stored_arguments[i].first.first));
    result += (", --" + StringArguments.mult_stored_arguments[i].first.second);
    result += ("=<string>,  " + StringArguments.mult_stored_arguments_description[i]);
    result += " [multi value, stored]";
    result += "\n";
  }
  for (int i = 0; i < IntArguments.arguments.size(); ++i) {
    result += ("-" + std::string(1, IntArguments.arguments[i].first.first));
    result += (", --" + IntArguments.arguments[i].first.second);
    result += ("=<int32>,  " + IntArguments.arguments_description[i]);
    result += "\n";
  }
  for (int i = 0; i < IntArguments.stored_arguments.size(); ++i) {
    result += ("-" + std::string(1, IntArguments.stored_arguments[i].first.first));
    result += (", --" + IntArguments.stored_arguments[i].first.second);
    result += ("=<int32>,  " + IntArguments.stored_arguments_description[i]);
    result += " [stored]";
    result += "\n";
  }
  for (int i = 0; i < IntArguments.mult_arguments.size(); ++i) {
    result += ("-" + std::string(1, IntArguments.mult_arguments[i].first.first));
    result += (",  --" + IntArguments.mult_arguments[i].first.second);
    result += ("=<int32>,  " + IntArguments.mult_arguments_description[i]);
    result += " [multi value]";
    result += "\n";
  }
  for (int i = 0; i < IntArguments.mult_stored_arguments.size(); ++i) {
    result += ("-" + std::string(1, IntArguments.mult_stored_arguments[i].first.first));
    result += (", --" + IntArguments.mult_stored_arguments[i].first.second);
    result += ("=<int32>,  " + IntArguments.mult_stored_arguments_description[i]);
    result += " [multi value, stored]";
    result += "\n";
  }
  for (int i = 0; i < FlagArguments.arguments.size(); ++i) {
    result += ("-" + std::string(1, FlagArguments.arguments[i].first.first));
    result += (", --" + FlagArguments.arguments[i].first.second);
    result += ("=<bool>,  " + FlagArguments.arguments_description[i]);
    result += "\n";
  }
  for (int i = 0; i < FlagArguments.stored_arguments.size(); ++i) {
    result += ("-" + std::string(1, FlagArguments.stored_arguments[i].first.first));
    result += (", --" + FlagArguments.stored_arguments[i].first.second);
    result += ("=<bool>,  " + FlagArguments.stored_arguments_description[i]);
    result += " [stored]";
    result += "\n";
  }
  result += "\n";
  result += ("-" + std::string(1, HelpArgument.help_flag.first));
  result += (",\t--" + HelpArgument.help_flag.second);
  result += (" Display this help end exit\n");
  return result;
}