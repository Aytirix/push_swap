import os
import random
from colorama import Fore, Back, Style

def execute_command(command):
    return os.popen(command).read().strip()

def generate_unique_random_numbers(x):
    return ' '.join(str(num) for num in random.sample(range(1, x*10), x))

def apply_instruction(stack_a, stack_b, instruction):
    if instruction == 'sa':
        if len(stack_a) > 1:
            stack_a[0], stack_a[1] = stack_a[1], stack_a[0]
    elif instruction == 'sb':
        if len(stack_b) > 1:
            stack_b[0], stack_b[1] = stack_b[1], stack_b[0]
    elif instruction == 'ss':
        apply_instruction(stack_a, stack_b, 'sa')
        apply_instruction(stack_a, stack_b, 'sb')
    elif instruction == 'pa':
        if stack_b:
            stack_a.insert(0, stack_b.pop(0))
    elif instruction == 'pb':
        if stack_a:
            stack_b.insert(0, stack_a.pop(0))
    elif instruction == 'ra':
        if stack_a:
            stack_a.append(stack_a.pop(0))
    elif instruction == 'rb':
        if stack_b:
            stack_b.append(stack_b.pop(0))
    elif instruction == 'rr':
        apply_instruction(stack_a, stack_b, 'ra')
        apply_instruction(stack_a, stack_b, 'rb')
    elif instruction == 'rra':
        if stack_a:
            stack_a.insert(0, stack_a.pop())
    elif instruction == 'rrb':
        if stack_b:
            stack_b.insert(0, stack_b.pop())
    elif instruction == 'rrr':
        apply_instruction(stack_a, stack_b, 'rra')
        apply_instruction(stack_a, stack_b, 'rrb')

def is_sorted(stack):
    return all(stack[i] <= stack[i + 1] for i in range(len(stack) - 1))

def custom_checker(arg, instructions):
    stack_a = list(map(int, arg.split()))
    stack_b = []
    for instruction in instructions.split('\n'):
        if instruction:
            apply_instruction(stack_a, stack_b, instruction)
    return is_sorted(stack_a) and not stack_b

def test_push_swap(nb, iterations):
    results = []
    for _ in range(iterations):
        arg = generate_unique_random_numbers(nb)
        push_swap_result = execute_command(f'./push_swap {arg}')
        operation_count = len(push_swap_result.split('\n')) - 1  # Adjust if necessary
        checker_result = "OK" if custom_checker(arg, push_swap_result) else "KO"
        results.append((arg, operation_count, checker_result))
    return results

def main():
    os.system('clear')
    os.system('make')
    test_cases = [[3, 20], [5, 50], [100, 500], [500, 250]]

    for nb, iterations in test_cases:
        print(f"{Fore.BLUE}Testing with {nb} numbers, {iterations} iterations{Style.RESET_ALL}")
        results = test_push_swap(nb, iterations)

        total_operations = 0
        min_operations = float('inf')
        max_operations = 0
        checker_results = True
        
        for idx, (arg, operation_count, checker_result) in enumerate(results, 1):
            total_operations += operation_count
            if operation_count < min_operations:
                min_operations = operation_count
            if operation_count > max_operations:
                max_operations = operation_count
            if checker_result != "OK":
                checker_results = False
        
        avg_operations = total_operations / iterations
        print(f"Results for {nb} numbers with {iterations} iterations:")
        print(f"Min operations: {min_operations}")
        print(f"Max operations: {max_operations}")
        print(f"Avg operations: {avg_operations}")
        print(f"Checker results: {'OK' if checker_results else 'KO'}")
        print(f"{Fore.YELLOW}{'-'*50}{Style.RESET_ALL}")

if __name__ == "__main__":
    main()
