#include <linux/init.h> // For module init and exit
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h> // For fops
#include <linux/uaccess.h>
#include <linux/random.h>
#include <linux/ioctl.h>
//#include <string.h> // Can't use it!
#define bufsize 5000
static int buffpt=0;
static int volume=30;
static int mute=0;
char buf[bufsize];
#define DEVICE_NAME "iut_device"

#define IOCTL_MUTE _IO('i', 1)
#define IOCTL_UNMUTE _IO('i', 2)
#define IOCTL_SET_VOLUME _IOW('i', 3, int)
#define IOCTL_GET_VOLUME _IOR('i', 4, int)


MODULE_LICENSE("GPL");

// FILE OPERATIONS
static int iut_open(struct inode*, struct file*);
static int iut_release(struct inode*, struct file*);
static ssize_t iut_read(struct file*, char*, size_t, loff_t*);
static ssize_t iut_write(struct file*,const char*,size_t,loff_t*);
static long iut_ioctl(struct file*, unsigned int, unsigned long);


static struct file_operations fops = {
   .open = iut_open,
   .read = iut_read,
   .release = iut_release,
   .unlocked_ioctl = iut_ioctl,
   .write = iut_write,
};


static ssize_t iut_write(struct file* file,const char *buffer, size_t len, loff_t *offset){

    if (volume == 0) {
        printk(KERN_INFO "Vol = 0\n");
        return -EINVAL;
    }
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
    if(mute==1){
        printk(KERN_INFO "muted!!!\n");
        return 0;
    }
    buff=kzalloc(len,GFP_KERNEL);
    if(!buff){
        printk("memory allocation failed");
        return -ENOMEM;
    }
    get_random_bytes(buff,len);
    if(copy_to_user(buffer,buff,len)){
        printk("failed to fill the buffer\n");
        kfree(buff);
        return -EFAULT;
    }
    kfree(buff);
    return len;
}

static long iut_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    int user_volume;
    switch (cmd) {
        case IOCTL_MUTE:
            mute = 1;
            printk(KERN_INFO "Microphone muted.\n");
            break;
        case IOCTL_UNMUTE:
            mute = 0;
            printk(KERN_INFO "Microphone unmuted.\n");
            break;
        case IOCTL_SET_VOLUME:
            if (copy_from_user(&user_volume, (int __user *)arg, sizeof(int)))
                return -EFAULT;
            if (user_volume < 0 || user_volume > 100)
                return -EINVAL;
            volume = user_volume;
            printk(KERN_INFO "Volume set to %d.\n", volume);
            break;
        case IOCTL_GET_VOLUME:
            if (copy_to_user((int __user *)arg, &volume, sizeof(int)))
                return -EFAULT;
            printk(KERN_INFO "Volume returned: %d.\n", volume);
            break;
        default:
            return -EINVAL;
    }
    return 0;
}

// Registering load and unload functions.
module_init(iut_init);
module_exit(iut_exit);
