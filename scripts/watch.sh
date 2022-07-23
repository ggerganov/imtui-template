#!/bin/sh

if [ $# -ne 2 ]; then
    echo "Usage: $0 <src> <cmd>"
    exit 1
fi

killall fswatch

fswatch $1/* | while read line; do
    #echo "Building ..."

    cmake --build . > /dev/null 2>&1
done &

fswatch $2 | while read line; do
    #echo "Reloading ..."

    killall `basename $2`
done &

while true; do
    $2
    if [ $? -eq 0 ]; then
        break;
    fi
done

reset

exit 0
