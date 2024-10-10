#include "startmusic.h"
#include <cstdlib>
#include <string>
#include <filesystem>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace fs = std::filesystem;

void startBackgroundMusic(const char* audioFile) {
    fs::path execPath = fs::current_path() / "playAudio.py";
    fs::path audioPath = fs::current_path() / audioFile;

    std::string command;
#ifdef _WIN32
    command = "start /B python \"" + execPath.string() + "\" play \"" + audioPath.string() + "\"";
#else
    command = "python \"" + execPath.string() + "\" play \"" + audioPath.string() + "\" &";
#endif

    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Failed to start background music. Error code: " << result << std::endl;
    }
}

void stopBackgroundMusic() {
    fs::path execPath = fs::current_path() / "playAudio.py";

    std::string command = "python \"" + execPath.string() + "\" stop";
    system(command.c_str());
}