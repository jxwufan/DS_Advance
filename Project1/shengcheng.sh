#!/bin/bash
for i in $(seq 10); 
do
./generator > input$i
./bit < input$1 >output$i
done;

