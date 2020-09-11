#include "test.h"

int main()
{
    /*************************************************************
    * 模板的声明和定义分开，会导致链接期出现错误
    * 下面定义了类a，但是main只能看到test.h文件，也就是只看到了类的声明，不知道如何实现，
    * 所以编译器会认为实现方式在其他的.cpp文件中，而不对下面的类声明进行实例化，
    * 因此没有得到模板的特化，导致链接时找不到定义。
    * 
    * 模板的实现必须与具体的使用结合才能被编译。
    *************************************************************/
    test<int> a(2);
    return 0;
}