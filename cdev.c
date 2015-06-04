#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
dev_t dev;
int dev_cnt = 1;
char* l_dev_name = "cdedddd";
struct class* classptr;
static int d_open(struct inode* inode, struct file* filp)
{
	printk(KERN_INFO"d_open\n");
	return 0;
}

static int d_close(struct inode* inode, struct file* filp)
{
	printk(KERN_INFO"d_close\n");
	return 0;
}

static ssize_t d_read(struct file* filp, char* buf, size_t s, loff_t* off)
{
	printk(KERN_INFO"d_read\n");
	return 0;
}

static ssize_t d_write(struct file* filp, const char* buf, size_t s, loff_t* off)
{
	printk(KERN_INFO"d_write\n");
	return 0;
}

struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = d_open,
	.release = d_close,
	.read = d_read,
	.write = d_write
};

struct cdev cdev;
int tmp;
int init_module(void)
{
	int ret = 0;
	printk(KERN_INFO"cdev init\n");
	dev = MKDEV(97, 0);
	//ret = register_chrdev_region(dev, dev_cnt, l_dev_name);
	//tmp = register_chrdev(0, "abc", &fops);
	ret = alloc_chrdev_region(&dev, 0, 1, l_dev_name);
	if(ret){
		printk(KERN_INFO"ERROR register chrdev region\n");
		unregister_chrdev_region(dev, dev_cnt);
		return -1;
	}else{
		printk(KERN_INFO"dev: Major:%d Minor:%d\n", MAJOR(dev), MINOR(dev));
	}
	cdev_init(&cdev, &fops);
	cdev.owner = THIS_MODULE;
	cdev_add(&cdev, dev, dev_cnt);
	classptr = class_create(THIS_MODULE, "classname");
	if(IS_ERR(classptr)){
		printk(KERN_INFO"class create error\n");
		return -1;
	}
	device_create(classptr, NULL, dev, 0, "dcreatename");	
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO"cdev exit\n");
	device_destroy(classptr, dev);
	class_destroy(classptr);
	cdev_del(&cdev);
	unregister_chrdev_region(dev, dev_cnt);
	//unregister_chrdev(tmp, "a1bc");
}	

MODULE_LICENSE("GPL");

