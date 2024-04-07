#include "20192944.h"

int BUF_SIZE = 0;

int8_t *get_input()
{
    FILE *fp;
    int8_t *buffer = (int8_t *)malloc(MAX_BUF_SIZE);

    char filename[] = "input";

    fp = fopen(filename, "r");

    // Handle file exception
    if (fp == NULL)
    {
        printf("[*] Failed to read file..\n");
        return 1;
    }

    // Handle file exception
    if (fgets(buffer, MAX_BUF_SIZE, fp) == NULL)
    {
        printf("[*] Failed to read file..\n");
        return 1;
    }

    BUF_SIZE = strlen(buffer);
    printf("BUF SIZE: %d\n\n", BUF_SIZE);

    printf("[*] input: %s\n\n", buffer);

    // convert char -> numeric value
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        buffer[i] -= '0';
    }

    fclose(fp);

    return buffer;
}

void print_signed_char(int8_t *bit_arr)
{
    printf("[*] Signed char: ");
    // outer 'for' statement jump '8bytes'(== size of signed char)
    for (int i = 0; i < BUF_SIZE; i += 8)
    {
        // XOR operation with shifting bit-by-bit
        int8_t val = 0;
        for (int j = 0; j < 8; j++)
        {
            val |= (bit_arr[i + j] << (7 - j));
        }
        printf("%d ", val);
    }
    printf("\n");
}

void print_ASCII(int8_t *bit_arr)
{
    printf("[*] ASCII codes: ");
    for (int i = 0; i < BUF_SIZE; i += 8)
    {
        // Same as signed char(32bit)
        int8_t val = 0;
        for (int j = 0; j < 8; j++)
        {
            val |= (bit_arr[i + j] << (7 - j));
        }
        // ASCII val (33~126)
        if (val > ASCII_MAX | val < ASCII_MIN)
        {
            printf(". ");
        }
        else
        {
            printf("%c ", val);
        }
    }
    printf("\n");
}

void print_unsigned_char(int8_t *bit_arr)
{
    printf("[*] unsigned char: ");
    for (int i = 0; i < BUF_SIZE; i += 8)
    {
        // unsigned char == uint8_t (8bit)
        int8_t val = 0;
        for (int j = 0; j < 8; j++)
        {
            val |= (bit_arr[i + j] << (7 - j));
        }
        // print as unsigned value
        printf("%u ", val);
    }
    printf("\n");
}

void print_signed_int(int8_t *bit_arr)
{
    printf("[*] signed int: ");
    for (int i = 0; i < BUF_SIZE; i += 32)
    {
        // we need 4byte(32bit) value to print as signed int
        int32_t val = 0;
        for (int j = 0; j < 32; j++)
        {
            val |= ((int32_t)bit_arr[i + j] << (31 - j));
        }
        printf("%d ", val);
    }
    printf("\n");
}

void print_unsigned_int(int8_t *bit_arr)
{
    printf("[*] unsigned int: ");
    for (int i = 0; i < BUF_SIZE; i += 32)
    {
        // we need 4byte(32bit) value to print as unsigned int
        uint32_t val = 0;
        for (int j = 0; j < 32; j++)
        {
            val |= ((uint32_t)(uint8_t)bit_arr[i + j] << (31 - j));
        }
        // print as unsigned value
        printf("%u ", val);
    }
    printf("\n");
}

void print_float(int8_t *bit_arr)
{
    printf("[*] float: ");
    for (int i = 0; i < BUF_SIZE; i += 32)
    {
        // we need 4byte value to print float(4byte)
        int32_t val = 0;
        for (int j = 0; j < 32; j++)
        {
            // index of bit_arr is 1byte(8bit), so we need to make it 4byte(32bit) with casting
            val |= ((int32_t)bit_arr[i + j] << (31 - j));
        }
        // save data in bytes with memcpy
        float float_val;
        memcpy(&float_val, &val, sizeof(float));
        printf("%.4f ", float_val);
    }
    printf("\n");
}

void print_double(int8_t *bit_arr)
{
    printf("[*] double: ");
    for (int i = 0; i < BUF_SIZE; i += 64)
    {
        // we need 8byte value to print double(8byte)
        int64_t val = 0;
        for (int j = 0; j < 64; j++)
        {
            // index of bit_arr is 1byte(8bit), so we need to make it 8byte(64bit) with casting
            val |= ((int64_t)bit_arr[i + j] << (63 - j));
        }
        // save data in bytes with memcpy
        double double_val;
        memcpy(&double_val, &val, sizeof(double));
        printf("%.4lf ", double_val);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int8_t *bit_arr = get_input();

    print_signed_char(bit_arr);

    print_ASCII(bit_arr);

    print_unsigned_char(bit_arr);

    print_signed_int(bit_arr);

    print_unsigned_int(bit_arr);

    print_float(bit_arr);

    print_double(bit_arr);

    free(bit_arr);
    return 0;
}