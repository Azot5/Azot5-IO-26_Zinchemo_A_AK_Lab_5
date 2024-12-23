// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_AUTHOR("Andriy Zinchenko <andriyzinchenko@gmail.com>");
MODULE_DESCRIPTION("Hello2 module");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int hello_count = 1;
module_param(hello_count, uint, S_IRUGO);
MODULE_PARM_DESC(hello_count, "Number of times to print 'Hello, world!'");

static int __init hello2_init(void)
{
	if (hello_count == 0 || (hello_count >= 5 && hello_count <= 10)) {
		pr_warn("hello2: hello_count is 0 or between 5 and 10\n");
	}
	else if (hello_count > 10) {
		pr_err("hello2: hello_count is greater than 10\n");
		return -EINVAL;
	}

	pr_info("hello2: Module loaded, invoking hello1\n");
	print_hello(hello_count);
	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("hello2: Module unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
