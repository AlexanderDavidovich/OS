#include <iostream>
#include <memory>
#include <vector>

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() {};
};

class Light {
public:
    void turnOn() { 
        std::cout << "Light is ON\n";
    }
    void turnOff() { 
        std::cout << "Light is OFF\n"; 
    }
};

class TurnOnCommand : public Command {
    Light& light;
public:
    TurnOnCommand(Light& l) : light(l) {}
    void execute() override { 
        light.turnOn(); 
    }
};

class TurnOffCommand : public Command {
    Light& light;
public:
    TurnOffCommand(Light& l) : light(l) {}
    void execute() override { 
        light.turnOff(); 
    }
};

class RemoteControl {
private:
    std::vector<Command*> commands;
public:
    void setCommand(Command* cmd) {
        commands.push_back(cmd);
    }
    void runCommands() {
        for (Command* cmd : commands) {
            cmd->execute();
        }
    }
    void cleanup() {
        for (Command* cmd : commands) {
            delete cmd;
        }
        commands.clear();
    }
};

int main() {
    Light lamp;
    RemoteControl remote;

    remote.setCommand(new TurnOnCommand(lamp));
    remote.setCommand(new TurnOffCommand(lamp));
    remote.setCommand(new TurnOnCommand(lamp));

    remote.runCommands();
    remote.cleanup();

    return 0;
}