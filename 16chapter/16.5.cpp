/*********************************************************************************
*     File Name           :     16.5.cpp
*     Created By          :     edward
*     Creation Date       :     [2015-04-26 11:16]
*     Last Modified       :     [2015-04-26 11:19]
*     Description         :      
**********************************************************************************/
int main(){
    const char *const str = "ssss";
    const char *const str1 = "ssss";
    const char *const &p = str;
    const char &p1 = *str;
    p1 = str1;
}
