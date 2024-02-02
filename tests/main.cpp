

#include <iostream>

#define explicit_link
#include <autopilot.h>

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
#define lib_name "autopilot.dll"
#else
#define lib_name "libautopilot.so"
#endif
bool init()
{

    auto fp = fopen(lib_name, "rb");
    std::shared_ptr<FILE> fp_ptr(fp, [](FILE *fp)
                                 { if(fp)fclose(fp); });
    if (fp_ptr == nullptr)
    {
        std::cout << lib_name " not found" << std::endl;
        return 0;
    }
    return 1;
}

int main()
{
    if (!init())
        return 0;
    std::cout << "init success" << std::endl;

    inface inface(lib_name);
    if (!inface.is_valid)
    {
        std::cout << "inface is invalid" << std::endl;
        return 0;
    }

    auto alloc_res = inface.alloc_string();
    if (alloc_res == nullptr)
    {
        std::cout << "alloc_res is nullptr" << std::endl;
        return 0;
    }
    int error_define_count = inface.get_error_define_count();
    std::cout << "error_define_count: " << error_define_count << std::endl;
    for (int i = 0; i < error_define_count; i++)
    {
        std::cout << "error_define[" << i << "]: " << inface.get_error_define(i) << std::endl;
    }
    int task_callback_count = inface.get_task_callback_count();
    std::cout << "task_callback_count: " << task_callback_count << std::endl;
    for (int i = 0; i < task_callback_count; i++)
    {
        std::cout << "task_callback[" << i << "]: " << inface.get_task_callback_name(i) << std::endl;
    }

    return 0;
}