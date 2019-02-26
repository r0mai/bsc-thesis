*** Settings ***
Library         Collections

*** Keywords ***
Empty Database
    ${database} =   Make Database
    Append To List     ${databases}  ${database}

Single Variable
    ${variable} =       Make Variable  int  a  test.cpp:1:1
    Set Test Variable   ${variable}
    [Return]            ${variable}

Database with one variable
    ${variable} =   Single Variable
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

Clear Databases
    @{databases} =  Create List
    Set Test Variable  ${databases}

Clear Variable
    ${variable} =  Evaluate  None
    Set Test Variable  ${variable}
