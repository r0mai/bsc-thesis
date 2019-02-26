*** Settings ***
Documentation   Tests that the logic involved in suggesting variables based on
...             complete information is correct.

Library         libraries/DatabaseLibrary.py
Resource        resources/DatabaseKeywords.robot
Test Setup      Run Keywords
...             Clear Databases
...             Clear Suggestions
...             Clear Variable

*** Test Cases ***
Database with one variable should suggest its own name
    Given Database with one variable
      And Databases are merged
     When Suggestions are requested
     Then Suggestions have ${1} elements

*** Keywords ***
Suggestions are requested
    ${suggestions} =    Make suggestions  ${merged_database}  ${variable}
    Set Test Variable   ${suggestions}

Suggestions have ${n} elements
    Length Should Be  ${suggestions}  ${n}

Clear Suggestions
    @{suggestions} =  Create List
    Set Test Variable  ${suggestions}
