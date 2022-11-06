#include "apc.h"

int f_division (Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int ret;

    Dlist * rem_h = NULL;
    Dlist * rem_t = NULL;

    if (compare_LL_lt (*head1, *head2) != LT) // num >= denomenator
    {
        ret = division(head1, tail1, head2, tail2, headR, tailR);
        if (ret == FAILURE) {
            printf("division failed before floating point\n");
            return FAILURE;
        }
        pretty_print_list("before fp quotient", *headR);

        ret = modulus(head1, tail1, head2, tail2, &rem_h, &rem_t);
        pretty_print_list("before fp remainder", rem_h);

        dl_insert_last(headR, tailR, -1); // indicates floating point
        pretty_print_list("after fp", *headR);

        if (is_zero(rem_h) == SUCCESS) {
            dl_insert_last(headR, tailR, 0); // integer multiple case
            return SUCCESS;
        }
    }

    printf("after fp addition, remainder non zero\n");
    // add extra zeroes to make remainder greater than denomenator
    while(compare_LL_lt(rem_h, *head2) != GT) {
        dl_insert_last(&rem_h, &rem_t, 0);
    }

    pretty_print_list("new dividend, after adding 0s ", rem_h);

    Dlist * float_h = NULL;
    Dlist * float_t = NULL;
    ret = division(&    rem_h, &rem_t, head2, tail2, &float_h, &float_t);
    if (ret == FAILURE) {
        printf("division failed before floating point\n");
        return FAILURE;
    }

    pretty_print_list("fractional part", float_h);

    // joining ll after fp to result before fp
    (*tailR)->next = float_h;
    float_h->prev = *tailR;
    *tailR = float_t;

    pretty_print_list("final answer", *headR);

    return SUCCESS;
}