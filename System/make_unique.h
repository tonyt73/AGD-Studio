#ifndef make_unique_H
#define make_unique_H
#if defined(__ANDROID__) && defined(__arm__)
#include <memory>
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
#endif  // Android
#endif // make_unique_H
