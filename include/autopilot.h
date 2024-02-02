#ifndef AUTOPILOT_H
#define AUTOPILOT_H

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
#ifdef AUTOPILOT_EXPORTS
#define AUTOPILOT_API __declspec(dllexport)
#else
#define AUTOPILOT_API __declspec(dllimport)
#endif
#elif __GNUC__ >= 4
#define AUTOPILOT_API __attribute__((visibility("default")))
#else
#define AUTOPILOT_API
#endif

#ifndef explicit_link

#if __cplusplus
extern "C"
{
#endif

    // string alloc
    struct inface_string;
    typedef struct inface_string *inface_string_ptr;

    // string alloc and free
    AUTOPILOT_API inface_string_ptr alloc_string();
    AUTOPILOT_API int get_string_length(inface_string_ptr str);
    AUTOPILOT_API int get_string_context(inface_string_ptr str, char *buffer, int buffer_size);
    AUTOPILOT_API void free_string(inface_string_ptr str);

    // error code
    AUTOPILOT_API int get_last_error();
    AUTOPILOT_API int get_error_define_count();
    AUTOPILOT_API int get_error_define(int index, inface_string_ptr result);

    // callback install an remove
    AUTOPILOT_API int get_task_callback_count();
    AUTOPILOT_API int get_task_callback_name(int index, inface_string_ptr result);
    AUTOPILOT_API int install_task_callback(const char *task_name, int (*callback)(const char * /*json*/));
    AUTOPILOT_API int remove_task_callback(const char *task_name);

#if __cplusplus
}
#endif

#else // explicit_link

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
#include <Windows.h>
#define library_handle_t HMODULE
#define load_lib(path) LoadLibrary(path.c_str())
#define free_lib(lib) FreeLibrary(lib)
#define get_proc(lib, name) GetProcAddress(lib, name)
#else
#include <dlfcn.h>
#define library_handle_t void *
#define load_lib(path) dlopen(path.c_str(), RTLD_LAZY)
#define free_lib(lib) dlclose(lib)
#define get_proc(lib, name) dlsym(lib, name)
#endif
#include <string>
#include <memory>
#include <functional>

struct inface_string;
typedef struct inface_string *inface_string_ptr;

typedef inface_string_ptr (*alloc_string_t)();
typedef int (*get_string_length_t)(inface_string_ptr str);
typedef int (*get_string_context_t)(inface_string_ptr str, char *buffer, int buffer_size);
typedef void (*free_string_t)(inface_string_ptr str);
typedef int (*get_last_error_t)();
typedef int (*get_error_define_count_t)();
typedef int (*get_error_define_t)(int index, inface_string_ptr result);

typedef bool (*get_task_callback_count_t)();
typedef bool (*get_task_callback_name_t)(int index, inface_string_ptr result);
typedef bool (*install_task_callback_t)(const char *task_name, int (*callback)(const char * /*json*/));
typedef bool (*remove_task_callback_t)(const char *task_name);

struct inface
{
    library_handle_t lib;

    bool is_valid = false;

    alloc_string_t alloc_string_func;
    get_string_length_t get_string_length_func;
    get_string_context_t get_string_context_func;
    free_string_t free_string_func;
    get_last_error_t get_last_error_func;
    get_error_define_count_t get_error_define_count_func;
    get_error_define_t get_error_define_func;

    get_task_callback_count_t get_task_callback_count_func;
    get_task_callback_name_t get_task_callback_name_func;
    install_task_callback_t install_task_callback_func;
    remove_task_callback_t remove_task_callback_func;

    inface(std::string path)
    {
        lib = load_lib(path);
        if (lib == nullptr)
            return;
        is_valid = true;

        alloc_string_func = (alloc_string_t)get_proc(lib, "alloc_string");
        get_string_length_func = (get_string_length_t)get_proc(lib, "get_string_length");
        get_string_context_func = (get_string_context_t)get_proc(lib, "get_string_context");
        free_string_func = (free_string_t)get_proc(lib, "free_string");
        get_last_error_func = (get_last_error_t)get_proc(lib, "get_last_error");
        get_error_define_count_func = (get_error_define_count_t)get_proc(lib, "get_error_define_count");
        get_error_define_func = (get_error_define_t)get_proc(lib, "get_error_define");

        get_task_callback_count_func = (get_task_callback_count_t)get_proc(lib, "get_task_callback_count");
        get_task_callback_name_func = (get_task_callback_name_t)get_proc(lib, "get_task_callback_name");
        install_task_callback_func = (install_task_callback_t)get_proc(lib, "install_task_callback");
        remove_task_callback_func = (remove_task_callback_t)get_proc(lib, "remove_task_callback");
    }
    ~inface()
    {
        if (lib != nullptr)
            free_lib(lib);
    }

    inface_string_ptr alloc_string()
    {
        if (alloc_string_func == nullptr)
            return nullptr;
        return alloc_string_func();
    }
    int get_string_length(inface_string_ptr str)
    {
        if (get_string_length_func == nullptr)
            return 0;
        return get_string_length_func(str);
    }
    int get_string_context(inface_string_ptr str, char *buffer, int buffer_size)
    {
        if (get_string_context_func == nullptr)
            return 0;
        return get_string_context_func(str, buffer, buffer_size);
    }
    void free_string(inface_string_ptr str)
    {
        if (free_string_func == nullptr)
            return;
        free_string_func(str);
    }
    int get_last_error()
    {
        if (get_last_error_func == nullptr)
            return 0;
        return get_last_error_func();
    }
    int get_error_define_count()
    {
        if (get_error_define_count_func == nullptr)
            return 0;
        return get_error_define_count_func();
    }
    int get_error_define(int index, inface_string_ptr result)
    {
        if (get_error_define_func == nullptr)
            return 0;
        return get_error_define_func(index, result);
    }

    int get_task_callback_count()
    {
        if (get_task_callback_count_func == nullptr)
            return 0;
        return get_task_callback_count_func();
    }
    int get_task_callback_name(int index, inface_string_ptr result)
    {
        if (get_task_callback_name_func == nullptr)
            return 0;
        return get_task_callback_name_func(index, result);
    }
    int install_task_callback(const char *task_name, int (*callback)(const char * /*json*/))
    {
        if (install_task_callback_func == nullptr)
            return 0;
        return install_task_callback_func(task_name, callback);
    }
    int remove_task_callback(const char *task_name)
    {
        if (remove_task_callback_func == nullptr)
            return 0;
        return remove_task_callback_func(task_name);
    }

    std::string get_error_define(int index)
    {
        auto alloc_res = alloc_string();
        auto get_error_define_res = get_error_define(index, alloc_res);
        auto get_string_length_res = get_string_length(alloc_res);
        char buffer[1024] = {0};
        auto get_string_context_res = get_string_context(alloc_res, buffer, sizeof(buffer));
        std::string result = buffer;
        free_string(alloc_res);
        return result;
    }
    std::string get_task_callback_name(int index)
    {
        auto alloc_res = alloc_string();
        auto get_task_callback_name_res = get_task_callback_name(index, alloc_res);
        auto get_string_length_res = get_string_length(alloc_res);
        char buffer[1024] = {0};
        auto get_string_context_res = get_string_context(alloc_res, buffer, sizeof(buffer));
        std::string result = buffer;
        free_string(alloc_res);
        return result;
    }
};

#endif // explicit_link

#endif // AUTOPILOT_H
