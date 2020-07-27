# char 和 string 的区别  

字符数组和字符串最重要的区别是结尾处是否有\0  

字符数组可以存储字符串，整体输入时即是字符串形式  

sizeof()计算内存长度，strlen()/.length()/.size()计算眼见长度  

## 例子：
```C++
char a[] = {1, 2, 3};  

char b[] = {'l', 'o', 'v'}; // a, b 都是字符数组，sizeof(a) = sizeof(b) = 3   

char c[] = "lov"; // c是字符串，内存中存储的是 'l' 'o' 'v' '\0'，sizeof(c)=4，注意 sizeof 计算的是内存长度，sizeof("lov")=4  

char d[10]; cin>>d; //d也是字符串，注意 sizeof(d)=10, 即 d 向内存申请的空间，d 的真实长度用 strlen 计算，长度计算结果不包含 \0（所见即所得），如输入 lov，strlen(d) = 3  

char e[10] = {'l', 'o', 'v'};  

char f[10] = "lov"; // sizeof(e) = sizeof(f) = 10, strlen(e) = srelen(f) = 3  

char g[10]; cin.getline(h, 9); // 若输入lov lov， strlen(g) = 7 (包含空格），sizeof(g) = 10  

string h = "lov"; // sizeof(h) = 8，即字符串类型占8个字节，h.length() = h.size() = 3， 即 h 的真实长度（所见即所得）  

"lov".length(); // 会报错，因为 "lov" 应视为字符串常量，因此不能直接调用类方法  

```
---
# 静态变量的生存周期和作用域

不管是在全局还是局部声明的 static 变量都存放于程序的全局数据区域，它的生命周期是从程序开始到程序结束。但是 static 变量的作用域并不等同于它的生存周期，它的作用域决定于它被定义的位置。

把局部变量改变为静态局部变量后是改变了它的存储方式，即改变了它的生存期。把全局变量改变为静态全局变量后是改变了它的作用域，即限制了它的使用范围。
