#ifndef TB_APP_API_VERSION_HPP
#define TB_APP_API_VERSION_HPP

#define API_VERSION_MAJOR 1
#define API_VERSION_MINOR 0

// Two-stage macro expansion to force evaluation of API_VERSION_MAJOR
#define TB_CONCAT_IMPL(x, y) x ## y
#define TB_CONCAT(x, y) TB_CONCAT_IMPL(x, y)

#define TB_API_VERSION_NAMESPACE inline namespace TB_CONCAT(v, API_VERSION_MAJOR)

#endif // TB_APP_API_VERSION_HPP