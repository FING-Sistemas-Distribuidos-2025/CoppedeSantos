# Trabajo Practico N°4 - Patrones de Comunicacion

### Alumno: Coppede Santos Ignacio 

## Patrón Request-Reply

### Ejercicio 5

**a.**  
Se modificó el comportamiento del servidor para responder con un mensaje simple `"Hola"`, modificando directamente el archivo `server.js`.

**b.**  
Si se detiene el servidor y se ejecuta el cliente, este se queda esperando indefinidamente una respuesta, ya que la operación `await sock.receive()` bloquea la ejecución del cliente hasta recibir una respuesta. En cuanto el servidor se vuelve a iniciar, procesa el mensaje que quedó pendiente y responde, permitiendo que el cliente finalice su ejecución.  
Esto se diferencia del protocolo HTTP, donde ante una desconexión se lanza un error (como el 404). Aquí el cliente no recibe un error inmediato, sino que espera activamente por una respuesta.

**c.**  
Utilizando `nmap -sT <ip_server>` desde el cliente, se puede observar que cuando el servidor está activo, el puerto 3000/TCP se encuentra abierto para recibir conexiones. Desde el cliente este puerto no aparece como abierto, ya que está configurado solo para conectarse, no para escuchar.

---

## Patrón Publisher-Subscriber

### Ejercicio 1

**a.**  
Si se detiene el subscriber, el publisher continúa enviando mensajes. Sin embargo, como no hay nadie suscripto, esos mensajes se pierden. Al volver a levantar el subscriber, este recibe solo los mensajes que se publiquen desde ese momento, no los anteriores.

**b.**  
Si se detiene el publisher, el subscriber sigue esperando por nuevos mensajes. Al volver a ejecutar el publisher, el subscriber vuelve a recibir mensajes, aunque generalmente pierde el primer mensaje porque este es enviado antes de que el subscriber esté completamente conectado al tópico.

### Ejercicio 2  
Si hay múltiples subscribers suscriptos al mismo tópico, todos reciben los mensajes que publica el publisher de forma simultánea.

### Ejercicio 3  
No se pueden ejecutar dos publishers en el mismo puerto (por ejemplo, 3000) simultáneamente, ya que solo un proceso puede estar vinculado a un puerto en escucha a la vez. Esto genera un error de conflicto de puertos.

### Ejercicio 4  
Si se modifican los tópicos y el subscriber escucha un tópico distinto del que emite el publisher, no recibirá los mensajes. Ambos deben coincidir en el tópico para que la comunicación ocurra.

### Ejercicio 5  
Es posible que un publisher publique en varios tópicos, y que un subscriber escuche múltiples tópicos. Esto permite crear una arquitectura más flexible, en la que se pueden manejar múltiples categorías de mensajes.

---

## Patrón Push-Pull

### Ejercicio 1

**a.**  
Si se detiene el worker y no hay ningún otro activo, el producer deja de enviar mensajes pero sigue ejecutándose. El mensaje pendiente queda en buffer hasta que un worker se vuelva a conectar y lo procese. Al volver a ejecutar un worker, este recibe ese mensaje pendiente y continúa procesando los siguientes.

**b.**  
Si se detiene el producer, los workers se quedan esperando mensajes. Cuando el producer se reinicia, los workers vuelven a recibir mensajes. A diferencia del patrón Pub-Sub, aquí no se pierden los mensajes iniciales, ya que el producer espera tener un worker disponible para enviar el mensaje.

### Ejercicio 2  
Si hay más de un worker ejecutándose al mismo tiempo, los mensajes que envía el producer se reparten entre ellos de forma balanceada. ZeroMQ utiliza un esquema Round-Robin para distribuir los mensajes entre los workers disponibles.  
Esta es otra diferencia clave con el patrón Pub-Sub, donde todos los subscribers reciben todos los mensajes: en Push-Pull, cada mensaje se consume una única vez por un único worker.

---
