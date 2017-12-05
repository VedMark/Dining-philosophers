#!/bin/bash

f()
{
	./dining_philosophers $1 "$2"
}

f 0 'Immanuel Kant' 1>Kant.log 2>&1 &
f 1 'Baruch Spinoza'1>Spinoza.log 2>&1 &
f 2 'Friedrich Nietzsche' 1>Nietzsche.log 2>&1 &
f 3 'Arthur Schopenhauer' 1>Schopenhauer.log 2>&1 &
f 4 'Jean-Paul Sartre' 1>Sartre.log 2>&1 &

exit 0

