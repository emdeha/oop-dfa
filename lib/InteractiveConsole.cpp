#include "./InteractiveConsole.h"

#include <algorithm>
#include <cstdio>
#include <sstream>
// TODO: It's not a good practice to output stuff to stdout from libs
#include <iostream>

void InteractiveConsole::AcceptOtherCommands(const std::string &filename) {
  canAcceptOtherCommands = true;
  currentlyOpenFilename = filename;
}
void InteractiveConsole::StopAcceptingOtherCommands() {
  canAcceptOtherCommands = false;
  currentlyOpenFilename = "";
}

void InteractiveConsole::Stop() {
  isRunning = false;
}

void InteractiveConsole::Loop() {
  std::cout << "DFA 0.0.0\n";

  std::string cmdLine;
  while (isRunning) {
    std::cout << "\\> ";
    std::string cmdName;
    std::vector<std::string> cmdArgs;
    std::cin >> cmdName;
    while (!std::cin.eof() && std::cin.peek() != '\n') {
      std::string arg;
      std::cin >> arg;
      cmdArgs.push_back(arg);
    }

    auto cmd = std::find_if(commands.begin(), commands.end(), [&cmdName](Command &cmd)
        { return cmd.name == cmdName; });
    if (cmd == commands.end()) {
      std::cout << "No such command\n";
      continue;
    }

    if (cmdArgs.size() != cmd->numArgs) {
      std::cout << "Expecting " << cmd->numArgs << " arguments; "
                <<  cmdArgs.size() << " passed\n";
      continue;
    }

    try {
      cmd->command(cmdArgs);
    } catch (const std::exception &e) {
      std::cout << "Failed with exception [" << e.what() << "]\n";
    }
    std::cout << "Executed a command with " << cmd->numArgs << " args\n";
  }
}

void InteractiveConsole::AddCommand(const std::string &name, size_t numArgs, CommandType cmd) {
  commands.push_back(Command(name, numArgs, cmd, false));
}
void InteractiveConsole::SetMainCommands(const std::vector<std::string> &cmdNames) {
  for (auto &cName: cmdNames) {
    auto cmd = std::find_if(commands.begin(), commands.end(), [&cName](Command &cmd)
        { return cmd.name == cName; });
    if (cmd != commands.end()) {
      cmd->isMain = true;
    } else {
      std::cout << "Error: No such command" << cName << "\n";
      return;
    }
  }
}
void InteractiveConsole::ListCommands() const {
  std::cout << "Available commands:\n";
  for (auto &c: commands) {
    std::cout << "  " << c.name << " " << c.numArgs << "\n";
  }
}

std::string InteractiveConsole::GetCurrentFile() const {
  return currentlyOpenFilename;
}

size_t InteractiveConsole::ArgToSizeT(const std::string &arg) {
  size_t properArg;
  std::sscanf(arg.c_str(), "%zu", &properArg);
  return properArg;
}
