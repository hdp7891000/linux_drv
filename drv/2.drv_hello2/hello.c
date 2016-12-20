#include <linux/module.h>
#include <linux/init.h>

static int __init hello_init(void)
{
  	int i;
	for(i = 0; i < 10; i++){
  		printk(KERN_ALERT"Hello, I'm ready %d!\n", i);
	}
  	return 0;
}

static void __exit hello_exit(void)
{
  	int i;
	for(i = 0; i < 10; i++){
		printk(KERN_ALERT"I'll be leaving, bye! \n");
	}
  	return 0;
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
