#include <iostream>

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
    CNode *head = new CNode;

    head->next = nullptr;
    head->data = L'A';
    head->size = 1;

    addNode(head, L'B');
    addNode(head, L'C');
    addNode(head, L'D');
    addNode(head, L'E');
    addNode(head, L'F');

    displayNode(head);

    std::wcout << L"\n\n";

    head = insertNodeBefore(head, L'K', 2);
    displayNode(head);
    std::wcout << L"\n\n";

    head = insertNodeBefore(head, L'L', 0);
    displayNode(head);
    std::wcout << L"\n\n";

    head = insertNodeBefore(head, L'M', 8);
    displayNode(head);
    std::wcout << L"\n\n";

    head = deleteNode(head, 2);
    displayNode(head);
    std::wcout << L"\n\n";

    head = deleteNode(head, 4);
    displayNode(head);
    std::wcout << L"\n\n";

    head = deleteNode(head, 0);
    displayNode(head);
    std::wcout << L"\n\ninsertNodeBefore";

    return 0;
}