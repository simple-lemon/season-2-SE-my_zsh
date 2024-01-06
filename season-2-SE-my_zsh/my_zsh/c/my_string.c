#include "../h/my_string.h"

int my_strlen(char *p1)
{
    int i = 0;
    while (p1[i] != '\0')
    {
        i++;
    }
    return i;
}

char *my_strdup(char *p1)
{
    int size = my_strlen(p1);
    char *str = calloc(sizeof(char), (size + 1));
    fill_null(str, size + 1);
    for (int i = 0; i < size; i++)
    {
        str[i] = p1[i];
    }
    return str;
}

char *my_strcpy(char *str1, char *str2)
{
    for (int i = 0; str2[i]; i++)
    {
        str1[i] = str2[i];
    }
    return str1;
}

char *my_strcpy_pro(char *str1, char *str2, char add)
{
    if (add == 0)
    {
        add = ' ';
    }
    int last_i = my_strlen(str1);
    int len2 = my_strlen(str2);
    // int lenForNewStr = last_i + len2 + 1;
    // str1 = realloc(str1, lenForNewStr + 1);
    str1[last_i++] = add;
    for (int i = 0; i < len2; i++)
    {
        str1[last_i++] = str2[i];
    }
    return str1;
}

int my_strcmp(char *p1, char *p2)
{
    for (int i = 0; p1[i] || p2[i]; i++)
    {
        if (p1[i] != p2[i])
        {
            return p1[i] - p2[i];
        }
    }
    return 0;
}

int my_strncmp(char *p1, char *p2, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (p1[i] != p2[i])
        {
            return p1[i] - p2[i];
        }
    }
    return 0;
}

void fill_null(char *str, int size)
{
    for (int i = 0; i < size; i++)
    {
        str[i] = '\0';
    }
}

char *my_scanf()
{
    int count = 1;
    int flag = 0;
    int memory_size = 2;
    int i = 0;
    char c;
    char *str = calloc(sizeof(char), memory_size + 1);
    while ((flag = read(0, &c, 1)))
    {
        count += flag;
        if (c == '\n')
        {
            str[i] = '\0';
            return str;
        }
        else if (count == memory_size)
        {
            memory_size *= 2;
            str = realloc(str, memory_size + 1);
        }
        str[i++] = c;
    }
    free(str);
    return my_strdup("stop");
}

int find_pieces(char *p1, char p2)
{
    int count = 0;
    for (int i = 0; p1[i]; i++)
    {
        if (p1[i] == p2)
        {
            count++;
        }
    }
    return count + 1;
}

int pieces_len(int start, char *str, char c)
{
    int count = 0;
    for (int i = start; str[i]; i++)
    {
        if (str[i] != c)
        {
            count++;
        }
    }
    return count;
}

void f_delete_space(char *p1)
{
    int i, j;
    int count = 0;
    int skip = 1;
    int len = my_strlen(p1);
    for (i = 0, j = 0; i < len; i++)
    {
        if (p1[i] == 32)
        {
            if (skip)
            {
                continue;
            }
            else
            {
                count++;
                if (count > 1)
                {
                    continue;
                }
            }
        }
        else
        {
            count = 0;
            skip = 0;
        }
        p1[j++] = p1[i];
    }
    if (j > 0 && p1[j - 1] == 32)
    {
        p1[j - 1] = '\0';
    }
    else
    {
        p1[j] = '\0';
    }
}

str_array *split(char *p1, char p2)
{
    str_array *arr = (str_array *)malloc(sizeof(str_array));
    int i = 0, j = 0, n = 0;
    f_delete_space(p1);
    int len = pieces_len(0, p1, p2);
    int length = my_strlen(p1);
    arr->count = find_pieces(p1, p2);
    arr->array = calloc(sizeof(char *), (arr->count + 1));
    arr->array[0] = calloc(sizeof(char), (len + 1));
    fill_null(arr->array[0], len + 1);
    while (i < arr->count)
    {
        while (j < length)
        {
            if (p1[j] == p2)
            {
                break;
            }
            arr->array[i][n] = p1[j];
            j++;
            n++;
        }
        i++;
        if (i < arr->count)
        {
            len = pieces_len(j, p1, p2);
            arr->array[i] = calloc(sizeof(char), (len + 1));
            fill_null(arr->array[i], len + 1);
            n = 0;
            j++;
        }
    }
    return arr;
}

void deallocate_str_array(str_array *s_array)
{
    for (int i = 0; i < s_array->count; i++)
    {
        free(s_array->array[i]);
    }
    free(s_array->array);
    free(s_array);
}