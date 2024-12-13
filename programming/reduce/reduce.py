"""
Implement the following functions, at least enough to get the tests to pass.

Try implementing each from scratch, but also once you've implement reduce, try implementing
them in terms of reduce!

As stretch goals:

    - Add more tests, and have them pass
    - Increase the flexibility of each function, e.g. enable my_map to operate over any iterable type
    - Implement more functions in terms of what you already have, e.g. "flatten", "unique", "group_by" etc. See https://lodash.com/docs/ for a long list of interesting utility functions.
"""


def reduce(f, xs, init=None):
    """
    Apply the function f cummulatively to the items of xs, reducing to a single value.

    If initializer is provided, use it as the first value. Otherwise, use only the
    values in xs.

    >>> reduce(lambda acc, x: acc + x, [1, 2, 3, 4])
    10
    >>> def mirror(d, x):
    ...     d[x] = x
    ...     return d
    >>> reduce(mirror, ['foo', 'bar'], {})
    {'foo': 'foo', 'bar': 'bar'}
    """
    pass


def product(nums):
    """
    Return the product of the given numbers

    >>> product([2, 3])
    6
    >>> product([-1.0, -1.0, -1.0])
    -1.0
    >>> product([])
    1
    """
    pass


def my_map(f, xs):
    """
    Return a new list, with the function f applied to each item in the given list

    >>> my_map(lambda x: x * x, [1, 2, 3, 4])
    [1, 4, 9, 16]
    """
    pass


def my_filter(f, xs):
    """
    Given a predicate function f (a function which returns True or False) and a list
    xs, return a new list with only the items of xs where f(x) is True

    >>> my_filter(lambda x: x > 0, [-1, 3, -2, 5])
    [3, 5]
    >>> my_filter(lambda x: False, [1, 2])
    []
    """
    pass


def my_zip(*iters):
    """
    Given one or more iterables of the same length, return a list of lists of them
    "zipped" together, ie grouped by index

    >>> my_zip('abc', 'def', (1, 2, 3))
    [['a', 'd', 1], ['b', 'e', 2], ['c', 'f', 3]]
    """
    pass


if __name__ == "__main__":
    import doctest
    doctest.testmod()
    print('ok')
