# bsc-thesis [![Build Status](https://travis-ci.org/matthiasvegh/bsc-thesis.svg?branch=master)](https://travis-ci.org/matthiasvegh/bsc-thesis)

This repository contains my Bachelor's Thesis.

## Title
Clang-based Variable Name Suggestions for C++

## Description
Variable-naming is a non-trivial activity of developers. The motivation
of this thesis is to aid developers in this when writing C++ code.

The programs written in this thesis will be able to provide the user
with suggestions for variable names after initial analysis of the
user-supplied project. This analysis will be done with a plug-in written
for the Clang C++ compiler, which will track variables across all
translation units. After analysis, a separate program will allow the
user to ask for suggestions for replacement names of variables present
in the code.

Suggestions made shall be based on the names present in the supplied
project, will follow the naming conventions in it, taking into account
the type, and usage of the variable.
