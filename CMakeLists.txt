find_package(Boost REQUIRED)

# https://github.com/rizsotto/Constantine/blob/master/src/CMakeLists.txt
add_library(RenameVariablesA OBJECT
    src/AstAction.cpp
    src/AstConsumer.cpp
    src/AstVisitor.cpp
    src/VariableDeclaration.cpp
)

target_include_directories(RenameVariablesA PUBLIC
    include
    ${Boost_INCLUDE_DIRS}
)

target_compile_options(RenameVariablesA PRIVATE
    -fno-rtti
)

add_library(RenameVariables SHARED
    src/plugin.cpp
)

target_link_libraries(RenameVariables
    RenameVariablesA
)

target_link_options(RenameVariables PUBLIC "LINKER:-flat_namespace,-undefined,suppress")
