# Six-Robotics-Vex-Bot
![](6ix.png)

# How to code good

## Docs & Code Quality
- Use doc-string comments on each function
```cpp
/**
* This is a doc string and should appear
* as a vibrant color in clion by default
*
* @param param_name what the param is for
* @returns what the function returns
**/
void foo();
```

- Use namespaces instead of classes unless classes make absolute sense. <br>
Generally the codebase is supposed to be more c-like than c++ by containing more functions<br>
than classes. This is **not** to say classes are outlawed. Instead use them where appropriate.

## Branches
- Dev: Commit WIP code here
- Master: Commit **ONLY** code which can be uploaded and used in comp here

## Writing commits
**NO ATOMIC COMMITS** If you have many changes, instead of commiting them all at once,
split the changes up into separate commits explaining the changes.
<br>

####Example:
```
Added vision sensor cube alignment.
```
This is simple, to the point, and starts with an UPPERCASE. 
Almost as if someone who passed elementary school wrote it.

####If you just have minor changes that fix many things:
```
Misc bug fixes.
```

<br><br><br><br><br>

# Project Setup

## Getting Clion Working:
- Use mingw
- This error message is ok: <b>c:/mingw/bin/../lib/gcc/mingw32/8.2.0/../../../../mingw32/bin/ld.exe: c:/mingw/bin/../lib/gcc/mingw32/8.2.0/../../../libmingw32.a(main.o):(.text.startup+0xb0): undefined reference to `WinMain@16'</b>
- Restart clion and refresh NOT rebuild cmake project



## PROS INSTALLATION
 ####DO NOT COMMIT PROS LIB FILES
