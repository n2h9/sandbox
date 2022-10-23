# License

Makefile is taken from 

https://github.com/PacktPublishing/Linux-Kernel-Programming/blob/master/ch5/modstacking/Makefile


# Usage

observe kernel logs
```sh
journalctl -f
```

build module
```sh
make
```

insert module
```sh
sudo insmod n2h9_foreach_proc.ko
```

remove module
```sh
sudo rmmod n2h9_foreach_proc
```
