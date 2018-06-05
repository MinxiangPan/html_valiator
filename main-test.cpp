//
// Created by pmx97 on 11/5/2017.
//
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stack>
#include "Tag.hpp"
#include "a4.cpp"

using namespace std;


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

int main(){
    vector<string> location {"invalid-no-doctype.html", "invalid-no-title.html", "valid-hello.html", "valid-no-content.html", "valid 01.html", "valid 02.html"};
    vector<bool> valid {false, false, true, true, true, true};
//    cout << html_is_valid(read_file("sample-pages/" + location[4])) << endl;
    for(int i=0; i<6; ++i){
        string filename = "sample-pages/" + location[i];
        string document = read_file(filename);
//        string view = document;
//        superCleanUp(view);
//        cout << view  << " " << valid[i]<< endl;
        if(html_is_valid(document) == valid[i]){
            cout << "File Name: " << location[i] << " is been CORRECTLY detemind" << endl;
        }
        else{
            cout << "File Name: " << location[i] << " is NOT been correctly detemind" << endl;
        }

    }

    Tag html("html", Tag::HTML ,"HTML");
    Tag head("head", Tag::HEAD, "head");
    Tag title("title", Tag::TITLE, "title");

    Tag body("body", Tag::BODY, "body");
    Tag p("p", Tag::P, "p");
    Tag span("span" , Tag::SPAN, "span");
    Tag div("div", Tag::DIV, "div");
    Tag br("br", Tag::BR, "br");
    Tag content("content", Tag::CONTENT, "content");
    Tag content2("content2", Tag::CONTENT,"content2");
    span._children.push_back(&content);
    span._children.push_back(&content2);
    body._children.push_back(&p);
    body._children.push_back(&span);
    body._children.push_back(&br);
    body._children.push_back(&div);
    title._content = "TITLE CONTENT";
    content._content = "I AM HERE!" ;
    content2._content = "You Found Me!";
    head._children.push_back(&title);
    html._children.push_back(&head);
    html._children.push_back(&body);

    determine_visible_objects(&html);
    cout << print_visible_elements(&html)<< endl;
    Tag* getID = getElementByID(&html, "content");
    if(getID->_tagname == Tag::CONTENT){
        cout << "Get!" << endl;
    }
    else{
        cout << "Not Get..." << endl;
    }

    Tag* notGetID = getElementByID(&html, "hi");
    if(notGetID == nullptr){
        cout << "Get! with nullptr" << endl;
    }
    else{
        cout << "Not Get... with nullptr" << endl;
    }

    string tryTest = read_file("sample-pages/valid 01.html");
    Tag* root = generate_DOM_tree(tryTest);
    determine_visible_objects(root);

    cout << print_visible_elements(root) << endl;
    cout <<"\n Get ID for Title: " << getElementByID(root, "W_A")->_name << " " << getElementByID(root,"W_A")->_id << endl;
    superCleanUp(tryTest);
    cout << tryTest << endl;

//    cout << "\n \n AutoLab Result: \n" << endl;

}