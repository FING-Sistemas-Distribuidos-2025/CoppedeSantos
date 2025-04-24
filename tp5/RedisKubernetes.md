# Trabajo Práctico N.º 5 – Redis en Kubernetes 
**Alumno:** Ignacio Coppede Santos

**Carrera:** Licenciatura en Ciencias de la Computación   

**Año:** 2025  

---

## 1. a) ¿Qué es Helm y qué es un chart?

**Respuesta:**  
Helm es un gestor de paquetes para Kubernetes que permite simplificar el despliegue, la gestión y la reutilización de configuraciones de aplicaciones complejas dentro de clústeres. Un *Helm chart* es un paquete que contiene todos los recursos necesarios para desplegar una aplicación, incluyendo:  
- Plantillas YAML para definir objetos de Kubernetes.  
- Un archivo `values.yaml` con parámetros configurables.  
- Metadatos del chart (nombre, versión, dependencias, etc.).

Es una especie de "receta" que automatiza y estandariza el proceso de despliegue en Kubernetes.

---

## 3. a) ¿Qué sucede inicialmente con los nodos?

**Respuesta:**  
Todos los nodos se encuentran en estado `Pending`. Esto significa que, aunque Kubernetes ha reconocido la definición de los pods, no puede programarlos en ningún nodo porque no cumple con todos los requisitos necesarios (como recursos de almacenamiento persistente).

---

## 3. b) ¿Qué indica el warning `FailedScheduling`?

**Respuesta:**  
El warning `FailedScheduling` aparece al intentar iniciar un pod que requiere volúmenes persistentes (`PersistentVolumeClaims`). Kubernetes no logra asignar este pod a ningún nodo porque no hay volúmenes disponibles o configurados en el clúster que puedan ser enlazados al pod. Por eso, la planificación del pod falla.

---

## 4. d) ¿Qué sucede cuando se agregan volúmenes persistentes?

**Respuesta:**  
Cuando se agregan volúmenes persistentes al clúster, los pods pueden finalmente enlazar sus `PersistentVolumeClaims` a estos recursos. Como resultado, los nodos que estaban en estado `Pending` pasan a `Running` porque ahora cuentan con todos los recursos necesarios para ejecutar los pods. Esto confirma que la falta de almacenamiento persistente era la causa del problema.

---
