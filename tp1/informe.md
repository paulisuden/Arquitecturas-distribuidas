# Arquitecturas Distribuidas
## Trabajo Práctico Nº1
### Año 2024
### Tema: Paralelismo a Nivel de Hilos

### Características de la computadora en la que se ejecutaron los programas:
- **Cantidad de núcleos:**
- **Cantidad de hilos:** (puede usar comandos como `lshw` o `lscpu`)


## Ejercicio 1
### Resultados obtenidos:

![](https://github.com/paulisuden/Arquitecturas-distribuidas/blob/main/tp1/images/ej1.png)

## Ejercicio 2
### Resultados obtenidos:

![](https://github.com/paulisuden/Arquitecturas-distribuidas/blob/main/tp1/images/ej2.1.png)
![](https://github.com/paulisuden/Arquitecturas-distribuidas/blob/main/tp1/images/ej2.2.png)
![](https://github.com/paulisuden/Arquitecturas-distribuidas/blob/main/tp1/images/ej2.3.png)

## Ejercicio 3
### Resultados obtenidos:

![](https://github.com/paulisuden/Arquitecturas-distribuidas/blob/main/tp1/images/ej3.png)

En este ejercicio se utilizó BLOCK_SIZE, el cual define el tamaño de los bloques que se usarán en la técnica de tiling o bloqueo para mejorar el rendimiento de la multiplicación de matrices. Es decir que, en lugar de procesar la matriz entera de una vez, se divide en pequeños bloques de 64x64, lo que mejora el uso de la caché de la CPU. Esta técnica entonces reduce los accesos a memoria, acelerando la ejecución.


## Ejercicio 4
### Resultados obtenidos:

![](https://github.com/paulisuden/Arquitecturas-distribuidas/blob/main/tp1/images/ej4.png)