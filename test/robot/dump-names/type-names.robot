*** Settings ***
Library         OperatingSystem
Library         Process
Library         libraries/TypeNames.py

*** Variables ***
${varnames}     /tmp/varnames.json


*** Test Cases ***
No Variables Should Make TypeNames Empty
    Given Empty File is Passed To Analyzer
     Then TypeNames Should Have ${0} Entries

Single Variable Makes TypeNames Have 1 Entry
    Given File single_int.cpp is Passed to Analyzer
     Then TypeNames Should Have ${1} Entries

Single Argument Makes TypeNames Have 1 Entry
    Given File single_int_argument.cpp is Passed to Analyzer
     Then TypeNames Should Have ${1} Entries


*** Keywords ***
Empty File is Passed To Analyzer
    Get Variable Name Analysis From Source  empty.cpp

File ${filename} is Passed to Analyzer
    Get Variable Name Analysis From Source  ${filename}


TypeNames Should Have ${n} entries
    ${typenames} =  Get Resulting Typenames
    Length Should Be  ${typenames}  ${n}

Get Resulting Typenames
    ${result} =     Load Typenames From Analysis  ${analysis}
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
