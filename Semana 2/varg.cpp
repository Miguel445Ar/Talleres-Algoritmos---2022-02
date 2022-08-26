#include <iostream>
#include <string>
#include <stdarg.h>

using std::string;

void __cdecl myPrintf(const char* buffer,...) {
    using std::cout;

    va_list tag;
    string s = buffer; // O(|buffer|)

    va_start(tag,buffer);
    
    for(size_t i = 0; i < s.length(); ++i){ // O(|buffer|)
        if(s[i] != '%' || i == s.length() - 1) {
            cout << s[i];
            continue;
        }
        switch(s[i + 1]) {
            case 's': cout << va_arg(tag,char*); break;
            case 'd': cout << va_arg(tag,int); break;
            case 'f': cout << va_arg(tag,double); break;
            case 'c': cout << (char)(va_arg(tag,int)); break;
            case 'm': cout << va_arg(tag,void*); break;
        }
        ++i;
    }
    va_end(tag);
}

int main() {
    char n = 19;
    printf("");
    myPrintf("Mi nombre es %s y mi edad es %f, %d, %s, %m", "Miguel", 19.5, 8, "XDDD",&n);
    return 0;
}