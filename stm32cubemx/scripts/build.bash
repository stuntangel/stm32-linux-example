#!/bin/bash
set -euox pipefail
cd "$(dirname "$0")/.."

type arm-none-eabi-gcc

# 開いているファイルの path を VS Code から受け取る
if [[ -v 1 ]]; then
  # pathの一番上を保存
  path="${1%%/*}"
  # ディレクトリが存在して, かつ, *.ioc ファイルが存在する場合
  ioc_file=$(find "$path" -maxdepth 1 -name "*.ioc" -print -quit)
  if [[ -d "$path" ]] && [[ -n "$ioc_file" ]]; then
    cd "$path"
  fi
fi

mkdir -p build
cd build
cmake ..
make -j$(nproc)
