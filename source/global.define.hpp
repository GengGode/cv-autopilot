#include <string>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <any>
#include <optional>
#include <expected>
#include <memory>
#include <thread>

struct context
{
    std::expected<std::string, std::shared_ptr<context>> feel;

    struct where
    {
        std::vector<std::string> position_names;
        std::map<std::string, std::pair<std::string, int>> position_map;
    };
    struct have
    {
        std::vector<std::string> has_key_names;
        std::map<std::string, std::optional<std::any>> has_same_map;
    };
    struct cando
    {
    };
};

struct insighter
{
    std::weak_ptr<context> now_context;
    std::list<std::shared_ptr<context>> context_queue;
    std::list<std::shared_ptr<context>> deep_context_queue;

    void focus_attention(int attentio_intensity = 100)
    {
        if (deep_context_queue.size() > attentio_intensity)
        {
            // remove the oldest context to keep the queue size
            for (int i = 0; i < deep_context_queue.size() - attentio_intensity; i++)
            {
                deep_context_queue.pop_front();
            }
        }
    }

    void feel_me()
    {
    }

    void feel_time() {}

    void feeling() {}

    std::weak_ptr<std::jthread> deep_understand;
};