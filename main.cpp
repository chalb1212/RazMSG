#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <pthread.h>
#include <ntripclient.h>
#include <sbas.h>

int main()
{
    char *s  = (char*)"212.15.100.143";
    char *pr = (char*)"5000";
    char *u = (char*)"user";
    char *p = (char*)"1234";
    char *m = (char*)"sbas0";
    int  md = AUTO;
    int reconect_time = 5;

    int prn = 0;
    sbsmsg_t *sbsmsg;
    gtime_t time;
    unsigned int *words;


    NtCl *client = new NtCl(s, pr, u, p, m, md, reconect_time);
    client->Run();

    Buffer my_buf_struct;
    int buyte_count = -1;
    while(true)
    {
        my_buf_struct = client->GetBuf();
        if(buyte_count != my_buf_struct.buyte_count)
        {

            //fwrite(my_buf_struct.buf, my_buf_struct.size_msg, 1, stdout);
            int i = sbsdecodemsg(time, prn, my_buf_struct.buf, sbsmsg);

            fwrite(my_buf_struct.buf, my_buf_struct.size_msg, 1, stdout);
            buyte_count = my_buf_struct.buyte_count;
        }
    }
    return 0;
}

