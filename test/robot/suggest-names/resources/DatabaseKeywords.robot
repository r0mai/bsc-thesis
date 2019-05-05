*** Settings ***
Library         Collections

*** Keywords ***
Empty database
    ${database} =       Make database
    Append To List      ${databases}    ${database}

Single variable
    [Arguments]         @{occurences}
    ${variable} =       Make variable   int     a
    ...                         test.cpp:1:1    ${occurences}
    Set Test Variable   ${variable}
    [Return]            ${variable}

Database with one variable
    ${variable} =       Single Variable
    ${database} =       Make Database   ${variable}
    Append To List      ${databases}    ${database}

Stale database
    ${variable} =       Make Variable   int     stale
    ...                         /non_existent:1:1
    ${database} =       Make Database   ${variable}
    ...                         filename="/non_existent"
    Append To List      ${databases}  ${database}

Database with one variable and one occurence
    ${variable} =       Single variable     test.cpp:2:1
    ${database} =       Make database  ${variable}
    Append To List      ${databases}  ${database}

Database with one variable and an other occurence
    ${variable} =       Single variable     test2.cpp:2:1
    ${database} =       Make database  ${variable}
    Append To List      ${databases}  ${database}

Database with an other variable
    ${variable} =       Make variable  int  b   test.cpp:2:1
    ${database} =       Make database  ${variable}
    Append To List      ${databases}  ${database}

Databases are merged
    ${merged_database} =    Merge databases   ${databases}
    Set Test Variable   ${merged_database}

The merged database has ${n} variables
    Length Should Be    ${merged_database.variables}  ${n}

Each ${n} variables have ${k} occurences
    Length Should Be    ${merged_database.variables}  ${n}
    :FOR    ${ELEMENT}  IN  @{merged_database.variables}
    \   Length Should Be  ${ELEMENT.occurences}  ${k}

Clear Databases
    @{databases} =      Create List
    Set Test Variable   ${databases}

Clear Variable
    ${variable} =       Evaluate    None
    Set Test Variable   ${variable}
