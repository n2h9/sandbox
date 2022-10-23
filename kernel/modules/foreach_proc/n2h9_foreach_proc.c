#define pr_fmt(fmt) "%s:%s(): " fmt, KBUILD_MODNAME, __func__

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

#define MODNAME   "n2h9_foreach_proc"
MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("n2 h9");
MODULE_DESCRIPTION("The module is iteratting over the all processes and printk process name with pid in a kernel log");


static int __init n2h9_foreach_proc_init(void)
{
	struct task_struct *p;
	int count = 0;
	
	pr_info("inserted\n");
	
	for_each_process(p) {
		pr_info(
			"<process pid=\"%d\" name=\"%s\"></process>\n",
			p->pid, 
			p->comm
		);
		count++;
	}
	
	pr_info("total number of processes %d\n", count);

	return 0;
}

static void __exit n2h9_foreach_proc_exit(void)
{
	pr_info("removed\n");
}

module_init(n2h9_foreach_proc_init);
module_exit(n2h9_foreach_proc_exit);