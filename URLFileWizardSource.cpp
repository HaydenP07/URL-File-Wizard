//Hayden Price 2026

//IO
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>

//Types
#include <vector>
#include <string>
#include <unordered_map>

//Headers
#include <windows.h>
#include <shlobj.h>

//Misc
#include <cctype>
#include <algorithm>
#include <thread>
#include <chrono>

//Aliases
using String = std::string;

//Classes
class Website {
public:
    String name;
    String link;
    Website() : link(""), name("Unknown_Website") {};
    Website(const String& url) : link(url), name(url2Name(url)) {};

private:
    String url2Name(String url) {
        size_t startPos = url.find("://");
        if (startPos != String::npos) {
            startPos += 3;
        } else {
            startPos = 0;
        };

        if (url.length() >= startPos + 4 && url.substr(startPos, 4) == "www.") {
            startPos += 4;
        };

        size_t endPos = url.find('.', startPos);

        if (endPos != String::npos) {
            String extractedName = url.substr(startPos, endPos - startPos);

            if (!extractedName.empty()) {
                extractedName[0] = std::toupper(extractedName[0]);
            };
            return extractedName;
        };

        return "Unknown_Website";
    };
};

//Functions
String getAppDataPath() {
    namespace fs = std::filesystem;
    char path[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path))) {
        fs::path appDir = fs::path(path) / "URL File Wizard";
        
        if (!fs::exists(appDir)) {
            fs::create_directories(appDir);
        }
        return (appDir / "history.txt").string();
    }
    return "history.txt";
}

void saveHistory(const std::vector<String>& history) {
    String filePath = getAppDataPath();
    std::ofstream outFile(filePath);
    
    if (outFile.is_open()) {
        for (const auto& url : history) {
            outFile << url << "\n";
        }
    }
}

std::vector<String> loadHistory() {
    std::vector<String> history;
    String filePath = getAppDataPath();
    std::ifstream inFile(filePath);
    String line;
    
    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            if (!line.empty()) {
                history.push_back(line);
            }
        }
    }
    return history;
}

void addDestination(std::vector<String>& history, const String& newUrl, size_t maxItems = 5) {
    for (auto it = history.begin(); it != history.end(); ++it) {
        if (*it == newUrl) {
            history.erase(it);
            break;
        }
    }
    
    history.insert(history.begin(), newUrl);
    
    if (history.size() > maxItems) {
        history.resize(maxItems);
    }
    
    saveHistory(history);
}

void lower(String& input){
    for (char& c : input) {
        c = std::tolower(c);
    };
}

void output(String text, String color = "white") {
    static const std::unordered_map<String, String> color2code = {
        {"reset", "\033[0m"},
        {"red", "\033[31m"},
        {"green", "\033[32m"},
        {"yellow", "\033[33m"},
        {"blue", "\033[34m"},
        {"magenta", "\033[35m"},
        {"cyan", "\033[36m"},
        {"white", "\033[37m"}
    };

    lower(color);
	std::cout << color2code.at(color) << text << color2code.at("reset") << "\n";
};

void credits(){
    output("-------------------------------------------------------------------------------");
    output("Hayden Price 2026");
    output("\nURL File Wizard\n");
    output("GitHub: https://github.com/HaydenP07");
    output("LinkedIn: https://www.linkedin.com/in/hayden-price-11452342b/");
    output("Handshake: https://app.joinhandshake.com/profiles/cuagsr");
    output("\nThanks for checking out my app! I hope that you find it useful.", "green");
    output("-------------------------------------------------------------------------------");
};

void generateFile(Website website, String fileDestination){
    fileDestination.erase(std::remove(fileDestination.begin(), fileDestination.end(), '\"'), fileDestination.end());
    String fileName = fileDestination + "\\" + website.name + ".url";
    output("Creating file at -> " + fileName, "yellow");
    std::ofstream outFile(fileName);

    if (outFile.is_open()) {
        outFile << "[InternetShortcut]\n";
        outFile << "URL=" << website.link << "\n";
        outFile << "IconFile=C:\\Windows\\System32\\shell32.dll\n";
        outFile << "IconIndex=13\n";
        outFile.close();
        
        output("Successfully generated " + fileName + "!", "green");
    } else {
        output("Error: Could not create shortcut file.", "red");
    };
};

//Main
int main(){
    SetConsoleTitleA("URL File Wizard");
    
    String inputLink;
    Website website;
    String destinationPath;

    credits();
	output("\nWelcome to URL File Wizard.\n");
	output("This app is used to make files stored locally on your computer that can be used to access websites.");
	output("To begin, paste the link of the website below:");
    std::cin >> inputLink;
    website = Website(inputLink);

    while (true){
        output("\nDoes everything look right? Enter yes if correct, otherwise enter link or name to reenter them.");
        output("Link: " + website.link);
        output("Name: " + website.name);
        String userInput;

        while (true){
            std::cin >> userInput;
            lower(userInput);

            if ((userInput == "yes") || (userInput == "link") || (userInput == "name")){
                break;

            } else {
                output("Please enter a valid input:", "yellow");
            };
        };

        if (userInput == "yes"){
            break;

        } else if (userInput == "link"){
            output("Reenter link:");
            std::cin >> website.link;

        } else if (userInput == "name"){
            output("Reenter name:");
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            std::getline(std::cin, website.name);
        }
    };

    output("\nThanks! Where should this file be stored?");
    std::vector<String> history = loadHistory();

    if (!history.empty()) {
        output("Select a number from your recent destinations, or paste a new location:", "cyan");
        for (size_t i = 0; i < history.size(); ++i) {
            output("  " + std::to_string(i + 1) + ". " + history[i], "white");
        }
        
    } else {
        output("Paste a location below:", "yellow");
    }

    output("");
    
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); 
    std::getline(std::cin, destinationPath);

    if (!history.empty() && destinationPath.length() == 1 && std::isdigit(destinationPath[0])) {
        int choice = destinationPath[0] - '1';
        if (choice >= 0 && choice < static_cast<int>(history.size())) {
            destinationPath = history[choice];
        }
    }

    if (!destinationPath.empty()) {
        addDestination(history, destinationPath);
    }

    output("");
    generateFile(website, destinationPath);

	output("\nThanks for using URL File Wizard!", "cyan");
    output("Press any key to exit...", "yellow");
    system("pause > nul");
};