*** Settings ***
Library         Collections

*** Keywords ***
Empty Database
    ${database} =   Make Database
    Append To List     ${databases}  ${database}

Single Variable
    [Arguments]         @{occurences}
    ${variable} =       Make Variable  int  a  test.cpp:1:1  ${occurences}
    Set Test Variable   ${variable}
    [Return]            ${variable}

Database with one variable
    ${variable} =   Single Variable
    ${database} =   Make Database  ${variable}
    Append To List      ${databases}  ${database}

Database with one variable and one occurence
    ${variable} =   Single Variable  test.cpp:2:1
    ${database} =   Make Database  ${variable}
    Append To List      ${databases}  ${database}

Database with one variable and an other occurence
    ${variable} =   Single Variable  test2.cpp:2:1
    ${database} =   Make Database  ${variable}
    Append To List      ${databases}  ${database}

Database with an other variable
    ${variable} =   Make Variable  int  b  test.cpp:2:1
    ${database} =   Make Database  ${variable}
    Append To List      ${databases}  ${database}

Databases are merged
    ${merged_database} =  Merge Databases  ${databases}
    Set Test Variable  ${merged_database}

The merged database has ${n} variables
    Length Should Be  ${merged_database.variables}  ${n}

Then Each ${n} variables have ${k} occurences
    Length Should Be  ${merged_database.variables}  ${n}
    :FOR    ${ELEMENT}  IN  @{merged_database.variables}
    \   Length Should Be  ${ELEMENT.occurences}  ${k}

Clear Databases
    @{databases} =  Create List
    Set Test Variable  ${databases}

Clear Variable
    ${variable} =  Evaluate  None
    Set Test Variable  ${variable}
