Este driver en cuestión, tiene como finalidad detectar el momento en el que se inserte un USB en el pc y el momento de extracción.
Realizada la extracción, debe devolver el tiempo que ha transcurrido entre una acción y otra.

Lo primero de todo, dejar claro que no funciona como debería debido a que linux tiene unos driveres, llamados uas y usb_storage, que invaden las fuciones de los propios USBs.

Respecto al código, las biblitecas primordiales que se usarán serán "usb.h", para detectar y manejar los dispositivos; "time.h", para la medición del tiempo; y "slab.h" para ir guardando variables en memoria la memoria.
Al principio de todo, se creará un struct en donde se guardará el tiempo de conexión de entrada del USB, usando una variable "ktime_t". Ésta variable se guardará en memoria para usarla depués, por lo que hay que tener en cuenta que se debe liberar una vez usada.
Ésta variable se creará y rellenará en "my_usb_connect" y, en "my_usb_disconnect", se calculará el tiempo final con la hora actual y la anterior guardada.

Finalmente, se muestra por pantalla y se libera aquí la variable en memoria.

Destacar también que, en el código se implementan ciertas comprobaciones en caso de ocurrir algún error o alguna falla al recoger los datos.
