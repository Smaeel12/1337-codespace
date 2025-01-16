int    labelling(int *stack, int size)
{
    int    i;
    int    j;
    int    rank;

    i = 0;
    int *clone = malloc(size * sizeof(int));
    while (i < size)
    {
        j = 0;
        rank = -1;
        while (j < size)
            if (stack[j++] <= stack[i])
                rank++;
        clone[i] = rank;
        i++;
    }
    i = -1;
    while (++i < size)
        stack[i] = clone[i];
    free(clone);
    return (0);
}

int main() {
    int arr[] = {5, 1, 6, 0, 2};
    labelling(arr, 5);
    return 0;
}