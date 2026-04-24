#!/usr/bin/env bash
set -euo pipefail

if [[ $# -lt 1 || $# -gt 2 ]]; then
    echo "Usage: $0 <input.ppm> [output-name-no-ext]" >&2
    exit 84
fi

input_ppm="$1"
if [[ ! -f "$input_ppm" ]]; then
    echo "error: input file not found: $input_ppm" >&2
    exit 84
fi

mkdir -p screenshots

base_name="${2:-$(basename "$input_ppm" .ppm)}"
output_png="screenshots/${base_name}.png"

if command -v magick >/dev/null 2>&1; then
    magick "$input_ppm" "$output_png"
elif command -v convert >/dev/null 2>&1; then
    convert "$input_ppm" "$output_png"
elif command -v ffmpeg >/dev/null 2>&1; then
    ffmpeg -loglevel error -y -i "$input_ppm" "$output_png"
else
    echo "error: need one converter installed: magick, convert, or ffmpeg" >&2
    exit 84
fi

echo "snapshot created: $output_png"
