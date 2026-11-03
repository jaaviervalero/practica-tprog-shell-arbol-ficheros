# Shell sobre un árbol de ficheros virtual (C++)

Práctica 4 de **Tecnología de la Programación** (Ingeniería Informática, Universidad de Zaragoza, curso 2025-26).

Un intérprete de comandos tipo Unix que trabaja sobre un sistema de ficheros en memoria:

- **Jerarquía de nodos:** `Nodo`, del que heredan `Fichero`, `Directorio` y `Enlace` (enlaces a otros nodos).
- **Comandos:** `pwd`, `ls`, `du`, `vi`, `mkdir`, `cd`, `ln`, `stat` y `rm`, con rutas absolutas y relativas.
- **Errores:** una jerarquía de excepciones propia (`ruta_inexistente_error`, `no_es_directorio_error`, `elemento_existente_error`…).

Se compila con `make`.

**Autores:** Javier Valero y Pablo Muruzábal.
