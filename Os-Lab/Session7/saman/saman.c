#include <linux/kernel.h>
#include <linux/syscalls.h>

struct process_info{
    char state_str[16];
    unsigned long memory_usage;
    char name[32];
};

SYSCALL_DEFINE2(saman,pid_t,processid, struct process_info*, mystruct)
{
    struct process_info pro;
    struct task_struct * task;
    task=pid_task(find_vpid(processid),PIDTYPE_PID);
    if(task==NULL){
        return -ESRCH;
    }
    else{
        strcpy(mystruct->name,task->comm);
        if(task->__state==0){
            strcpy(mystruct->state_str,"RUNNING\n");
        }
        else{
            if(task->__state==-1){
            strcpy(mystruct->state_str,"SLEEPING\n");
        }
        else{
            strcpy(mystruct->state_str,"UNKOWN\n");
        }

        mystruct->memory_usage = task->mm ? task->mm->total_vm : 0;

        if (task->mm){
            mystruct->memory_usage = task->mm->total_vm ;
        }else
        {
            mystruct->memory_usage = 0;
        }
        
        }

        return 0;
    }
    
}
