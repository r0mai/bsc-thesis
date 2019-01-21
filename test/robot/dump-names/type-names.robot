*** Settings ***
Library         OperatingSystem
Library         Process
Library         libraries/TypeNames.py

*** Variables ***
${varnames}     /tmp/varnames.json


*** Test Cases ***
No Variables Should Make TypeNames Empty
    Given Empty File is Passed To Analyzer
     Then TypeNames Should Be Empty


*** Keywords ***
Empty File is Passed To Analyzer
    Run Process  pwd
    Get Variable Name Analysis From Source  empty.cpp

Get Resulting Typenames
    ${result} =     Load Typenames From Analysis  ${analysis}
    [Return]        ${result}

TypeNames Should Be Empty
    ${typenames} =  Get Resulting Typenames
    Should Be Empty     ${typenames}


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
    Should Be Equal  ${result.rc}  ${0}
    ${analysis} =    Get File  ${varnames}
    Set Test Variable  ${analysis}
