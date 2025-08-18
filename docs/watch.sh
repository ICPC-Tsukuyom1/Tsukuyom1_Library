#!/bin/bash

cd "$(dirname "$0")"

typst watch --root .. main.typ
