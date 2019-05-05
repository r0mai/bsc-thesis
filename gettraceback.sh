#!/usr/bin/env bash

REPO_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && git rev-parse --show-toplevel )"

"$@" 3>&2 2>&1 1>&3 | sed "s|${REPO_DIR}|.|g"
