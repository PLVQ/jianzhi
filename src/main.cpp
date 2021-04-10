#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <list>

std::vector<int> reOrderArray(std::vector<int> &array)
{
    std::vector<int> oddArra;
    std::vector<int> evenArra;
    std::vector<int> result;
    for (auto iter : array)
    {
        if (iter % 2 == 0)
        {
            evenArra.push_back(iter);
        }
        else
        {
            oddArra.push_back(iter);
        }
    }
    result.insert(result.end(), oddArra.begin(), oddArra.end());
    result.insert(result.end(), evenArra.begin(), evenArra.end());
    return result;
}
struct ListNode
{
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *FindKthToTail(ListNode *pHead, int k)
{
    ListNode *head = pHead;
    ListNode *tail = pHead;
    int i = 0;
    while (tail)
    {
        if (i < k)
        {
            tail = tail->next;
            i++;
        }
        else
        {
            head = head->next;
            tail = tail->next;
        }
    }
    return pHead;
}

ListNode *ReverseList(ListNode *pHead)
{
    ListNode *head = pHead;
    ListNode *next = pHead->next;
    while (next)
    {
        head->next = next->next;
        next->next = pHead;
        pHead = next;
        next = head->next;
    }
    return pHead;
}

ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
{
    if (pHead1 == nullptr && pHead2 == nullptr)
        return nullptr;
    if (pHead1 == nullptr)
        return pHead2;
    if (pHead2 == nullptr)
        return pHead1;

    ListNode *pCur1 = pHead1;
    ListNode *pCur2 = pHead2;
    ListNode *pPre = nullptr;
    ListNode *pHead = pHead1;

    while (pCur1 && pCur2)
    {
        if (pCur2->val < pCur1->val)
        {
            ListNode *temp = pCur2->next;
            pCur2->next = pCur1;
            if (pPre)
            {
                pPre->next = pCur2;
                pPre = pCur2;
            }
            else
            {
                pHead = pCur2;
            }
            pCur2 = temp;
        }
        else
        {
            pPre = pCur1;
            pCur1 = pCur1->next;
        }
    }
    if (pCur1 == nullptr && pCur2 != nullptr)
        pPre->next = pCur2;
    return pHead;
}

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL)
    {
    }
};

void orderTra(TreeNode *root, std::string &result)
{
    if (root == nullptr)
        return;
    orderTra(root->left, result);
    result.push_back(root->val);
    orderTra(root->right, result);
}

bool HasSubtree(TreeNode *pRoot1, TreeNode *pRoot2)
{
    if (pRoot1 == nullptr || pRoot2 == nullptr)
    {
        return false;
    }
    std::string result1;
    std::string result2;
    orderTra(pRoot1, result1);
    orderTra(pRoot2, result2);
    if (result1.find(result2) == -1)
    {
        return false;
    }
    return true;
}

TreeNode *Mirror(TreeNode *pRoot)
{
    if (pRoot == nullptr)
    {
        return nullptr;
    }
    TreeNode *temp = pRoot->left;
    pRoot->left = pRoot->right;
    pRoot->right = temp;
    Mirror(pRoot->left);
    Mirror(pRoot->right);
    return pRoot;
}

void printOne(std::vector<std::vector<int>> matrix, int row, int col, std::vector<int> &result)
{
    int length = matrix[0].size();
    int width = matrix.size();

    int c = col;
    int r = row;

    // 列递增
    for (; c < length - col; ++c)
    {
        result.push_back(matrix[row][c]);
    }
    // 行递增
    if (row < width - row - 1)
    {
        for (r = row + 1; r < width - row; ++r)
        {
            result.push_back(matrix[r][length - col - 1]);
        }
    }
    // 列递减
    if (width - row - 1 > row)
    {
        for (c = length - col - 2; c >= col; --c)
        {
            result.push_back(matrix[width - row - 1][c]);
        }
    }
    // 行递减
    if (length - col - 1 > col)
    {
        for (r = width - row - 2; r > row; --r)
        {
            result.push_back(matrix[r][col]);
        }
    }
}

std::vector<int> printMatrix(std::vector<std::vector<int>> matrix)
{
    if (matrix.size() == 0 || matrix[0].size() == 0 || matrix.size() == 1)
    {
        return matrix[0];
    }

    std::vector<int> result;
    int lengt = matrix[0].size();
    int width = matrix.size();
    int row = 0;
    int col = 0;
    while (row * 2 < width && col * 2 < lengt)
    {
        printOne(matrix, row, col, result);
        ++row;
        ++col;
    }
    return result;
}

std::vector<int> minStack;
std::list<int> minList;
void push(int value) {
    minStack.push_back(value);
    if (minList.empty()) {
        minList.push_back(minStack.size() - 1);
    }
    else {
        auto iter = minList.begin();
        while(iter!=minList.end()){
            if (value < minStack[*iter]){
                minList.insert(iter, minStack.size() - 1);
            }
            iter++;
        }
    }
}
void pop() {
    minList.remove(minStack.size() - 1);
    minStack.pop_back();
}
int top() {
    return minStack[minStack.size() - 1];
}
int min() {
    return minStack[minList.front()];
}
// 1 2 3 4 5        4 5 3 2 1        4 3 5 1 2
bool IsPopOrder(std::vector<int> pushV,std::vector<int> popV) 
{
    std::stack<int> vStack;
    auto pushIter = pushV.begin(); 
    for (auto popIter : popV){
        while(pushIter < pushV.end()) {
            if (popIter != *pushIter) {
                if (!vStack.empty() && vStack.top() == popIter) {
                    vStack.pop();
                    break;
                }
                else {
                    vStack.push(*pushIter);
                    pushIter++;
                }
            }
            else {
                pushIter++;
                break;
            }
        }
        if (!vStack.empty() && vStack.top() == popIter) {
            vStack.pop();
        }
    }
    return vStack.empty();
}

int main()
{
    // std::vector<int> arra = {1,2,3,4};
    // auto ret = reOrderArray(arra);
    // for (auto iter : ret) {
    //     std::cout << iter << " ";
    // }
    // std::cout << std::endl;
    // std::vector<std::vector<int>> arra = {{1}, {3}, {5}, {7}, {9}};
    // [[1,2,3,4,5],[6,7,8,9,10],[11,12,13,14,15],[16,17,18,19,20],[21,22,23,24,25]]
    // std::vector<int> ret = printMatrix(arra);
    // std::vector<int> ret;

    // for (auto iter : ret)
    // {
    //     std::cout << iter << " ";
    // }
    // std::cout << std::endl;
    // push(2);
    // push(3);
    // push(1);
    // push(4);
    // push(0);
    // std::cout << min() << std::endl;
    // pop();
    // std::cout << min() << std::endl;
    // std::cout << top() << std::endl;
    std::vector<int> pushV = {1,2,3,4,5};
    std::vector<int> popV = {4,3,5,1,2};
    std::cout << IsPopOrder(pushV, popV) << std::endl;
    return 0;
}