#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

static int major = 232; /* ��̬�豸�ŷ�ʽ��Ĭ��ֵ */
static int minor = 0;   /* ��̬�豸�ŷ�ʽ��Ĭ��ֵ */
module_param(major, int, S_IRUGO);
module_param(minor, int, S_IRUGO);

struct cdev *char_null_udev;    /* cdev ���ݽṹ */
static dev_t devno;             /* �豸��� */
static struct class *char_null_udev_class;

#define DEVICE_NAME "char_null_udev"

static int __init char_null_udev_init(void)
{
    int ret;

    if (major > 0) { /* ��̬�豸�� */
        devno = MKDEV(major, minor);
        ret = register_chrdev_region(devno, 1, "char_null_udev");
    } else { /* ��̬�豸�� */
        ret = alloc_chrdev_region(&devno, minor, 1, "char_null_udev"); /* ��ϵͳ��ȡ���豸�� */
        major = MAJOR(devno);
    }
    if (ret < 0) {
        printk(KERN_ERR "cannot get major %d \n", major);
        return -1;
    }
    
    char_null_udev = cdev_alloc(); /* ���� char_null_udev �ṹ */
    if (char_null_udev != NULL) {
        cdev_init(char_null_udev, &major); /* ��ʼ�� char_null_udev �ṹ */
        char_null_udev->owner = THIS_MODULE;
        if (cdev_add(char_null_udev, devno, 1) != 0) { /* ���� char_null_udev ��ϵͳ�� */
            printk(KERN_ERR "add cdev error! \n");
            goto error;
        }
    } else {
        printk(KERN_ERR "cdev_alloc error!\n");
        return -1;
    }
    
    //��/sys/class/�´��� char_null_udev_class Ŀ¼
    char_null_udev_class = class_create(THIS_MODULE, "char_null_udev_class");
    if (IS_ERR(char_null_udev_class)) {
        printk(KERN_INFO "create class error\n");
        return -1;
    }
    /* ������/dev/char_null_udev0 �ļ� */
    //device_create(char_null_udev_class, NULL, devno, NULL, "char_null_udev" "%d",MINOR(devno));
    /* ������/dev/char_null_udev �ļ� */
    device_create(char_null_udev_class, NULL, devno, NULL, "char_null_udev");
    
    return 0;
    
    error:
    unregister_chrdev_region(devno, 1); /* �ͷ��Ѿ���õ��豸�� */
    return ret;
}
    
static void __exit char_null_udev_exit(void)
{
    device_destroy(char_null_udev_class, devno);
    class_destroy(char_null_udev_class);
    cdev_del(char_null_udev);           /* �Ƴ��ַ��豸 */
    unregister_chrdev_region(devno, 1); /* �ͷ��豸�� */
}
    
module_init(char_null_udev_init);
module_exit(char_null_udev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Han, 181506933@qq.com");