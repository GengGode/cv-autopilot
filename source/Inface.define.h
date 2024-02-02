#ifndef __INFACE_DEFINE_H__
#define __INFACE_DEFINE_H__
#include <string>
#include <map>
#include <functional>

// string alloc
struct inface_string
{
    std::string context;
};
typedef struct inface_string *inface_string_ptr;

// task map
inline static std::map<std::string, std::function<int(std::string)>> inface_task_map = {
    {"download_start", nullptr},
    {"download_progress", nullptr},
    {"download_failed", nullptr},
    {"download_success", nullptr}};
// value map
inline static std::map<std::string, std::string> inface_value_map = {
    {"cvAutoTrack dll path", "./"},
    {"cvAutoTrack dll name", "cvAutoTrack.dll"},
    {"cvAutoTrack download url path", "https://download.api.weixitianli.com/cvAutoTrack/downloadUrl"},
    {"cvAutoTrack download cache name", "cvAutoTrack.zip"}};

#endif // __INFACE_DEFINE_H__
