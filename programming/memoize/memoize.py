import urllib.request


def fetch(url):
    with urllib.request.urlopen(url) as response:
        content = response.read().decode('utf-8')
        return content


def fib(n):
    if n <= 1:
        return n
    return fib(n - 1) + fib(n - 2)


if __name__ == '__main__':
    print(fetch('http://google.com')[:80])
