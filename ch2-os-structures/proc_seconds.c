/** proc_seconds.c
 * Kernel module that creates a /proc file named /proc/seconds
 * that reports the number of seconds since the kernel module was loaded.
**/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <asm/param.h>
#include <linux/jiffies.h>

#define BUFFER_SIZE 16

#define PROC_NAME "seconds"

// Function prototypes
ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t *pos);

static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
    .read = proc_read,
};

unsigned long from_jiffies;

/* This function is called when the module is loaded. */
int proc_init(void)
{
    // Create the /proc/seconds entry
    proc_create(PROC_NAME, 0, NULL, &proc_ops);

    printk(KERN_INFO "/proc/%s created\n", PROC_NAME);

    // Save jiffies when module was loaded
    from_jiffies = jiffies;

    return 0;
}

/* This function is called when the module is removed. */
void proc_exit(void)
{
    // Remove the /proc/jiffies entry
    remove_proc_entry(PROC_NAME, NULL);

    printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);
}

/* This function is called each time the /proc/seconds is read. */
ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
    unsigned long to_jiffies, seconds, rv = 0;
    char buffer[BUFFER_SIZE];
    static int completed = 0;

    if (completed)
    {
        completed = 0;
        return 0;
    }

    // Compute the seconds elapsed
    completed = 1;
    to_jiffies = jiffies;
    seconds = (to_jiffies - from_jiffies) / HZ;

    rv = sprintf(buffer, "%lu\n", seconds);

    // Copies the content of the buffer to userspace usr_buf
    copy_to_user(usr_buf, buffer, rv);

    return rv;
}

/* Macros for registering module entry and exit points. */
module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Proc_seconds Module");
MODULE_AUTHOR("KCB");
