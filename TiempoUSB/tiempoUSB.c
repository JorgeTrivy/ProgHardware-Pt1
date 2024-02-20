#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/time.h>
#include <linux/slab.h>

struct usb_data {
    ktime_t connect_time;
};

// Funcion cuando dispositivo USB es compatible
static int my_usb_connect(struct usb_interface *interface, const struct usb_device_id *id)
{
    struct usb_data *data;
    
    printk(KERN_INFO "aaaaaaaaaaaaaaaaaa");
    
    // Asignacion de memoria
    data = kzalloc(sizeof(struct usb_data), GFP_KERNEL);
    if (!data) {
        return -ENOMEM;
    }

    // Hora actual
    data->connect_time = ktime_get_real();

    // Se guarda en funcion driver_data de usb_driver
    usb_set_intfdata(interface, data);

    return 0;
}

// Desconecsion de dispositivo USB
static void my_usb_disconnect(struct usb_interface *interface)
{
    struct usb_data *data;
    ktime_t disconnect_time;
    s64 duration;

    // Estructura usb_data almacenada con el tiempo
    data = usb_get_intfdata(interface);
    if (!data) {
        return;
    }

    // Hora de desconexión actual
    disconnect_time = ktime_get_real();

    // Calculo de tiempo de conexión
    duration = ktime_to_ms(ktime_sub(disconnect_time, data->connect_time));

    // Mostrar tiempo de uso del dispositivo
    printk(KERN_INFO "Dispositivo USB desconectado. Tiempo de uso: %lld milisegundos.\n", duration);

    // Liberacion de memoria
    kfree(data);
}

// Estructura que define el controlador USB
static struct usb_driver my_usb_driver = {
    .name = "my_usb_driver",            
    .probe = my_usb_connect,              
    .disconnect = my_usb_disconnect,    
};

// Inicialización del módulo
static int __init my_usb_init(void)
{
    int ret;
    printk(KERN_INFO "aaaaaaaaaaaaaaaaaa %lld", ret);
    // Registro del USB
    ret = usb_register(&my_usb_driver);
    
    if (ret) {
        printk(KERN_ERR "Error al registrar el controlador USB: %d\n", ret);
        return ret;
    }

    printk(KERN_INFO "Controlador USB registrado correctamente.\n");
    return 0;
}

// Salida del módulo
static void __exit my_usb_exit(void)
{
    usb_deregister(&my_usb_driver);

    printk(KERN_INFO "Controlador USB deregistrado correctamente.\n");
}

module_init(my_usb_init); 
module_exit(my_usb_exit); 

MODULE_AUTHOR("Jorge Vico Martos");                 
MODULE_DESCRIPTION("Medicion de tiempo de uso de USB");   
MODULE_LICENSE("GPL");                      

