#include <iostream>
#include <string>

// 命令模式，将执行的命令剥离出来与系统实现松耦合，可以很好的保存执行过的指令
// 同时又可以很容易的添加新的命令

// 一个指令执行的工厂，管理所有的执行者
class cmdReciver {
public:
    virtual bool doCmd() = 0;
};

class saveReciver : public cmdReciver {
    bool doCmd() {
        std::cout << "do save cmd...\n";
        return true;
    }
};

class changeReciver : public cmdReciver {
    bool doCmd() {
        std::cout << "do change cmd...\n";
        return true;
    }
};

// 所有指令的基类
class command {
public:
    command() {
        if (cmdrec != nullptr) {
            delete cmdrec;
            cmdrec = nullptr;
        }
    }
    virtual ~command(){
        if (cmdrec != nullptr) {
            delete cmdrec;
            cmdrec = nullptr;
        }
    }
    virtual bool exec() = 0;
protected:
    cmdReciver* cmdrec = nullptr;
};

class savecommand : public command {
public:
    savecommand(std::string& _text) : text(_text) {
        cmdrec = new saveReciver;
    }
    bool exec() override {
        std::cout << "execute save " << text << "\n";
        return cmdrec->doCmd();
    }
private:
    std::string text;
};

class changecommand : public command {
public:
    changecommand(std::string& _text) : text(_text) {
        cmdrec = new changeReciver;
    }
    bool exec() override {
        std::cout << "execute change " << text << "\n";
        return cmdrec->doCmd();
    }
private:
    std::string text;
};

// 客户端，指令的调用者
class invoker {
public:
    bool setcommand(command* _cmd) {
        cmd = _cmd;
        return true;
    }
    bool run() const {
        cmd->exec();
        return true;
    }
private:
    command *cmd;
};

int main() {
    invoker client;
    std::string cmd = "123";
    command* cmd1 = new savecommand(cmd);
    client.setcommand(cmd1);
    client.run();
    cmd = "asd";
    cmd1 = new changecommand(cmd);
    client.setcommand(cmd1);
    client.run();
    delete cmd1;
    return 0;
}