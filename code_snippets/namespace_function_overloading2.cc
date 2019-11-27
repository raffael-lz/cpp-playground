#include <algorithm>
#include <iostream>
#include <vector>

/*
 * Method std::sort should be overloaded to accept sort(container) and not only
 * sort(container.begin, container.end)
 */

template <typename T> void print(const std::vector<T> &vec)
{
    for (const auto &elem : vec)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

namespace better_std
{
    using namespace std; // check StrStr page 412
    template <typename T>
        void sort(T& container)
        {
            std::cout << "overloaded sort" << std::endl;
            std::sort(container.begin(), container.end());
        }
}

int main()
{
    using namespace better_std;
    using namespace std;

    std::vector<int> vec{2, 6, 3, 8, 5, 7, 10};
    sort(vec.begin(), vec.end());
    print(vec);

    std::vector<float> vec2 {2.0, 6.0, 3.0f, 8.0f, 5.0f, 7.0f, 10.0f};
    sort(vec2);
    print(vec2);
}
