import os
import random

def generate_unique_random_numbers(x):
    return ' '.join(str(num) for num in random.sample(range(1, x*10), x))

nb = 100
arg = generate_unique_random_numbers(nb)
push_swap_result = os.popen(f'./push_swap {arg}').read().strip()
print(len(push_swap_result.split('\n')))
result = os.popen(f'./push_swap {arg} | ./checker_linux {arg}').read().strip()
print(result)