#include <string>
#include <fstream>
#include <map>
#include <iostream>

std::string returnKey(std::string s) {
    std::string a;
    for (auto i : s) {
        if (i == ':') break;
        else if (i != '\t') a += i;
    }
    return a;
}

std::string returnValue(std::string s, int pass) {
    return s.substr(pass, s.length() - 1); // del space and \n
}

class ListNode
{
    public:
        ListNode* Prev;
        ListNode* Next;
        ListNode* Rand;
        std::string Data;

        ListNode() {
            this->Prev = nullptr;
            this->Next = nullptr;
            this->Rand = nullptr;
            this->Data = "";
        };

        ListNode(ListNode* prev, ListNode* next, ListNode* rand, std::string data) {
            this->Prev = prev;
            this->Next = next;
            this->Rand = rand;
            this->Data = data;
        };

};

class ListRand
{
public:
    ListNode* Head;
    ListNode* Tail;
    int Count;

    void Serialize(std::string filename) { 
        ListNode* node = Head;

        std::map<std::string, std::map<std::string, std::string>> serializatorMap;
        // loop 1: save prev and next
        for (int i = 1; ; i++) {
            std::string si = std::to_string(i);

            serializatorMap[si]["LengthData"] = std::to_string(node->Data.length());
            serializatorMap[si]["Data"] = node->Data;
            node->Data = si; // to next loop orientation of rand

            if (node->Next == nullptr) break;
            node = node->Next;
        }

        node = Head;
        // loop 2: save rand
        for (int i = 1; ; i++) {
            std::string si = std::to_string(i);

            std::map<std::string, std::string> tmpInline;
            // save rand as a hash of map
            if (node->Rand != nullptr) serializatorMap[si]["Rand"] = node->Rand->Data; // data is already hash of map
            else serializatorMap[si]["Rand"] = "nullptr";

            if (node->Next == nullptr) break;
            node = node->Next;
        }

        std::ofstream out;
        out.open(filename);

        if (out.is_open()) {
            for (auto& x : serializatorMap) {
                out << x.first << ":\n";
                out << "Rand: " << x.second["Rand"] << "\n";
                out << "LengthData: " << x.second["LengthData"] << "\n";
                out << "Data:\n" << x.second["Data"] << "\n";
            }
        }

        out.close();
    }

    void Deserialize(std::string filename) {
        std::map<std::string, std::string> deserializatorMapRand;
        std::map<std::string, ListNode> deserializatorMapListNode;

        std::ifstream in(filename);
        std::string line;

        int count = 0;

        std::string key, data, rand;
        int length = 0;

        // loop 1 read file
        while (getline(in, line)) {
            switch (count)
            {
            case 0:
                key = returnKey(line);
                break;
            case 1:
                rand = returnValue(line, 6);
                break;
            case 2:
                std::cout << returnValue(line, 12);
                length = std::stoi(returnValue(line, 12));
                break;
            case 3:
                data = "";
                while (true) {
                    getline(in, line);

                    if (line.length() >= length) {
                        data += line.substr(0, length);
                        break;
                    }
                    if (line.length() < length) {
                        data += line;
                        data += '\n';
                        length -= line.length() + 1;
                    }
                }
                break;
            }
            count++;
            if (count > 3) {
                count = 0;
                deserializatorMapListNode[key] = ListNode(nullptr, nullptr, nullptr, data);
                deserializatorMapRand[key] = rand;
            }
        }

        in.close();

        // loop 2 set links 
        auto itRand = deserializatorMapRand.begin();
        auto itListNode = deserializatorMapListNode.begin();
        auto end = deserializatorMapRand.end();
        end--;

        while (true) {
            if (itRand != deserializatorMapRand.begin()) {
                auto tmp = itListNode;
                tmp--;
                itListNode->second.Prev = &(tmp)->second;
            }
            if (itRand != end) {
                auto tmp = itListNode;
                tmp++;
                itListNode->second.Next = &(tmp)->second;
            }
            if (itRand->second != "nullptr") {
                itListNode->second.Rand = &deserializatorMapListNode.at(itRand->second);
            }

            itRand++; itListNode++;

            if (itRand == deserializatorMapRand.end()) break;
        }

        this->Head = &deserializatorMapListNode.begin()->second;
    }
};

std::string replaseAll(std::string str, const std::string from, const std::string to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

void showListNode(ListNode* head) {
    ListNode* node = head;
    while (true) {
        std::cout << "Data: " << replaseAll(node->Data, "\n", "\\n");
        if (node->Next != nullptr) std::cout << " Next: " << replaseAll(node->Next->Data, "\n", "\\n");
        else std::cout << " Next: nullptr";
        if (node->Prev != nullptr) std::cout << " Prev: " << replaseAll(node->Prev->Data, "\n", "\\n");
        else std::cout << " Prev: nullptr";
        if (node->Rand != nullptr) std::cout << " Rand: " << replaseAll(node->Rand->Data, "\n", "\\n") << std::endl;
        else std::cout << " Rand: nullptr\n";

        if (node->Next == nullptr) break;
        node = node->Next;
    }
}


int mycheck() {
    ListNode a = ListNode(nullptr, nullptr, nullptr, "data_a\ndata_a2\n");
    ListNode b = ListNode(nullptr, nullptr, nullptr, "data_b\ndata_b2");
    ListNode c = ListNode(nullptr, nullptr, nullptr, "data_c\t\n");
    ListNode d = ListNode(nullptr, nullptr, nullptr, "data_d");

    a.Next = &b;

    b.Next = &c;
    b.Prev = &a;
    b.Rand = &b;

    c.Next = &d;
    c.Prev = &b;
    c.Rand = &a;

    d.Prev = &c;
    d.Rand = &b;

    ListRand listRand1, listRand2;
    listRand1.Head = &a;
    // show(listRand.Head);
    std::cout << "Before serialization: \n";
    showListNode(listRand1.Head);

    listRand1.Serialize("data.myaml");

    listRand2.Deserialize("data.myaml");

    std::cout << "After deserialization: \n";
    showListNode(listRand2.Head);

    std::cout << "Press Enter...";
    std::cin.get(); // pause 
    return 0;
}


int main(){
    mycheck();
    
}


