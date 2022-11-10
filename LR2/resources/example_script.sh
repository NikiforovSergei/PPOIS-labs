#!/bin/bash

while IFS=, read -r line
do
  echo "query: " $line
  echo "output: {" 
  ../build/xml_project "/Users/glebchanskiy/main/PPOIS-labs/LR2/resources/input.xml" "$line"

  echo "}"
  echo
done < queries.txt
