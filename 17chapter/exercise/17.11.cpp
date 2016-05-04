/*********************************************************************************
*     Last Modified       :     [2015-12-26 14:51]
*     Description         :      
**********************************************************************************/
#include <bitset>
#include <iostream>
#include <string>
class answer_100{
private:
    std::bitset<100> ans;
public:
    void set_bitset(unsigned pos,std:: string report);
    const std::bitset<100> &get_answer()
    {
        return ans;
    }
    answer_100()=default;
    answer_100(std::bitset<100> a):ans(a){}
};
void answer_100::set_bitset(unsigned pos, std::string report)
{
    if(report == "yes")
    {
        ans.set(pos);
    }
    else if(report == "no")
    {
        ans.reset(pos);
    }
    else{
        std::cout << "answer is wrong" << std::endl;
    }
}
class test_ans{
private:
    answer_100 test_answer;
    answer_100 real_answer;
public:
    test_ans(answer_100 a, answer_100 b):real_answer(a),test_answer(b){}
    unsigned trueAnswerNum()
    {
        answer_100 true_answer(test_answer.get_answer() & real_answer.get_answer());
        return true_answer.get_answer().count();
    }
};
int main(int argc, char *argv[])
{
    int i;
    std::string s;
    answer_100 my_ans;
    while(std::cin >> i)
    {
        std::cin >> s;
        my_ans.set_bitset(i, s);
    }
    std::cout << my_ans.get_answer() << std::endl; 
    answer_100 answer(std::bitset<100> (0x1c));
    test_ans tst_answer(my_ans, answer);
    std::cout << tst_answer.trueAnswerNum() << std::endl;
    return 0;
}

