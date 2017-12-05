#!/bin/bash

f()
{
  ./dining_philosophers $1 "$2"
}

pids=[]
mkdir -p logs

f 0 'Immanuel Kant' 2>&1 | tee logs/Kant.log &
f 1 'Baruch Spinoza' 2>&1 | tee logs/Spinoza.log &
f 2 'Friedrich Nietzsche' 2>&1 | tee logs/Nietzsche.log &
f 3 'Arthur Schopenhauer' 2>&1 | tee logs/Schopenhauer.log &
f 4 'Jean-Paul Sartre' 2>&1 | tee logs/Sartre.log &

for job in `jobs -p`
do
  wait $job
done

exit 0

