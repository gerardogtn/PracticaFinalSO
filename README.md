# PracticaFinal Sistemas Operativos

## Instrucciones de compilacion
`` g++ main.cpp -o main.o -std=c++11 -pthread``

## Instrucciones de ejecucion
``./main.o $nombreArchivo$ $numPuerto$``

Por ejemplo: ``main.o procesos 8000``


## Algoritmos

### Prioridad Apropiativo
Selecciona el proceso con la menor prioridad.

### Round Robin
Alterna los procesos activos y los ejecuta durante un quanta de tiempo. Ignora
la prioridad del proceso. El desempate se realiza por medio de _first come first
serve_, es decir por el primer proceso en llegar.

## TDD
Se uso la metodologia de TDD, para ejecutar los tests configurar las variables
de ambiente GMOCK_DIR y GTEST_DIR con la ubicacion de los directorios de
googletest y googlemock.
