/*
（1）将每个维度的集合的元素视为List,多个集合构成List> dimvalue作为输入
（2）将多维笛卡尔乘积的结果放到List result之中作为输出
（3）int layer, string curstring只是两个中间过程的参数携带变量
*/


#include <string>
#include <vector>

using namespace std;

class Descartes
{
public:
    void run(vector<vector<string>> dimvalue, vector<string> result, int layer, string curstring)
    {
        if(layer < dimvalue.size() - 1)
        {
            if(dimvalue[layer].size() == 0)
                run(dimvalue, result, layer + 1, curstring);
            else
            {
                for(int i = 0; i < dimvalue[layer].size(); i++)
                {
                    string s1 = string();
                    s1.append(curstring);
                    s1.append(dimvalue[layer][i]);
                    run(dimvalue, result, layer + 1, s1);
                }
            }
        }
        else if(layer == dimvalue.size() - 1)
        {
            if(dimvalue[layer].size() == 0) result.push_back(curstring);
            else
            {
                for(int i = 0; i < dimvalue[layer].size(); i++)
                result.push_back(curstring + dimvalue[layer][i]);
            }
        }
    }
};