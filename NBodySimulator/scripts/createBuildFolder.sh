#!/usr/bin/env bash

project_dir=$(pwd)

echo "$project_dir"

build_dir="$project_dir/build"

rm -rd "$build_dir"
rsync -av -f"+ */" -f"- *" "$project_dir/" "$build_dir"
