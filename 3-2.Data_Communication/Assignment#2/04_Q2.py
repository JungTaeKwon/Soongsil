# 20192944_Data-Communication_Assignment#2_Ch04_Q2
def avg_numbers(*args):
    total = sum(args)
    return total / len(args)


print(avg_numbers(1, 2))
print(avg_numbers(1, 2, 3, 4, 5))
