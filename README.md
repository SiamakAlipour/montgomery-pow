# Montgomery Modular Exponentiation

This repository contains an implementation of modular exponentiation using the **Montgomery reduction algorithm**.

## 🔍 What is Montgomery Exponentiation?

Montgomery exponentiation is a technique for performing modular exponentiation efficiently, especially with very large numbers — which is common in cryptography (e.g., RSA, Diffie-Hellman).

Instead of doing expensive divisions for each modular reduction, it uses a transformation into **Montgomery form** where modular multiplication can be performed **without costly division**.

## ⚙️ Why Montgomery?

Modular exponentiation using the naive method involves repeated multiplication followed by `% mod`, which includes **division**, and division is slow for large integers.

Montgomery reduction transforms numbers into a special form where modular operations can be done using only **additions, multiplications, and bit shifts** — much faster for big integers.

Benefits:
- 🚀 Faster modular multiplication for large numbers
- 🛡️ Ideal for cryptographic applications
- 💡 Especially effective when multiple modular multiplications are needed

## 📦 Requirements

- [GMP Library](https://gmplib.org/) (GNU Multiple Precision Arithmetic Library)

## 🚀 How to Build

```bash
g++ -o monty main.cpp -lgmpxx -lgmp
./monty

