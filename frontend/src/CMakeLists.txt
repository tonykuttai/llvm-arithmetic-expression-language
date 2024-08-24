# src/CMakeLists.txt

# Specify the source files
set(SOURCES Lexer.cpp)

# Create a library or executable (e.g., a static library)
add_library(frontend_lib ${SOURCES})

# Link against any required libraries here
target_link_libraries(frontend_lib ${llvm_libs})
