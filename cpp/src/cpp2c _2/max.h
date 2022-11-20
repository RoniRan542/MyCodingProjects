#define TEMPLATE_MAX(T)       \
    T Max_##T(T a, T b)       \
    {                         \
        return a > b ? a : b; \
    }
