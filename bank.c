#include<stdio.h>
struct file 
{
    int alloc[10];
    int max[10];
    int need[10];
    int flag;
};

int main()
{
    struct file f[10];
    int avail[10], seq[10];
    int no_process;
    int no_resource;
    int cnt=0;
    int flag1,flag2;
    printf("Enter the number of processes: ");
    scanf("%d", &no_process);
    printf("Enter the number of resources: ");
    scanf("%d", &no_resource);

    for (int i = 0; i < no_process; i++) 
    {
        printf("Enter details for process P%d:\n", i);
        printf("Enter the allocation: \n");
        for (int j = 0; j < no_resource; j++) 
        {
            scanf("%d", &f[i].alloc[j]);
        }
        printf("Enter the maximum requirement: \n");
        for (int j = 0; j < no_resource; j++) 
        {
            scanf("%d", &f[i].max[j]);
        }
        f[i].flag = 0;
    }

    printf("Enter available resources: ");
    for (int i = 0; i < no_resource; i++) 
    {
        scanf("%d", &avail[i]);
    }

    for (int i = 0; i < no_process; i++) 
    {
        for (int j = 0; j < no_resource; j++) 
        {
            f[i].need[j] = f[i].max[j] - f[i].alloc[j];
            if (f[i].need[j] < 0) 
            {
                f[i].need[j] = 0;
            }
        }
    }
    while(cnt<no_process)
    {
        flag1=0;
        for(int i=0;i<no_process;i++)
        {
            if(f[i].flag==0)
            {
                flag2=0;
                for(int j=0;j<no_resource;j++)
                {
                    if(avail[j]<f[i].need[j])
                    {
                        flag2=1;
                        break;
                    }
                }
                if(flag2==0)
                {
                    printf("process P%d exeuted\n",i);
                    seq[cnt++]=i;
                    f[i].flag=1;
                    flag1=1;
                }
            }
        }
        if(flag1==0)
        {
            printf("unsafe sequence\n");
            break;
        }
    }
    if(cnt==no_process)
    {
        printf("sequence:");
        for(int i=0;i<no_process;i++)
        {
            printf("P%d ",seq[i]);
        }
    }
}