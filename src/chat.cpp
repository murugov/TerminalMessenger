#include "chat.hpp"

size_t Messanger::getFileSize() {
    std::ifstream file(CHAT_FILE, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        return 0;
    }
    return static_cast<size_t>(file.tellg());
}

void Messanger::listenForMessages() {
    size_t last_size = getFileSize();

    while (true) {
        size_t current_size = getFileSize();

        if (current_size < last_size) {
            last_size = 0;
        }

        if (current_size > last_size) {
            std::ifstream file(CHAT_FILE);
            if (file.is_open()) {
                file.seekg(static_cast<long long>(last_size));
                
                std::string line {};
                while (std::getline(file, line)) {
                    if (line.size() > 10 && line[0] == '[' && line[9] == ']') {
                        std::string time_part = line.substr(0, 10); // "[HH:MM:SS]"
                        std::string rest = line.substr(10);
                        
                        size_t colon_pos = rest.find(':');
                        if (colon_pos != std::string::npos) {
                            std::string name_part = rest.substr(0, colon_pos + 1); // " Name:"
                            std::string msg_part = rest.substr(colon_pos + 1);    // " Message"
                            
                            std::cout << GRAY << time_part << GREEN << name_part << RESET << msg_part << std::endl;
                            continue;
                        }
                    }
                    std::cout << line << std::endl;
                }
                
                last_size = current_size;
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
