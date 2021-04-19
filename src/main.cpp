#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <list>
#include <queue>
#include <algorithm>
#include <memory>
#include <string.h>

#include <stdio.h>

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

std::vector<int> PrintFromTopToBottom(TreeNode* root) {
    std::vector<int> result;
    if (root == nullptr) {
        return result;
    }
    std::queue<TreeNode*> nodeQue;
    TreeNode* cur = nullptr;
    nodeQue.push(root);
    while(!nodeQue.empty()) {
        result.push_back(nodeQue.front()->val);
        cur = nodeQue.front();
        nodeQue.pop();
        if (cur->left != nullptr) {
            nodeQue.push(cur->left);
        }
        if (cur->right != nullptr) {
            nodeQue.push(cur->right);
        }
    }
    return result;
}

TreeNode* reConstructBinaryTree(std::vector<int> vin, std::vector<int> sequence, bool& ret)
{
    if (ret == false) {
        return nullptr;
    }
    if (vin.size() != sequence.size()) {
        ret = false;
        return nullptr;
    }
    if (vin.size() == 0 || sequence.size() == 0)
        return nullptr; 

    std::vector<int> preVin, lastVin;
    std::vector<int> preSeq, lastSeq;
    std::vector<int>::iterator curSeq = sequence.begin();
    auto root = new TreeNode(*(sequence.end() - 1));
    bool flag = false;
    for (auto iter : vin) {
        if (iter == *(sequence.end() - 1)) {
            flag = true;
            continue;
        }
        if (flag) {
            lastVin.push_back(iter);
            lastSeq.push_back(*curSeq++);
        }
        else {
            preVin.push_back(iter);
            preSeq.push_back(*curSeq++);
        }
    }
    if (flag == false) {
        ret = false;
        return nullptr;
    }
    root->left = reConstructBinaryTree(preVin, preSeq, ret);
    root->right = reConstructBinaryTree(lastVin, lastSeq, ret);
    return root;
}

bool VerifySquenceOfBST(std::vector<int> sequence) {
    if (sequence.size() == 0) {
        return false;
    }
    std::vector<int> vin(sequence);
    std::sort(vin.begin(), vin.end());
    bool ret = true;
    reConstructBinaryTree(vin, sequence, ret);
    return ret;
}

std::vector<std::vector<int> > FindPath(TreeNode* root,int expectNumber) {
    std::vector<std::vector<int>> retArray;
    std::vector<int> pathArray(10);
    std::stack<TreeNode*> nodeStack;
    std::stack<int> lenStack;
    nodeStack.push(root);
    int pathLen = 0;
    lenStack.push(pathLen);
    while(!nodeStack.empty()) {
        TreeNode* curNode = nodeStack.top();
        int curLen = lenStack.top();
        if (pathArray.capacity() == curLen - 1) {
            pathArray.resize(pathArray.capacity() * 2);
        }
        pathArray[curLen] = curNode->val;
        nodeStack.pop();
        lenStack.pop();
        if (curNode->right || curNode->left) {
            curLen++;
        }
        if (curNode->right) {
            nodeStack.push(curNode->right);
            lenStack.push(curLen);
        }
        if (curNode->left) {
            nodeStack.push(curNode->left);
            lenStack.push(curLen);
        }
        if (curNode->right == nullptr && curNode->left == nullptr) {
            int sum = 0;
            for (int i = 0; i <= curLen; i++)
            {
                sum = sum + pathArray[i];
            }
            if (sum == expectNumber) {
                std::vector<int> temp(pathArray.begin(), pathArray.begin() + curLen + 1);
                retArray.push_back(temp);
            }
        }
    }
    return retArray;
}

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};

RandomListNode* Clone(RandomListNode* pHead) {
    if (pHead == nullptr) {
        return nullptr;
    }
    auto pCur = pHead;
    while(pCur) {
        RandomListNode* newNode = new RandomListNode(pCur->label);
        newNode->next = pCur->next;
        newNode->random = pCur->random;
        pCur->next = newNode;
        pCur = newNode->next;
    }
    auto pNewHead = pHead->next;
    do {
        if (pNewHead->random != nullptr)
            pNewHead->random = pNewHead->random->next;
        pNewHead = pNewHead->next;
        if (pNewHead!=nullptr)
            pNewHead = pNewHead->next;
    }while(pNewHead);

    pNewHead = pHead->next;
    pCur = pHead;
    auto pNewCur = pHead->next;
    while(pCur) {
        pNewCur = pCur->next;
        pCur->next = pNewCur->next;
        pCur = pNewCur->next;
        if (pCur) {
            pNewCur->next = pCur->next;
        }
    }
    return pNewHead;
}

TreeNode* orderTra(TreeNode* pRootOfTree, std::vector<TreeNode*>& result) {
    if (pRootOfTree == nullptr){
        return nullptr;
    }
    orderTra(pRootOfTree->left, result);
    result.push_back(pRootOfTree);
    orderTra(pRootOfTree->right, result);
    return pRootOfTree;
}

TreeNode* Convert(TreeNode* pRootOfTree) {
    if (pRootOfTree == nullptr){
        return nullptr;
    }
    std::vector<TreeNode*> result;
    orderTra(pRootOfTree, result);
 

    for (int i = 1; i < result.size()-1; ++i) {
        result[i]->left = result[i-1];
        result[i]->right = result[i+1];
    }
    return result[0];
}
int count = 0;
void Perm(int start, int end, int a[]) {
    //得到全排列的一种情况，输出结果
    if (start == end) {
        for (int i = 0; i < end; i++)
            std::cout << a[i] << ' ';
        std::cout << std::endl;
        count++;
        return;
    }
    for (int i = start; i < end; i++) {
        if (i>0 && a[i] == a[i-1])
            continue;
        std::swap(a[start], a[i]);      //交换
        Perm(start + 1, end, a);   //分解为子问题a[start+1,...,end-1]的全排列
        std::swap(a[i], a[start]);      //回溯
    }
}

bool is_swap(std::string& str, int begin, int k)
{
    for (int i = begin; i < k; ++i)
    {
        if (str[i] == str[k]) {
            return false;
        }
    }
    return true;
}

void StrPerm(int start, int end, std::string str, std::vector<std::string>& result)
{
    if (start == end-1) {
            printf("%s\n", str.c_str());
            result.push_back(str);
    }
    for (int i = start; i < end; ++i){
        if (is_swap(str, start, i)) {
            std::swap(str[start], str[i]);
            StrPerm(start+1, end, str, result);
            std::swap(str[i], str[start]);
        }
    }
}

std::vector<std::string> Permutation(std::string str) {
    std::vector<std::string> result;
    StrPerm(0, str.length(), str, result);
    // std::sort(result.begin(), result.end());
    return result;
}

void MoreThanHalfNum_Solution(std::vector<int>& numbers, int start, int end, int k) {
    if (start>=end){
        return ;
    }
    int pHead = start;
    int pTail = end;
    int temp = numbers[pTail];
    while(pHead < pTail){
        while(pHead < pTail && numbers[pHead] <= temp){
            pHead++;
        }
        if(pHead < pTail && numbers[pHead] > temp){
            numbers[pTail] = numbers[pHead];
        }
        while(pHead < pTail && numbers[pTail] >= temp){
            pTail--;
        }
        if(pHead < pTail && numbers[pTail] < temp){
            numbers[pHead] = numbers[pTail];
        }
    }
    numbers[pHead] = temp;
    if (pHead > k)
        MoreThanHalfNum_Solution(numbers, start, pHead-1, k);
    else if (pHead < k)
        MoreThanHalfNum_Solution(numbers, pTail+1, end, k);
    else
        return;
}

std::vector<int> GetLeastNumbers_Solution(std::vector<int> input, int k) {
    MoreThanHalfNum_Solution(input, 0, input.size() - 1, k);
    return std::vector<int>(input.begin(), input.begin() + k);
}

int FindGreatestSumOfSubArray(std::vector<int> array) {
    if (array.empty())
        return 0;
    int maxSum = array[0];
    int sum = 0;
    for(int i = 0; i < array.size(); ++i) {
        sum = sum + array[i];
        if (sum > maxSum) {
            maxSum = sum;
        }
        if (sum < 0) {
            sum = 0;
        }
    }
    return maxSum;
}

int MoreThanHalfNum_Solution(std::vector<int> numbers) {
    if (numbers.empty()) {
        return 0;
    }
    int count = 1;
    int number = numbers[0];
    for (int i = 1; i < numbers.size(); ++i) {
        if (count == 0) {
            number = numbers[i];
        }
        if (numbers[i] == number) {
            count++;
        }
        else {
            count--;
        }
    }
    int nums = 0;
    for (auto iter : numbers) {
        if (iter == number) {
            nums++;
        }
    }
    if (nums > numbers.size()/2) {
        return number;
    }
    else {
        return 0;
    }
}

// 输入一个整数 n ，求1～n这n个整数的十进制表示中1出现的次数
int NumberOf1Between1AndN_Solution(int n) {
    int iBit = 1;
    int iExtral = n%10;
    int iNum = n/10;
    int iRet = 0;
    int iLow = 0;
    while(iNum != 0 && iExtral != 0) {
        if (iExtral == 0) {
            iRet += iNum*iBit;
        }
        else if (iExtral == 1) {
            iRet += iNum*iBit + iLow + 1; 
        }
        else {
            iRet += (iNum + 1)*iBit;
        }

        iLow += iExtral*iBit;
        iExtral = iNum%10;
        iNum = iNum/10;
        iBit = iBit*10;
    }
    return iRet;
}

bool IntAndStrCompare(std::vector<int> numbers, std::string& result) 
{
    std::string str = "";
    for(auto iter : numbers) {
        str += std::to_string(iter);
    }
    printf("%s, %s\n", str.c_str(), result.c_str());
    if (result.empty()) {
        result = str;
        return true;
    }
    else if (str < result) {
        result = str;
        return true;
    }
    return false;
}

void numPrem(std::vector<int> numbers, std::string& result, int start)
{
    if (start == numbers.size() - 1) {
        IntAndStrCompare(numbers, result);
    }
    for (int i = start; i < numbers.size(); ++i) {
        std::swap(numbers[start], numbers[i]);
        if (!IntAndStrCompare(numbers, result)) {
            std::swap(numbers[i], numbers[start]);
            continue;
        }
        numPrem(numbers, result, start+1);
        std::swap(numbers[i], numbers[start]);
    }
}

std::string PrintMinNumber(std::vector<int> numbers) {
    std::string result;
    numPrem(numbers, result, 0);
    return result;
}

int FirstNotRepeatingChar(std::string str) {
    int* nums = new int[129];
    memset(nums, 0, 129);
    for (int i = 0; i < str.size(); ++i) {
        int ascNum = str[i];
        printf("%d ", ascNum);
        nums[ascNum] += 1;
    }
    for (int i = 0; i < str.size(); ++i) {
        int ascNum = str[i];
        if (nums[ascNum] == 1) {
            return i;
        }
    }
    return -1;
}

int GetUglyNumber_Solution(int index) {
    std::vector<int> uglyNumber;
    uglyNumber.push_back(1);
    int pTow = 0;
    int pThree = 0;
    int pFive = 0;
    while(true) {
        int minUglyNum = 0;
        for (int i = pTow; i < uglyNumber.size(); ++i) {
            if (uglyNumber[i]*2 > uglyNumber[uglyNumber.size()-1]) {
                pTow = i;
                minUglyNum = uglyNumber[i]*2;
                break;
            }
        }

        for (int i = pThree; i < uglyNumber.size(); ++i) {
            if (uglyNumber[i]*3 > uglyNumber[uglyNumber.size()-1]) {
                if (uglyNumber[i]*3 < minUglyNum) {
                    pThree = i;
                    minUglyNum = uglyNumber[i]*3;
                }
                break;
            }
        }

        for (int i = pFive; i < uglyNumber.size(); ++i) {
            if (uglyNumber[i]*5 > uglyNumber[uglyNumber.size()-1]) {
                if (uglyNumber[i]*5 < minUglyNum) {
                    pFive = i;
                    minUglyNum = uglyNumber[i]*5;
                }
                break;
            }
        }
        uglyNumber.push_back(minUglyNum);
        if (uglyNumber.size() >= index) {
            return uglyNumber[index-1];
        }
    }
    return 0;
}

int InversePairs(std::vector<int> data) {
    int end = data.size()-1; 
    int count = 0;
    for (; end >= 0; --end) {
        for (int i = 0; i < end; ++i) {
            if (data[i] > data[end]) {
                count++;
                if (count > 1000000007)
                    count = count%1000000007;
            }
        }
    }
    return count;
}

void test() {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    for (auto iter : vec) {
        printf("%d ", iter);
        if (iter == 2) {
            vec.push_back(3);
        }
    }
    for (auto iter : vec) {
        printf("%d ", iter);
    }
}

int main()
{
    std::vector<int> input = {1,2,3,4,5,6,7,0};
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
    // std::vector<int> pushV = {1,2,3,4,5};
    // std::vector<int> popV = {4,3,5,1,2,3,5,6,8,9,7,2};
    // MoreThanHalfNum_Solution(popV, 0, popV.size()-1);
    // for (auto iter : popV) {
    //     printf("%d,", iter);
    // }
    // printf("\n");
    // int a[] = {1,2,3,4,4};
    // Perm(0,5,a);
    // printf("%d\n", count);
    // std::cout << IsPopOrder(pushV, popV) << std::endl;
    // std::string str = "abb";
    // auto result = Permutation(str);
    // for (auto iter : result){
    //     printf("%s\n", iter.c_str());
    // }
    // printf("%d\n", FindGreatestSumOfSubArray(input));
    // printf("%d\n", MoreThanHalfNum_Solution(input));
    // PrintMinNumber(input);

    // printf("%d\n", FirstNotRepeatingChar("google"));

    // test();
    // printf("%d", GetUglyNumber_Solution(7));
    printf("%d", InversePairs(input));
    return 0;
}