#include "chat.hpp"

int main() {
    Messanger messanger ("RT_messanger");
    
    std::string name {};
    std::cout << CYAN << "Enter your nickname: " << RESET;
    std::getline(std::cin, name);

    if (name.empty()) name = "Anonymous";

    std::cout << "\n" << YELLOW << "=== Welcome, " << name << "! ===" << RESET << "\n\n";

    std::thread reader(&Messanger::listenForMessages, &messanger);
    reader.detach(); 

    std::string message {};
    while (std::getline(std::cin, message)) {
        if (!message.empty()) {
            std::ofstream file(CHAT_FILE, std::ios::app);
            if (file.is_open()) {
                std::time_t now = std::time(nullptr);
                char time_str[9];
                std::strftime(time_str, sizeof(time_str), "%H:%M:%S", std::localtime(&now));

                file << "[" << time_str << "] " << name << ": " << message << "\n";
                file.close();
            }
        }
    }
    return 0;
}
