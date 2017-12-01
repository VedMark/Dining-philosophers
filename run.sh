#!/bin/bash

f()
{
	./dining_philosophers $1 "$2"
}

f 0 'Immanuel Kant' &
f 1 'Baruch Spinoza' &
f 2 'Friedrich Nietzsche' &
f 3 'Arthur Schopenhauer' &
f 4 'Jean-Paul Sartre' &

exit 0

