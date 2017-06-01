#pragma once

#include <vector>
#include <functional>


typedef std::function<void(std::vector<std::string>)> CommandType;
typedef std::vector<std::string> ArgVector;

struct Command {
  std::string name;
  size_t numArgs;
  CommandType command;
  bool isMain;

  Command(const std::string &_name, size_t _numArgs, CommandType _command, bool _isMain)
    : name(_name), numArgs(_numArgs), command(_command), isMain(_isMain) {}
};

class InteractiveConsole {
	private:
    std::vector<Command> commands;
    std::string currentlyOpenFilename;

    bool canAcceptOtherCommands;
    bool isRunning;

	public:
    InteractiveConsole()
      : canAcceptOtherCommands(false), isRunning(true) {}

    void AcceptOtherCommands(const std::string&);
    void StopAcceptingOtherCommands();
    void Stop();
    void Loop();

    void AddCommand(const std::string&, size_t, CommandType);
    void SetMainCommands(const std::vector<std::string>&);

    void ListCommands() const;
    std::string GetCurrentFile() const;

  public:
    static size_t ArgToSizeT(const std::string&);
};
