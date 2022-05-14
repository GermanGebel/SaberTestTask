#include <string>
#include <fstream>
#include <map>
#include <iostream>

std::string returnKey(std::string s){
    std::string a;
    for(auto i : s){
        if (i == ':') break;
        else if (i != '\t') a += i;
    }
    return a;
}

std::string returnValue(std::string s){
    return s.substr(7, s.size() - 2);
}

class ListNode
{
    public: 
        ListNode *Prev;
        ListNode *Next;
        ListNode *Rand; // произвольный элемент внутри списка
        std::string Data;

        ListNode(){
            this->Prev = nullptr;
            this->Next = nullptr;
            this->Rand = nullptr;
            this->Data = "";
        };

        ListNode(ListNode* prev, ListNode* next, ListNode* rand, std::string data){
            this->Prev = prev;
            this->Next = next;
            this->Rand = rand;
            this->Data = data;
        };
};

class ListRand
{
    public: 
        ListNode *Head;
        ListNode *Tail;
        int Count;

        void Serialize(std::string filename){
            ListNode *node = Head;
            
            std::map<std::string, std::map<std::string, std::string>> serializatorMap;
            // loop 1: save prev and next
            for(int i=1; ;i++){
                std::string si = std::to_string(i);

                serializatorMap[si]["Data"] = node->Data;
                node->Data = si; // to next loop orientation of rand

                if (node->Next == nullptr) break;
                node = node->Next;
            }

            node = Head;
            // loop 2: save rand
            for(int i=1; ;i++){
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

            if (out.is_open()){
                for (auto &x : serializatorMap){
                    out << x.first << ":\n\t";
                    out << "Data: " << x.second["Data"] << "\n\t";
                    out << "Rand: " << x.second["Rand"] << "\n";
                }
            }

            out.close();
        }
            
        void Deserialize(std::string filename){
            std::map<std::string, std::string> deserializatorMapRand;
            std::map<std::string, ListNode> deserializatorMapListNode;

            std::ifstream in(filename);
	        std::string line;

            int count = 0;

            std::string key, data, rand;
            
            // loop 1 read file
            while (getline(in, line)){
                switch (count)
                {
                case 0:
                    key = returnKey(line);
                    break;
                case 1:
                    data = returnValue(line);
                    break;
                case 2:
                    rand = returnValue(line);
                    break;
                }
                count++; 
                if (count > 2) {
                    count = 0;
                    deserializatorMapListNode[key] = ListNode(nullptr, nullptr, nullptr, data);
                    deserializatorMapRand[key] = rand;
                }
            }

            in.close();

            // loop 2 set links 
            auto itRand=deserializatorMapRand.begin();
            auto itListNode=deserializatorMapListNode.begin();
            auto end = deserializatorMapRand.end();
            end--;

            while (true){
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

                itRand++;itListNode++;

                if (itRand == deserializatorMapRand.end()) break;
            }

            this->Head = &deserializatorMapListNode.begin()->second;
        }
};

void showListNode(ListNode *head){
    ListNode *node = head;
    while (true){
        std::cout << "Data: " << node->Data;
        if (node->Next != nullptr) std::cout << " Next: " << node->Next->Data;
        else std::cout << " Next: nullptr";
        if (node->Prev != nullptr) std::cout << " Prev: " << node->Prev->Data;
        else std::cout << " Prev: nullptr";
        if (node->Rand != nullptr) std::cout << " Rand: " << node->Rand->Data << std::endl;
        else std::cout << " Rand: nullptr\n";

        if (node->Next == nullptr) break;
        node = node->Next;
    }
}

int main(){
    ListNode a = ListNode(nullptr, nullptr, nullptr, "data_a");
    ListNode b = ListNode(nullptr, nullptr, nullptr, "data_b");
    ListNode c = ListNode(nullptr, nullptr, nullptr, "data_c");
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

    ListRand listRand;
    listRand.Head = &a;
    // show(listRand.Head);
    std::cout << "Before serialization: \n";
    showListNode(listRand.Head);

    listRand.Serialize("data.myaml");
    listRand.Deserialize("data.myaml");

    std::cout << "After deserialization: \n";
    showListNode(listRand.Head);

    std::cin.get();
    return 0;
}


