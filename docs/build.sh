#!/bin/bash

cd "$(dirname "$0")"

typst compile --root .. main.typ
