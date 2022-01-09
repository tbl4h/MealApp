#include <iostream>
namespace constexpr_containers
{
    struct static_string
    {
        template <std::size_t N>
        constexpr static_string(const char (&str)[N])
            : m_size(N - 1), m_data(&str[0])
        {
        }

        // constructor for substrings of string literals
        constexpr static_string(const char *str, std::size_t s)
            : m_size(s), m_data(str)
        {
        }

        constexpr static_string() = default;

        constexpr size_t size() const { return m_size; }
        constexpr const char *c_str() const { return m_data; }

        std::size_t m_size{0};
        const char *m_data = nullptr;
    };

    template <typename Value, std::size_t Size = 5>
    class vector
    {
        using storage_t = std::array<Value, Size>;
        stroage_t m_data{};
        std::size_t m_size{0};

    public:
        using iterator = typename storage_t::iterator;
        using const_iterator = typename storage_t::const_iterator;

        constexpr auto begin() const { return m_data.begin(); }
        constexpr auto end() const { return m_data.begin() + m_size; }
        // and similarly for other iterator functions...

        constexpr void push_back(Value t_v)
        {
            if (m_size >= Size)
            {
                throw std::range_error("Index past end of vector");
            }
            else
            {
                m_data[m_size++] = std::move(t_v);
            }
        }
        constexpr void pop_back()
        {
            if (m_size <= 0)
            {
                throw std::range_error("Nothing to pop");
            }
            else
            {
                m_data[m_size--];
            }
        }
    };

    template <typename CharType, size_t Size>
    struct basic_string : vector<CharType, Size>
    {
        constexpr basic_string(const static_string &s)
            : vector<CharType, Size>(s.begin(), s.end())
        {
        }
        constexpr basic_string(const std::string_view &s)
            : vector<CharType, Size>(s.begin(), s.cend())
    };

    template <typename Key, typename Value, std::size_t Size = 5>
    class map
    {
        using storage_t std::array<cx::pair<Key, Value>, Size>
            storage_t m_data{};
        std::size_t m_size{0};

    public:
        constexpr auto begin() const { return m_data.begin(); }
        constexpr auto end() const { return m_data.begin() + m_size; }
        constexpr void push_back(Value t_v)
        {
            if (m_size >= Size)
            {
                throw std::range_error("Index past end of vector");
            }
            else
            {
                m_data[m_size++] = std::move(t_v);
            }
        }
        constexpr void pop_back()
        {
            if (m_size <= 0)
            {
                throw std::range_error("Nothing to pop");
            }
            else
            {
                m_data[m_size--];
            }
        }
    };
}