*** Settings ***
Documentation   Tests that the compiler-plugin produces the appropriate
...             database for an input.
...             It achieves this by invoking the compiler with one or more
...             source files, and then validates the database.
Suite Setup  Set Suite Variable  ${input_directory}  ${CURDIR}/inputs  children=${TRUE}
