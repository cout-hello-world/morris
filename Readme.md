# Morris
This program generates Morse tones to standard output in real time in raw PCM.
It attempts to be cross-platform, with no dependencies apart from the C++
standard library.

## Getting the source
You can either clone this repository with a command such as
```
git clone https://github.com/cout-hello-world/morris
```
or you can fetch a release tar ball from
```
https://github.com/cout-hello-world/morris/releases
```

## Compiling and installing
Compile with `make` and install by copying the `morris` executable wherever you
want.

## Usage
Run the executable and type. The tones will be sent to standard output
whenever the return key is pressed. The return key also signals a space
character in the output.

The following example shows how to output live sound on Linux using `aplay`
```
./morris | aplay -f S16_LE -c 1 -r 48 -
```

Note that `morris` outputs 16-bit signed samples in one channel at a 48 kHz
sampling rate.
