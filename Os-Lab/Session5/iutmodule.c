#include <linux/init.h> // For module init and exit
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h> // For fops
#include <linux/uaccess.h>
#include <linux/random.h>

//#include <string.h> // Can't use it!
#define bufsize 5000
static int buffpt=0;
char buf[bufsize];

#define DEVICE_NAME "iut_device"
MODULE_LICENSE("GPL");

// FILE OPERATIONS
static int iut_open(struct inode*, struct file*);
static int iut_release(struct inode*, struct file*);
static ssize_t iut_read(struct file*, char*, size_t, loff_t*);
static ssize_t iut_write(struct file*,const char*,size_t,loff_t*);

static struct file_operations fops = {
   .open = iut_open,
   .read = iut_read,
   .release = iut_release,
   .write = iut_write,
};

static ssize_t iut_write(struct file* file,const char *buffer, size_t len, loff_t *offset){
    char* buff=buf+buffpt;
    //buff=kzalloc(len,GFP_KERNEL);
    if(!buff){
        printk("failed to allocate\n");
        return -ENOMEM;
    }
    
    if(copy_from_user(buff,buffer ,len)==0){
        buffpt+=len;
        
        if(buffpt>=200){
            buf[buffpt]='\0';
            printk(KERN_INFO"data: %s\n",buf);
            buffpt=0;
        }

        return len;
    }
    else{
        return -ENOMEM;
    }


}

// Why "static"? --> To bound it to the current file and compiler won't think these functions are used elsewhere

static int major; // Device major number. Driver reacts to this major number.

// Event --> LOAD
static int __init iut_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops); // 0: dynamically assign a major number ||| name is displayed in /proc/devices ||| fops.
    if (major < 0) {
        printk(KERN_ALERT "iut_device load failed.\n");
        return major;
    }
    printk(KERN_INFO "iut_device module loaded: %d\n", major);
    return 0;
}

// Event --> UNLOAD
static void __exit iut_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "iut_device module unloaded.\n");
}


// Event --> OPEN
static int iut_open(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "iut_device opened.\n");
   return 0;
}

// Event --> CLOSE
static int iut_release(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "iut_device closed.\n");
   return 0;
}

// Event --> READ
static ssize_t iut_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    char* buff;
    buff=kzalloc(len,GFP_KERNEL);
    if(!buff){
        printk("memory allocation failed");
        return -ENOMEM;
    }
    get_random_bytes(buff,len);
    if(copy_to_user(buffer,buff,len)){
        printk("failed to fill the buffer\n");
        kfree(buff);
        return -ENOMEM;
    }
    kfree(buff);
    return len;
}

// Registering load and unload functions.
module_init(iut_init);
module_exit(iut_exit);
