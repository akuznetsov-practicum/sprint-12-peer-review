cmake_minimum_required(VERSION 3.10.0)

add_compile_options(-Wall -Wextra -Wpedantic -O0)

project(ebook VERSION 0.1.0 LANGUAGES CXX)

add_executable(ebook)

add_subdirectory(src)

set_target_properties(ebook PROPERTIES CXX_STANDARD 20)
add_custom_command(TARGET ebook POST_BUILD
    COMMAND objcopy --only-keep-debug ebook ebook.dbg
    COMMAND objcopy --strip-all ebook
    COMMAND objcopy --add-gnu-debuglink=ebook.dbg ebook
)
