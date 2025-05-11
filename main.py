import random
file = 'input_arrays.txt'
with open(file, 'w') as f:
    pass

def generate_pattern(size):
    arr = []
    current_num = 1

    while len(arr) < size:
        arr.extend([current_num] * current_num)  # Add `current_num` repeated `current_num` times
        current_num += 1

    return arr[:size]

def construct_best_case_quick_sort(sorted_arr):
    if not sorted_arr:
        return []
    n = len(sorted_arr)
    mid = n // 2
    pivot = sorted_arr[mid]
    left = construct_best_case_quick_sort(sorted_arr[:mid])
    right = construct_best_case_quick_sort(sorted_arr[mid+1:])
    return [pivot] + left + right


def generate_worst_case_input_merge_sort(size):
    # Create a sorted list from 1 to size
    arr = list(range(1, size + 1))

    # Generate the alternating pattern (e.g., 2, 4, 6, 1, 3, 5)
    result = []
    left = 0
    right = size - 1
    while left <= right:
        if left <= right:
            result.append(arr[right])  # Take the largest element
            right -= 1
        if left <= right:
            result.append(arr[left])  # Take the smallest element
            left += 1

    return result


def ratio_array_with_majority(size, majority_element, majority_ratio):
    majority_count = int(size * majority_ratio)

    arr = [majority_element] * majority_count

    remaining_count = size - majority_count
    for _ in range(remaining_count):
        value = random.randint(0, 99)
        while value == majority_element:
            value = random.randint(0, 99)
        arr.append(value)

    return arr

def arr_with_majority(arr, size, majority_element):
    arr[:(size // 2) + 1] = [majority_element] * ((size // 2) + 1)

    for i in range((size // 2) + 1, size):
        arr[i] = random.randint(0, 99)
        while arr[i] == majority_element:
            arr[i] = random.randint(0, 99)


def generate(size):
    with open('input_arrays.txt', 'a') as f:
        arr = [random.randint(1, 100) for _ in range(size)]
        arr2 = [random.randint(1, 100) for _ in range(size)]
        print("size=", size, arr, file = f)  # worst brute force

        arr_with_majority(arr2, size, 7)
        print("size=", size, arr2, file = f)  # best brute force

        arr.sort(reverse=1)
        print("size=", size, arr, file = f)  # worst quick sort

        arr2.sort()
        print("size=", size, arr2, file = f)  # best quick sort, best merge sort

        worst_case_array = generate_worst_case_input_merge_sort(size)
        print("size=", size, worst_case_array, file = f)

        arr3 = list(range(1, size + 1))
        print("size=", size, arr3, file = f)  # quick sort worst, worst for divide and conquer

        arr = list(range(1, size + 1))
        new_arr = construct_best_case_quick_sort(arr)
        print("size=", size, new_arr, file = f)

        arr = [13] *size
        print("size=", size, arr, file = f)    #hashing worst

        majority = 7
        arr = [majority] * size
        print("size=", size, arr, file = f)  # best divide and conquer, also best for abbasov algorithm

        arr = generate_pattern(size)
        print("size=", size, arr, file = f)  # worst abbasov algorithm

        arr = ratio_array_with_majority(size, 7, 0.65)
        print("size=", size, arr, file = f)
        arr.sort()
        print("size=", size, arr, file = f)
        arr.sort(reverse=1)
        print("size=", size, arr, file = f)
        random.shuffle(arr)
        print("size=", size, arr, file = f)

        arr = ratio_array_with_majority(size, 7, ((size / 2) + 1) / size)
        random.shuffle(arr)
        print("size=", size, arr, file = f)

        arr = ratio_array_with_majority(size, 7, 0.65)
        print("size=", size, arr, file = f)
        arr.sort()
        print("size=", size, arr, file = f)
        arr.sort(reverse=1)
        print("size=", size, arr, file = f)
        random.shuffle(arr)
        print("size=", size, arr, file = f)

        arr = ratio_array_with_majority(size, 7, 0.75)
        print("size=", size, arr, file = f)
        arr.sort()
        print("size=", size, arr, file = f)
        arr.sort(reverse=1)
        print("size=", size, arr, file = f)
        random.shuffle(arr)
        print("size=", size, arr, file = f)

        arr = ratio_array_with_majority(size, 7, 0.90)
        print("size=", size, arr, file = f)
        arr.sort()
        print("size=", size, arr, file = f)
        arr.sort(reverse=1)
        print("size=", size, arr, file = f)
        random.shuffle(arr)
        print("size=", size, arr, file = f)

        arr = [random.randint(1, 100) for _ in range(size)]
        print("size=", size, arr, file = f)
        arr = [random.randint(1, 100) for _ in range(size)]
        print("size=", size, arr, file = f)
        arr = [random.randint(1, 100) for _ in range(size)]
        print("size=", size, arr, file = f)
        arr = [random.randint(1, 100) for _ in range(size)]
        print("size=", size, arr, file = f)
        arr = [random.randint(1, 100) for _ in range(size)]
        print("size=", size, arr, file = f)
        arr = [random.randint(1, 100) for _ in range(size)]
        print("size=", size, arr, file = f)
        arr = [random.randint(1, 100) for _ in range(size)]
        print("size=", size, arr, file = f)

sizes = [10,15,30,40,50]
for size in sizes:
    generate(size)