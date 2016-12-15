def qsort(lst):
    if len(lst) <= 1:
        return lst
    pivot = lst[len(lst) / 2]
    left = [x for x in lst if x < pivot]
    middle = [x for x in lst if x == pivot]
    right = [x for x in lst if x > pivot]
    return qsort(left) + middle + qsort(right)

print qsort([1231, 1, 231, 123, 41])
