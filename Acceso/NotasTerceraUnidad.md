## Tercera Unidad - Métodos de Almacenamiento

Estructuras de Datos: Estas estructuras deberán ser utilizadas en la implementación del SGBD

- B+ Tree
- **B-Trees:** Mantienen tantos niveles de índices para el tamaño del archivo que se indexa, gestiona el espacio en los bloques.
    - **Estructura:**
        - Organiza los bloques en un árbol balanceado.
        - Todos los caminos de la raíz a las hojas tienen la misma longitud.
        - Tiene tres capas: raíz, capa intermedia y hojas.
    - **Operaciones:**
        - Inserción.
        - Eliminación.

## Esposición Lunes

1. ¿Qué es un índice denso y disperso? Ventajas / Desventajas, Ejemplos.
2. ¿Qué es un índice con clustering y sin clustering? Ventajas / Desventajas, Ejemplos.
3. Analizar los 4 índices según los criterios de indexación (Tiempo de Acceso, Tiempo de Inserción, Tiempo de Borrado, Espacio Adicional requerido).
4. ¿Como funcionan los índices durante el proceso de solicitud de un registro?. Explique el proceso, cual es el más costoso.

Reformular la pregunta 4.

## Presentación Laboratorio viernes 12 de Julio.

- Árbol B+ implementado correctamente sin unión al Buffer o Disco, hacer pruebas. Empezar desde el lunes o martes para evitar problemas un día antes de la presentación. Explicar el B+ Tree (Inserción y Eliminación.)

- Criterios de minimizar: Memoria / Amacenamiento
    - Indice
    - Consulta -> Dinámicos / Estáticos
    - Cantidad de Datos.
    - Aplica -> Temporales / Espaciales
        - Loteria -> app
        - Redes Sociales -> post
        - Sensores -> salud

## Presentación Lunes 15 de Julio

- Diagrama de Casos de B+ Tree con unión al Disco y usando de caso el 2 de post en el server 3. No hacer fallar el B+ Tree.