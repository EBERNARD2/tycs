import csv
import datetime
import math
import time


class Payment(object):
    def __init__(self, time, dollars, cents):
        self.dollars = dollars
        self.cents = cents
        self.time = time
     



class User(object):
    def __init__(self, user_id, name, age, address_line, zipcode ,payments):
        self.user_id = user_id
        self.name = name
        self.age = age
        self.address_line = address_line
        self.zipcode = zipcode
        self.payments = payments


def average_age(users):
    total = 0
    for u in users.values():
        total += u.age
    return total / len(users)


def average_payment_amount(users):
    amount = 0
    count = 0
    for u in users.values():
        count += len(u.payments)
        for p in u.payments:
            amount += float(p.dollars) + float(p.cents) / 100
    return amount / count


def stddev_payment_amount(users):
    mean = average_payment_amount(users)
    squared_diffs = 0
    count = 0
    for u in users.values():
        count += len(u.payments)
        for p in u.payments:
            amount = float(p.dollars) + float(p.cents) / 100
            diff = amount - mean
            squared_diffs += diff * diff
    return math.sqrt(squared_diffs / count)


def load_data():
    users = {}
    data = {}
    with open('users.csv') as f:
        for line in csv.reader(f):
            uid, name, age, address_line, zip_code = line
            users[int(uid)] = User(int(uid), name, int(age), address_line, zip_code, [])
    with open('payments.csv') as f:
        for line in csv.reader(f):
            amount, timestamp, uid = line
            payment = Payment(
                dollars=int(amount)//100, 
                cents=int(amount) % 100,
                time=datetime.datetime.fromisoformat(timestamp))
            users[int(uid)].payments.append(payment)
    return users


if __name__ == '__main__':
    t = time.perf_counter()
    users = load_data()
    print(f'Data loading: {time.perf_counter() - t:.3f}s')
    t = time.perf_counter()
    assert abs(average_age(users) - 59.626) < 0.01
    assert abs(stddev_payment_amount(users) - 288684.849) < 0.01
    assert abs(average_payment_amount(users) - 499850.559) < 0.01
    print(f'Computation {time.perf_counter() - t:.3f}s')
