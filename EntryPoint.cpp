
#include "Engine/Application.h"
#include "Engine/Core/SubSystems/CommandLineParse/CommandLineParse.h"

int main(int argc, char* argv[]) {
    CommandLineParser::parse(argc, argv);
    bool _initSuccessful = Core::Application::Get()->Initialize();
    if (!_initSuccessful) { return -1;}
    Core::Application::Get()->Run();
    Core::Application::Get()->UnInitialize();
    return 0;
}
