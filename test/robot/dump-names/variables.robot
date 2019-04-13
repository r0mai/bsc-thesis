*** Settings ***
Documentation   Tests that the part of the database that stores information
...             about variable declarations is correct.
Library         OperatingSystem
Library         Process
Library         libraries/Variables.py

*** Variables ***
${varnames}     /tmp/varnames.json


*** Test Cases ***
No Variables Should Make Variables Empty
    [Documentation]     Tests that an empty file produces an empty output.
    Given Empty File is Passed To Analyzer
     Then Variables Should Be Empty

Single Variable Makes Variables Have 1 Entry
    [Documentation]     Tests that an file with a single variable produces an
    ...                 output with a single entry.
    ...                 As this argument is modified twice, there should be two
    ...                 occurences.
    Given File single_int.cpp is Passed to Analyzer
     Then There Should Be ${1} Entries that Occur ${2} Times

Single Argument Makes Variables Have 1 Entry
    [Documentation]     Tests that a file with a single function with a single
    ...                 argument produces an output with a single entry.
    Given File single_int_argument.cpp is Passed to Analyzer
     Then There Should Be ${1} Entries that Occur ${1} Times

Single Unnamed Argument Makes Variables Empty
    [Documentation]     Tests that a file with a single function with a single
    ...                 unnamed argument produces an output with no entries.
    Given File unnamed_int_argument.cpp is Passed to Analyzer
     Then There Should Be ${0} Entries that Occur ${0} Times

Single Member of Struct Makes Variables Have 1 Entry
    [Documentation]     Tests that a file with a single struct with a single
    ...                 member produces an output with a single entry.
    Given File single_struct_member.cpp is Passed to Analyzer
     Then There Should Be ${1} Entries that Occur ${0} Times


*** Keywords ***
Empty File is Passed To Analyzer
    Get Variable Name Analysis From Source  empty.cpp

File ${filename} is Passed to Analyzer
    Get Variable Name Analysis From Source  ${filename}

Variables Should Be Empty
    ${variables} =  Get Resulting Variables
    Should Be Empty  ${variables}

There Should Be ${n} Entries that Occur ${k} times
    ${variables} =  Get Resulting Variables
    Length Should Be  ${variables}  ${n}
    :FOR    ${ELEMENT}  IN  @{variables}
    \   Length Should Be    ${ELEMENT["occurences"]}  ${k}

Get Resulting Variables
    ${result} =     Load Variables From Analysis  ${analysis}
    [Return]        ${result}

Get Variable Name Analysis From Source
    [Arguments]     ${sourcefile}
    ${result} =     Run Process
    ...             clang++
    ...             -fplugin\=${dump_names}
    ...             -Xclang
    ...             -plugin-arg-dump-names
    ...             -Xclang
    ...             output-file
    ...             -Xclang
    ...             -plugin-arg-dump-names
    ...             -Xclang
    ...             ${varnames}
    ...             -c
    ...             ${input_directory}/${sourcefile}
    ...             -o
    ...             /dev/null
    Log             ${result.stderr}
    ...             level=DEBUG
    Should Be Equal  ${result.rc}  ${0}
    ${analysis} =    Get File  ${varnames}
    Set Test Variable  ${analysis}
