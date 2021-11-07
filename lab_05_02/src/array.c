#include "defines.h"
#include "list.h"

int arr_push(queue **pin, queue *pout, queue *begin, int entries_count)
{
    if (*pin == NULL || begin == NULL)
        return ERR_NULL;
    (**pin).entry = entries_count;
    *pin += 1;
    if (*pin == pout)
        return ERR_LENGTH;
    if (*pin == begin + N)
        *pin = begin;
    return OK;
}

int arr_pop(queue **pout, queue *begin, int *entries_count)
{
    if (*pout == NULL || begin == NULL)
        return ERR_LENGTH;
    *entries_count = (**pout).entry;
    *pout += 1;
    if (*pout == begin + N)
        *pout = begin;
    return OK;
}

void get_time_work_exit_element_arr(double *t_work, double t_out, queue *head, int *n_quit)
{
    *n_quit += 1;
    *t_work += t_out;
    pop(head);
}


void add_element_to_queue_arr(queue *head, int *count)
{
    *count += 1;
    list *tail = NULL;
    if (!*head)
        *head = create_list(*head);
    else
    {
        tail = create_list(tail);
        *head = add_end(*head, tail);
    }
}

int start_arr_time(interval t1, interval t2, interval t3, interval t4)
{
    void *adr[N];
    int adr_num = 0;
    double t_in_1 = 0, t_out = 0, t_wait = 0, time = 0, t_in_2 = 0, t_min = 0, t_work = 0;
    queue q_1[MAXSIZE], q_2[MAXSIZE], *pin_1 = &q_1[0], *pout_1 = &q_1[0], *pin_2 = &q_2[0], *pout_2 = &q_2[0];
    int count = 0, n_quit = 0, flag = 0, n_quit_2 = 0, count_2 = 0;
    double av_len = 0;
    int i = 0;
    int64_t t = 0;
    struct timeval tv_start, tv_stop;
    
    while (n_quit < 1000)
    {
        gettimeofday(&tv_start, NULL);
        if (t_in_1 <= 0)
        {
            t_in_1 = get_random_time(t1.min, t1.max);
            add_element_to_queue_arr(&head, &count);
        } 
        if (t_in_2 <= 0)
        {
            t_in_2 = get_random_time(t2.min, t2.max);
            add_element_to_queue_arr(&head_2, &count_2);
        }
        if (t_out <= 0)
        {
            if (!head)
                if (!head_2)
                    t_wait += t_min;
                else
                {
                    t_out = get_random_time(t4.min, t4.max);
                    get_time_work_exit_element_arr(&t_work, t_out, flag, adr, &adr_num, &head_2, &n_quit_2);
                }
            else
            {
                t_out = get_random_time(t3.min, t3.max);
                get_time_work_exit_element_arr(&t_work, t_out, flag, adr, &adr_num, &head, &n_quit);
            } 
        }
        t_min = get_min(t_in_1, t_in_2, t_out);
        t_in_1 -= t_min;
        t_in_2 -= t_min;
        t_out -= t_min;
        time += t_min;
        if (n_quit % 100 == 0 && i != n_quit)
        {
            i = n_quit;
            int len;
            printf("-----------------------------------------------------------------\n");
            printf("Время : %lf\n", time);
            len = list_size(head);
            av_len += len / (n_quit / 100);
            printf("Средняя длина первой очереди: %lf\n", av_len);
            printf("Количество элементов первой очереди: %d\n", len);
            len = list_size(head_2);
            av_len += len / (n_quit_2 / 100);
            printf("Средняя длина второй очереди: %lf\n", av_len);
            printf("Количество элементов второй очереди: %d\n", len);
            printf("Время ожидания: %lf\n", t_wait);
            printf("Количество прошедших элементов через первую очередь: %d\n", count);
            printf("Количество заявок вышедших из первой очереди: %d\n", n_quit);
            printf("Среднее время пребывание в первой очереди: %lf\n", time / n_quit);
            printf("Среднее время пребывание в второй очереди: %lf\n", time / n_quit_2);
        }
    }
    gettimeofday(&tv_stop, NULL);
    printf("-----------------------------------------------------------------\n");
    t = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("Время использование стеком = %lf mcs\n", (float)t / N_TIME);
    printf("Количество вошедших заявок во вторую очередь: %d\n", count_2);
    printf("Количество вышедших заявок из второй очереди: %d\n", n_quit_2);
    
    double average = ((t1.max + t1.min + t3.max + t3.min) / 4.0 + (t2.max + t2.min + t4.max + t4.min) / 4.0) * N;
    /*
    printf("Ожидаемое время: %lf\n", average);
    if (time <= average)
    {
        double deviation = (average - time) / average * 100;
        printf("Разница первой очереди: %f%%\n", deviation);
    }
    else
    {
        double deviation = (time - average) / time * 100;
        printf("Разница первой очереди: %f%%\n", deviation);
    }
    */
    average =  n_quit + n_quit_2 + t_wait;
    if (time <= average)
    {
        double deviation = (average - time) / average * 100;
        printf("Погрешность: %f%%\n", deviation);
    }
    else
    {
        double deviation = (time - average) / time * 100;
        printf("Погрешность: %f%%\n", deviation);
    }
    return OK;
}