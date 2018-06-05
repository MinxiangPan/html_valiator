#include "Tag.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <queue>

// Required functions from a4.cpp. Do not remove these.
bool html_is_valid(const std::string& document);

Tag* generate_DOM_tree(const std::string& document);

void determine_visible_objects(Tag* const root);

std::string print_visible_elements(Tag* const root);

Tag* getElementByID(Tag* const root, const std::string& id);

// -------------------------------------------------------------------

// Helper functions for tests. Feel free to add more.
const std::string read_file(const std::string& filename) {
    std::ifstream file(filename, std::ifstream::ate);
    if (!file.is_open()) {
        std::cout << "File: " << filename << " failed to open." << std::endl;
        return 0;
    }
    size_t stringLength = file.tellg();
    file.seekg(0, file.beg);

    char* const data = new char[stringLength + 1];
    data[stringLength] = '\0';
    file.read(data, stringLength);
    file.close();

    const std::string fileContent(data);
    delete[] data;
    return fileContent;
}

bool test_html_is_valid(const bool& validHTML, const std::string& fileContent, const std::string& filename) {
    if (validHTML) {
        if (html_is_valid(fileContent)) {
            std::cout << "Correctly validated the valid file: " << filename << std::endl;
            return true;
        }
        else {
            std::cout << "Incorrectly said the file " << filename << " was invalid when it is actually valid." << std::endl;
            return false;
        }
    }
    else {
        if (!html_is_valid(fileContent)) {
            std::cout << "Correctly detected the invalid file: " << filename << std::endl;
            return true;
        }
        else {
            std::cout << "Incorrectly said the file " << filename << " was valid file when it is actually invalid." << std::endl;
            return false;
        }
    }
}

void cleanup_tree(Tag* root) {
    if (root == nullptr) {
        return;
    }
    std::queue<Tag*> nodesToCleanup;
    nodesToCleanup.push(root);
    while (!nodesToCleanup.empty()) {
        Tag* element = nodesToCleanup.front();
        nodesToCleanup.pop();
        for (Tag* child : element->_children) {
            nodesToCleanup.push(child);
        }
        delete element;
    }
}


// -------------------------------------------------------------------


int main() {
    std::string source_folder = "sample-pages/";
    // Add more files here and whether or not they are valid.
    const std::vector<std::pair<std::string, bool>> sample_files_tests{{"invalid-head-before-html.html", false},
                                                                       {"invalid-div-in-head.html",      false},
                                                                       {"invalid-span-in-head.html",     false},
                                                                       {"invalid-p-in-head.html",        false},
                                                                       {"invalid-br-in-head.html",       false},
                                                                       {"invalid-body-before-head.html", false},
                                                                       {"invalid-id-with-space.html",    false},
                                                                       {"invalid-span-with-span.html",   false},
                                                                       {"invalid-span-with-div.html",    false},
                                                                       {"invalid-span-with-p.html",      false},
                                                                       {"invalid-no-exclamation.html",   false},
                                                                       {"invalid-extra-head.html",       false},
                                                                       {"invalid-extra-body.html",       false},
                                                                       {"invalid-extra-html.html",       false},
                                                                       {"invalid-extra-close-div.html",  false},
                                                                       {"invalid-no-doctype.html",       false},
                                                                       {"invalid-no-title.html",         false},
                                                                       {"invalid-no-title-spaces.html",  false},
                                                                       {"invalid-extra-open-p.html",     false},
                                                                       {"invalid-html-left-open.html",   false},
                                                                       {"valid-span-in-p.html",          true},
                                                                       {"valid-hello.html",              true},
                                                                       {"valid-no-content.html",         true},
                                                                       {"valid-lots-of-spaces.html",     true},
                                                                       {"valid-nested-div.html",         true},
                                                                       {"valid-nested-div-extra.html",   true},
                                                                       {"valid-jason-uber-test.html",    true}};
    bool passed = false;

    for (size_t fileIndex = 0; fileIndex < sample_files_tests.size(); ++fileIndex) {
        const std::string filename = source_folder + sample_files_tests.at(fileIndex).first;
        const std::string fileContent = read_file(filename);
        const bool& validHTML = sample_files_tests.at(fileIndex).second;

        // Run test to check if html file is valid or not.
        if(test_html_is_valid(validHTML, fileContent, filename)) {
            std::cout << "Passed test for " << filename << std::endl;
        }
        else {
            std::cout << "Failed test for " << filename << std::endl;
        }
    }
    
    for (size_t i = 0; i < sample_files_tests.size(); ++i) {
        passed = false;
        const std::string filename = source_folder + sample_files_tests.at(i).first;
        const std::string fileContent = read_file(filename);

        // std::cout << "\"" << fileContent << "\"" << std::endl;

        const bool& validHTML = sample_files_tests.at(i).second;


        if (validHTML) {
            Tag* domTreeRoot = generate_DOM_tree(fileContent);
            determine_visible_objects(domTreeRoot);
            std::cout << "Visible tree contents for file " << filename << ":" << std::endl;
            std::cout << print_visible_elements(domTreeRoot) << std::endl;
            Tag* element = getElementByID(domTreeRoot, "");
            if (element != nullptr) {
                std::cout << "Should return nullptr when empty ID is searched. Got id: \"" << element->_id << "\"" << std::endl;
                if(element->_tagname == Tag::TAGNAME::CONTENT) {
                    std::cout << "Element returned has TAGNAME set to CONTENT." << std::endl;
                }
            }

            
            cleanup_tree(domTreeRoot);
        }
    }

    std::string line = read_file("sample-pages/valid-span-in-p.html");
    Tag* root = generate_DOM_tree(line);
    auto get = getElementByID(root, "cspan");
    if(get != nullptr) {
        std::cout << "\n SPAN ID: " << get->_name + " " + get->_id << std::endl;
    }
    else{
        std::cout << "Something Wrong" << std::endl;
    }

    line = read_file("sample-pages/valid-jason-uber-test.html");
    root = generate_DOM_tree(line);
    get = getElementByID(root,"AreYouStillSure");
    if(get != nullptr) {
        std::cout << "\n Title ID: " << get->_name + " " + get->_id << std::endl;
    }
    else{
        std::cout << "Something Wrong" << std::endl;
    }

    return 0;
}