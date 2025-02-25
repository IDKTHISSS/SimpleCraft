#include <glm/glm.hpp>
#include "Engine/Application.h"
#include "Engine/Core/SubSystems/CommandLineParse/CommandLineParse.h"
#include "Game/SimpleCraft.h"


int main(int argc, char* argv[]) {
    CommandLineParser::parse(argc, argv);
    SimpleCraft::Get()->Initialize();
    SimpleCraft::Get()->Run();
    SimpleCraft::Get()->UnInitialize();
    return 0;
}
