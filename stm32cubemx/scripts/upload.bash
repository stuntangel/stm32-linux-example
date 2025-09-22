#!/bin/bash
set -euox pipefail
cd "$(dirname "$0")/.."

# 開いているファイルの path を VS Code から受け取る
if [[ -v 1 ]]; then
  # pathの一番上を保存
  path="${1%%/*}"
  # ディレクトリが存在して, かつ, *.ioc ファイルが存在する場合
  ioc_file=$(find "$path" -maxdepth 1 -name "*.ioc" -print -quit)
  if [[ -d "$path" ]] && [[ -n "$ioc_file" ]]; then
    cd "$path"
    project_name=$(basename "$ioc_file" .ioc)
  fi
else
  project_name="$(basename "$(pwd)")"
fi

echo "Uploading. Please wait..."
cp -v "build/${project_name}.bin" "/media/${USER}/NOD_F446RE"
echo "Upload successful"
