/**
 * a4.cpp
 * Name:
 * Person number:
 *
 * All definitions of functions required for A4 are contained in here.
 * Feel free to add more function definitions to this, but you must
 * include at least the required functions.
 *
 * You may only use the following headers:
 *    <algorithm>, <cstring>, <string>, <vector>, <list>, <stack>,
 *    <queue>, <sstream>, "Tag.hpp"
 */

#include "Tag.hpp"
#include<algorithm>
#include <cstring>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

bool BothAreSpace(char lhs, char rhs){
    return (lhs == rhs) && (lhs == ' ');
}

void superCleanUp(string& document){
    //Making all new line and tabs into a space, then all whitespace into one
    for(size_t i=0; i<document.length(); ++i){
        if(document[i] == '\n' || document[i] == '\t' || document[i] == '\r'){
            document[i] = ' ';
        }
    }
    document.erase(unique(document.begin(), document.end(), BothAreSpace), document.end());

    //Clean Up ALl Whitespace between '>' and Content && Content and '<'
    //Note: this is assume '<' and '>' comes in pair
    for(size_t i=0; i<document.length(); ++i){
        if(document[i] == '>' && i != (document.length()-1) && document[i+1] == ' '){
            document.erase(i+1, 1);
        }
        else if(document[i] == '<' && i != 0 && document[i-1] == ' '){
            document.erase(i-1,1);
        }
    }
}

bool basisMatch(const string& document){
    stack<char> match;
    for(char i : document){
        if(i == '<'){
            if(!match.empty() && match.top() == i){
                return false;
            }
            match.push('<');
        }
        else if(i == '>'){
            if(match.empty() || match.top() != '<'){
                return false;
            }
            match.pop();
        }
    }
    return match.empty();
}

bool checkTagName(const string& line, const string& tagName){
    for(size_t i=0; i<tagName.length(); ++i){
        if(line[i] != tagName[i] && (char)(line[i]+32) != tagName[i]){
            return false;
        }
    }
    return true;
}

bool idCheck(const string& tag, const string& tagName){
    //Make string begin after the tag name
    string id = tag.substr(tagName.length());
    //Check if there's id, if not then just return true
    if(id.length() < 4){
        return true;
    }
    int L = id.length();
    //if there are something attach to tag name then invalid
    if(id.at(0) != ' '){
        return false;
    }
    size_t empty = 0;
    string check = "id=";
    size_t inc = 0;
    //Clean Up all whitesapce before '"'
    for(size_t i=0; i<id.length(); ++i){
        if(id[i] == ' '){
            id.erase(i,1);
        }
        if(id[i] == check[inc] || (char)(id[i] + 32) == check[inc]){
            ++inc;
        }
        else if(id[i] == '\"'){
            empty = i;
            break;
        }
    }
    if(tagName[1] == 'r'){
        if((inc != 3 || id.at(3) != '\"') || (id.length()-4) < 4){
            return false;
        }
    }
    else if((inc != 3 || id.at(3) != '\"') || (id.length()-4) < 3){
        return false;
    }
    //Check if there are any space in id
    for(size_t i=4; i<id.length(); ++i){
        if(id[i] == '\"'){
            if((i-empty) < 2){
                return false;
            }
            if(id[i+1] != '>' && id[i+2] != '>'){
                if(tagName[1] != 'r'){
                    return false;
                }
                else{
                    return id[i+3] == '>';
                }
            }
            break;
        }
        if(id[i] == ' '){
            return false;
        }
    }
    return true;
}

bool tagNameMatch(const string& document){
    stack<string> match;
    string remaining = document;
    size_t bpos = remaining.find('<');
    size_t epos = remaining.find('>');
    if(bpos != 0 || remaining.at(epos+1) != '<'){
        return false;
    }
    if(remaining.at(epos-1) == ' '){
        if(remaining.at(epos-2) != 'l' && remaining.at(epos-2) != 'L'){
            return false;
        }
    }
    else{
        if(remaining.at(epos-1) != 'l' && remaining.at(epos-1) != 'L'){
            return false;
        }
    }
    //Check First tagName !doctype html
    if(!checkTagName(remaining.substr(bpos+1, epos-bpos),"!doctypehtml")){
        if(!checkTagName(remaining.substr(bpos+1, epos-bpos),"!doctype html")){
            return false;
        }
    }
    remaining = remaining.substr(epos+1);
    bpos = remaining.find('<');
    epos = remaining.find('>');
    vector<string> openTag {"html", "head", "title", "body"};
    vector<string> closeTag {"/title", "/head"};
    int openPos = 0;
    int closePos = 0;
    //Check Follow tagName on the first section from html to body to make sure head and title end correctly
    for(int i=0; i<(openTag.size()+closeTag.size()); ++i) {
        string tagNameString = remaining.substr(bpos + 1, epos - bpos);
        if (tagNameString[0] == '/') {
            //If there are two '/' in a tag then it is invalid
            string findChar = tagNameString.substr(1);
            if(findChar.find('/') != string::npos){
                return false;
            }

            if (!match.empty() && checkTagName('/' + match.top(), closeTag[closePos])) {
                match.pop();
                //Check If title is empty or not
                if(closePos == 0){
                    if(bpos < 1 || (bpos < 2 && remaining[0] == ' ')){
                        return false;
                    }
                }
                else{
                    if(bpos > 1){
                        return false;
                    }
                    if(remaining.at(epos+1) != '<'){
                        return false;
                    }
                }
                //Check if there's id in closing
                if((tagNameString.length()-closeTag[closePos].length()) > 2){
                    return false;
                }
                ++closePos;
            }
            else {
                return false;
            }
        }
        else {
            //If there's no '/' at beginning for close tag, then it should not have '/' anywhere in the tag except tag br
            if(tagNameString.find('/') != string::npos){
                return false;
            }
            //Check if there are any content, if do then invalid
            if(bpos > 1){
                return false;
            }
            if(!checkTagName(tagNameString, "title") && !checkTagName(tagNameString,"body")){
                if(remaining.at(epos+1) != '<'){
                    return false;
                }
            }
            if (checkTagName(tagNameString, openTag[openPos])) {
                match.push(openTag[openPos]);
                if(!idCheck(tagNameString,openTag[openPos])){
                    return false;
                }
                ++openPos;
            }
            else {
                return false;
            }
        }
        remaining = remaining.substr(epos+1);
        bpos = remaining.find('<');
        epos = remaining.find('>');
    }
    if(match.size() != 2){
        return false;
    }
    //Check the remaining tagName
    vector<string> remainingOpenTag {"div", "p", "span"};
    vector<string> remainingCloseTag {"/div", "/p", "/span"};
    vector<string> finalCloseTag {"/body", "/html"};
    char exchange = 'r';
    int finalPos = 0;
    bool period = false;
    while(bpos != string::npos && !period){
        string tagName = remaining.substr(bpos + 1, (epos - bpos));
        if(tagName[0] == '/'){
            if(match.empty()){
                return false;
            }
            //If there are two '/' in a tag then it is invalid
            string findChar = tagName.substr(1);
            if(findChar.find('/') != string::npos){
                return false;
            }

            if(exchange == 'r') {
                bool found = false;
                for (int i = 0; i < remainingCloseTag.size(); ++i) {
                    if (checkTagName(tagName, remainingCloseTag[i])) {
                        if (checkTagName(match.top(), remainingOpenTag[i])) {
                            match.pop();
                            if(tagName.length()-remainingOpenTag[i].length()-1 > 2){
                                return false;
                            }
                            found = true;
                            break;
                        }
                        else{
                            return false;
                        }
                    }
                }
                if (!found) {
                    exchange = 'f';
                }
            }
            if(exchange == 'f'){
                if (finalPos == 1) {
                    period = true;
                }
                if (checkTagName(tagName, finalCloseTag[finalPos])) {
                    if (checkTagName(match.top(), finalCloseTag[finalPos].substr(1))) {
                        if(epos != remaining.length()-1 && remaining.at(epos+1) != '<'){
                            return false;
                        }
                        match.pop();
                        if(tagName.length()-finalCloseTag[finalPos].length() > 2){
                            return false;
                        }
                        ++finalPos;
                    }
                }
                else {
                    return false;
                }
            }
        }
        else if(tagName.at(0) == 'b' && tagName.at(1) == 'r'){
            //This make sure br doesn't goes into span tag
            if(!match.empty() && checkTagName(match.top(), "span")){
                return false;
            }
            size_t specialPos = tagName.find('/');
            if(specialPos != string::npos && tagName.at(tagName.length()-2) != '/'){
                return false;
            }
            if(!idCheck(tagName,"br")){
                return false;
            }
        }
        else{
            //If there's no '/' at beginning for close tag, then it should not have '/' anywhere in the tag except tag br
            if(tagName.find('/') != string::npos){
                return false;
            }
            if(!match.empty() && checkTagName(match.top(), "span")){
                return false;
            }
            //Make sure div is only inside body or div
            if(!match.empty() && checkTagName(tagName, "div")){
                if(!checkTagName(match.top(),"body") && !checkTagName(match.top(), "div")){
                    return false;
                }
            }
            bool found = false;
            for(string s : remainingOpenTag){
                if(checkTagName(tagName, s)){
                    if(!idCheck(tagName,s)){
                        return false;
                    }
                    match.push(s);
                    found = true;
                    break;
                }
            }
            if(!found){
                return false;
            }
        }

        remaining = remaining.substr(epos+1);
        bpos = remaining.find('<');
        epos = remaining.find('>');
    }
    if(bpos != string::npos){
        return false;
    }
    return match.empty();
}

bool html_is_valid (const std::string& document) {
    //Minimum length of a valid html source code
    if(document.length() < 68){
        return false;
    }

    //Clean Up ALl Whitespace
    if(!basisMatch(document)){
        return false;
    }
    string cleanUpString = document;
    superCleanUp(cleanUpString);

    return tagNameMatch(cleanUpString);
}

bool caseNotSensitive(char lhs, char rhs){
    return lhs == rhs || (char)(lhs+32) == rhs || lhs == (char)(rhs+32);
}

const string grabID(string tag){
    string returnVal = "";
    for(size_t i=0; i<tag.length() ; ++i){
        if(tag[i] == '\"'){
            break;
        }
        else if(tag[i] == ' '){
            tag.erase(i,1);
            --i;
        }
    }
    for(int i=4; i<tag.length(); ++i){
        if(tag[i] == '\"'){
            break;
        }
        else{
            returnVal += tag[i];
        }
    }
    return returnVal;
}

Tag* recursive_generate_DOM_tree(const std::string& document, const vector<string>& name, const vector<Tag::TAGNAME>& tag, stack<Tag*>& match, size_t& index){
    size_t bpos = 0;
    size_t epos = 0;
    for(index; index<document.length(); ++index){
        if(document[index] == '<'){
            bpos = index;
        }
        else if(document[index] == '>'){
            epos = index;
            break;
        }
    }
    if(caseNotSensitive(document[bpos+1],'b') && caseNotSensitive(document[bpos+2],'r')){
        string tagName = "";
        string id = "";
        if(epos - bpos > 5){
            id = grabID(document.substr(bpos+3));
        }
        Tag* final = new Tag("br", Tag::BR, id);
        if(document[epos+1] != '<'){
            string content = "";
            for(size_t q=epos+1; q<document.length(); ++q){
                if(document[q] != '<'){
                    content += document[q];
                }
                else{
                    break;
                }
            }
            Tag* conTag = new Tag("content" , Tag::CONTENT, "");
            conTag->_content = content;
            if(!match.empty()) {
                match.top()->_children.push_back(final);
                match.top()->_children.push_back(conTag);
            }
        }
        else{
            if(!match.empty()){
                match.top()->_children.push_back(final);
            }
        }
    }
    else if(document[bpos+1] != '/'){
        Tag::TAGNAME tagSign;
        string id = "";
        for(int n=0; n<name.size(); ++n){
            bool found = true;
            string tagName = "";
            for(int i=0; i<name[n].length(); ++i){
                if(!caseNotSensitive(document[bpos+i+1],name[n][i])){
                    found = false;
                }
                tagName += name[n][i];
            }
            if(found){
                tagSign = tag[n];
//                if(!caseNotSensitive(document[epos-1],name[n][name[n].length()-1]) &&
//                        !caseNotSensitive(document[epos-2],name[n][name[n].length()-1])){
                if((epos-bpos+1)-name[n].length()-3 > 0){
                    id = grabID(document.substr(bpos+name[n].length()+2, epos-(bpos+name[n].length()+1)));
                }
                Tag* final = new Tag(tagName, tagSign, id);
                //Grab Content
                if(document[epos+1] != '<'){
                    string content = "";
                    for(size_t q=epos+1; q<document.length(); ++q){
                        if(document[q] != '<'){
                            content += document[q];
                        }
                        else{
                            break;
                        }
                    }
                    if(name[n][0] == 't' && name[n][1] == 'i'){
                        final->_content = content;
                    }
                    else{
                        Tag* conTag = new Tag("content", Tag::CONTENT,"");
                        conTag->_content = content;
                        final->_children.push_back(conTag);
                    }
                }
                match.push(final);
            }
        }
    }
    else{
        if(caseNotSensitive(document[bpos+2],'h') && caseNotSensitive(document[bpos+3],'t')){
            if(!match.empty()) {
                return match.top();
            }
        }
        else {
            if(!match.empty()) {
                Tag* children = match.top();
                match.pop();
                match.top()->_children.push_back(children);
                if(document[epos+1] != '<'){
                    string content = "";
                    for(size_t q=epos+1; q<document.length(); ++q){
                        if(document[q] != '<'){
                            content += document[q];
                        }
                        else{
                            break;
                        }
                    }
                    Tag* conTag = new Tag("content", Tag::CONTENT, "");
                    conTag->_content = content;
                    if(!match.empty()){
                        match.top()->_children.push_back(conTag);
                    }
                }
//                for (index; index < document.length(); ++index) {
//                    if (document[index] == '>') {
//                        break;
//                    }
//                }
            }
        }
    }
    return recursive_generate_DOM_tree(document,name,tag,match,++index);
}

Tag* generate_DOM_tree(const std::string& document) {
    string cleanUp = document;
    superCleanUp(cleanUp);
    vector<Tag::TAGNAME> tag {Tag::HTML, Tag::HEAD, Tag::TITLE, Tag::BODY, Tag::DIV, Tag::P, Tag::SPAN, Tag::BR};
    vector<string> name {"html","head","title","body","div","p","span","br"};
    stack<Tag*> match;
    size_t index = 0;
    //This for-loop get rid of <!doctype html>
    for(index; index < cleanUp.length(); ++index){
        if(cleanUp[index] == '>'){
            break;
        }
    }
    return recursive_generate_DOM_tree(cleanUp, name, tag, match, ++index);
}

bool recursive_determine_visible_object(Tag* const root){
    if((root->_tagname) == Tag::TITLE || (root->_tagname) == Tag::CONTENT){
        root->_displayed = true;
        return root->_displayed;
    }
    if(!(root->_children).empty()){
        for(Tag* t : root->_children){
            root->_displayed = recursive_determine_visible_object(t) || root->_displayed;
        }
    }
    return root->_displayed;
}

void determine_visible_objects(Tag* const root) {
    recursive_determine_visible_object(root);
}

std::string recursive_print_visible_elements(Tag* const root, const string& space){
    if((root->_tagname) == Tag::TITLE || (root->_tagname) == Tag::CONTENT){
        return space + root->_name + "\n" + space + "  " + root->_content;
    }
    string returnVal = space + root->_name;
    if(!(root->_content).empty()){
        returnVal += "\n" + space + "  " + root->_content;
    }
    if(!(root->_children).empty()){
        for(auto t: root->_children){
            if(t->_displayed){
                returnVal += "\n" + recursive_print_visible_elements(t, (space + "  "));
            }
        }
    }
    return returnVal;
}

std::string print_visible_elements(Tag* const root) {
    return recursive_print_visible_elements(root,"") + "\n";
}

Tag* recursive_getElementByID(Tag* const root, const std::string& id){
    if(!(root->_id).empty() && root->_id == id){
        return root;
    }
    if(!(root->_children).empty()){
        for(auto t : root->_children){
            auto returnVal = recursive_getElementByID(t,id);
            if(returnVal != nullptr){
                return returnVal;
            }
        }
    }
    return nullptr;
}

Tag* getElementByID(Tag* const root, const std::string& id) {
    return recursive_getElementByID(root,id);
}