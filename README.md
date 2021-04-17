# Public-Key Cryptosystem

## Files
- wsu-pub-crypt.c                                  (Main Program)
- Miller_Expon.c                                   (Helper program for main program, it includes all math calc features)
- Miller_Expon.h                                   (Header file for  Miller_Expon.c program)
- ptext.txt, ctext.txt, prikey.txt, pubkey.txt     (All text files use for encrypt/decrypt, Test files)
- Makefile                                         (Makefile for program compilation)
- README.md                                        (Manual - Description use of the program )

## Compile Steps
- make all          (Will compile all nessacery file with error flags)
- make clean        (Will clean/remove the created files by the compilers)


## Run Instructions
./wsu-pub-crypt -genkey
./wsu-pub-crypt -e -k pubkey.txt -in ptext.txt -out ctext.txt
./wsu-pub-crypt -d -k prikey.txt -in ctext.txt -out dtxt.txt


## Author
### 👤 Yekaalo Habtemichael
* Github: [@ymikea](https://github.com/ymikea)
* Email: [@y.habtemichael](y.habtemichael@wsu.edu)


## Implementation
The program is an encryption algorithm that works using public/private key codes. The public is what we share with the world to recieve data contents. Private key should be secret, shouldn't be shared or no one else should know beside the owner. This system works by shareing public keys. 
    For example: If Alice and Bob want to share information in encrypted system. If Bob is sending message to Alice. Alice need to share her public key with Bob. Basically, Alice is sending an unlocked box with public to Bob, then Bob will put the message in and lock the box with the public key. When Alice recieved the box, she can unlock the box with her private key that bob locked with public key. 
 
 * Key Generation
    Generically the key can be generated from 32bits and above. For our program it will only work with 64bit max for now. When running program ./wsu-pub-crypt -genkey will generate the both keys private and public. The -genkey flag will let the program know to generate the keys. The private key will be stored in privateKey.txt file and the public key in publicKey.txt. How does it generates? First it picks random prime and odd number of n-bit. Thats what we called 'q', if the 'q' we find multiplied by 2 and added to one is also prime number, then we call 'q' a safe prime. So using 'p' that we found from 'q', we generate our private key in our case we called it 'd'. This 'd' can be pick randomly between 1 to p-2. To generate public key, calculate 2^d mod p, we called it e2. We used to as generator to mod p. If we find p and q right 2 gurantee to be primitive root. So we have all the keys we need to encrypt/decrypt.

* Encryption
    To encrypt, it uses the public key generated the encrypted text from the plain text (ptext.txt). If we look at the example about Alice and Bob. Here is where Bob sends Alice message using public key of Alice. To start encryption, started reading file every 32bit (4byte) each to gurantee the text we are reading is less than the prime 'p' we generated. If the bits we read is less than 32bits then we apply padding. To encrpty the text, we will randomly pick number between 1 to p-1, we called it 'kk'. For every text we generate new 'kk', this we will allow to mask for every the same text will have different encrpted value. We store all the encrypted values (in numbers) in ctext.txt file. 

* Decryption
    To decrypt, it uses the private key. Once Bob sent the message, Alice will use private key to decrypt it. Read ctext.txt encrypted file line by line and start decryption. The mathematical equation will decrypt the encrypted (magiclly ^). Once decrypted if it was padded, then we reverse it back. The decrpted value will be outputed in dtxt.txt file.


## License
[MIT](https://choosealicense.com/licenses/mit/) &copy; 2020 Yekaalo Habtemichael 
