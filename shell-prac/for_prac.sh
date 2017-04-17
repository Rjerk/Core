#!/bin/bash

for planet in Mercury Venus Earth Mars Jupiter Saturn Uranus Neptune Pluto
do
    echo $planet
done

echo; echo

for planet in "Mercury Venus Earth Mars Jupiter Saturn Uranus Neptune Pluto"
do
    echo $planet
done

echo; echo "Whoops! Pluto is no longer a planet!"

echo; echo

for planet in "Mercury 36" "Venus 67" "Earth 93" "Mars 142" "Jupiter 483"
do
    set -- $planet
    echo "$1 $2,000,000 miles from the sun."
done

exit 0
