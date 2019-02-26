*** Settings ***
Documentation   Tests that the logic involved in merging multiple databases
...             merges the databases as though the source was concatenated
...             before creating the database.

Library         libraries/DatabaseLibrary.py
Resource        resources/DatabaseKeywords.robot
Test Setup      Run Keywords
...             Clear Databases
...             Clear Variable

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
