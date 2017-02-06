#!/bin/bash
clear && clear
echo "" &>> logs.log
echo "" &>> logs.log
echo "*****************************************" &>> logs.log
echo "****** LANCEMENT DU SCRIPT MAKE.SH ******" &>> logs.log
echo "*****************************************" &>> logs.log
echo "" &>> logs.log
echo " >> Compilation des differentes representations de graphes." &>> logs.log
echo " >> Compilation des elements relatifs a la matrice d'adjacence non orientee." &>> logs.log
cd UndirectedAdjacenceMatrix
gcc -c *.c
cd ..

echo " >> Compilation des elements relatifs a la matrice d'adjacence orientee." &>> logs.log
cd DirectedAdjacenceMatrix
gcc -c *.c
cd ..

echo " >> Compilation des elements relatifs a la list d'adjacence non orientee." &>> logs.log
cd UndirectedAdjacenceList
gcc -c *.c
cd ..

echo " >> Compilation des elements relatifs a la list d'adjacence orientee." &>> logs.log
cd DirectedAdjacenceList
gcc -c *.c
cd ..

echo " >> Compilation des elements relatifs a la matrice d'incidence non orientee." &>> logs.log
cd UndirectedIncidenceMatrix
gcc -c *.c
cd ..

gcc -c Graph.c
gcc testGenericGraph.c -o testGenericGraph Graph.o */*.o
echo "***************** Test 0 ********************"
valgrind ./testGenericGraph 10 20 0 >> logs.log
echo "***************** Test 1 ********************"
./testGenericGraph 10 20 1 >> logs.log
echo "***************** Test 2 ********************"
./testGenericGraph 10 20 2 >> logs.log
echo "***************** Test 3 ********************"
./testGenericGraph 10 20 3 >> logs.log
echo "***************** Test 4 ********************"
./testGenericGraph 10 20 4 >> logs.log

subl logs.log