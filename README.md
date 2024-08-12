# Implementación de un Gestor de Base de Datos para el curso de Base de Datos 2 (Universidad Nacional de San Agustín de Arequipa - UNSA)

## Descripción del Proyecto

Este repositorio contiene la implementación de un Gestor de Base de Datos desarrollado en **C++** para la manipulación de datos y realizar consultas. Este Gestor de Base de Datos fue para el curso de **Base de Datos II** en la **Escuela Profesional de Ciencia de la Computación** de la **Universidad Nacional de San Agustín de Arequipa**. Aclarar que la implementación fue hecho en equipos, por lo cual esta implementación fue desarrollado por los estudiantes:

- ***Piero Adriano Cárdenas Villagómez*:** (https://github.com/pieroadrianoCV)
- ***Josue Samuel Philco Puma*:** (https://github.com/2023JoshuaP)

### Propósito del Repositorio

Este repositorio se proporciona como una **guía educativa** para futuros estudiantes del curso **Base de Datos II**. Está diseñado para ayudar a comprender las ideas y enfoques posibles en el desarrollo de un Gestor de Bases de Datos, no para ser copiado o presentado como propio.

**Nota Importante:** Se alienta a los usuarios a usar este repositorio como referencia para inspirarse y aprender, pero se desaconseja su uso para copiar y presentar el trabajo como propio. El propósito principal es servir de ayuda y guía en el proceso de aprendizaje.

## Características Principales

1. **Generación de Esquemas**:
   - Transforma archivos CSV en un formato de texto estructurado basado en esquemas definidos. Esto es crucial para manejar y organizar datos de manera eficiente. Estos esquemas serán útiles para las consultas y verificación de la existencia de una tabla.

2. **Conversión de CSV a los datos/registros**:
   - Se maneja la conversión de registros desde un archivo CSV a una relación en un archivo de texto, lo cual nos servirá en consultas de Gestores conocidos como MySql, además que más adelante se verán conversiones de Registros a Longitud Fija para los demás módulos del curso.

3. **Creación de un Disco Virtual**:
   - Simula un disco con una estructura detallada que incluye platos, pistas, sectores y bloques. Este modelo de disco permite experimentar con conceptos de almacenamiento físico en sistemas de bases de datos.

4. **Gestión de Datos en el Disco Virtual**:
   - Permite llenar los sectores y bloques del disco con registros, mostrar la capacidad del disco, y realizar operaciones de eliminación en el disco.

5. **Gestión de la Memoria en el Buffer Manager**:
   - Permite una mejor gestión para los bloques/páginas del disco, manejo de registros en la inserción, modificación y eliminación de dichos registros y guardarlos en memoria y también en el disco.

6. **Gestión en los métodos de Acceso**:
   - Se maneja las estructuras de Datos como el **B+ Tree** para la recuperación de un cierto registro mediante la indexación. Este contiene donde se encuentra almacenado un registro en el disco, también manejando inserción y eliminación en la memoria Buffer y de ahi mandándolo al disco.

## Estructura del Sistema Gestor de Base de Datos

El proyecto está organizado en varias carpetas y archivos, cada uno con su propósito específico. En las diferentes carpetas se encuentra las notas de clase de cada avance que se ha presentado durante el curso.

***NOTA IMPORTANTE:*** Los avances son acumulativos y va escalando en cada unidad hasta llegar al final, si no tienes avances o tienes faltas en la implementación no podrás realizar los siguientes módulos.

## Contribuciones

Las contribuciones son bienvenidas. Si estás interesado en mejorar o expandir este proyecto, por favor sigue estos pasos:

1. Haz un fork del repositorio.
2. Crea una nueva rama para tu característica (`git checkout -b feature/nueva-caracteristica`).
3. Realiza un commit de tus cambios (`git commit -am 'Agregar nueva característica'`).
4. Haz push de la rama (`git push origin feature/nueva-caracteristica`).
5. Abre un Pull Request para revisión.