#!/bin/bash

for f in *.mp4; do
  echo mv "$f" \
    "$(awk -F '[._]' '{ si = sprintf("%02d", substr($5, 2));
  print $3 "_" $4 "_s" si "e" $1 "." $6 }' <<< $f)"
done 

# for fname in *.mp4; do
#   mv $fname "$(echo $fname | awk -F '[._]' '{si = sprintf("%02d", substr($5, 2)); print $3 "_" $4 "_" "s" si "e" $1 ".mp4"}')"
# done
