#include "GameGui.h"

int main() {
    //GameGui gameGui(50);
    GameGui gameGui("easy");
    gameGui.eventLoop();
    return 0;
}