#include <linux/init.h>
#include <linux/module.h>

static int __init hello_init(void)
{
    printk(KERN_INFO "Run the hello_init \n");
    return 0;
}
static void __exit hello_exit(void)
{
    printk(KERN_INFO "Run the hello_exit \n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL v2");
