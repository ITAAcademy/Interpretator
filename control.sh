#!/bin/bash
PROGRAM_FOLDER=/var/www/fcgi/
PROGRAM_NAME=test.fcgi
SOCKET_PATCH=/var/www/fcgi/mysocket
if [[ $1 == a ]]
then
echo "Програма запущена в фоні"
sudo spawn-fcgi -s $SOCKET_PATCH -n $PROGRAM_FOLDER$PROGRAM_NAME &
elif [[ $1 == r ]]
then
sudo killall $PROGRAM_NAME
sudo sudo spawn-fcgi -s $SOCKET_PATCH -n $PROGRAM_FOLDER$PROGRAM_NAME &
elif [[ $1 == k ]]
then
sudo killall $PROGRAM_NAME
elif [[ $1 == p ]]
then
sudo sudo spawn-fcgi -p $2 -n $PROGRAM_FOLDER$PROGRAM_NAME &
else
echo "Виконати fcgi-программу у фоні (y\n)?"
read answer
if [[ $answer == y ]]
then
echo "Програма запущена в фоні"
sudo spawn-fcgi -s $SOCKET_PATCH -n $PROGRAM_FOLDER$PROGRAM_NAME &
else 
echo "Програма запущена"
sudo spawn-fcgi -s $SOCKET_PATCH -n $PROGRAM_FOLDER$PROGRAM_NAME
fi
fi


