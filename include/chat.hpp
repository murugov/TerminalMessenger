#ifndef CHAT_HPP
#define CHAT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <ctime>
#include <cstddef>

const std::string CHAT_FILE = "./shared_chat.txt";

// --- ANSI color codes ---
const std::string RESET   = "\033[0m";
const std::string GRAY    = "\033[90m";
const std::string GREEN   = "\033[32m";
const std::string YELLOW  = "\033[33m";
const std::string CYAN    = "\033[36m";

class Messanger {
private:
    std::string name_;

public:
    // --- Constructor ---
    Messanger(const std::string& name) : name_(name) {}

    // --- Distructor ---
    ~Messanger() = default;
    
    // --- Methods ---
    size_t getFileSize ();
    void listenForMessages ();
};

#endif