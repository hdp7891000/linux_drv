#include <linux/module.h>
#include <linux/init.h>

static int print_num = 10;

module_param(print_num, int, S_IRUGO);

static int __init hello_init(void)
{
  	int i;
	for(i = 0; i < print_num; i++){
  		printk(KERN_INFO "Hello, I'm ready %d!\n", i);
	}
  	return 0;
}

static void __exit hello_exit(void)
{
  	int i;
	for(i = 0; i < print_num; i++){
		printk(KERN_INFO "I'll be leaving, bye! \n");
	}
  	return 0;
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
