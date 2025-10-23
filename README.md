# C library : UTF-8

*C library for decoding **UTF-8** text*

&nbsp;

&nbsp;

# Description

This library allows you to encode/decode UTF-8 text into a byte sequence in Unicode.

Examples :

|Unicode | Binary Code Point                  | Bits | UTF-8 preparation
|:-------|:----------------------------------:|-----:|-------------------------------------------------------------------------------:
|U+00024 | 0000   0000   0000   00**10 0100** |    6 | 0**XXX   XXXX**
|U+000A3 | 0000   0000   0000   **1010 0011** |    8 | 110**X   XXXX** &nbsp; 10**XX XXXX**
|U+00418 | 0000   0000   0100   000**1 1000** |   11 | 1110   **XXXX** &nbsp; 10**XX XXXX** &nbsp; 10**XX XXXX**
|U+00939 | 0000   0000   **1001 0011   1001** |   12 | 1110   **XXXX** &nbsp; 10**XX XXXX** &nbsp; 10**XX XXXX**
|U+020AC | 0000   00**10 0000   1010   1100** |   14 | 1110   **XXXX** &nbsp; 10**XX XXXX** &nbsp; 10**XX XXXX**
|U+0D55C | 0000   **1101 0101   0101   1100** |   16 | 1110   **XXXX** &nbsp; 10**XX XXXX** &nbsp; 10**XX XXXX**
|U+10348 | 000**1 0000   0011   0100   1000** |   17 | 1111   0**XXX** &nbsp; 10**XX XXXX** &nbsp; 10**XX XXXX** &nbsp; 10**XX XXXX**

Finally :

|Unicode | UTF-8
|:-------|--------------------------------------------------------------------------------:
|U+00024 | 0**010   0010**
|U+000A3 | 110**0   0010** &nbsp; 10**10 0011**
|U+00418 | 1110   **0000** &nbsp; 10**01 0000** &nbsp; 10**01 1000**
|U+00939 | 1110   **0000** &nbsp; 10**10 0100** &nbsp; 10**11 1001**
|U+020AC | 1110   **0010** &nbsp; 10**00 0010** &nbsp; 10**10 1100**
|U+0D55C | 1110   **1101** &nbsp; 10**01 0101** &nbsp; 10**01 1100**
|U+10348 | 1111   0**000** &nbsp; 10**01 0000** &nbsp; 10**00 1101** &nbsp; 10**00 1000**

&nbsp;

&nbsp;


*Contact: https://github.com/iasebsil83*<br>

Let's Code ! &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;By I.A.
