*** Settings ***
Library         OperatingSystem
Library         Process
Library         libraries/Variables.py

*** Variables ***
${varnames}     /tmp/varnames.json


*** Test Cases ***
No Variables Should Make Variables Empty
    [Documentation]     Tests that an empty file produces an empty output.
    Given Empty File is Passed To Analyzer
     Then Variables Should Have ${0} Entries

Single Variable Makes Variables Have 1 Entry
    [Documentation]     Tests that an file with a single variable produces an
    ...                 output with a single entry.
    Given File single_int.cpp is Passed to Analyzer
     Then Variables Should Have ${1} Entries

Single Argument Makes Variables Have 1 Entry
    [Documentation]     Tests that an file with a single function with a single
    ...                 argument produces an output with a single entry.
    Given File single_int_argument.cpp is Passed to Analyzer
     Then Variables Should Have ${1} Entries


*** Keywords ***
Empty File is Passed To Analyzer
    Get Variable Name Analysis From Source  empty.cpp

File ${filename} is Passed to Analyzer
    Get Variable Name Analysis From Source  ${filename}


Variables Should Have ${n} entries
    ${variables} =  Get Resulting Variables
    Length Should Be  ${variables}  ${n}

Get Resulting Variables
    ${result} =     Load Variables From Analysis  ${analysis}
    [Return]        ${result}


Make Variables
    [Arguments]     &{kwargs}
    ${result} =     Create Dictionary  &{kwargs}
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
