// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include "hello1.h"

MODULE_AUTHOR("Andriy Zinchenko <andriyzinchenko@gmail.com>");
MODULE_DESCRIPTION("Hello1, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

struct my_list_item {
	struct list_head list;
	ktime_t start_time;
	ktime_t end_time;
};

static LIST_HEAD(my_list);

void print_hello(unsigned int count)
{
	while (count--) {
		struct my_list_item* item = kmalloc(sizeof(*item), GFP_KERNEL);
		if (!item) {
			pr_err("Memory allocation failed\n");
			return;
		}
		item->start_time = ktime_get();
		list_add_tail(&item->list, &my_list);
		pr_info("Hello, world!\n");
		item->end_time = ktime_get();
	}
}
EXPORT_SYMBOL(print_hello);

static void print_and_clear_list(void)
{
	struct my_list_item* item;
	struct list_head* pos, * n;

	list_for_each_safe(pos, n, &my_list) {
		item = list_entry(pos, struct my_list_item, list);
		pr_info("Start: %lld ns, End: %lld ns, Duration: %lld ns\n",
			ktime_to_ns(item->start_time),
			ktime_to_ns(item->end_time),
			ktime_to_ns(item->end_time) - ktime_to_ns(item->start_time));
		list_del(&item->list);
		kfree(item);
	}
}

static int __init hello1_init(void)
{
	pr_info("Hello1 module loaded\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	print_and_clear_list();
	pr_info("Hello1 module unloaded\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
