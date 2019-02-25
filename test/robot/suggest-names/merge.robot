*** Settings ***
Documentation   Tests that the logic involved in merging multiple databases
...             merges the databases as though the source was concatenated
...             before creating the database.

Library         Collections
Library         libraries/DatabaseLibrary.py
Test Setup      Clear Databases

*** Test Cases ***
Empty database and empty database merge to empty database
    Given Empty database
      And Empty database
     When Databases are merged
     Then The merged database has ${0} variables

Empty database and single variable database merge to single variable database
    Given Empty database
      And Database with one variable
     When Databases are merged
     Then The merged database has ${1} variables

Two single variable databases merge to database with one variable
    Given Database with one variable
      And Database with one variable
     When Databases are merged
     Then The merged database has ${1} variables

Two different single variable databases merge to database with two variables
    Given Database with one variable
      And Database with an other variable
     When Databases are merged
     Then The merged database has ${2} variables

*** Keywords ***
Empty Database
    ${database} =   Make Database
    Append To List     ${databases}  ${database}

Database with one variable
    ${variable} =   Make Variable  int  a  test.cpp:1:1
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
