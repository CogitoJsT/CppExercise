#include <iostream>
#include <string>
#include <vector>

struct CNode{
    CNode *next;
    wchar_t data;
    size_t size;
};

void addNode(CNode *head, wchar_t data)
{
    CNode *cur = head;

    while(cur->next != nullptr)
    {
        cur = cur->next;
    }

    auto newNode = new CNode;
    newNode->next = nullptr;
    newNode->data = data;
    newNode->size = 0;
    cur->next = newNode;

    head->size++;

}

CNode* insertNodeBefore(CNode *head, wchar_t data, size_t pos)
{
    if(pos > head->size)
    {
        return nullptr;
    }

    if(pos == head->size)
    {
        addNode(head, data);
        return head;
    }

    CNode *cur = head;
    CNode *prev = nullptr;
    for(int i = 0; i < pos; ++i)
    {
        prev = cur;
        cur = cur->next;
    }

    if(cur == head)
    {
        CNode *newNode = new CNode;
        newNode->data = data;
        newNode->next = head;
        newNode->size = head->size + 1;
        return newNode;
    }
    else
    {
        CNode *newNode = new CNode;
        newNode->data = data;
        newNode->next = cur;
        newNode->size = 0;
        prev->next = newNode;
        head->size++;
        return head;
    }
}

CNode* deleteNode(CNode *head, size_t pos)
{
    if(pos > head->size - 1)
    {
        return nullptr;
    }

    CNode *cur = head;
    CNode *prev = nullptr;
    for(int i = 0; i < pos; ++i)
    {
        prev = cur;
        cur = cur->next;
    }

    if(cur == head)
    {
        cur = head->next;
        cur->size = head->size - 1;
        delete head;
        return cur;
    }
    else if(cur->next == nullptr)
    {
        prev->next = nullptr;
        delete cur;
        head->size--;
        return head;
    }
    else
    {
        prev->next = cur->next;
        delete cur;
        head->size--;
        return head;
    }
}

void displayNode(CNode *head)
{
    CNode *cur = head;
    auto index = 0L;

    while(true)
    {
        std::wcout << L"//// Index " << index << L" ////\n";
        std::wcout << L"data : " << cur->data << L"\n";
        std::wcout << L"size : " << cur->size << L"\n";
        cur = cur->next;
        index++;

        if(cur == nullptr)
        {
            break;
        }
    }
}

int main()
{
    std::wcin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::wstring inputString;
    inputString.reserve(100000);
    std::wcin >> inputString;

    CNode *head = new CNode;
    head->next = nullptr;
    head->data = L'A';
    head->size = 1;
    for(auto elem : inputString)
    {
        addNode(head, elem);
    }
    head = deleteNode(head, 0);

    int numOfCommands{0};
    std::wcin >> numOfCommands;

    auto cursorPos = head->size;
    for(int i = 0; i < numOfCommands; ++i)
    {
        wchar_t com0;
        std::wcin >> com0;
        if(com0 == L'P')
        {
            wchar_t com1;
            std::wcin >> com1;
            head = insertNodeBefore(head, com1, cursorPos++);
        }

        if(com0 == L'L')
        {
            if(cursorPos > 0)
            {
                --cursorPos;
            }
        }
        else if(com0 == L'D')
        {
            if(cursorPos < head->size)
            {
                ++cursorPos;
            }
        }
        else if(com0 == L'B')
        {
            if(cursorPos > 0)
            {
                head = deleteNode(head, cursorPos-1);
                --cursorPos;
            }
        }
    }

    CNode *cur = head;
    while(cur != nullptr)
    {
        std::wcout << cur->data;
        cur = cur->next;
    }

    std::wcout << L"\n";

    return 0;
}