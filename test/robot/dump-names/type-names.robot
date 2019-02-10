*** Settings ***
Library         OperatingSystem
Library         Process
Library         libraries/InputBuilder.py
Library         libraries/Variables.py

Test Setup      Remove File     ${sourcefile}
Test Teardown   Remove File     ${sourcefile}

*** Variables ***
${sourcefile}   /tmp/test.cpp
${varnames}     /tmp/varnames.json


*** Test Cases ***
No Variables Should Make Variables Empty
    Given Empty File is Passed To Analyzer
     Then Variables Should Be Empty


*** Keywords ***
Empty File is Passed To Analyzer
    ${vars} =       Make Variables
    ${source} =     Get Source  ${vars}
    Get Variable Name Analysis From Source  ${source}

Get Resulting Variables
    ${result} =     Load Variables From Analysis  ${analysis}
    [Return]        ${result}

Variables Should Be Empty
    ${typenames} =  Get Resulting Variables
    Should Be Empty     ${typenames}


Make Variables
    [Arguments]     &{kwargs}
    ${result} =     Create Dictionary  &{kwargs}
    [Return]        ${result}

Get Variable Name Analysis From Source
    [Arguments]     ${source}
    Create File     path=${sourcefile}  content=${source}
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
    ...             ${sourcefile}
    ...             -o
    ...             /dev/null
    Should Be Equal  ${result.rc}  ${0}
    ${analysis} =    Get File  ${varnames}
    Set Test Variable  ${analysis}
