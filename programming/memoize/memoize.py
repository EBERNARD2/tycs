import urllib.request
import time



def mem(fn):
    if fn == None or not hasattr(fn, "__call__"):
        raise Exception("Must call mem with function")
    cache = {}

    def mem_function(param):
        if param in cache:
            print("using cache")
            return cache[param]
        else:
            val = fn(param)
            cache[param] = val
            return val
        
    return mem_function

@mem
def fetch(url):
    with urllib.request.urlopen(url) as response:
        content = response.read().decode('utf-8')
        return content

@mem
def fib(n):
    if n <= 1:
        return n
    return fib(n - 1) + fib(n - 2)





if __name__ == '__main__':
    print("first url test")
    fetch_url = mem(fetch)
    start = time.time()
    print(f"Start: {time}")
    fetch_url('http://google.com')
    end = time.time()
    print(f"{end - start} seconds")

    print("second utl test")
    start = time.time()
    fetch_url('http://google.com')
    end = time.time()
    print(f"{end - start} seconds")   

    print("first fib test")
    start = time.time()
    fib(40)
    end = time.time()
    print(f"{end - start} seconds")
    
    print("second fib test")
    start = time.time()
    fib_func = mem(fib)
    fib_func(40)
    end = time.time()
    print(f"{end - start} seconds")






