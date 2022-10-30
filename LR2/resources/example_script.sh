#!/bin/bash

while IFS=, read -r line
do
  echo "query: " $line
  echo "output: {" 
  ../build/xml_project "$line"

  echo "}"
  echo
done < queries.txt
