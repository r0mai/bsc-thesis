*** Settings ***
Documentation   Tests that the logic involved in merging multiple databases
...             merges the databases as though the source was concatenated
...             before creating the database.

Library         Collections
Library         libraries/DatabaseLibrary.py
Test Setup      Clear Databases

*** Test Cases ***
Empty database and single variable database merge to single variable database
    Given Empty database
      And Database with one variable
     When Databases are merged
     Then The merged database has ${1} variables

*** Keywords ***
Empty Database
    ${database} =   Make Database
    Append To List     ${databases}  ${database}

Database with one Variable
    ${variable} =   Make Variable  int  a  test.cpp:1:1
    ${database} =   Make Database  ${variable}
    Append To List      ${databases}  ${database}

Databases are merged
    ${merged_database} =  Merge Databases  ${databases}
    Set Test Variable  ${merged_database}

The merged database has ${n} variables
    Length Should Be  ${merged_database.variables}  1

Clear Databases
    @{databases} =  Create List
    Set Test Variable  ${databases}