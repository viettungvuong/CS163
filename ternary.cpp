#include "ternary.h"
#include "functions.h"
#include <QFile>

bool isLetter(char ch, bool capital = false) {
    if (!capital)
        return (ch >= 'a' && ch <= 'z');
    return (ch >= 'A' && ch <= 'Z');
}

TernarySearchTree::TernarySearchTree()
{
    root = new TernaryTreeNode;
    root->ch = 'n';
    root->definition = new std::string;
    *root->definition = "The letter N";
}

void TernarySearchTree::deleteTree()
{
    deletetree(this->root);
    this->root = nullptr;
}
TernaryTreeNode* TernarySearchTree::getRandomWord(bool normal, int i) {
    std::string word = "";

    int c;
    bool done = false;
    char ch = 65 + rand() % 26;
    std::string startChar(1, ch);
    TernaryTreeNode* tem = nullptr;
    bool start = true;
    bool turned = false;
    bool outFirstTwoChar = true;
    while (1) {
        if (start) {
            do {
                ch = 97 + rand() % 26;
                std::string addChar(1, ch); //de check lai cai random nay no ra tu gi
                word = startChar + addChar;
                tem = search4keyword(word, false);
            } while (!tem);
            start = false;
            turned = false;
        }
        else {
            c = rand() % 5;
            if (c == 0) {
                if (tem->right && isLetter(tem->right->ch)) {
                    //phai them delete char trc o day
                    if (!turned)
                        word.pop_back();
                    tem = tem->right;
                    word += tem->ch;
                    turned = true;
                }
                else if (!tem->right)
                    if (tem->definition)
                        break;
            }
            else if (c == 1) {
                if (tem->left && isLetter(tem->left->ch))
                {
                    if (!turned)
                        word.pop_back();
                    tem = tem->left;
                    word += tem->ch;
                    turned = true;
                }
                else if (!tem->left)
                    if (tem->definition)
                        break;
            }
            else {
                if (tem->mid) {
                    std::string addChar(1, tem->mid->ch);

                    word += addChar;
                    tem = tem->mid;
                    turned = false;
                }
                else if (!tem->mid)
                    if (tem->definition)
                        break;
            }
            //de ti kiem cach random khac
        }
    }
    tem->word = word;
    if (normal) {
        std::cout << word << " - " << *tem->definition << "\n";
    }
    else {
        std::pair<std::string, std::string> newPair;
        newPair.first = word;
        newPair.second = *tem->definition;
        this->wordAndDefinition[i] = newPair;
    }
    return tem;

}
TernaryTreeNode* TernarySearchTree::getRandomWord2(bool normal, int i) { //danh cho slang va emotional dictionary
    std::string word = "";

    int c;
    bool done = false;
    char ch = 65 + rand() % 26;
    std::string startChar(1, ch);
    TernaryTreeNode* tem = nullptr;
    bool start = true;
    bool turned = false;
    bool outFirstTwoChar = true;
    while (1) {
        if (start) {
            do {
                ch = 65 + rand() % 26;
                std::string addChar(1, ch); //de check lai cai random nay no ra tu gi
                word = startChar + addChar;
                tem = search4keyword(word, false, true);
            } while (!tem);
            start = false;
            turned = false;
        }
        else {
            c = rand() % 5;
            if (c == 0) {
                if (tem->right && isLetter(tem->right->ch)) {
                    //phai them delete char trc o day
                    if (!turned)
                        word.pop_back();
                    tem = tem->right;
                    word += tem->ch;
                    turned = true;
                }
                else if (!tem->right)
                    if (tem->definition)
                        break;
            }
            else if (c == 1) {
                if (tem->left && isLetter(tem->left->ch))
                {
                    if (!turned)
                        word.pop_back();
                    tem = tem->left;
                    word += tem->ch;
                    turned = true;
                }
                else if (!tem->left)
                    if (tem->definition)
                        break;
            }
            else {
                if (tem->mid) {
                    std::string addChar(1, tem->mid->ch);

                    word += addChar;
                    tem = tem->mid;
                    turned = false;
                }
                else if (!tem->mid)
                    if (tem->definition)
                        break;
            }
            //de ti kiem cach random khac
        }
    }
    if (normal) {
        std::cout << word << " - " << *tem->definition << "\n";
    }
    else {
        std::pair<std::string, std::string> newPair;
        newPair.first = word;
        newPair.second = *tem->definition;
        this->wordAndDefinition[i] = newPair;
    }
    return tem;

}
void TernarySearchTree::guessRandomWord(bool nonWord) {
    for (int i = 0; i < 4; i++) {
        if (nonWord)
            getRandomWord2(false, i);
        else
            getRandomWord(false, i);
    }
    int chooseWord = rand() % 4;
    std::cout << "The word has this definition: \n" << wordAndDefinition[chooseWord].second << "\nPlease choose the correct word: \n";
    for (int i = 0; i < 4; i++) {
        std::cout << i + 1 << ". " << wordAndDefinition[i].first << "\n";
    }
    std::cout << "Please choose your answer: ";
    int in;
    std::cin >> in;
    if ((in - 1) == chooseWord) {
        std::cout << "Congratulations, you got the correct answer!";
    }
    else {
        std::cout << "WASTED, the correct answer is " << wordAndDefinition[chooseWord].first;
    }
}
void TernarySearchTree::guessRandomDefinition(bool nonWord) {
    for (int i = 0; i < 4; i++) {
        if (nonWord)
            getRandomWord2(false, i);
        else
            getRandomWord(false, i);
    }
    int chooseWord = rand() % 4;
    std::cout << "The word is: \n" << wordAndDefinition[chooseWord].first << "\nPlease choose the correct definition: \n";
    for (int i = 0; i < 4; i++) {
        std::cout << i + 1 << ". " << wordAndDefinition[i].second << "\n";
    }
    std::cout << "Please choose your answer: ";
    int in;
    std::cin >> in;
    if ((in - 1) == chooseWord) {
        std::cout << "Congratulations, you got the correct answer!";
    }
    else {
        std::cout << "WASTED, the correct answer is " << wordAndDefinition[chooseWord].second;
    }
}
void TernarySearchTree::addNewWordToDict(std::string keyword, std::string definition) {
    this->add2Tree(keyword, definition, 0);
}
void updateWord(TernaryTreeNode*& tem,std::string newDefinition) {
    *tem->definition = newDefinition;
}
void TernarySearchTree::add2Tree(std::string keyword, std::string definition, bool importing)
{
    if (!this->root)
    {
        this->root = new TernaryTreeNode;
        this->root->ch = 'n';
        this->root->definition = new std::string;
        *this->root->definition = "The letter N";
    }
    TernaryTreeNode* tem = this->root;
    for (int i = 0; i < keyword.length(); ++i)
    {
        if (tem->ch == keyword[i]) // go mid
        {
            /*if (!importing && i == keyword.length() - 1 && tem->definition) { //tu da co
                std::cout << "The word " << keyword << " is already in the dictionary \nDo you want to edit its definition instead? ";
                char in;
                std::cin >> in;
                if (toupper(in) == 'Y') {
                    std::string newDefinition;
                    std::getline(std::cin, newDefinition);
                    updateWord(tem, newDefinition);
                    std::cout << "Update new definition successfully for " << keyword << " \n";
                }
                return;
            }*/
            if (tem->mid)
            {
                tem = tem->mid;
            }
            else
            {
                if (i == keyword.length() - 1)
                {
                    //if (!importing && tem->definition) {
                    //	std::cout << "Already in the dictionary!\n"; //tu da co
                    //	return;
                    //}
                    break; //da den ki tu cuoi, kh can add gi them
                }
                else
                {
                    tem->mid = new TernaryTreeNode;
                    tem = tem->mid;
                    tem->ch = keyword[i + 1];
                }
            }
            continue;
        }
        if (tem->ch < keyword[i]) // go right;
        {
            if (tem->right)
            {
                tem = tem->right;
            }
            else
            {
                tem->right = new TernaryTreeNode;
                tem = tem->right;
                tem->ch = keyword[i];
            }
            --i;
            continue;
        }
        if (tem->ch > keyword[i]) // go left
        {
            if (tem->left)
            {
                tem = tem->left;
            }
            else
            {
                tem->left = new TernaryTreeNode;
                tem = tem->left;
                tem->ch = keyword[i];
            }
            --i;
            continue;
        }
    }
    tem->definition = new std::string;
    *tem->definition = definition;
}
void TernarySearchTree::editKeyword(TernaryTreeNode*& tem, std::string newDefinition) {
    *tem->definition = newDefinition;
    //de them cai save ra file nua
}
TernaryTreeNode* TernarySearchTree::search4keyword(std::string keyword, bool normal, bool nonWord)
{
    for (int i = 0; i < keyword.length(); i++) {
        if (!nonWord)
            keyword[i] = tolower(keyword[i]);
        else
            keyword[i] = toupper(keyword[i]);
    }
    keyword[0] = toupper(keyword[0]); //tranh truong case sensitive tim kh ra du ta do co
    // those line with "//" at the end is for debug
    // chinh cho viet hoa thuong search van duoc
    TernaryTreeNode* tem = this->root;
    // int count = 0;//
    for (int i = 0; i < keyword.length(); ++i)
    {
        if (tem == nullptr)
        {
            if (normal)
                std::cout << "Not found\n";
            // std::cout << "Pass over " << count << " nodes\n";//
            return tem;
        }
        //++count;//
        // std::cout << tem->ch;//
        if (tem->ch == keyword[i])
        {
            if (i == keyword.length() - 1) //den dung tu
            {
                break;
            }
            else
            {
                tem = tem->mid;
                continue;
            }
        }
        if (tem->ch > keyword[i]) // go left
        {
            tem = tem->left;
            --i; //de no kh tang len qua chu ke tiep
            continue;
        }
        if (tem->ch < keyword[i]) // go right
        {
            tem = tem->right;
            --i;
            continue;
        }
    }
    if (normal) {
        if (tem->definition)
        {
            std::cout << *tem->definition << "\n";
        }
        else
            std::cout << "Not found\n";
    }
    // std::cout << "Pass over " << count << " nodes\n";//
    return tem;
}


void TernarySearchTree::import_dictionary(int index, bool forReset)
{
    QFile f;
    if (forReset)
    {
        switch (index)
        {
        case 0:
            f.setFileName(qApp->applicationDirPath()+"/DefaultLibrary/slang.txt");
            break;
        case 1:
            f.setFileName(qApp->applicationDirPath()+"/DefaultLibrary/emotional.txt");
            break;
        case 2:
            f.setFileName(qApp->applicationDirPath()+"/DefaultLibrary/dictionary.txt");
            break;
        }
    }
    else
    {
        switch (index)
        {
        case 0:
            f.setFileName(qApp->applicationDirPath()+"/Library/slang.txt");
            break;
        case 1:
            f.setFileName(qApp->applicationDirPath()+"/Library/emotional.txt");
            break;
        case 2:
            f.setFileName(qApp->applicationDirPath()+"/Library/dictionary.txt");
            break;
        }
    }
    if (!f.open(QIODevice::ReadOnly))
        return;
    QTextStream fin(&f);
    std::string keyword;
    std::string input_str;
    //int c = 0;
    while (!fin.atEnd())
    {
        input_str=convertTo(fin.readLine());
        if (input_str.length() <= 3)
            continue;
        while (1)
        {
            keyword.push_back(input_str[0]);
            input_str.erase(input_str.begin());
            if (input_str[0] == ' ' && input_str[1] == ' ')
            {
                input_str.erase(input_str.begin());
                input_str.erase(input_str.begin());
                break;
            }
        }
        this->add2Tree(keyword, input_str, 1);
        /*if(index==2&&forReset==1)
            std::cout << keyword << " *** " << input_str<<'\n';*/
        keyword.clear();
        //++c;
    }
    //std::cout << c<<"\n";//dem so tu
    f.close();
}

void TernarySearchTree::deleteKeword(std::string keyword)
{
    TernaryTreeNode* tem = this->root, * breakpoint = nullptr;
    std::vector<TernaryTreeNode*> myVec;
    for (int i = 0; i < keyword.length(); ++i)
    {
        if (tem == nullptr)
        {
            return;
        }
        if (tem->ch == keyword[i])
        {
            if (i == keyword.length() - 1) //den dung tu
            {
                break;
            }
            else
            {
                if (childOfNode(tem) == 1 && tem->definition == nullptr)
                    myVec.push_back(tem);
                else
                {
                    breakpoint = tem;
                    myVec.clear();
                }
                tem = tem->mid;
                continue;
            }
        }
        if (tem->ch > keyword[i]) // go left
        {
            if (childOfNode(tem) == 1 && tem->definition == nullptr)
                myVec.push_back(tem);
            else
            {
                breakpoint = tem;
                myVec.clear();
            }
            tem = tem->left;
            --i;
            continue;
        }
        if (tem->ch < keyword[i]) // go right
        {
            if (childOfNode(tem) == 1 && tem->definition == nullptr)
                myVec.push_back(tem);
            else
            {
                breakpoint = tem;
                myVec.clear();
            }
            tem = tem->right;
            --i;
            continue;
        }
    }
    if (tem->definition)
    {
        if (childOfNode(tem))
        {
            delete tem->definition;
            tem->definition = nullptr;
            return;
        }
        if (myVec.empty() && breakpoint)
        {
            if (breakpoint->left == tem)
                breakpoint->left = nullptr;
            else if (breakpoint->mid == tem)
                breakpoint->mid = nullptr;
            else if (breakpoint->right == tem)
                breakpoint->right = nullptr;
            return;
        }
        delete tem->definition;
        delete tem;
        if (breakpoint->left == myVec[0])
            breakpoint->left = nullptr;
        else if (breakpoint->mid == myVec[0])
            breakpoint->mid = nullptr;
        else if (breakpoint->right == myVec[0])
            breakpoint->right = nullptr;
        else
            return;
        for (int i = 0; i < myVec.size(); ++i)
        {
            delete myVec[i];
        }
        myVec.clear();
    }
}

TernaryTreeNode* TernarySearchTree::getRoot()
{
    return this->root;
}
void TernarySearchTree::inorderTraversal() {
    inorderTraversalAux(this->root, "");
}
void TernarySearchTree::inorderTraversalAux(TernaryTreeNode* node, std::string currentStr) {
    if (!node)
        return;
    inorderTraversalAux(node->left, currentStr);
    if (node->definition) {
        std::cout << currentStr << node->ch << "\n";
    }
    inorderTraversalAux(node->mid, currentStr + node->ch);
    inorderTraversalAux(node->right, currentStr);
}
void LinkedList::insert(WordAndDef wad) {
    LinkedListNode* insert = new LinkedListNode;
    insert->wad = wad;
    if (!this->root) {
        root = insert;
        return;
    }
    LinkedListNode* current = this->root;
    while (current->next) {
        current = current->next;
    }
    current->next = insert;
}
void LinkedList::display(const std::string& definition) {
    if (!this->root) {
        std::cout << "No result";
        return;
    }
    LinkedListNode* current = this->root;
    int count = 1;
    std::cout << "Words that contains '" << definition << "' in its definition:\n";
    while (current) {
        std::cout << count++ << ". " << current->wad.word << " - " << current->wad.definition << "\n\n";
        current = current->next;
    }
}
void TernarySearchTree::inorderTraversalForSearch(TernaryTreeNode* node, std::string currentStr, std::string definition, std::vector<WordAndDef>& v) {
    if (!node)
        return;
    inorderTraversalForSearch(node->left, currentStr, definition, v);
    if (node->definition) {
        for (int i = 0; i < definition.length(); i++) {
            definition[i] = tolower(definition[i]);
        }
        std::string toUpperFirst = definition;
        toUpperFirst[0] = toupper(toUpperFirst[0]); //de phong truong hop chi co chu o dau viet hoa no bao kh ra
        if ((*node->definition).find(definition) != std::string::npos || (*node->definition).find(toUpperFirst) != std::string::npos) { //definition la substr cua cai nay
            WordAndDef wad;
            wad.word = currentStr + node->ch;
            wad.definition = *node->definition;
            v.push_back(wad);
        }
    }
    inorderTraversalForSearch(node->mid, currentStr + node->ch, definition, v);
    inorderTraversalForSearch(node->right, currentStr, definition, v);
}
void TernarySearchTree::inorderTraversalForSuggest(TernaryTreeNode* node, std::string currentStr, std::vector<WordAndDef>& suggest) {
    if (!node)
        return;

    if (node->definition) {
        WordAndDef newWaD;
        newWaD.word = currentStr + node->ch;
        newWaD.definition = *node->definition;
        suggest.push_back(newWaD);
    }
    inorderTraversalForSuggest(node->left, currentStr, suggest);

    inorderTraversalForSuggest(node->mid, currentStr + node->ch, suggest);

    inorderTraversalForSuggest(node->right, currentStr, suggest);

}
std::vector<WordAndDef> TernarySearchTree::search4Definition(std::string definition) {
    std::vector<WordAndDef> ans;
    inorderTraversalForSearch(this->root, "", definition, ans);
    return ans;
}
