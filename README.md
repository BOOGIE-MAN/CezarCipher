# CezarCipher

## About the project
Program allows user to either encrypt or automatically decode messages with Cezar Cipher.

### Language
 * c++14

### What is Cezar Cipher
The simplest way to encrypt text messages is with no doubt Cezar Cipher. Each character is shifted by some natural number called key i.e. a -> c with key = 2. If key is greater than the number of letters in alphabet, number is wrapped around with modulo operator: key = 27 will result in actual key = 1. 
In this program only lower-case letters are encrypted, every other character such as numbers or spaces are ommited.

### How auto decoding works?
The idea lies in calculating the frequency of each letter appearing in the string to be decoded(read from "secretMessage.txt") for each possible key value in range [0; 25]. Then compare that frequency to the average letter frequency specific to the English language and choose such key that the error is the smallest i.e. both frequencies are mostly similar. This solution is not perfect, thus some messages may not be properly decoded, however accuracy of this algorithm increases as string to be decoded gets longer.

## How to run it
It can be run through Visual Studio 2022 in any configuration or directly from the .exe file[BUT only if files "statisticsEn.txt" and "secretMessage.txt" are present in the same directory as .exe]

### Input restrictions
In encryption mode any string consisting of lower-case letter, spaces, commas, numbers etc. is considered valid. However ONLY lower-case letters can encrypted/decoded, rest is left as it is.
Program will only work with messages in English. The longer the message is the better programs key predictions are in automatic decoding mode.

## Idea
The project originally was written as a high-school project.
