#!/usr/bin/env bash

set -euo pipefail

if [[ $# -ne 1 ]]; then
  echo "Usage: $0 <input-file>" >&2
  exit 1
fi

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
INPUT_ARG="$1"

if [[ "$INPUT_ARG" = /* ]]; then
  INPUT_PATH="$INPUT_ARG"
else
  INPUT_PATH="$ROOT_DIR/$INPUT_ARG"
fi

if [[ ! -f "$INPUT_PATH" && -f "$ROOT_DIR/tools/$INPUT_ARG" ]]; then
  INPUT_PATH="$ROOT_DIR/tools/$INPUT_ARG"
fi

if [[ ! -f "$INPUT_PATH" ]]; then
  echo "input file not found: $INPUT_ARG" >&2
  exit 1
fi

mkdir -p "$ROOT_DIR/build"
cmake -S "$ROOT_DIR" -B "$ROOT_DIR/build"
cmake --build "$ROOT_DIR/build"

OUT_FILE="$ROOT_DIR/out.txt"
"$ROOT_DIR/build/ahc062" < "$INPUT_PATH" > "$OUT_FILE"

INPUT_FOR_VIS="$INPUT_PATH"
case "$INPUT_PATH" in
  "$ROOT_DIR/tools/"*)
    INPUT_FOR_VIS="${INPUT_PATH#"$ROOT_DIR/tools/"}"
    ;;
esac

(
  cd "$ROOT_DIR/tools"
  cargo run -r --bin vis "$INPUT_FOR_VIS" "$OUT_FILE"
)

echo "Generated:"
echo "  output: $OUT_FILE"
echo "  visualizer: $ROOT_DIR/tools/vis.html"

