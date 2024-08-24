import csv
import datetime
import math
import time


# average age 

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
    mean = average_payment_amount
    squared_diffs = 0
    for u in users.values():
        for p in u:
            amount = float(p["dollars"]) + float(p["cents"]) / 100
            diff = amount - mean
            squared_diffs += diff * diff
    return math.sqrt(squared_diffs / user_count)    
   


def load_data():
    users = {}
    global age_total 
    age_total = 0
    global average_age 
    average_age = 0

    # average_payment_amount
    global average_payment_amount 
    average_payment_amount = 0
    global payments_in_total
    payments_in_total = 0
    global payment_count
    payment_count = 0
    global user_count
    user_count = 0

    with open('users.csv') as f:
        for line in csv.reader(f):
            uid, _, age, _, _ = line
            age_total += int(age)
            user_count += 1
            users[int(uid)] = [] 

    with open('payments.csv') as f:
        for line in csv.reader(f):
            amount, timestamp, uid = line
            payment = {}
            payment['dollars'] = int(amount)//100
            payment['cents'] = int(amount) % 100
            payment_count += 1
            payments_in_total += float(int(amount) // 100) + float(int(amount) % 100) / 100
            users[int(uid)].append(payment)

    average_payment_amount += payments_in_total / payment_count
    average_age += age_total / user_count
    return users


if __name__ == '__main__':
    t = time.perf_counter()
    users = load_data()
    print(f'Data loading: {time.perf_counter() - t:.3f}s')
    t = time.perf_counter()
    assert abs(average_age - 59.626) < 0.01
    stddev_payment_amount(users)
    # assert abs(stddev_payment_amount(users) - 288684.849) < 0.01
    assert abs(average_payment_amount - 499850.559) < 0.01
    print(f'Computation {time.perf_counter() - t:.3f}s')
